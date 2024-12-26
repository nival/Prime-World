//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Sun, Aug 16, 2009 11:15:57 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows Vista Service Pack 1 (Build 6001)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 320 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 328 "Ratcatcher_rt_upArm_fk_ctrl_Align.align" 
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
		2 198 "null_stuffGRP.translateX" 1 61 "null_stuffGRP.translateY" 
		1 62 "null_stuffGRP.translateZ" 1 63 "null_stuffGRP.rotateX" 2 
		199 "null_stuffGRP.rotateY" 2 200 "null_stuffGRP.rotateZ" 2 201  ;
	setAttr ".cd[0].cim" -type "Int32Array" 328 0 1 2 3 4
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
		 317 318 319 320 321 322 323 324 325 326 327 ;
createNode animClip -n "moveSource1";
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
		yes yes yes yes yes yes yes yes yes yes yes no no no yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 24;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU65";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA197";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA198";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635176e-015 24 3.1805546814635176e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA199";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.9392333795734924e-017 24 9.9392333795734924e-017;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU66";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU67";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU68";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU69";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA200";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635168e-015 24 3.1805546814635168e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.7708320221952728e-015 24 4.7708320221952728e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU70";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 8 0 12 0 19 0 24 0;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU71";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 8 0 12 0 19 0 24 0;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL61";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.40930268174563 8 0.1266291149486829 
		12 0.069222986777820683 19 0.45618637529411021 24 0.40930268174563;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99975031614303589 1 1 1 0.99975031614303589;
	setAttr -s 5 ".kiy[0:4]"  0.022343836724758148 0 0 0 0.022343836724758148;
	setAttr -s 5 ".kox[0:4]"  0.99975031614303589 1 1 1 0.99975031614303589;
	setAttr -s 5 ".koy[0:4]"  0.022343836724758148 0 0 0 0.022343836724758148;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL62";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.057823715136270243 8 -0.12108970782452966 
		12 -0.14183923194759274 19 -0.049134833715399479 24 -0.057823715136270243;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL63";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.22451480617215203 8 -0.53885317730305105 
		12 -0.55883703878700131 19 -0.14947391479380856 24 -0.22451480617215203;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99498391151428223 1 1 0.76728755235671997 
		0.99498391151428223;
	setAttr -s 5 ".kiy[0:4]"  -0.10003558546304703 0 0 0.64130318164825439 
		-0.10003558546304703;
	setAttr -s 5 ".kox[0:4]"  0.99498391151428223 1 1 0.76728755235671997 
		0.99498391151428223;
	setAttr -s 5 ".koy[0:4]"  -0.10003558546304703 0 0 0.64130318164825439 
		-0.10003558546304703;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA204";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635168e-015 24 3.1805546814635168e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA205";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -7.9513867036587899e-016 24 -7.9513867036587899e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA206";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 21.459131300514464 8 16.605943421077143 
		12 16.605943421077143 18 10.217368655365346 24 21.459131300514464;
	setAttr -s 5 ".kit[3:4]"  10 3;
	setAttr -s 5 ".kot[3:4]"  10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA207";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.72089968334967991 8 -7.5398172157720449 
		12 -7.5398172157720449 18 -10.144163099623649 24 -0.72089968334967991;
	setAttr -s 5 ".kit[3:4]"  10 3;
	setAttr -s 5 ".kot[3:4]"  10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU72";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 3 6 3 12 3 24 3;
	setAttr -s 4 ".kit[0:3]"  1 10 10 10;
	setAttr -s 4 ".kot[0:3]"  1 10 10 10;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU73";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 0 12 0 24 0;
	setAttr -s 4 ".kit[0:3]"  1 10 10 10;
	setAttr -s 4 ".kot[0:3]"  1 10 10 10;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU74";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 6 1 12 1 24 1;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU75";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 0 12 0 24 0;
	setAttr -s 4 ".kit[0:3]"  1 10 10 10;
	setAttr -s 4 ".kot[0:3]"  1 10 10 10;
	setAttr -s 4 ".kix[0:3]"  1 1 1 1;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  1 1 1 1;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA208";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 95.027912018899102 6 93.539062770550316 
		12 95.383315301004515 18 95.513685222092874 24 95.027912018899102;
	setAttr -s 5 ".kit[0:4]"  1 10 9 9 9;
	setAttr -s 5 ".kot[0:4]"  1 10 9 9 9;
	setAttr -s 5 ".kix[0:4]"  0.99910265207290649 1 0.99630886316299438 
		0.99987983703613281 0.99910265207290649;
	setAttr -s 5 ".kiy[0:4]"  -0.042353671044111252 0 0.08584112673997879 
		-0.015505529940128326 -0.042353671044111252;
	setAttr -s 5 ".kox[0:4]"  0.99910265207290649 1 0.99630886316299438 
		0.99987983703613281 0.99910265207290649;
	setAttr -s 5 ".koy[0:4]"  -0.042353671044111252 0 0.08584112673997879 
		-0.015505529940128326 -0.042353671044111252;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA209";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 91.954078189911641 6 86.92248621129221 
		12 93.64044411946918 18 89.130564530671236 24 91.954078189911641;
	setAttr -s 5 ".kit[0:4]"  1 10 10 9 3;
	setAttr -s 5 ".kot[0:4]"  1 10 10 9 3;
	setAttr -s 5 ".kix[0:4]"  1 0.99730384349822998 0.99539077281951904 
		0.99730384349822998 1;
	setAttr -s 5 ".kiy[0:4]"  0 0.073383204638957977 0.095901504158973694 
		-0.073383204638957977 0;
	setAttr -s 5 ".kox[0:4]"  1 0.99730384349822998 0.99539077281951904 
		0.99730384349822998 1;
	setAttr -s 5 ".koy[0:4]"  0 0.073383204638957977 0.095901504158973694 
		-0.073383204638957977 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA210";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.3475119642090769 6 2.1736965574982299 
		12 4.5606038129591076 18 6.3404620405505296 24 7.3475119642090769;
	setAttr -s 5 ".kit[0:4]"  1 10 10 1 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 1 10;
	setAttr -s 5 ".kix[0:4]"  1 1 1 0.99920141696929932 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0.039956346154212952 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 0.99920141696929932 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0.039956346154212952 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.19751656702699438 3 0.29871070270008804 
		6 0.3475800171335407 9 0.34751345684521362 12 0.23448863198177339 15 0.31854835666602888 
		18 0.36573468597226833 21 0.29046561065939658 24 0.19751656702699438;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 9 9 9 9 9 9 9 
		3;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.18549442709713693 3 -0.18831327086961247 
		6 -0.16208891253059554 9 -0.15532748000810326 12 -0.17821096314762475 15 -0.1919116770517717 
		18 -0.17948470423115601 21 -0.18538140967301464 24 -0.18549442709713693;
	setAttr -s 9 ".kit[0:8]"  1 3 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kot[0:8]"  1 3 9 9 9 9 9 9 
		9;
	setAttr -s 9 ".kix[0:8]"  0.99999934434890747 1 0.98667055368423462 
		0.99676680564880371 0.98367846012115479 0.99997973442077637 0.99946743249893188 0.99954885244369507 
		0.99999934434890747;
	setAttr -s 9 ".kiy[0:8]"  -0.0011301732156425714 0 0.16273052990436554 
		-0.080349624156951904 -0.17993544042110443 -0.0063685760833323002 0.0326339490711689 
		-0.030035059899091721 -0.0011301732156425714;
	setAttr -s 9 ".kox[0:8]"  0.99999934434890747 1 0.98667055368423462 
		0.99676680564880371 0.98367846012115479 0.99997973442077637 0.99946743249893188 0.99954885244369507 
		0.99999934434890747;
	setAttr -s 9 ".koy[0:8]"  -0.0011301732156425714 0 0.16273052990436554 
		-0.080349624156951904 -0.17993544042110443 -0.0063685760833323002 0.0326339490711689 
		-0.030035059899091721 -0.0011301732156425714;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.26334592628767134 3 0.29720713540599641 
		6 0.34338278334414563 9 0.33517906923595353 12 0.2429854448792923 15 0.32954055514239977 
		18 0.36144084243144681 21 0.36335142353617211 24 0.26334592628767134;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 9 9 9 
		3;
	setAttr -s 9 ".kot[0:8]"  3 9 9 9 9 9 9 9 
		3;
