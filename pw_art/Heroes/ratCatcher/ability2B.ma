//Maya ASCII 2008 scene
//Name: ability02.ma
//Last modified: Sun, Aug 16, 2009 10:49:48 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows Vista Service Pack 1 (Build 6001)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 321 ".cel[0].cev";
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
createNode animClip -n "ability2Source1";
	setAttr ".ihi" 0;
	setAttr -s 321 ".ac";
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
		yes yes yes yes yes yes yes yes yes no no no yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[321]" yes;
	setAttr ".se" 30;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU65";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA198";
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
createNode animCurveTA -n "animCurveTA199";
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
createNode animCurveTA -n "animCurveTA200";
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
createNode animCurveTU -n "animCurveTU66";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU67";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU68";
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
createNode animCurveTU -n "animCurveTU69";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 28 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 9 1 1 9 1;
	setAttr -s 6 ".kot[0:5]"  3 5 1 1 5 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 0 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA201";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 -61.403500377965969 2 -137.99901841819744 
		4 -252.84049563335682 17 -252.80391640482625 21 -252.78238481744347 25 -252.84049563335682 
		26 -187.47357474525086 27 -309.42472191649165 28 -224.17206001577603 30 3.1805546814635168e-015;
	setAttr -s 11 ".kit[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 0.067351721227169037 0.10352456569671631 
		0.018513703718781471 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 -0.99772930145263672 -0.99462687969207764 
		0.99982857704162598 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 0.067351721227169037 0.10352456569671631 
		0.018513703718781471 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 -0.99772930145263672 -0.99462687969207764 
		0.99982857704162598 0;
createNode animCurveTA -n "animCurveTA202";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 22.828941404043128 2 103.7186814126237 
		4 168.03995309430235 17 167.06353517276258 21 166.84648068107907 25 168.03995309430235 
		26 191.07341303852033 27 230.9743763928326 28 208.89349386197188 30 0;
	setAttr -s 11 ".kit[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 0.060582146048545837 0.20958836376667023 
		0.024798497557640076 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 0.99816322326660156 0.97778975963592529 
		-0.99969244003295898 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 0.060582146048545837 0.20958836376667023 
		0.024798497557640076 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 0.99816322326660156 0.97778975963592529 
		-0.99969244003295898 0;
createNode animCurveTA -n "animCurveTA203";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 1 -164.8427536490708 2 -151.35627704346362 
		4 -179.43235630586318 17 -176.27546630536861 21 -175.57855833217607 25 -179.43235630586318 
		26 -326.6019436100961 27 -272.43300456672262 28 -332.41958525935536 30 4.7708320221952728e-015;
	setAttr -s 11 ".kit[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  3 10 10 1 10 10 1 10 
		10 10 1;
	setAttr -s 11 ".kix[3:10]"  1 1 1 1 0.041037354618310928 0.54884636402130127 
		0.021026499569416046 1;
	setAttr -s 11 ".kiy[3:10]"  0 0 0 0 -0.9991576075553894 -0.83592325448989868 
		0.99977892637252808 0;
	setAttr -s 11 ".kox[3:10]"  1 1 1 1 0.041037354618310928 0.54884636402130127 
		0.021026499569416046 1;
	setAttr -s 11 ".koy[3:10]"  0 0 0 0 -0.9991576075553894 -0.83592325448989868 
		0.99977892637252808 0;
createNode animCurveTU -n "animCurveTU70";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0.71712508848813183 4 1 25 1 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU71";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL61";
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
createNode animCurveTL -n "animCurveTL62";
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
createNode animCurveTL -n "animCurveTL63";
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
createNode animCurveTA -n "animCurveTA204";
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
createNode animCurveTA -n "animCurveTA205";
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
createNode animCurveTA -n "animCurveTA206";
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
createNode animCurveTA -n "animCurveTA207";
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
createNode animCurveTA -n "animCurveTA208";
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
createNode animCurveTU -n "animCurveTU72";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 1 3 4 3 25 3 30 3;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU73";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU74";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU75";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA209";
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
createNode animCurveTA -n "animCurveTA210";
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
createNode animCurveTA -n "animCurveTA211";
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
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.23689498628395578 1 0.45507832682116767 
		4 0.73901262070044915 25 0.73901262070044915 30 -0.23689498628395578;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.91706329584121704;
	setAttr -s 5 ".kiy[2:4]"  0 0 0.39874157309532166;
	setAttr -s 5 ".kox[2:4]"  1 1 0.91706329584121704;
	setAttr -s 5 ".koy[2:4]"  0 0 0.39874157309532166;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.30633990936382105 1 0.035927604262727814 
		4 0.058343699132305325 25 0.058343699132305325 30 -0.30633990936382105;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.87166357040405273;
	setAttr -s 5 ".kiy[2:4]"  0 0 0.49010470509529114;
	setAttr -s 5 ".kox[2:4]"  1 1 0.87166357040405273;
	setAttr -s 5 ".koy[2:4]"  0 0 0.49010470509529114;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.52899036848843184 1 0.54469780185042005 
		4 0.88454783783504309 25 0.88454783783504309 30 0.52899036848843184;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.71746116876602173;
	setAttr -s 5 ".kiy[2:4]"  0 0 -0.69659852981567383;
	setAttr -s 5 ".kox[2:4]"  1 1 0.71746116876602173;
	setAttr -s 5 ".koy[2:4]"  0 0 -0.69659852981567383;