createNode animCurveTU -n "animCurveTU76";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 21 0 24 0;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA211";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -9.2343529322129996 2 1.3939494861773341 
		5 2.1049147119501312 9 0.95317154037125262 16 -47.688610151764678 21 -35.275629831627803 
		24 -9.2343529322129996;
	setAttr -s 7 ".kit[1:6]"  3 10 10 3 1 10;
	setAttr -s 7 ".kot[1:6]"  3 10 10 3 1 10;
	setAttr -s 7 ".kix[5:6]"  0.45263832807540894 0.21487963199615479;
	setAttr -s 7 ".kiy[5:6]"  0.89169418811798096 0.97664058208465576;
	setAttr -s 7 ".kox[5:6]"  0.44829991459846497 0.21487963199615479;
	setAttr -s 7 ".koy[5:6]"  0.89388316869735718 0.97664058208465576;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA212";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -15.11110170915666 2 -21.097407490493634 
		5 -22.486604130264269 9 -18.951369824388426 16 -15.841591971397007 21 -8.2458376881622417 
		24 -15.11110170915666;
	setAttr -s 7 ".kit[1:6]"  9 10 10 10 3 10;
	setAttr -s 7 ".kot[1:6]"  9 10 10 10 3 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA213";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 18.196383878722202 2 11.366856285265159 
		5 7.5569882581250578 9 23.203154965304496 16 58.867079013078659 21 36.789955984241644 
		24 18.196383878722202;
	setAttr -s 7 ".kit[1:6]"  9 10 10 10 10 10;
	setAttr -s 7 ".kot[1:6]"  9 10 10 10 10 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU77";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 19 0 21 0 24 0;
	setAttr -s 5 ".kit[0:4]"  9 9 9 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU78";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 19 0 21 0 24 0;
	setAttr -s 5 ".kit[0:4]"  9 9 9 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU79";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 19 0 21 0 24 0;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU80";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 19 0 21 0 24 0;
	setAttr -s 5 ".kit[0:4]"  9 9 9 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA214";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 3.9531091186723013 7 -13.626913972284052 
		11 -14.95726523372595 15 -23.689546145255783 19 1.0004230652131565 21 9.2057560647238983 
		24 3.9531091186723013;
	setAttr -s 7 ".kit[1:6]"  1 1 3 10 10 1;
	setAttr -s 7 ".kot[1:6]"  1 1 3 10 10 1;
	setAttr -s 7 ".kix[1:6]"  0.69834357500076294 0.96418184041976929 
		1 0.32896390557289124 0.95537203550338745 0.60531854629516602;
	setAttr -s 7 ".kiy[1:6]"  -0.71576279401779175 -0.26524212956428528 
		0 0.94434243440628052 0.29540535807609558 -0.79598337411880493;
	setAttr -s 7 ".kox[1:6]"  0.69834357500076294 0.96418184041976929 
		1 0.32896390557289124 0.95537203550338745 0.60531854629516602;
	setAttr -s 7 ".koy[1:6]"  -0.71576279401779175 -0.26524209976196289 
		0 0.94434243440628052 0.29540535807609558 -0.79598337411880493;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA215";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.62018686761647346 7 -16.88999020677533 
		11 -8.6516808422924303 15 11.420533699135925 19 40.663264488489752 21 31.025692405764847 
		24 0.62018686761647346;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  0.60684502124786377;
	setAttr -s 7 ".kiy[6]"  -0.79482018947601318;
	setAttr -s 7 ".kox[6]"  0.60684502124786377;
	setAttr -s 7 ".koy[6]"  -0.79482018947601318;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA216";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 5.3292188742882338 7 -12.390360176189946 
		11 2.5384855386720244 15 13.177761621436977 19 8.4319074245084593 21 8.5028062447939892 
		24 5.3292188742882338;
	setAttr -s 7 ".kit[6]"  1;
	setAttr -s 7 ".kot[6]"  1;
	setAttr -s 7 ".kix[6]"  0.60228490829467773;
	setAttr -s 7 ".kiy[6]"  -0.79828125238418579;
	setAttr -s 7 ".kox[6]"  0.60228490829467773;
	setAttr -s 7 ".koy[6]"  -0.79828125238418579;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU81";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU82";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL69";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.1102230246251565e-016 24 -1.1102230246251565e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA217";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -19.513757781440109 4 17.647124332826355 
		9 -1.9327821473979894 17 -57.880900818362441 21 -51.07738924415311 24 -19.513757781440109;
	setAttr -s 6 ".kit[1:5]"  3 10 3 1 10;
	setAttr -s 6 ".kot[1:5]"  3 10 3 1 10;
	setAttr -s 6 ".kix[4:5]"  0.39925819635391235 0.17860591411590576;
	setAttr -s 6 ".kiy[4:5]"  0.91683858633041382 0.98392069339752197;
	setAttr -s 6 ".kox[4:5]"  0.38147377967834473 0.17860591411590576;
	setAttr -s 6 ".koy[4:5]"  0.92437964677810669 0.98392069339752197;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA218";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  4 0 15 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  4 0 15 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -11.226354836536574 11 -10.02711003493188 
		16 -4.8286472162956802 21 -15.497636630436423 24 -11.226354836536574;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA221";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.99923745724103941 5 -3.3913369990003561 
		11 -15.810254142055145 16 0.8784266099385063 21 -9.7055132810580851 24 -0.99923745724103941;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU83";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3 24 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU86";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU87";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA222";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA223";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA224";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL70";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.2204460492503131e-016 24 2.2204460492503131e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL72";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.4408920985006262e-016 24 4.4408920985006262e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU88";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 12 1 17 1 24 1;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA225";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.8674792585271232 5 -1.2574238070006207 
		12 -12.651341509624858 17 -21.742068756587592 24 -3.8674792585271232;
	setAttr -s 5 ".kit[1:4]"  3 9 3 9;
	setAttr -s 5 ".kot[1:4]"  3 9 3 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA226";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.134175752092313 5 11.595332580399456 
		12 17.038516552174194 17 14.982241136703291 24 12.134175752092313;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA227";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10.746835796865771 5 10.38849422706739 
		12 10.682707951774423 17 8.76529840862597 24 10.746835796865771;
	setAttr -s 5 ".kit[2:4]"  9 9 1;
	setAttr -s 5 ".kot[2:4]"  9 9 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU89";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA228";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 68.629003384766676 24 68.629003384766676;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA229";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 5.1251585428584878 24 5.1251585428584878;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.4794141658124507 24 -1.4794141658124507;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA231";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.9967431843380723 24 2.9967431843380723;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA232";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 27.356153209428296 24 27.356153209428296;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA233";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.8891453517792058 24 4.8891453517792058;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU90";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA234";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA235";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA236";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA237";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 61.945270723308987 24 61.945270723308987;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA238";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA239";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU91";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA241";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA242";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA243";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 61.945270723308987 24 61.945270723308987;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA244";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA245";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU92";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA246";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA247";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA248";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA249";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 72.878304588436421 24 72.878304588436421;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA250";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA251";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU93";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA252";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 77.67986202714836 24 77.67986202714836;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA253";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA254";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA255";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 65.952779168408995 24 65.952779168408995;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 12.091864976351665 24 12.091864976351665;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -6.5683373417752975 24 -6.5683373417752975;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -1.3702025198741257 6 0 8 1.1578657319170393 
		12 0 17 0 24 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 22.22655582994615 6 0 8 -9.1157511074389408 
		12 0 17 0 24 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 2.822023341375564 6 0 8 -0.25798525016657786 
		12 0 17 0 24 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU94";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 13.729997542293324 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 0.63874595844642235 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 6.1520328136917257 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 2.6646619917013665 13 1.9373926035036853 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA265";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 4.961351675227804 13 3.9566911421785878 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA266";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 8.8684278089956265 13 7.9229985932156008 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU95";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA267";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -17.642997232323477 13 9.1407201674254317 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA268";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.93848795149607789 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA269";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.92427193607252134 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA270";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -22.5760742608601 13 -4.1145899246833526 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA271";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -5.8309265890133206 13 -0.90543740643721604 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA272";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 2.4435995647855426 13 -1.1263561059675398 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU96";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA273";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -17.642997232323477 13 9.1407201674254317 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA274";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.93848795149607789 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA275";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.92427193607252134 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA276";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -6.8075220033640305 13 5.0415058561552222 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA277";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -12.016363506895738 13 -8.9238146958442357 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA278";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -1.2514024913402597 13 -1.2216349854939013 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA279";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -15.546441969357463 13 11.401709114863877 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA280";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -1.0263724082885994 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA281";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.86866692003361745 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA282";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -16.07758801342198 13 -0.61916420632540081 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA283";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -4.1900875643121465 13 6.5116984727812151 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA284";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -4.5469560145144108 13 -3.0802581235749198 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA285";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -5.6482082233636417 13 11.401709114863877 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA286";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 1.1803122184191976 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA287";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -7.3066417485869275 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA288";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -15.543934669382823 13 -0.29323023447363011 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA289";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -3.8872905273843954 13 8.3138486829487519 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA290";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 1.1402657424823999 13 -3.5854133604909983 
		24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA291";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 8 0 11 0 12 0 15 -28.935611844012797 
		17 0 20 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA292";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 8 0 11 0 12 0 15 0.7682761180006098 
		17 0 20 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA293";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 8 0 11 0 12 0 15 -2.681026809990688 
		17 0 20 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU99";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 8 0 12 0 17 0 20 0 23 0 24 
		0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 1 9 9 
		1;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		1;
	setAttr -s 9 ".kix[5:8]"  1 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU100";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 8 0 12 0 17 0 20 0 23 0 24 
		0;
	setAttr -s 9 ".kit[0:8]"  3 9 9 9 9 1 9 9 
		1;
	setAttr -s 9 ".kot[0:8]"  3 5 5 5 5 5 5 5 
		1;
	setAttr -s 9 ".kix[5:8]"  1 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU101";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 1 3 1 6 1 8 1 12 1 17 1 20 1 23 1 24 
		1;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 1 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 1 10 10 
		1;
	setAttr -s 9 ".kix[5:8]"  1 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0 0 0 0;
	setAttr -s 9 ".kox[5:8]"  1 1 1 1;
	setAttr -s 9 ".koy[5:8]"  0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA294";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.92590198521464373 3 0.92590198521464373 
		6 0.92590198521464373 8 15.229577257019759 12 35.327873057260085 17 -2.956924226026048 
		20 1.7284443702105792 23 1.0512994346753108 24 0.92590198521464373;
	setAttr -s 9 ".kit[1:8]"  10 10 10 3 3 3 10 1;
	setAttr -s 9 ".kot[1:8]"  10 10 10 3 3 3 10 1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  1;
	setAttr -s 9 ".koy[8]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA295";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 8 25.74872880722797 12 41.325562581368409 
		17 -8.2248102992440604 20 0.61798211287443394 23 0 24 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 1 1 10 
		1;
	setAttr -s 9 ".kix[5:8]"  0.11498091369867325 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  0.99336779117584229 0 0 0;
	setAttr -s 9 ".kox[5:8]"  0.11498091369867325 1 1 1;
	setAttr -s 9 ".koy[5:8]"  0.99336779117584229 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA296";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 33.528617897202352 6 88.192071497048218 
		8 117.99905930497518 12 119.95704556635344 17 23.014063627681658 20 -32.892085116060272 
		23 0 24 0;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 10 1 3 10 
		9;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 10 1 3 10 
		9;
	setAttr -s 9 ".kix[5:8]"  0.081218138337135315 1 1 1;
	setAttr -s 9 ".kiy[5:8]"  -0.99669629335403442 0 0 0;
	setAttr -s 9 ".kox[5:8]"  0.081218138337135315 1 1 1;
	setAttr -s 9 ".koy[5:8]"  -0.99669629335403442 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL73";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.25174406818772932 6 0.88562438051685899 
		9 1.3492214685625625 12 1.1038762275260849 17 0.3190849823399261 20 0.096214110365183514 
		23 0.0058586053064999533 24 0;
	setAttr -s 9 ".kit[2:8]"  10 10 10 1 1 10 1;
	setAttr -s 9 ".kot[2:8]"  10 10 10 1 1 10 1;
	setAttr -s 9 ".kix[0:8]"  1 0.21600891649723053 0.17928341031074524 
		0.67560678720474243 0.25060480833053589 0.19395223259925842 0.56299322843551636 1 
		1;
	setAttr -s 9 ".kiy[0:8]"  0 0.97639131546020508 0.98379743099212646 
		0.73726212978363037 -0.96808946132659912 -0.9810110330581665 -0.82646149396896362 
		0 0;
	setAttr -s 9 ".kox[0:8]"  1 0.21600891649723053 0.17928341031074524 
		0.67560678720474243 0.25060480833053589 0.19395223259925842 0.56299322843551636 1 
		1;
	setAttr -s 9 ".koy[0:8]"  0 0.97639131546020508 0.98379743099212646 
		0.73726212978363037 -0.96808946132659912 -0.9810110330581665 -0.82646149396896362 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL74";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.36869042509528277 3 0.4340236883059152 
		6 0.8170094863479247 9 0.58876636490708534 12 0.078254692248154289 17 -0.93496014798080607 
		20 -1.2639054256812567 23 -0.64463406345950247 24 -0.36869042509528277;
	setAttr -s 9 ".kit[0:8]"  1 1 3 10 10 9 3 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 1 3 10 10 9 3 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.13651072978973389 0.14379683136940002 
		1 0.26131880283355713 0.17238941788673401 0.19487552344799042 1 0.14731502532958984 
		0.13651072978973389;
	setAttr -s 9 ".kiy[0:8]"  0.9906386137008667 0.98960727453231812 
		0 -0.96525251865386963 -0.98502886295318604 -0.98082804679870605 0 0.98908966779708862 
		0.9906386137008667;
	setAttr -s 9 ".kox[0:8]"  0.13651072978973389 0.14379683136940002 
		1 0.26131880283355713 0.17238941788673401 0.19487552344799042 1 0.14731502532958984 
		0.13651072978973389;
	setAttr -s 9 ".koy[0:8]"  0.9906386137008667 0.98960727453231812 
		0 -0.96525251865386963 -0.98502886295318604 -0.98082804679870605 0 0.98908966779708862 
		0.9906386137008667;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL75";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.32507334843177282 3 0.33851885391234293 
		6 0.33914424808934462 9 0.36679148883723967 12 0.38101992288627168 17 0.3187765452866459 
		20 0.31548013640990213 23 0.32222536073868063 24 0.32507334843177282;
	setAttr -s 9 ".kit[0:8]"  1 10 10 9 10 1 10 10 
		9;
	setAttr -s 9 ".kot[0:8]"  1 10 10 9 10 1 10 10 
		9;
	setAttr -s 9 ".kix[0:8]"  0.9920840859413147 1 1 0.9787757396697998 
		1 0.99485069513320923 1 1 0.99636989831924438;
	setAttr -s 9 ".kiy[0:8]"  0.12557573616504669 0 0 0.20493446290493011 
		0 -0.1013520136475563 0 0 0.085129402577877045;
	setAttr -s 9 ".kox[0:8]"  0.9920840859413147 1 1 0.9787757396697998 
		1 0.99485069513320923 1 1 0.99636989831924438;
	setAttr -s 9 ".koy[0:8]"  0.1255757212638855 0 0 0.20493446290493011 
		0 -0.1013520136475563 0 0 0.085129402577877045;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA297";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA298";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA299";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU102";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA300";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA301";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA302";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA303";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA304";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA305";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA306";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA307";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA308";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU103";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 12 1 17 1 24 1;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA309";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.2739658544589174 5 -8.9016659371002209 
		12 -30.808951318343549 17 -12.181446842961105 24 4.2739658544589174;
	setAttr -s 5 ".kit[3:4]"  9 1;
	setAttr -s 5 ".kot[3:4]"  9 1;
	setAttr -s 5 ".kix[0:4]"  1 0.99692535400390625 1 0.54690629243850708 
		1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.07835736870765686 0 0.83719378709793091 
		0;
	setAttr -s 5 ".kox[0:4]"  1 0.99692535400390625 1 0.54690629243850708 
		1;
	setAttr -s 5 ".koy[0:4]"  0 -0.078357353806495667 0 0.83719378709793091 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA310";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -41.531258985004385 5 -47.845258727942557 
		12 -58.168748234626982 17 -79.511983413854594 24 -41.531258985004385;
	setAttr -s 5 ".kit[1:4]"  10 9 3 1;
	setAttr -s 5 ".kot[1:4]"  10 9 3 1;
	setAttr -s 5 ".kix[0:4]"  1 0.80924594402313232 0.58629554510116577 
		1 1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.58746999502182007 -0.81009721755981445 
		0 0;
	setAttr -s 5 ".kox[0:4]"  1 0.80924594402313232 0.58629554510116577 
		1 1;
	setAttr -s 5 ".koy[0:4]"  0 -0.58746999502182007 -0.81009721755981445 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA311";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 43.535238447847377 5 41.643808480848548 
		12 31.80096923199795 17 27.291181478928003 24 43.535238447847377;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU104";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 5 0 7 0 8 0 11 0 12 0 15 0 18 0 20 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  1 9 1 9 3 3 9 1 
		9 1;
	setAttr -s 10 ".kot[0:9]"  1 5 5 5 3 3 5 5 
		5 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 0 0 0 1 1 0 0 0 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU105";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 5 0 7 0 8 0 11 0 12 0 15 0 18 0 20 
		0 24 0;
	setAttr -s 10 ".kit[0:9]"  1 9 1 9 3 3 9 1 
		9 1;
	setAttr -s 10 ".kot[0:9]"  1 5 5 5 3 3 5 5 
		5 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 0 0 0 1 1 0 0 0 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU106";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 5 1 7 1 8 1 11 1 12 1 15 1 18 1 20 
		1 24 1;
	setAttr -s 10 ".kit[0:9]"  1 10 1 10 3 3 10 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 1 10 3 3 10 1 
		10 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 1 1 1 1 1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0 0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA312";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -2.5120182699055205 5 -1.5504551894040821 
		7 -10.244969948153551 8 -10.244969948153551 9 -8.5407385303094898 11 -5.0279179475818161 
		12 -5.5829613605362214 15 -5.5829613605362152 18 -5.5829613605362214 20 24.626167893495882 
		24 -2.5120182699055205;
	setAttr -s 11 ".kit[0:10]"  1 3 1 10 10 3 3 10 
		1 3 3;
	setAttr -s 11 ".kot[0:10]"  1 3 1 10 10 3 3 10 
		1 3 3;
	setAttr -s 11 ".kix[0:10]"  1 1 0.95690858364105225 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[0:10]"  0 0 -0.29038909077644348 0 0 0 0 0 0 0 
		0;
	setAttr -s 11 ".kox[0:10]"  1 1 0.95690858364105225 1 1 1 1 1 1 1 1;
	setAttr -s 11 ".koy[0:10]"  0 0 -0.29038909077644348 0 0 0 0 0 0 0 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA313";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.4434920278151244 5 -0.79211684677945338 
		7 1.6255054978159931 8 1.6255054978159931 9 1.1901586683330809 11 0.26325385903641024 
		12 0 15 0 18 0 20 29.301628467192298 24 -1.4434920278151244;
	setAttr -s 11 ".kit[1:10]"  3 1 10 10 3 3 10 1 
		1 1;
	setAttr -s 11 ".kot[1:10]"  3 1 10 10 3 3 10 1 
		1 1;
	setAttr -s 11 ".kix[0:10]"  0.85406249761581421 1 1 1 1 1 1 1 1 0.22051014006137848 
		0.85406249761581421;
	setAttr -s 11 ".kiy[0:10]"  -0.52017033100128174 0 0 0 0 0 0 0 0 0.97538465261459351 
		-0.52017033100128174;
	setAttr -s 11 ".kox[0:10]"  0.85406249761581421 1 1 1 1 1 1 1 1 0.22051014006137848 
		0.85406249761581421;
	setAttr -s 11 ".koy[0:10]"  -0.52017039060592651 0 0 0 0 0 0 0 0 0.97538465261459351 
		-0.52017039060592651;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA314";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 111.72754493272389 5 21.742682806609242 
		7 -28.799955684763198 8 -28.799955684763198 9 -5.3944955863388291 11 -0.11902331130774031 
		12 0 15 46.356911215564658 18 88.192071497048218 20 117.99905930497518 24 111.72754493272389;
	setAttr -s 11 ".kit[3:10]"  10 10 3 3 10 9 1 1;
	setAttr -s 11 ".kot[3:10]"  10 10 3 3 10 9 1 1;
	setAttr -s 11 ".kix[0:10]"  1 0.081218138337135315 0.46425449848175049 
		1 0.19589886069297791 1 1 0.12885095179080963 0.13212308287620544 0.58004611730575562 
		1;
	setAttr -s 11 ".kiy[0:10]"  0 -0.99669629335403442 -0.88570183515548706 
		0 0.98062413930892944 0 0 0.99166393280029297 0.99123334884643555 0.81458365917205811 
		0;
	setAttr -s 11 ".kox[0:10]"  1 0.081218138337135315 0.46425449848175049 
		1 0.19589886069297791 1 1 0.12885095179080963 0.13212308287620544 0.58004611730575562 
		1;
	setAttr -s 11 ".koy[0:10]"  0 -0.99669629335403442 -0.88570183515548706 
		0 0.98062413930892944 0 0 0.99166393280029297 0.99123334884643555 0.81458365917205811 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1.1038762275260849 5 0.3190849823399261 
		7 0.050176580627946943 8 0.012785533435193897 11 0.0065351534126827787 12 0 15 0.3409948909222863 
		18 0.81586127282138932 21 1.3492214685625625 24 1.1038762275260849;
	setAttr -s 10 ".kit[4:9]"  3 3 10 1 1 1;
	setAttr -s 10 ".kot[4:9]"  3 3 10 1 1 1;
	setAttr -s 10 ".kix[0:9]"  0.2796078622341156 0.19395223259925842 
		0.56299322843551636 0.9749375581741333 1 1 0.23809024691581726 0.2795386016368866 
		0.67560678720474243 0.2796078622341156;
	setAttr -s 10 ".kiy[0:9]"  -0.96011430025100708 -0.9810110330581665 
		-0.82646149396896362 -0.2224787175655365 0 0 0.97124302387237549 0.96013444662094116 
		0.73726212978363037 -0.96011430025100708;
	setAttr -s 10 ".kox[0:9]"  0.2796078622341156 0.19395223259925842 
		0.56299322843551636 0.9749375581741333 1 1 0.23809024691581726 0.2795386016368866 
		0.67560678720474243 0.2796078622341156;
	setAttr -s 10 ".koy[0:9]"  -0.96011430025100708 -0.9810110330581665 
		-0.82646149396896362 -0.22247874736785889 0 0 0.97124302387237549 0.96013444662094116 
		0.73726212978363037 -0.96011430025100708;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.078254692248154289 5 -0.93496014798080607 
		7 -1.4368538057560147 8 -1.3832923395066608 11 -0.63103669590606137 12 -0.35361170172989098 
		15 0.34671593512523591 18 0.73560321859646693 21 0.58876636490708534 24 0.078254692248154289;
	setAttr -s 10 ".kit[4:9]"  9 9 10 1 1 1;
	setAttr -s 10 ".kot[4:9]"  9 9 10 1 1 1;
	setAttr -s 10 ".kix[0:9]"  0.19317714869976044 0.19487552344799042 
		1 1 0.12841783463954926 0.13511660695075989 0.18059922754764557 1 0.26131880283355713 
		0.19317714869976044;
	setAttr -s 10 ".kiy[0:9]"  -0.98116385936737061 -0.98082804679870605 
		0 0 0.99172019958496094 0.9908297061920166 0.98355674743652344 0 -0.96525251865386963 
		-0.98116385936737061;
	setAttr -s 10 ".kox[0:9]"  0.19317714869976044 0.19487552344799042 
		1 1 0.12841783463954926 0.13511660695075989 0.18059922754764557 1 0.26131880283355713 
		0.19317714869976044;
	setAttr -s 10 ".koy[0:9]"  -0.98116385936737061 -0.98082804679870605 
		0 0 0.99172019958496094 0.9908297061920166 0.98355674743652344 0 -0.96525251865386963 
		-0.98116385936737061;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.3584706980247494 5 -0.32524016744648854 
		7 -0.32318219346466359 8 -0.32318219346466359 11 -0.29645476257826264 12 -0.28486618669920571 
		15 -0.28486618669920571 18 -0.29735003431097695 21 -0.31001235294600388 24 -0.3584706980247494;
	setAttr -s 10 ".kit[0:9]"  1 10 1 10 9 3 10 9 
		10 1;
	setAttr -s 10 ".kot[0:9]"  1 10 1 10 9 3 10 9 
		10 1;
	setAttr -s 10 ".kix[0:9]"  1 1 1 1 0.96110248565673828 1 1 0.99218833446502686 
		1 1;
	setAttr -s 10 ".kiy[0:9]"  0 0 0 0 0.2761920690536499 0 0 -0.12474867701530457 
		0 0;
	setAttr -s 10 ".kox[0:9]"  1 1 1 1 0.96110248565673828 1 1 0.99218833446502686 
		1 1;
	setAttr -s 10 ".koy[0:9]"  0 0 0 0 0.2761920690536499 0 0 -0.12474867701530457 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA315";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA316";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA317";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU107";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA318";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA319";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA320";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA321";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA322";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA323";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA324";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA325";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA326";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA327";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -29.311636586952385 5 -13.025278258882192 
		12 -24.53711599522936 17 -42.953935733671784 24 -29.311636586952385;
	setAttr -s 5 ".kit[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kot[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kix[0:4]"  0.41200023889541626 1 0.60798048973083496 
		1 0.41200023889541626;
	setAttr -s 5 ".kiy[0:4]"  0.91118377447128296 0 -0.79395204782485962 
		0 0.91118377447128296;
	setAttr -s 5 ".kox[0:4]"  0.41200023889541626 1 0.60798048973083496 
		1 0.41200023889541626;
	setAttr -s 5 ".koy[0:4]"  0.91118377447128296 0 -0.79395204782485962 
		0 0.91118377447128296;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA328";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.7546656733329762 5 -4.2371594989346901 
		12 -8.1654715053760238 17 -13.77593474704031 24 -5.7546656733329762;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 9;
	setAttr -s 5 ".kix[0:4]"  0.94282537698745728 0.99451291561126709 
		0.92322736978530884 0.99451291561126709 0.85749691724777222;
	setAttr -s 5 ".kiy[0:4]"  0.33328738808631897 -0.10461404919624329 
		-0.38425424695014954 0.10461404919624329 0.51448917388916016;
	setAttr -s 5 ".kox[0:4]"  0.9428253173828125 0.99451291561126709 
		0.92322736978530884 0.99451291561126709 0.85749691724777222;
	setAttr -s 5 ".koy[0:4]"  0.33328735828399658 -0.10461404919624329 
		-0.38425424695014954 0.10461404919624329 0.51448917388916016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA329";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 24.135668239007668 5 22.190293486204155 
		12 24.136754111877469 17 21.072980417302848 24 24.135668239007668;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  1 1 0.99881374835968018 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 4.7380141040775925e-005 -0.048694152384996414 
		-4.7380141040775925e-005 0;
	setAttr -s 5 ".kox[0:4]"  1 1 0.99881374835968018 1 1;
	setAttr -s 5 ".koy[0:4]"  0 4.7380141040775925e-005 -0.048694152384996414 
		-4.7380141040775925e-005 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA330";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -28.064725223295074 5 -38.633148253619417 
		12 -28.064725223295074 17 -13.546480404736556 21 -20.99378270830891 24 -28.064725223295074;
	setAttr -s 6 ".kit[3:5]"  1 10 9;
	setAttr -s 6 ".kot[3:5]"  1 10 9;
	setAttr -s 6 ".kix[3:5]"  1 0.67739212512969971 0.6295621395111084;
	setAttr -s 6 ".kiy[3:5]"  0 -0.73562216758728027 -0.7769501805305481;
	setAttr -s 6 ".kox[3:5]"  1 0.67739212512969971 0.6295621395111084;
	setAttr -s 6 ".koy[3:5]"  0 -0.73562216758728027 -0.7769501805305481;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA331";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.1722234572666252 5 -8.3233981649544031 
		12 8.1722234572666252 17 1.2885593448026365 21 -3.0738517406347574 24 8.1722234572666252;
	setAttr -s 6 ".kit[3:5]"  9 3 3;
	setAttr -s 6 ".kot[3:5]"  9 3 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA332";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 3.5236391014183068 5 5.9586233006698412 
		12 3.5236391014183068 17 16.285689375946131 21 8.52110857177051 24 3.5236391014183068;
	setAttr -s 6 ".kit[3:5]"  1 10 3;
	setAttr -s 6 ".kot[3:5]"  1 10 3;
	setAttr -s 6 ".kix[3:5]"  1 0.72333621978759766 1;
	setAttr -s 6 ".kiy[3:5]"  0 -0.69049608707427979 0;
	setAttr -s 6 ".kox[3:5]"  1 0.72333621978759766 1;
	setAttr -s 6 ".koy[3:5]"  0 -0.69049608707427979 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU108";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA333";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.011701251213865015 5 -0.4169474790072083 
		12 -0.98023146149616669 17 -0.4169474790072083 24 0.011476194518726878;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA334";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.6239866645927399 5 -0.70680717792549952 
		12 3.1249145630911239 17 -0.70680717792549952 24 -3.621145868974136;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 0.95901620388031006 1;
	setAttr -s 5 ".kiy[2:4]"  0 0.28335127234458923 0;
	setAttr -s 5 ".kox[2:4]"  1 0.95901620388031006 1;
	setAttr -s 5 ".koy[2:4]"  0 0.28335127234458923 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA335";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -11.528175235156185 24 -11.528175235156185;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU109";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 18 0 24 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA336";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 4 0.26765780220491242 7 9.0427303496385942 
		13 21.750782415578925 18 13.021440495481007 24 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 3 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 3 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA337";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 7 26.665584623237699 13 16.741206512732177 
		18 6.5618030339817643 24 0;
	setAttr -s 5 ".kit[2:4]"  10 10 3;
	setAttr -s 5 ".kot[2:4]"  10 10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA338";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 7 15.220742777486063 13 -5.3104763328442068 
		18 3.7994622487444314 24 0;
	setAttr -s 5 ".kit[3:4]"  10 3;
	setAttr -s 5 ".kot[3:4]"  10 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA339";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10.793181446349577 6 4.3074720942090678 
		12 4.9080510824661792 18 6.4815216497180153 24 10.793181446349577;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA340";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -11.069096393638221 6 -16.520236555909204 
		12 -17.425573702128485 18 -7.6126618227810043 24 -11.069096393638221;
	setAttr -s 5 ".kit[0:4]"  3 1 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.99585479497909546 1 0.96362322568893433 
		1;
	setAttr -s 5 ".kiy[1:4]"  -0.090957529842853546 0 0.26726442575454712 
		0;
	setAttr -s 5 ".kox[1:4]"  0.99585479497909546 1 0.96362322568893433 
		1;
	setAttr -s 5 ".koy[1:4]"  -0.090957529842853546 0 0.26726442575454712 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA341";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 46.971202074790767 6 36.18755492883863 
		12 21.675972247943367 18 26.943385274361837 24 46.971202074790767;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA342";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA343";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA344";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU110";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2 24 2;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU111";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA345";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -24.093441664171177 24 -24.093441664171177;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA346";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 49.48465546224881 24 49.48465546224881;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA347";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 58.801792680015588 24 58.801792680015588;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.2755255474500937 24 -1.2755255474500937;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.4392043230118035 24 -1.4392043230118035;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -2.1802956492995231 24 -2.1802956492995231;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA348";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.5234181098240844 7 1.1435997573817993 
		12 1.9770916181537193 17 6.9157021946676673 24 5.5234181098240844;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA349";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.3051662927822365 7 2.2166732505805404 
		12 10.375056716696976 17 5.2728092579838934 24 5.3051662927822365;
	setAttr -s 5 ".kit[2:4]"  10 10 9;
	setAttr -s 5 ".kot[2:4]"  10 10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA350";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.7971315161215564 7 -14.18927121487129 
		12 -25.109649193858807 17 4.6079003690305793 24 -5.7971315161215564;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 9;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 0.0094449017567307929 7 0.025933216454657081 
		17 0.084844636671492779 24 0;
	setAttr -s 5 ".kit[3:4]"  10 9;
	setAttr -s 5 ".kot[3:4]"  10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 4 -0.029396930599450352 7 -0.017465044875101043 
		17 0.062455812582672313 24 0;
	setAttr -s 5 ".kit[1:4]"  10 9 10 9;
	setAttr -s 5 ".kot[1:4]"  10 9 10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.073200132398645965 4 -0.054943965994824283 
		7 -0.075838075700927723 17 -0.065378090747560361 24 -0.073200132398645965;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 9;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 9;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA351";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU112";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 12 0 17 0 22 0 24 0;
	setAttr -s 6 ".kit[0:5]"  9 9 9 9 9 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA354";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.1107219305963252 5 -6.9202462639359652 
		12 -13.812809754224075 17 13.050114396647885 22 0.1454665251477886 24 -5.1107219305963252;
	setAttr -s 6 ".kit[5]"  1;
	setAttr -s 6 ".kot[5]"  1;
	setAttr -s 6 ".kix[5]"  0.80273735523223877;
	setAttr -s 6 ".kiy[5]"  0.59633272886276245;
	setAttr -s 6 ".kox[5]"  0.80273735523223877;
	setAttr -s 6 ".koy[5]"  0.59633272886276245;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA355";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.2811672786141717 5 18.126311648291551 
		12 13.949638710446296 17 7.4977957845155494 22 13.903336000752292 24 8.2811672786141717;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.98039668798446655;
	setAttr -s 6 ".kiy[5]"  -0.19703376293182373;
	setAttr -s 6 ".kox[5]"  0.98039668798446655;
	setAttr -s 6 ".koy[5]"  -0.19703376293182373;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA356";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.92645454014921158 5 5.2241867417761556 
		12 4.2689381701233664 17 2.9191521151535755 22 3.9032389512341754 24 -0.92645454014921158;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.70461183786392212;
	setAttr -s 6 ".kiy[5]"  -0.70959293842315674;
	setAttr -s 6 ".kox[5]"  0.70461183786392212;
	setAttr -s 6 ".koy[5]"  -0.70959293842315674;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.040515110247265507 5 -0.040515110247265507 
		12 -0.022944682016037984 17 -0.05070026780973292 22 -0.040515110247265507 24 -0.040515110247265507;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.041176417316286837 5 -0.041176417316286837 
		12 0.0053532923517711981 17 -0.057616174776636699 22 -0.041176417316286837 24 -0.041176417316286837;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.019976476006593587 5 0.019976476006593587 
		12 0.034122286956081493 17 0.018013831972907797 22 0.019976476006593587 24 0.019976476006593587;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.2399711943881462 6 5.8368103675692984 
		8 5.5371717889404417 12 13.701656763438768 18 -1.6578600985338485 20 -0.46947470793843232 
		24 -1.2399711943881462;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  1 1 1 0.93579554557800293 1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 -0.3525431752204895 0 0 0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 0.93579554557800293 1 1 1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 -0.3525431752204895 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -35.889138953044828 6 11.597858154803525 
		8 9.0436710387620245 12 -40.209706605817473 18 -9.3361108539774662 20 -3.5784081713286326 
		24 -35.889138953044828;
	setAttr -s 7 ".kit[0:6]"  1 10 10 3 10 10 3;
	setAttr -s 7 ".kot[0:6]"  1 10 10 3 10 10 3;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.38495531678199768 0.3962341845035553 
		1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.92293524742126465 -0.91814947128295898 
		0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.38495531678199768 0.3962341845035553 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.92293524742126465 -0.91814947128295898 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.5262114410899876 6 -23.5686128677299 
		8 -18.506208401779851 12 -0.7051828133608361 18 7.2421368171988538 20 4.8552604379823228 
		24 -3.5262114410899876;
	setAttr -s 7 ".kit[0:6]"  1 10 10 1 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.67363381385803223 0.71405631303787231 
		0.44807177782058716 0.70692986249923706 1 1 0.67363381385803223;
	setAttr -s 7 ".kiy[0:6]"  -0.73906528949737549 -0.7000882625579834 
		0.89399755001068115 0.70728373527526855 0 0 -0.73906528949737549;
	setAttr -s 7 ".kox[0:6]"  0.67363381385803223 0.71405631303787231 
		0.44807177782058716 0.70692980289459229 1 1 0.67363381385803223;
	setAttr -s 7 ".koy[0:6]"  -0.73906528949737549 -0.7000882625579834 
		0.89399755001068115 0.70728373527526855 0 0 -0.73906528949737549;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.0065040660698765188 6 0.13049271151826225 
		8 0.098677408176553433 12 0.0012548238460522562 18 0.064931251763181597 24 0.0065040660698765188;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.95987880229949951 1 1 0.99491441249847412 
		0.99991393089294434 0.95987880229949951;
	setAttr -s 6 ".kiy[0:5]"  -0.28041508793830872 0 0 -0.10072360932826996 
		0.013121975585818291 -0.28041508793830872;
	setAttr -s 6 ".kox[0:5]"  0.95987886190414429 1 1 0.99491441249847412 
		0.99991393089294434 0.95987886190414429;
	setAttr -s 6 ".koy[0:5]"  -0.2804151177406311 0 0 -0.10072360932826996 
		0.013121975585818291 -0.2804151177406311;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.0036428165940923392 6 0.069078341976550897 
		8 0.023615561477805441 12 -0.056967529699048947 18 -0.086535726212453826 24 0.0036428165940923392;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.91161668300628662 1 1 1 1 0.91161668300628662;
	setAttr -s 6 ".kiy[0:5]"  0.41104134917259216 0 0 0 0 0.41104134917259216;
	setAttr -s 6 ".kox[0:5]"  0.9116167426109314 1 1 1 1 0.9116167426109314;
	setAttr -s 6 ".koy[0:5]"  0.41104137897491455 0 0 0 0 0.41104137897491455;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.023792189127942898 6 0.11762735648074187 
		8 0.10375752814533244 12 0.01199586266937569 18 0.03000771434745025 24 -0.023792189127942898;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 10;
	setAttr -s 6 ".kix[0:5]"  0.96567171812057495 1 1 1 1 0.96567171812057495;
	setAttr -s 6 ".kiy[0:5]"  -0.25976526737213135 0 0 0 0 -0.25976526737213135;
	setAttr -s 6 ".kox[0:5]"  0.96567177772521973 1 1 1 1 0.96567177772521973;
	setAttr -s 6 ".koy[0:5]"  -0.25976529717445374 0 0 0 0 -0.25976529717445374;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA360";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA361";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA362";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA363";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.4820313138629455 3 0 8 3.973829032660805 
		12 5.701252073195783 15 0.61058816797814186 20 -3.8073012458519133 24 -3.4820313138629455;
	setAttr -s 7 ".kit[1:6]"  10 9 1 9 1 1;
	setAttr -s 7 ".kot[1:6]"  10 9 1 9 1 1;
	setAttr -s 7 ".kix[0:6]"  0.99019926786422729 0.8987046480178833 
		0.94915151596069336 1 0.84901422262191772 1 1;
	setAttr -s 7 ".kiy[0:6]"  0.13966159522533417 0.43855428695678711 
		0.31481969356536865 0 -0.52836990356445313 0 0;
	setAttr -s 7 ".kox[0:6]"  0.99019932746887207 0.8987046480178833 
		0.94915151596069336 1 0.84901422262191772 1 1;
	setAttr -s 7 ".koy[0:6]"  0.13966159522533417 0.43855428695678711 
		0.31481969356536865 0 -0.52836990356445313 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA364";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.2721832506814086 3 2.8239406809914485 
		8 5.1361197322684191 12 5.3282937037191127 15 6.9299179407933664 20 3.2886565526625673 
		24 1.2721832506814086;
	setAttr -s 7 ".kit[1:6]"  9 10 1 1 9 1;
	setAttr -s 7 ".kot[1:6]"  9 10 1 1 9 1;
	setAttr -s 7 ".kix[0:6]"  1 0.9694787859916687 1 1 1 0.94986754655838013 
		1;
	setAttr -s 7 ".kiy[0:6]"  0 0.24517540633678436 0 0 0 -0.31265237927436829 
		0;
	setAttr -s 7 ".kox[0:6]"  1 0.9694787859916687 1 1 1 0.94986754655838013 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0.24517540633678436 0 0 0 -0.31265237927436829 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA365";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 13.092921420682925 3 13.014389236491775 
		8 13.014389236491779 12 12.778206574749898 15 13.000304969547667 20 13.062382957861395 
		24 13.092921420682925;
	setAttr -s 7 ".kit[1:6]"  10 10 1 1 9 1;
	setAttr -s 7 ".kot[1:6]"  10 10 1 1 9 1;
	setAttr -s 7 ".kix[0:6]"  1 1 1 1 0.99991190433502197 0.9999854564666748 
		1;
	setAttr -s 7 ".kiy[0:6]"  0 0 0 0 0.013274434022605419 0.0053881281055510044 
		0;
	setAttr -s 7 ".kox[0:6]"  1 1 1 1 0.99991190433502197 0.9999854564666748 
		1;
	setAttr -s 7 ".koy[0:6]"  0 0 0 0 0.013274434953927994 0.0053881281055510044 
		0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL103";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.189 3 -0.11906859038629385 8 -0.046863885247281356 
		12 -0.18883902961318086 15 -0.11906859038629385 20 -0.046863885247281356 24 -0.189;
	setAttr -s 7 ".kit[1:6]"  9 3 1 9 3 1;
	setAttr -s 7 ".kot[1:6]"  9 3 1 9 3 1;
	setAttr -s 7 ".kix[0:6]"  1 0.88247132301330566 1 1 0.88269227743148804 
		1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0.47036638855934143 0 0 0.469951331615448 
		0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.88247132301330566 1 1 0.88269227743148804 
		1 1;
	setAttr -s 7 ".koy[0:6]"  0 0.47036638855934143 0 0 0.469951331615448 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL104";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.27905490988822479 3 -0.36053982586405164 
		8 -0.37220182488301928 12 -0.27905490988822479 15 -0.36053982586405164 20 -0.37220182488301928 
		24 -0.27905490988822479;
	setAttr -s 7 ".kit[2:6]"  10 1 1 1 1;
	setAttr -s 7 ".kot[2:6]"  10 1 1 1 1;
	setAttr -s 7 ".kix[0:6]"  1 0.99235612154006958 1 1 0.99434667825698853 
		1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.12340760231018066 0 0 -0.10618297010660172 
		0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.99235612154006958 1 1 0.99434667825698853 
		1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.12340763211250305 0 0 -0.10618294030427933 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL105";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.0035205622938596082 3 0.044961537715242215 
		8 0.051900223188162953 12 -0.0035205622938596082 15 0.044961537715242215 20 0.064587598399117707 
		24 -0.0035205622938596082;
	setAttr -s 7 ".kit[2:6]"  10 1 1 1 1;
	setAttr -s 7 ".kot[2:6]"  10 1 1 1 1;
	setAttr -s 7 ".kix[0:6]"  1 0.99550813436508179 1 1 0.98023557662963867 
		1 1;
	setAttr -s 7 ".kiy[0:6]"  0 0.09467586874961853 0 0 0.19783385097980499 
		0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.99550813436508179 1 1 0.98023563623428345 
		1 1;
	setAttr -s 7 ".koy[0:6]"  0 0.094675876200199127 0 0 0.19783391058444977 
		0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU113";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 5 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 0 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU114";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155571970393403 5 0.084155571970393403 
		12 0.084155571970393403 17 0.084155571970393403 24 0.084155571970393403;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL106";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL107";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.8360926868100278 5 -0.8360926868100278 
		12 -0.8360926868100278 17 -0.8360926868100278 24 -0.8360926868100278;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL108";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.7755575615628914e-017 5 0 12 0.074641244574413013 
		17 0 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU115";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[1:4]"  9 1 1 1;
	setAttr -s 5 ".kot[1:4]"  5 1 5 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 0 1 0 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU116";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.084155864375844894 5 0.084155864375844894 
		12 0.084155864375844894 17 0.084155864375844894 24 0.084155864375844894;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL109";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 5 0 12 0 17 0 24 0;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL110";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.8360926868100278 5 -0.8360926868100278 
		12 -0.8360926868100278 17 -0.8360926868100278 24 -0.8360926868100278;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL111";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.073926484418881333 5 0.024636370844023869 
		12 -0.091704596971160457 17 0.024636370844023869 24 -0.073926484418881333;
	setAttr -s 5 ".kit[1:4]"  10 1 1 1;
	setAttr -s 5 ".kot[1:4]"  10 1 1 1;
	setAttr -s 5 ".kix[0:4]"  1 0.99901378154754639 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.044401448220014572 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 0.99901378154754639 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 -0.044401448220014572 0 0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU117";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 10 1 16 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU118";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 10 1 16 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 10 1 16 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 -38.226730619495115 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 -7.9980081629911783 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 -4.5177916955893025 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL112";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL113";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL114";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 10 0 16 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU120";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU121";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU122";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA369";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 7.9924045306876481 24 7.9924045306876481;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  0.98513615131378174 1;
	setAttr -s 2 ".kiy[0:1]"  0.1717754602432251 0;
	setAttr -s 2 ".kox[0:1]"  0.98513615131378174 1;
	setAttr -s 2 ".koy[0:1]"  0.1717754602432251 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA370";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.22015986178417388 24 0.22015986178417388;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA371";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.4625123467392502 24 1.4625123467392502;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL115";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL116";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL117";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA372";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA381";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.592620239620459 4 -4.4209227778213602 
		12 -20.167976720124045 17 -5.8884832657047408 24 -18.592620239620459;
	setAttr -s 5 ".kit[0:4]"  1 10 3 10 3;
	setAttr -s 5 ".kot[0:4]"  1 10 3 10 3;
	setAttr -s 5 ".kix[0:4]"  1 0.99764591455459595 1 0.99764591455459595 
		1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.068576082587242126 0 0.068576082587242126 
		0;
	setAttr -s 5 ".kox[0:4]"  1 0.99764591455459595 1 0.99764591455459595 
		1;
	setAttr -s 5 ".koy[0:4]"  0 -0.068576082587242126 0 0.068576082587242126 
		0;
createNode animCurveTA -n "animCurveTA382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -4.0495369920864128 4 -26.860185241629672 
		12 -15.501722092690782 17 -8.920840200738823 24 -4.0495369920864128;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  1 0.89453601837158203 0.81055706739425659 
		0.89453601837158203 1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.44699591398239136 0.58565980195999146 
		0.44699591398239136 0;
	setAttr -s 5 ".kox[0:4]"  1 0.89453601837158203 0.81055706739425659 
		0.89453601837158203 1;
	setAttr -s 5 ".koy[0:4]"  0 -0.44699591398239136 0.58565980195999146 
		0.44699591398239136 0;
createNode animCurveTA -n "animCurveTA383";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -24.718935474963271 4 -30.785736808055759 
		12 -15.98049941147139 17 -40.030838516498854 24 -24.718935474963271;
	setAttr -s 5 ".kit[0:4]"  1 3 3 3 3;
	setAttr -s 5 ".kot[0:4]"  1 3 3 3 3;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA384";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA385";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA386";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA389";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 7.2644697342894906;
	setAttr ".kix[0]"  0.8445855975151062;
	setAttr ".kiy[0]"  0.53542047739028931;
	setAttr ".kox[0]"  0.84458565711975098;
	setAttr ".koy[0]"  0.53542053699493408;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL118";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL119";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL120";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.094586622247542 6 11.467648808165523 
		12 20.533875194298972 18 1.6670937744970662 24 5.094586622247542;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.95806193351745605 0.82936137914657593 
		0.91945821046829224 0.82936137914657593 0.95806193351745605;
	setAttr -s 5 ".kiy[0:4]"  0.28656131029129028 0.55871260166168213 
		-0.39318779110908508 -0.55871260166168213 0.28656131029129028;
	setAttr -s 5 ".kox[0:4]"  0.95806193351745605 0.82936137914657593 
		0.91945821046829224 0.82936137914657593 0.95806193351745605;
	setAttr -s 5 ".koy[0:4]"  0.28656131029129028 0.55871260166168213 
		-0.39318779110908508 -0.55871260166168213 0.28656131029129028;