createNode animCurveTU -n "animCurveTU76";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  9 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA212";
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
createNode animCurveTA -n "animCurveTA213";
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
createNode animCurveTA -n "animCurveTA214";
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
createNode animCurveTU -n "animCurveTU77";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU78";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU79";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 1 4 1 25 1 26 0 30 0;
	setAttr -s 6 ".kit[0:5]"  9 3 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  9 3 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU80";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA215";
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
createNode animCurveTA -n "animCurveTA216";
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
createNode animCurveTA -n "animCurveTA217";
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
createNode animCurveTU -n "animCurveTU81";
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
createNode animCurveTU -n "animCurveTU82";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 2 0 4 0 25 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 3 1 1 1;
	setAttr -s 6 ".kix[3:5]"  1 1 1;
	setAttr -s 6 ".kiy[3:5]"  0 0 0;
	setAttr -s 6 ".kox[3:5]"  1 1 1;
	setAttr -s 6 ".koy[3:5]"  0 0 0;
createNode animCurveTL -n "animCurveTL67";
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
createNode animCurveTL -n "animCurveTL68";
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
createNode animCurveTL -n "animCurveTL69";
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
createNode animCurveTA -n "animCurveTA218";
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
createNode animCurveTA -n "animCurveTA219";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 14 0 25 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA220";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 14 0 25 0;
	setAttr -s 3 ".kit[2]"  1;
	setAttr -s 3 ".kot[2]"  1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTA -n "animCurveTA221";
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
createNode animCurveTA -n "animCurveTA222";
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
createNode animCurveTU -n "animCurveTU83";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 1 25 1 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU84";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 3 1 3 4 3 25 3 30 3;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU85";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU86";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU87";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA223";
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
createNode animCurveTA -n "animCurveTA224";
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
createNode animCurveTA -n "animCurveTA225";
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
createNode animCurveTL -n "animCurveTL70";
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
createNode animCurveTL -n "animCurveTL71";
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
createNode animCurveTL -n "animCurveTL72";
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
createNode animCurveTU -n "animCurveTU88";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  9 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA226";
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
createNode animCurveTA -n "animCurveTA227";
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
createNode animCurveTA -n "animCurveTA228";
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
createNode animCurveTU -n "animCurveTU89";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA229";
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
createNode animCurveTA -n "animCurveTA230";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 5.1251585428584878 1 0 4 0 25 0 30 5.1251585428584878;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA231";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -1.4794141658124507 1 0 4 0 25 0 30 -1.4794141658124507;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA232";
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
createNode animCurveTA -n "animCurveTA233";
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
createNode animCurveTA -n "animCurveTA234";
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
createNode animCurveTU -n "animCurveTU90";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA235";
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
createNode animCurveTA -n "animCurveTA236";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA237";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA238";
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
createNode animCurveTA -n "animCurveTA239";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA240";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU91";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA241";
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
createNode animCurveTA -n "animCurveTA242";
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
createNode animCurveTA -n "animCurveTA243";
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
createNode animCurveTA -n "animCurveTA244";
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
createNode animCurveTA -n "animCurveTA245";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA246";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 1 0 4 0 25 0 27 0 30 0;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU92";
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
createNode animCurveTA -n "animCurveTA247";
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
createNode animCurveTA -n "animCurveTA248";
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
createNode animCurveTA -n "animCurveTA249";
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
createNode animCurveTA -n "animCurveTA250";
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
createNode animCurveTA -n "animCurveTA251";
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
createNode animCurveTA -n "animCurveTA252";
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
createNode animCurveTU -n "animCurveTU93";
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
createNode animCurveTA -n "animCurveTA253";
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
createNode animCurveTA -n "animCurveTA254";
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
createNode animCurveTA -n "animCurveTA255";
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
createNode animCurveTA -n "animCurveTA256";
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
createNode animCurveTA -n "animCurveTA257";
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
createNode animCurveTA -n "animCurveTA258";
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
createNode animCurveTA -n "animCurveTA259";
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
createNode animCurveTA -n "animCurveTA260";
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
createNode animCurveTA -n "animCurveTA261";
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
createNode animCurveTU -n "animCurveTU94";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 4.3501408210499193 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA265";
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
createNode animCurveTA -n "animCurveTA266";
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
createNode animCurveTA -n "animCurveTA267";
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
createNode animCurveTU -n "animCurveTU95";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA268";
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
createNode animCurveTA -n "animCurveTA269";
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
createNode animCurveTA -n "animCurveTA270";
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
createNode animCurveTA -n "animCurveTA271";
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
createNode animCurveTA -n "animCurveTA272";
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
createNode animCurveTA -n "animCurveTA273";
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
createNode animCurveTU -n "animCurveTU96";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA274";
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
createNode animCurveTA -n "animCurveTA275";
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
createNode animCurveTA -n "animCurveTA276";
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
createNode animCurveTA -n "animCurveTA277";
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
createNode animCurveTA -n "animCurveTA278";
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
createNode animCurveTA -n "animCurveTA279";
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
createNode animCurveTU -n "animCurveTU97";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA280";
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
createNode animCurveTA -n "animCurveTA281";
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
createNode animCurveTA -n "animCurveTA282";
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
createNode animCurveTA -n "animCurveTA283";
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
createNode animCurveTA -n "animCurveTA284";
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
createNode animCurveTA -n "animCurveTA285";
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
createNode animCurveTU -n "animCurveTU98";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA286";
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
createNode animCurveTA -n "animCurveTA287";
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
createNode animCurveTA -n "animCurveTA288";
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
createNode animCurveTA -n "animCurveTA289";
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
createNode animCurveTA -n "animCurveTA290";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA291";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA292";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA293";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA294";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU99";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU100";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU101";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA295";
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
createNode animCurveTA -n "animCurveTA296";
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
createNode animCurveTA -n "animCurveTA297";
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
createNode animCurveTL -n "animCurveTL73";
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
createNode animCurveTL -n "animCurveTL74";
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
createNode animCurveTL -n "animCurveTL75";
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
createNode animCurveTA -n "animCurveTA298";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA299";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA300";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU102";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA301";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA302";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA303";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA304";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA305";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA306";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA307";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA308";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA309";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU103";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA310";
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
createNode animCurveTA -n "animCurveTA311";
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
createNode animCurveTA -n "animCurveTA312";
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
createNode animCurveTU -n "animCurveTU104";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU105";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU106";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA313";
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
createNode animCurveTA -n "animCurveTA314";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA315";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL77";
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
createNode animCurveTL -n "animCurveTL78";
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
createNode animCurveTA -n "animCurveTA316";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA317";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA318";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU107";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA319";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA320";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA321";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA322";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA323";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA324";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA325";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA326";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA327";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA328";
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
createNode animCurveTA -n "animCurveTA329";
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
createNode animCurveTA -n "animCurveTA330";
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
createNode animCurveTA -n "animCurveTA331";
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
createNode animCurveTA -n "animCurveTA332";
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
createNode animCurveTA -n "animCurveTA333";
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
createNode animCurveTU -n "animCurveTU108";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 4 1 8 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kot[0:4]"  3 1 10 1 1;
	setAttr -s 5 ".kix[1:4]"  1 1 1 1;
	setAttr -s 5 ".kiy[1:4]"  0 0 0 0;
	setAttr -s 5 ".kox[1:4]"  1 1 1 1;
	setAttr -s 5 ".koy[1:4]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA334";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 20.69101533741409 4 -5.7951058335089671 
		8 -0.078468617291328327 19 -8.6896441352660858 25 -5.7951058335089671 30 20.69101533741409;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 0.99493438005447388 0.98485064506530762 
		1 1;
	setAttr -s 6 ".kiy[1:5]"  0 -0.10052662342786789 -0.17340464890003204 
		0 0;
	setAttr -s 6 ".kox[1:5]"  1 0.99493438005447388 0.98485064506530762 
		1 1;
	setAttr -s 6 ".koy[1:5]"  0 -0.10052662342786789 -0.17340464890003204 
		0 0;