createNode animCurveTA -n "animCurveTA391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.33056286880704516 6 10.422660991577057 
		12 -0.23238785415017568 18 -14.645646054709939 24 0.33056286880704516;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.60767632722854614 0.99969851970672607 
		0.67474865913391113 0.99969851970672607 0.60767632722854614;
	setAttr -s 5 ".kiy[0:4]"  0.79418486356735229 -0.024555953219532967 
		-0.73804759979248047 0.024555953219532967 0.79418486356735229;
	setAttr -s 5 ".kox[0:4]"  0.60767632722854614 0.99969851970672607 
		0.67474865913391113 0.99969851970672607 0.60767632722854614;
	setAttr -s 5 ".koy[0:4]"  0.79418486356735229 -0.024555953219532967 
		-0.73804759979248047 0.024555953219532967 0.79418486356735229;
createNode animCurveTA -n "animCurveTA392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 19.754064187382461 6 23.010877811645376 
		12 14.805173534649233 18 7.2581997050712603 24 19.754064187382461;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.67587250471115112 0.9774707555770874 
		0.82410341501235962 0.9774707555770874 0.67587250471115112;
	setAttr -s 5 ".kiy[0:4]"  0.7370186448097229 -0.2110712081193924 
		-0.56643939018249512 0.2110712081193924 0.7370186448097229;
	setAttr -s 5 ".kox[0:4]"  0.67587250471115112 0.9774707555770874 
		0.82410341501235962 0.9774707555770874 0.67587250471115112;
	setAttr -s 5 ".koy[0:4]"  0.7370186448097229 -0.2110712081193924 
		-0.56643939018249512 0.2110712081193924 0.7370186448097229;