createNode animCurveTA -n "animCurveTA335";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -8.3978566024888135 4 -6.3152610932253905 
		8 -13.869574206242925 19 7.1153341994888049 25 -6.3152610932253905 30 -8.3978566024888135;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 0.90543586015701294 0.97398346662521362 
		1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0.4244830310344696 0.22661899030208588 
		0 0;
	setAttr -s 6 ".kox[1:5]"  1 0.90543586015701294 0.97398346662521362 
		1 1;
	setAttr -s 6 ".koy[1:5]"  0 0.4244830310344696 0.22661899030208588 
		0 0;
createNode animCurveTA -n "animCurveTA336";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.8255796210686652 4 -1.7334603413036778 
		8 -4.6622382257816835 19 -6.5558997862124215 25 -1.7334603413036778 30 2.8255796210686652;
	setAttr -s 6 ".kit[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 1 10 10 1 1;
	setAttr -s 6 ".kix[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0;
	setAttr -s 6 ".kox[1:5]"  1 1 1 1 1;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0;
createNode animCurveTU -n "animCurveTU109";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 10 0 16 0 25 0 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA337";
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
createNode animCurveTA -n "animCurveTA338";
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
createNode animCurveTA -n "animCurveTA339";
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
createNode animCurveTA -n "animCurveTA340";
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
createNode animCurveTA -n "animCurveTA341";
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
createNode animCurveTA -n "animCurveTA342";
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
createNode animCurveTA -n "animCurveTA343";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -28.841216077843235 1 6.282786497024258 
		4 2.3544799545322679 25 2.3544799545322679 30 -28.841216077843235;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.13384941220283508;
	setAttr -s 5 ".kiy[2:4]"  0 0 0.99100172519683838;
	setAttr -s 5 ".kox[2:4]"  1 1 0.13384941220283508;
	setAttr -s 5 ".koy[2:4]"  0 0 0.99100172519683838;
createNode animCurveTA -n "animCurveTA344";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -21.716766331039956 1 5.788070298271653 
		4 10.399698204972548 25 10.399698204972548 30 -21.716766331039956;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.97047173976898193;
	setAttr -s 5 ".kiy[2:4]"  0 0 0.24121475219726563;
	setAttr -s 5 ".kox[2:4]"  1 1 0.97047173976898193;
	setAttr -s 5 ".koy[2:4]"  0 0 0.24121475219726563;
createNode animCurveTA -n "animCurveTA345";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 23.535235892507558 1 -30.107948258927088 
		4 3.1237624644807434 25 3.1237624644807434 30 23.535235892507558;
	setAttr -s 5 ".kit[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  9 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 0.1102796196937561;
	setAttr -s 5 ".kiy[2:4]"  0 0 -0.99390065670013428;
	setAttr -s 5 ".kox[2:4]"  1 1 0.1102796196937561;
	setAttr -s 5 ".koy[2:4]"  0 0 -0.99390065670013428;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU110";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 3 2 25 2 27 0 28 0 30 0;
	setAttr -s 7 ".kit[0:6]"  3 9 9 1 9 1 1;
	setAttr -s 7 ".kot[0:6]"  3 5 5 1 5 5 1;
	setAttr -s 7 ".kix[3:6]"  1 0.049937628209590912 0.049937617033720016 
		1;
	setAttr -s 7 ".kiy[3:6]"  0 -0.99875235557556152 0.99875235557556152 
		0;
	setAttr -s 7 ".kox[3:6]"  1 0 0 1;
	setAttr -s 7 ".koy[3:6]"  0 0 0 0;
createNode animCurveTU -n "animCurveTU111";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 3 0 25 0 30 0;
	setAttr -s 4 ".kit[0:3]"  3 9 1 1;
	setAttr -s 4 ".kot[0:3]"  3 5 1 1;
	setAttr -s 4 ".kix[2:3]"  1 1;
	setAttr -s 4 ".kiy[2:3]"  0 0;
	setAttr -s 4 ".kox[2:3]"  1 1;
	setAttr -s 4 ".koy[2:3]"  0 0;
createNode animCurveTA -n "animCurveTA346";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 77.067 1 91.704055915341442 2 190.82928621681378 
		27 190.82928621681378 28 85.412110293318918 30 77.067;
	setAttr -s 6 ".kit[3:5]"  1 1 10;
	setAttr -s 6 ".kot[3:5]"  1 1 10;
	setAttr -s 6 ".kix[3:5]"  0.96680843830108643 0.033557407557964325 
		0.41619327664375305;
	setAttr -s 6 ".kiy[3:5]"  -0.25550231337547302 0.99943679571151733 
		-0.90927612781524658;
	setAttr -s 6 ".kox[3:5]"  0.96680843830108643 0.033557407557964325 
		0.41619330644607544;
	setAttr -s 6 ".koy[3:5]"  -0.25550231337547302 0.99943679571151733 
		-0.90927618741989136;
createNode animCurveTA -n "animCurveTA347";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 21.4 1 42.36207872716227 2 60.547638966072277 
		27 60.547638966072277 28 29.319117069368009 30 21.4;
	setAttr -s 6 ".kit[3:5]"  1 1 10;
	setAttr -s 6 ".kot[3:5]"  1 1 10;
	setAttr -s 6 ".kix[3:5]"  0.93525689840316772 0.097110971808433533 
		0.43444430828094482;
	setAttr -s 6 ".kiy[3:5]"  -0.35396954417228699 0.99527353048324585 
		-0.90069866180419922;
	setAttr -s 6 ".kox[3:5]"  0.93525689840316772 0.097110971808433533 
		0.43444433808326721;
	setAttr -s 6 ".koy[3:5]"  -0.35396954417228699 0.99527353048324585 
		-0.90069872140884399;