createNode animCurveTU -n "animCurveTU123";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode animCurveTU -n "animCurveTU124";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode animCurveTU -n "animCurveTU125";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode animCurveTU -n "animCurveTU126";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode animCurveTU -n "animCurveTU127";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode animCurveTU -n "animCurveTU128";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 1;
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
	setAttr -s 24 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
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
select -ne :initialMaterialInfo;
select -ne :defaultResolution;
	setAttr ".pa" 1;
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
connectAttr "moveSource1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU65.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA197.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA198.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA199.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU66.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU67.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU68.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU69.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA200.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA201.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA202.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU70.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU71.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL61.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL62.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL63.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA203.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA204.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA205.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA206.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA207.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU72.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU73.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU74.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU75.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA208.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA209.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA210.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU76.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA211.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA212.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA213.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU77.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU78.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU79.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU80.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA214.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA215.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA216.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU81.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU82.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA217.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA218.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA219.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA220.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA221.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU83.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU84.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU85.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU86.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU87.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA222.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA223.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA224.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU88.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA225.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA226.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA227.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU89.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA228.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA229.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA230.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA231.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA232.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA233.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU90.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA234.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA235.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA236.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA237.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA238.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA239.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU91.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA240.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA241.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA242.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA243.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA244.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA245.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU92.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA246.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA247.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA248.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA249.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA250.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA251.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU93.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA252.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA253.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA254.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA255.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU94.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA264.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA265.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA266.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU95.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA267.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA268.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA269.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA270.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA271.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA272.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU96.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA273.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA274.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA275.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA276.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA277.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA278.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU97.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA279.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA280.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA281.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA282.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA283.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA284.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU98.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA285.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA286.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA287.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA288.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA289.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA290.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA291.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA292.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA293.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU99.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU100.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU101.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA294.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA295.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA296.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL73.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL74.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL75.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA297.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA298.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA299.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU102.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA300.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA301.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA302.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA303.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA304.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA305.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA306.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA307.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA308.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU103.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA309.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA310.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA311.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU104.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU105.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU106.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA312.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA313.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA314.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL76.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA315.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA316.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA317.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU107.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA318.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA319.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA320.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA321.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA322.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA323.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA324.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA325.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA326.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA327.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA328.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA329.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA330.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA331.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA332.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU108.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA333.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA334.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA335.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU109.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA336.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA337.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA338.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA339.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA340.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA341.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA342.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA343.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA344.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU110.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU111.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA345.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA346.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA347.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL82.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL83.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL84.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL85.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL86.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL87.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA348.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA349.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA350.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL88.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL89.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL90.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA351.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA352.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA353.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU112.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA354.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA355.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA356.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA357.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA358.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA359.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL97.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL98.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA360.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA361.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA362.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL100.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL101.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA363.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA364.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA365.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTL103.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTL104.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTL105.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTU113.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTU114.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTL106.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTL107.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTL108.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTU115.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU116.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL109.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL110.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL111.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTU117.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTU118.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTU119.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA366.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA367.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA368.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL112.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL113.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTL114.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU120.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU121.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU122.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA369.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA370.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA371.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL115.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTL116.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTL117.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA372.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA373.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA374.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTA375.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTA376.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTA377.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTA378.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA379.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA380.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA381.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA382.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA383.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTA384.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTA385.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA386.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA387.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA388.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA389.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL118.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL119.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL120.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTA390.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTA391.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTA392.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU123.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU124.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU125.a" "clipLibrary1.cel[0].cev[316].cevr";
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
// End of move.ma