createNode animCurveTA -n "animCurveTA348";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 26.997 1 34.889376869881893 2 93.934461980058913 
		27 93.934461980058913 28 -11.693607150639872 29 17.996660598717604 30 26.997;
	setAttr -s 7 ".kit[3:6]"  1 1 10 10;
	setAttr -s 7 ".kot[3:6]"  1 1 10 10;
	setAttr -s 7 ".kix[3:6]"  0.98999923467636108 0.056971311569213867 
		0.098247066140174866 0.20757681131362915;
	setAttr -s 7 ".kiy[3:6]"  -0.14107280969619751 0.99837577342987061 
		0.99516201019287109 0.97821873426437378;
	setAttr -s 7 ".kox[3:6]"  0.98999923467636108 0.056971311569213867 
		0.098247066140174866 0.20757681131362915;
	setAttr -s 7 ".koy[3:6]"  -0.14107280969619751 0.99837577342987061 
		0.99516201019287109 0.97821873426437378;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.32714610695432622 1 -0.74544067782127876 
		2 -1.1054375853521343 3 -1.2755255474500937 25 -1.2755255474500937 27 -1.1054375853521343 
		28 -0.96751952663587726 29 -0.57035005758157808 30 -0.32714610695432622;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kix[4:8]"  1 0.12478304654359818 0.085345186293125153 
		0.10354631394147873 1;
	setAttr -s 9 ".kiy[4:8]"  0 -0.9921841025352478 -0.99635148048400879 
		0.99462467432022095 0;
	setAttr -s 9 ".kox[4:8]"  1 0.12478304654359818 0.085345186293125153 
		0.10354631394147873 1;
	setAttr -s 9 ".koy[4:8]"  0 -0.9921841025352478 -0.99635148048400879 
		0.99462467432022095 0;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0.67722508790304892 1 0.89059098057898001 
		2 -0.21648548416532004 3 -1.4392043230118035 25 -1.4392043230118035 27 -0.21648548416532004 
		28 0.33901499322314682 29 0.84799543630728036 30 0.67722508790304892;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kix[4:8]"  1 0.02860310859978199 0.074388690292835236 
		0.19339476525783539 1;
	setAttr -s 9 ".kiy[4:8]"  0 -0.99959081411361694 -0.99722933769226074 
		0.9811210036277771 0;
	setAttr -s 9 ".kox[4:8]"  1 0.02860310859978199 0.074388690292835236 
		0.19339476525783539 1;
	setAttr -s 9 ".koy[4:8]"  0 -0.99959081411361694 -0.99722933769226074 
		0.9811210036277771 0;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -1.0382802411811836 1 -1.2945270341140935 
		2 -1.8840449347445418 3 -2.1802956492995231 25 -2.1802956492995231 27 -1.8840449347445418 
		28 -1.6287779672594793 29 -1.385550493833712 30 -1.0382802411811836;
	setAttr -s 9 ".kit[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kot[0:8]"  3 10 10 10 1 1 1 10 
		1;
	setAttr -s 9 ".kix[4:8]"  1 0.075051926076412201 0.078580394387245178 
		0.11218638718128204 1;
	setAttr -s 9 ".kiy[4:8]"  0 -0.99717962741851807 -0.99690783023834229 
		0.9936872124671936 0;
	setAttr -s 9 ".kox[4:8]"  1 0.075051926076412201 0.078580394387245178 
		0.11218638718128204 1;
	setAttr -s 9 ".koy[4:8]"  0 -0.99717962741851807 -0.99690783023834229 
		0.9936872124671936 0;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA349";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.5474409228097068 1 -3.3387029268937667 
		4 6.4698876464320998 16 -29.30482947941476 25 6.4698876464320998 30 -5.5474409228097068;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA350";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.8989001946622928 1 0.19763548006323398 
		4 4.0314766751676325 16 11.95465731029855 25 4.0314766751676325 30 8.8989001946622928;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA351";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 13.176125515933933 1 -9.4753377055041916 
		4 -19.984111675995049 16 -6.6000372179042346 25 -19.984111675995049 30 13.176125515933933;
	setAttr -s 6 ".kit[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 10 1 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.15315348837209278 1 0 4 0 25 0 30 0.15315348837209278;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA352";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA353";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA354";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU112";
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
createNode animCurveTA -n "animCurveTA355";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -3.5101256011206661 1 167.38055085130816 
		2 132.20417699892323 3 -90.205135987965633 4 -97.634461735480158 25 -97.634461735480158 
		27 -90.353815274197444 28 -125.07586289322535 29 -11.831799077644058 30 -3.5101256011206661;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.01482729334384203 0.016616838052868843 
		1 1 1 1 0.031405512243509293 1;
	setAttr -s 10 ".kiy[1:9]"  0 -0.9998900294303894 -0.9998619556427002 
		0 0 0 0 0.99950671195983887 0;
	setAttr -s 10 ".kox[1:9]"  1 0.01482729334384203 0.016616838052868843 
		1 1 1 1 0.031405512243509293 1;
	setAttr -s 10 ".koy[1:9]"  0 -0.9998900294303894 -0.9998619556427002 
		0 0 0 0 0.99950671195983887 0;
createNode animCurveTA -n "animCurveTA356";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 14.109633696872924 1 -48.3670658039795 
		2 -16.806291588608261 3 10.258339059860901 4 22.079889054909092 25 22.079889054909092 
		27 13.095879796843478 28 -4.7936286351636124 29 12.826831113715961 30 14.109633696872924;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.065016806125640869 0.097757689654827118 
		1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0.99788421392440796 0.99521028995513916 
		0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 0.065016806125640869 0.097757689654827118 
		1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0.99788421392440796 0.99521028995513916 
		0 0 0 0 0 0;
createNode animCurveTA -n "animCurveTA357";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.57775771072918292 1 -152.12414270297589 
		2 -183.16741777406727 3 -251.04071480094177 4 -133.78599490539997 25 -133.78599490539997 
		27 -129.41044717499418 28 -130.05070068860712 29 -42.386829976024892 30 -0.57775771072918292;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 0.038586799055337906 0.077120959758758545 
		1 1 1 1 0.029489228501915932 1;
	setAttr -s 10 ".kiy[1:9]"  0 -0.99925523996353149 0.99702173471450806 
		0 0 0 0 0.99956512451171875 0;
	setAttr -s 10 ".kox[1:9]"  1 0.038586799055337906 0.077120959758758545 
		1 1 1 1 0.029489228501915932 1;
	setAttr -s 10 ".koy[1:9]"  0 -0.99925523996353149 0.99702173471450806 
		0 0 0 0 0.99956512451171875 0;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0.011014375328914564 1 0.57476978983719573 
		2 0.60180920127496385 3 0.69224713869192411 4 0.7599607174422417 25 0.7599607174422417 
		27 0.72024292916195243 28 0.62894864507178694 29 0.033325902962271003 30 0.011014375328914564;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 1 0.38843587040901184 1 1 1 1 1 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0.92147576808929443 0 0 0 0 0 0;
	setAttr -s 10 ".kox[1:9]"  1 1 0.38843587040901184 1 1 1 1 1 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0.92147576808929443 0 0 0 0 0 0;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.033677566514294377 1 -0.456565503774708 
		2 -0.43136562683180496 3 -0.22231063023607212 4 -0.2000143469781071 25 -0.2000143469781071 
		27 -0.2489851188633308 28 -0.49825444242324818 29 0.089054199836426096 30 -0.033677566514294377;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 1 1 1 1 1 1 0.14204467833042145 1;
	setAttr -s 10 ".kiy[1:9]"  0 0 0 0 0 0 0 0.98986023664474487 0;
	setAttr -s 10 ".kox[1:9]"  1 1 1 1 1 1 1 0.14204467833042145 1;
	setAttr -s 10 ".koy[1:9]"  0 0 0 0 0 0 0 0.98986023664474487 0;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -0.12516676838562091 1 0.89044083060131674 
		2 0.90214202337835958 3 0.79977577897727259 4 0.88508173337898077 25 0.88508173337898077 
		27 0.83895386180672571 28 0.85078562451633222 29 -0.050468384057528869 30 -0.12516676838562091;
	setAttr -s 10 ".kit[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kot[0:9]"  3 1 10 10 1 1 1 1 
		10 1;
	setAttr -s 10 ".kix[1:9]"  1 1 0.96878170967102051 1 1 1 1 0.068150520324707031 
		1;
	setAttr -s 10 ".kiy[1:9]"  0 0 -0.24791544675827026 0 0 0 0 -0.99767506122589111 
		0;
	setAttr -s 10 ".kox[1:9]"  1 1 0.96878170967102051 1 1 1 1 0.068150520324707031 
		1;
	setAttr -s 10 ".koy[1:9]"  0 0 -0.24791544675827026 0 0 0 0 -0.99767506122589111 
		0;
createNode animCurveTA -n "animCurveTA358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.6266160090263075 1 0 4 7.0019883689133682 
		11 15.416333633171925 19 3.0074759034504819 25 7.0019883689133682 30 -1.6266160090263075;
	setAttr -s 7 ".kit[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.99041849374771118 0.95388180017471313 
		1 0.99864518642425537;
	setAttr -s 7 ".kiy[2:6]"  0 -0.13809879124164581 -0.30018258094787598 
		0 0.05203673243522644;
	setAttr -s 7 ".kox[2:6]"  1 0.99041849374771118 0.95388180017471313 
		1 0.99864518642425537;
	setAttr -s 7 ".koy[2:6]"  0 -0.13809879124164581 -0.30018258094787598 
		0 0.05203673243522644;
createNode animCurveTA -n "animCurveTA359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.0310113259678257 1 0 4 -5.1722244159819457 
		11 -11.82210502847173 19 -2.5250353857458467 25 -5.1722244159819457 30 -1.0310113259678257;
	setAttr -s 7 ".kit[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  9 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 0.99575787782669067 1 1 0.99585831165313721;
	setAttr -s 7 ".kiy[2:6]"  0 0.09201233834028244 0 0 -0.090918853878974915;
	setAttr -s 7 ".kox[2:6]"  1 0.99575787782669067 1 1 0.99585831165313721;
	setAttr -s 7 ".koy[2:6]"  0 0.09201233834028244 0 0 -0.090918853878974915;
createNode animCurveTA -n "animCurveTA360";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.7360481982364808 1 0 4 8.2763160985788637 
		11 2.6788284313103898 19 6.1639878525700169 25 8.2763160985788637 30 -3.7360481982364808;
	setAttr -s 7 ".kit[1:6]"  10 1 10 10 1 1;
	setAttr -s 7 ".kot[1:6]"  10 1 10 10 1 1;
	setAttr -s 7 ".kix[0:6]"  0.99369430541992188 0.53663575649261475 
		1 0.99729257822036743 1 1 0.99536222219467163;
	setAttr -s 7 ".kiy[0:6]"  0.1121232733130455 0.84381395578384399 
		0 -0.073534533381462097 0 0 0.096198268234729767;
	setAttr -s 7 ".kox[0:6]"  0.99369430541992188 0.53663575649261475 
		1 0.99729257822036743 1 1 0.99536222219467163;
	setAttr -s 7 ".koy[0:6]"  0.1121232733130455 0.84381395578384399 
		0 -0.073534533381462097 0 0 0.096198268234729767;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.015821220244533904 1 0 4 -0.0016769218538692557 
		11 0.010414976039566957 19 0.061588157450662748 25 -0.0016769218538692557 30 0.015821220244533904;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.99966442584991455 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.025902517139911652 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.99966442584991455 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 -0.025902517139911652 0 0;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -0.019762129127598303 1 0 4 -0.060478999393819163 
		11 -0.056385165373912999 19 -0.039920620580856422 25 -0.060478999393819163 30 -0.019762129127598303;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0.040939582646498267 1 0 4 0.012249058211337847 
		11 0.017126595039227359 19 -0.0024777979160130262 25 0.012249058211337847 30 0.040939582646498267;
	setAttr -s 7 ".kit[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 10 10 1 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTA -n "animCurveTA361";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA362";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA363";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA364";
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
createNode animCurveTA -n "animCurveTA365";
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
createNode animCurveTA -n "animCurveTA366";
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
createNode animCurveTL -n "animCurveTL103";
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
createNode animCurveTL -n "animCurveTL104";
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
createNode animCurveTL -n "animCurveTL105";
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
createNode animCurveTU -n "animCurveTU113";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU114";
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
createNode animCurveTL -n "animCurveTL106";
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
createNode animCurveTL -n "animCurveTL107";
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
createNode animCurveTL -n "animCurveTL108";
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
createNode animCurveTU -n "animCurveTU115";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 9 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 5 5 5 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
createNode animCurveTU -n "animCurveTU116";
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
createNode animCurveTL -n "animCurveTL109";
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
createNode animCurveTL -n "animCurveTL110";
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
createNode animCurveTL -n "animCurveTL111";
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
createNode animCurveTU -n "animCurveTU117";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU118";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU119";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA367";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.865855240731637 1 0 4 -60.114481521017375 
		25 -60.114481521017375 30 -18.865855240731637;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA368";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -14.58730447393145 1 0 4 -7.5975706713926163 
		25 -7.5975706713926163 30 -14.58730447393145;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA369";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 18.947646045538665 1 0 4 -11.60264135119041 
		25 -11.60264135119041 30 18.947646045538665;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL112";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0.015919995749841685 25 0.015919995749841685 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL113";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0.00026159956542019775 25 0.00026159956542019775 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL114";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0.00038496414924500005 25 0.00038496414924500005 
		30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU120";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU121";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTU -n "animCurveTU122";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 1 1 4 1 25 1 30 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 25 0 28 -12.800045426456389 
		29 -30.843191862354114 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 0.2404213547706604 0.28595367074012756 
		1;
	setAttr -s 7 ".kiy[2:6]"  0 0 -0.97066867351531982 0.95824342966079712 
		0;
	setAttr -s 7 ".kox[2:6]"  1 1 0.2404213547706604 0.28595367074012756 
		1;
	setAttr -s 7 ".koy[2:6]"  0 0 -0.97066867351531982 0.95824342966079712 
		0;
createNode animCurveTA -n "animCurveTA371";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 0 2 -4.595279301553747 4 0 25 0 28 
		0.11720944854363881 29 4.8658529556104488 30 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 1 1 10 10 1;
	setAttr -s 8 ".kot[0:7]"  3 10 10 1 1 10 10 1;
	setAttr -s 8 ".kix[3:7]"  1 1 1 0.99952948093414307 1;
	setAttr -s 8 ".kiy[3:7]"  0 0 0 -0.030670924112200737 0;
	setAttr -s 8 ".kox[3:7]"  1 1 1 0.99952948093414307 1;
	setAttr -s 8 ".koy[3:7]"  0 0 0 -0.030670924112200737 0;
createNode animCurveTA -n "animCurveTA372";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 0 4 0 25 0 28 0.96940305679808458 
		29 1.1518755807958694 30 0;
	setAttr -s 7 ".kit[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kot[0:6]"  3 10 1 1 10 10 1;
	setAttr -s 7 ".kix[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".kiy[2:6]"  0 0 0 0 0;
	setAttr -s 7 ".kox[2:6]"  1 1 1 1 1;
	setAttr -s 7 ".koy[2:6]"  0 0 0 0 0;
createNode animCurveTL -n "animCurveTL115";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL116";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL117";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA373";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA374";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA375";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA376";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA377";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA378";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA379";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA380";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA381";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA382";
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
createNode animCurveTA -n "animCurveTA383";
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
createNode animCurveTA -n "animCurveTA384";
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
createNode animCurveTA -n "animCurveTA385";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA386";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA387";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 30 0;
createNode animCurveTA -n "animCurveTA388";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA389";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA390";
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
createNode animCurveTL -n "animCurveTL118";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL119";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTL -n "animCurveTL120";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 1 0 4 0 25 0 30 0;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
createNode animCurveTA -n "animCurveTA391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -15.865935332414082 4 19.420586609803788 
		11 24.518171452717532 18 17.063598939000347 25 19.420586609803788 30 -15.865935332414082;
	setAttr -s 6 ".kit[4:5]"  1 10;
	setAttr -s 6 ".kot[4:5]"  1 10;
	setAttr -s 6 ".kix[4:5]"  1 0.26122510433197021;
	setAttr -s 6 ".kiy[4:5]"  0 -0.96527791023254395;
	setAttr -s 6 ".kox[4:5]"  1 0.26122510433197021;
	setAttr -s 6 ".koy[4:5]"  0 -0.96527791023254395;
createNode animCurveTA -n "animCurveTA392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -14.216978853750588 4 -11.610947793906632 
		11 -15.609536692762481 18 -8.8762793170138057 25 -11.610947793906632 30 -14.216978853750588;
	setAttr -s 6 ".kit[4:5]"  1 10;
	setAttr -s 6 ".kot[4:5]"  1 10;
	setAttr -s 6 ".kix[4:5]"  1 1;
	setAttr -s 6 ".kiy[4:5]"  0 0;
	setAttr -s 6 ".kox[4:5]"  1 1;
	setAttr -s 6 ".koy[4:5]"  0 0;
createNode animCurveTA -n "animCurveTA393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.2380578660743446 4 47.750414162211101 
		11 51.510970482624039 18 44.295511006685736 25 47.750414162211101 30 1.2380578660743446;
	setAttr -s 6 ".kit[4:5]"  1 10;
	setAttr -s 6 ".kot[4:5]"  1 10;
	setAttr -s 6 ".kix[4:5]"  1 0.20111191272735596;
	setAttr -s 6 ".kiy[4:5]"  0 -0.9795682430267334;
	setAttr -s 6 ".kox[4:5]"  1 0.20111192762851715;
	setAttr -s 6 ".koy[4:5]"  0 -0.97956830263137817;
createNode animCurveTU -n "animCurveTU123";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 29 1 30 1;
createNode animCurveTU -n "animCurveTU124";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 29 1 30 1;
createNode animCurveTU -n "animCurveTU125";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 1 1 29 1 30 1;
createNode animCurveTU -n "animCurveTU126";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 0 27 0 30 1;
	setAttr -s 4 ".kit[3]"  2;
	setAttr -s 4 ".kot[3]"  2;
createNode animCurveTU -n "animCurveTU127";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 0 27 0 30 1;
	setAttr -s 4 ".kit[3]"  2;
	setAttr -s 4 ".kot[3]"  2;
createNode animCurveTU -n "animCurveTU128";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 1 3 0 27 0 30 1;
	setAttr -s 4 ".kit[3]"  2;
	setAttr -s 4 ".kot[3]"  2;
createNode animCurveTA -n "animCurveTA394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 1 -90.273128364774379 2 -105.49614328453727 
		4 -21.669712835865695 26 -3.0825915410021989 27 27.166146276526518 28 -59.753186679501198 
		30 0;
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
	setAttr -s 4 ".sol";
connectAttr "ability2Source1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTU65.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA198.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA199.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA200.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTU66.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTU67.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTU68.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTU69.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA201.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA202.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA203.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTU70.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTU71.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTL61.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTL62.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTL63.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA204.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA205.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA206.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA207.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA208.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTU72.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTU73.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTU74.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTU75.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA209.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA210.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA211.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTU76.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA212.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA213.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA214.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTU77.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTU78.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTU79.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTU80.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA215.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA216.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA217.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTU81.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTU82.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA218.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA219.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA220.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA221.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA222.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU83.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU84.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU85.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU86.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU87.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA223.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA224.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA225.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU88.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA226.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA227.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA228.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU89.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA229.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA230.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA231.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA232.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA233.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA234.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU90.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA235.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA236.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA237.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA238.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA239.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA240.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU91.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA241.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA242.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA243.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA244.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA245.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA246.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU92.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA247.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA248.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA249.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA250.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA251.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA252.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU93.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA253.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA254.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA255.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU94.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA264.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA265.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA266.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA267.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU95.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA268.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA269.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA270.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA271.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA272.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA273.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU96.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA274.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA275.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA276.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA277.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA278.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA279.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU97.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA280.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA281.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA282.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA283.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA284.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA285.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU98.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA286.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA287.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA288.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA289.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA290.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA291.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA292.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA293.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA294.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU99.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU100.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU101.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA295.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA296.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA297.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL73.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL74.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL75.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA298.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA299.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA300.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU102.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA301.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA302.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA303.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA304.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA305.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA306.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA307.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA308.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA309.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU103.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA310.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA311.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA312.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU104.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU105.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU106.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA313.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA314.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA315.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL76.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA316.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA317.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA318.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU107.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA319.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA320.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA321.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA322.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA323.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA324.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA325.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA326.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA327.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA328.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA329.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA330.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA331.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA332.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA333.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU108.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA334.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA335.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA336.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU109.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA337.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA338.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA339.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA340.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA341.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA342.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA343.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA344.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA345.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU110.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU111.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA346.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA347.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA348.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL82.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL83.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL84.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL85.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL86.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL87.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA349.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA350.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA351.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL88.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL89.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL90.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA352.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA353.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA354.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU112.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA355.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA356.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA357.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA358.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA359.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA360.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL97.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL98.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA361.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA362.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA363.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL100.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL101.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA364.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA365.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA366.a" "clipLibrary1.cel[0].cev[258].cevr";
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
connectAttr "animCurveTA367.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA368.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA369.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL112.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL113.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTL114.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTU120.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTU121.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTU122.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA370.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA371.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA372.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL115.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTL116.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTL117.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA373.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA374.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA375.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTA376.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTA377.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTA378.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTA379.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTA380.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTA381.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA382.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA383.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA384.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTA385.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTA386.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTA387.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA388.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA389.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA390.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL118.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL119.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL120.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTA391.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTA392.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTA393.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTU123.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTU124.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU125.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTU126.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTU127.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTU128.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTA394.a" "clipLibrary1.cel[0].cev[321].cevr";
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
