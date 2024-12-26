//Maya ASCII 2008 scene
//Name: move2A.ma
//Last modified: Fri, Oct 16, 2009 10:00:39 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 312 ".cel[0].cev";
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
createNode animClip -n "move2Source1";
	setAttr ".ihi" 0;
	setAttr -s 312 ".ac";
	setAttr ".ac[0:47]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[50:313]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes no no no yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".se" 24;
	setAttr ".ci" no;
createNode animCurveTU -n "animCurveTU419";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1352";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1353";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635176e-015 24 3.1805546814635176e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1354";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 9.9392333795734924e-017 24 9.9392333795734924e-017;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU420";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU421";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1355";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635168e-015 24 3.1805546814635168e-015;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1356";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1357";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.7708320221952728e-015 24 4.7708320221952728e-015;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU424";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 8 0 12 0 20 0 24 0;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU425";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 8 0 12 0 20 0 24 0;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL430";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0.40930268174563 8 0.1266291149486829 
		12 0.069222986777820683 20 0.45618637529411021 24 0.40930268174563;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  0.99975031614303589 1 1 1 0.99975031614303589;
	setAttr -s 5 ".kiy[0:4]"  0.022343836724758148 0 0 0 0.022343836724758148;
	setAttr -s 5 ".kox[0:4]"  0.99975031614303589 1 1 1 0.99975031614303589;
	setAttr -s 5 ".koy[0:4]"  0.022343836724758148 0 0 0 0.022343836724758148;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL431";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.057823715136270243 8 -0.12108970782452966 
		12 -0.14183923194759274 20 -0.049134833715399479 24 -0.057823715136270243;
	setAttr -s 5 ".kit[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kot[0:4]"  1 3 3 10 1;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL432";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.22451480617215203 8 -0.53885317730305105 
		12 -0.55883703878700131 20 -0.14947391479380856 24 -0.22451480617215203;
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
createNode animCurveTA -n "animCurveTA1358";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1359";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.1805546814635168e-015 24 3.1805546814635168e-015;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1360";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -7.9513867036587899e-016 24 -7.9513867036587899e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1361";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 21.459131300514464 8 16.605943421077143 
		12 16.605943421077143 18 10.217368655365346 24 21.459131300514464;
	setAttr -s 5 ".kit[3:4]"  10 3;
	setAttr -s 5 ".kot[3:4]"  10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1362";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -0.72089968334967991 8 -7.5398172157720449 
		12 -7.5398172157720449 18 -10.144163099623649 24 -0.72089968334967991;
	setAttr -s 5 ".kit[3:4]"  10 3;
	setAttr -s 5 ".kot[3:4]"  10 3;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU426";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3 24 3;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU427";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU428";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr -s 2 ".kit[0:1]"  1 9;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU429";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1363";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 95.027912018899102 6 88.841116395239681 
		10 97.007517980569247 18 88.894813521796692 22 96.589775717155177 24 95.027912018899102;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 10 2;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 10 2;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1364";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 91.954078189911641 6 104.48654049104753 
		10 88.112731702648105 18 104.02502224481047 22 87.439318047878814 24 91.954078189911641;
	setAttr -s 6 ".kit[0:5]"  2 10 10 10 10 2;
	setAttr -s 6 ".kot[0:5]"  2 10 10 10 10 2;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1365";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 7.3475119642090769 6 -2.120265261764255 
		12 9.7734531089471286 18 -2.9370200450584569 24 7.3475119642090769;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.19751656702699438 5 0.20383017546085241 
		9 0.15450840071215205 16 0.266748823132339 22 0.14199678657311832 24 0.19751656702699438;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 9;
createNode animCurveTL -n "animCurveTL434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.18549442709713693 5 -0.16005039183546679 
		9 -0.27813225688831528 16 -0.14991362602012781 22 -0.28113845701960172 24 -0.18549442709713693;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 9;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 9;
	setAttr -s 6 ".kix[0:5]"  0.99999934434890747 1 0.9996180534362793 
		0.99997591972351074 0.99121558666229248 0.57182538509368896;
	setAttr -s 6 ".kiy[0:5]"  -0.0011301732156425714 0 0.027635164558887482 
		-0.0069372178986668587 -0.1322559267282486 0.82037532329559326;
	setAttr -s 6 ".kox[0:5]"  0.99999934434890747 1 0.9996180534362793 
		0.99997591972351074 0.99121558666229248 0.57182538509368896;
	setAttr -s 6 ".koy[0:5]"  -0.0011301732156425714 0 0.027635164558887482 
		-0.0069372178986668587 -0.1322559267282486 0.82037532329559326;
createNode animCurveTL -n "animCurveTL435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.26334592628767134 5 0.31966707746782264 
		9 0.074420067359867545 16 0.31234279204161297 22 0.079727493959951323 24 0.26334592628767134;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
createNode animCurveTU -n "animCurveTU430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1366";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -9.2343529322129996 8 26.207363431108853 
		12 0.26263073179406404 18 -29.053413745575117 24 -9.2343529322129996;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1367";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -15.11110170915666 8 -22.560255277665803 
		12 -12.305663620420683 18 -43.464309830248673 24 -15.11110170915666;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1368";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 18.196383878722202 8 -31.317467024052341 
		12 -16.473156843477689 18 12.761581585459012 24 18.196383878722202;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU431";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[0:1]"  9 1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU432";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[0:1]"  9 1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU434";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[0:1]"  9 1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1369";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3.9531091186723013 24 3.9531091186723013;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  0.60531854629516602;
	setAttr -s 2 ".kiy[1]"  -0.79598337411880493;
	setAttr -s 2 ".kox[1]"  0.60531854629516602;
	setAttr -s 2 ".koy[1]"  -0.79598337411880493;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1370";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.62018686761647346 24 0.62018686761647346;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  0.60684502124786377;
	setAttr -s 2 ".kiy[1]"  -0.79482018947601318;
	setAttr -s 2 ".kox[1]"  0.60684502124786377;
	setAttr -s 2 ".koy[1]"  -0.79482018947601318;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1371";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 5.3292188742882338 24 5.3292188742882338;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  0.60228490829467773;
	setAttr -s 2 ".kiy[1]"  -0.79828125238418579;
	setAttr -s 2 ".kox[1]"  0.60228490829467773;
	setAttr -s 2 ".koy[1]"  -0.79828125238418579;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.1102230246251565e-016 24 -1.1102230246251565e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1372";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -19.513757781440109 9 6.5456055724674922 
		17 -15.5947568468331 24 -19.513757781440109;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1373";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -11.226354836536574 11 -10.02711003493188 
		16 -4.8286472162956802 21 -15.497636630436423 24 -11.226354836536574;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1374";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.99923745724103941 5 -3.3913369990003561 
		11 -15.810254142055145 16 0.8784266099385063 21 -9.7055132810580851 24 -0.99923745724103941;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU437";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 3 24 3;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU440";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1375";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1376";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1377";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.2204460492503131e-016 24 2.2204460492503131e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.4408920985006262e-016 24 4.4408920985006262e-016;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU442";
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
createNode animCurveTA -n "animCurveTA1378";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -3.8674792585271232 5 13.696369270300705 
		12 -12.651341509624858 17 -33.424906303041737 24 -3.8674792585271232;
	setAttr -s 5 ".kit[1:4]"  3 9 3 9;
	setAttr -s 5 ".kot[1:4]"  3 9 3 9;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1379";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 12.134175752092313 5 11.595332580399456 
		12 17.038516552174194 17 14.982241136703291 24 12.134175752092313;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1380";
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
createNode animCurveTU -n "animCurveTU443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1381";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 68.629003384766676 24 68.629003384766676;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1382";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 5.1251585428584878 24 5.1251585428584878;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1383";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.4794141658124507 24 -1.4794141658124507;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1384";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.9967431843380723 24 2.9967431843380723;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1385";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 27.356153209428296 24 27.356153209428296;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1386";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 4.8891453517792058 24 4.8891453517792058;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1387";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1388";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1389";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1390";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 61.945270723308987 24 61.945270723308987;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1391";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1392";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1393";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1394";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1395";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1396";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 61.945270723308987 24 61.945270723308987;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1397";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1398";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1399";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 59.032884886088816 24 59.032884886088816;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1400";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1401";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1402";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 72.878304588436421 24 72.878304588436421;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1403";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1404";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1405";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 77.67986202714836 24 77.67986202714836;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1406";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1407";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1408";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 65.952779168408995 24 65.952779168408995;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1409";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 12.091864976351665 24 12.091864976351665;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1410";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -6.5683373417752975 24 -6.5683373417752975;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1411";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 6 -7.6014037587385497 24 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1412";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 2 15.672434621002276 3 30.967221676292326 
		6 1.1605546246599088 24 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 1;
	setAttr -s 5 ".kix[4]"  1;
	setAttr -s 5 ".kiy[4]"  0;
	setAttr -s 5 ".kox[4]"  1;
	setAttr -s 5 ".koy[4]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1413";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 6 21.182636747890534 24 0;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[2]"  1;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  1;
	setAttr -s 3 ".koy[2]"  0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1414";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 13.729997542293324 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1415";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 0.63874595844642235 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1416";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 13 6.1520328136917257 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1417";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 2.6646619917013665 13 1.9373926035036853 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1418";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 4.961351675227804 13 3.9566911421785878 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1419";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 9 8.8684278089956265 13 7.9229985932156008 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1420";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -17.642997232323477 13 9.1407201674254317 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1421";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.93848795149607789 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1422";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.92427193607252134 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1423";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -22.5760742608601 13 -4.1145899246833526 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1424";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -5.8309265890133206 13 -0.90543740643721604 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1425";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 2.4435995647855426 13 -1.1263561059675398 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU450";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1426";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -17.642997232323477 13 9.1407201674254317 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1427";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.93848795149607789 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1428";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.92427193607252134 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1429";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -6.8075220033640305 13 5.0415058561552222 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1430";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -12.016363506895738 13 -8.9238146958442357 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1431";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -1.2514024913402597 13 -1.2216349854939013 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1432";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -15.546441969357463 13 11.401709114863877 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1433";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -1.0263724082885994 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1434";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -0.86866692003361745 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1435";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -16.07758801342198 13 -0.61916420632540081 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1436";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -4.1900875643121465 13 6.5116984727812151 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1437";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -4.5469560145144108 13 -3.0802581235749198 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0 13 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1438";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -5.6482082233636417 13 11.401709114863877 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1439";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 1.1803122184191976 13 0.44652878551999398 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1440";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -7.3066417485869275 13 1.251413533982171 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1441";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -15.543934669382823 13 -0.29323023447363011 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 -3.8872905273843954 13 8.3138486829487519 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 1.1402657424823999 13 -3.5854133604909983 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1444";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 13 0 16 -45.915414855418632 19 -0.9966619265244735 
		24 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 13 0 16 7.5574010691608802 19 -2.6309827201324603 
		24 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 13 0 16 -14.537084522494677 19 2.0523665805617033 
		24 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU453";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU454";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU455";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1447";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.92590198521464373 3 4.0474752517269579 
		5 2.8379354588542749 8 176.85761078602656 12 178.74696219943303 15 180.77512938561802 
		18 180.05212515278467 21 179.80586512463421 22 191.01305326385759 23 5.4468934723264226 
		24 0.92590198521464373;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.98053771257400513;
	setAttr -s 11 ".koy[10]"  0.19633078575134277;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1448";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 2.9174110535850906 5 2.2747784624914273 
		8 176.51975291010194 12 178.27432387827653 15 181.05707827720477 18 180.91493342628846 
		21 177.89097719433536 22 180.88370806039151 23 1.3604483098193929 24 0;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.97278010845184326;
	setAttr -s 11 ".koy[10]"  0.23173007369041443;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1449";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 59.400273410863271 5 73.363013758592345 
		8 75.013485748760786 12 58.582425034644693 15 148.30894849878547 18 190.55651484922274 
		21 179.88926151412633 22 177.19082123607828 23 -0.10373109200056627 24 0;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.1958349347114563;
	setAttr -s 11 ".koy[10]"  0.98063689470291138;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL442";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0.34978214829119497 5 0.64277255703708225 
		8 1.1733834598260824 12 1.1776973696048545 15 0.57806391035549609 18 0.36704624572781147 
		21 0.016536709378649289 24 0;
	setAttr -s 9 ".kit[0:8]"  2 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  2 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  0.52077275514602661;
	setAttr -s 9 ".koy[8]"  0.85369527339935303;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL443";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 -0.36869042509528277 3 0.73567047827044196 
		5 1.0505858921208242 8 0.84783213251852296 12 0.11878137990599391 15 -0.46791035000704778 
		18 -1.5181343388795372 21 -1.1692804260151433 24 -0.36869042509528277;
	setAttr -s 9 ".kit[0:8]"  2 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  2 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[8]"  1;
	setAttr -s 9 ".kiy[8]"  0;
	setAttr -s 9 ".kox[8]"  0.090181149542331696;
	setAttr -s 9 ".koy[8]"  0.99592536687850952;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL444";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.32507334843177282 24 0.32507334843177282;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1450";
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
createNode animCurveTA -n "animCurveTA1451";
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
createNode animCurveTA -n "animCurveTA1452";
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
createNode animCurveTU -n "animCurveTU456";
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
createNode animCurveTA -n "animCurveTA1453";
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
createNode animCurveTA -n "animCurveTA1454";
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
createNode animCurveTA -n "animCurveTA1455";
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
createNode animCurveTA -n "animCurveTA1456";
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
createNode animCurveTA -n "animCurveTA1457";
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
createNode animCurveTA -n "animCurveTA1458";
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
createNode animCurveTA -n "animCurveTA1459";
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
createNode animCurveTA -n "animCurveTA1460";
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
createNode animCurveTA -n "animCurveTA1461";
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
createNode animCurveTU -n "animCurveTU457";
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
createNode animCurveTA -n "animCurveTA1462";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 4.2739658544589174 5 -1.8519338386522297 
		12 -26.108229692772159 17 -15.307150864039638 24 4.2739658544589174;
	setAttr -s 5 ".kit[3:4]"  9 1;
	setAttr -s 5 ".kot[3:4]"  9 1;
	setAttr -s 5 ".kix[0:4]"  1 0.99692535400390625 1 0.60221195220947266 
		1;
	setAttr -s 5 ".kiy[0:4]"  0 -0.07835736870765686 0 0.79833632707595825 
		0;
	setAttr -s 5 ".kox[0:4]"  1 0.99692535400390625 1 0.60221195220947266 
		1;
	setAttr -s 5 ".koy[0:4]"  0 -0.078357353806495667 0 0.79833632707595825 
		0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1463";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -41.531258985004385 5 -41.386432696118987 
		12 -55.457878298957581 17 -57.099544132696849 24 -41.531258985004385;
	setAttr -s 5 ".kit[1:4]"  10 9 3 1;
	setAttr -s 5 ".kot[1:4]"  10 9 3 1;
	setAttr -s 5 ".kix[0:4]"  1 1 0.82476752996444702 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 -0.5654720664024353 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 0.82476752996444702 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 -0.5654720664024353 0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1464";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 43.535238447847377 5 46.059443098083165 
		12 34.053158955942806 17 47.552352065552824 24 43.535238447847377;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU458";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU459";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU460";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1465";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -2.5120182699055205 2 -0.94903876996821279 
		4 3.1015208248984258 6 4.6727515928916912 9 2.9713527984763299 12 2.9580992827793215 
		15 3.6899422734307392 16 5.1659550704746202 18 6.0912259655003105 20 157.34528813451431 
		24 -2.5120182699055205;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.92551571130752563;
	setAttr -s 11 ".koy[10]"  0.37870904803276062;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -1.4434920278151244 2 0.57860511435695361 
		4 1.0372413820738213 6 1.4120198370952255 9 1.0327965842918785 12 1.0958493557359257 
		15 1.2410680212660434 16 2.4555037819733481 18 3.2578654958649418 20 154.32484118598845 
		24 -1.4434920278151244;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.88379812240600586;
	setAttr -s 11 ".koy[10]"  0.4678683876991272;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 111.72754493272389 2 22.561416496375372 
		4 5.5557290197465461 6 -7.4613130931721612 9 -1.6497933746574567 12 -3.3031120343516451 
		15 33.709848035468902 16 60.45384947952607 18 71.516075442820366 20 87.616695846922752 
		24 111.72754493272389;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.042798977345228195;
	setAttr -s 11 ".koy[10]"  -0.99908369779586792;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL445";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1.1038762275260849 2 0.5111500314638413 
		4 0.5396951559942651 6 0.15144327590475246 9 -0.012485295688597436 12 -0.015181489110057692 
		15 0.19026846391370375 16 0.36329459625798005 18 0.65617072002111898 20 1.0142252316592251 
		24 1.1038762275260849;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.1117698922753334;
	setAttr -s 11 ".koy[10]"  -0.99373406171798706;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL446";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0.078254692248154289 2 -0.78774137342720263 
		4 -1.3162247585682016 6 -1.3750416404716996 9 -1.2274920093324957 12 -0.20940930154221832 
		15 0.66631438354857042 16 0.76597815310670114 18 0.80004558669051373 20 0.75690648890278978 
		24 0.078254692248154289;
	setAttr -s 11 ".kit[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kot[0:10]"  2 10 10 10 10 10 10 10 
		10 10 1;
	setAttr -s 11 ".kix[10]"  1;
	setAttr -s 11 ".kiy[10]"  0;
	setAttr -s 11 ".kox[10]"  0.076755546033382416;
	setAttr -s 11 ".koy[10]"  -0.99704992771148682;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL447";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.3584706980247494 24 -0.3584706980247494;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1468";
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
createNode animCurveTA -n "animCurveTA1469";
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
createNode animCurveTA -n "animCurveTA1470";
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
createNode animCurveTU -n "animCurveTU461";
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
createNode animCurveTA -n "animCurveTA1471";
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
createNode animCurveTA -n "animCurveTA1472";
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
createNode animCurveTA -n "animCurveTA1473";
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
createNode animCurveTA -n "animCurveTA1474";
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
createNode animCurveTA -n "animCurveTA1475";
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
createNode animCurveTA -n "animCurveTA1476";
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
createNode animCurveTA -n "animCurveTA1477";
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
createNode animCurveTA -n "animCurveTA1478";
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
createNode animCurveTA -n "animCurveTA1479";
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
createNode animCurveTA -n "animCurveTA1480";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -29.311636586952385 5 -12.548994092377487 
		12 -24.53711599522936 17 -41.592634089983392 24 -29.311636586952385;
	setAttr -s 5 ".kit[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kot[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kix[0:4]"  0.41200023889541626 1 0.61946314573287964 
		1 0.41200023889541626;
	setAttr -s 5 ".kiy[0:4]"  0.91118377447128296 0 -0.78502577543258667 
		0 0.91118377447128296;
	setAttr -s 5 ".kox[0:4]"  0.41200023889541626 1 0.61946314573287964 
		1 0.41200023889541626;
	setAttr -s 5 ".koy[0:4]"  0.91118377447128296 0 -0.78502577543258667 
		0 0.91118377447128296;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1481";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -5.7546656733329762 5 -2.7892205026951693 
		12 -8.1654715053760238 17 -9.5749041077482939 24 -5.7546656733329762;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 9;
	setAttr -s 5 ".kix[0:4]"  0.94282537698745728 0.99451291561126709 
		0.95885419845581055 0.99451291561126709 0.96151411533355713;
	setAttr -s 5 ".kiy[0:4]"  0.33328738808631897 -0.10461404919624329 
		-0.28389883041381836 0.10461404919624329 0.27475568652153015;
	setAttr -s 5 ".kox[0:4]"  0.9428253173828125 0.99451291561126709 
		0.95885419845581055 0.99451291561126709 0.96151411533355713;
	setAttr -s 5 ".koy[0:4]"  0.33328735828399658 -0.10461404919624329 
		-0.28389883041381836 0.10461404919624329 0.27475568652153015;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1482";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 24.135668239007668 5 16.161416517159424 
		12 24.136754111877469 17 16.697523314238605 24 24.135668239007668;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  1 1 0.99972647428512573 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 4.7380141040775925e-005 0.023385675624012947 
		-4.7380141040775925e-005 0;
	setAttr -s 5 ".kox[0:4]"  1 1 0.99972647428512573 1 1;
	setAttr -s 5 ".koy[0:4]"  0 4.7380141040775925e-005 0.023385675624012947 
		-4.7380141040775925e-005 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1483";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -28.064725223295074 5 -45.870760394675024 
		12 -9.9332078065117209 17 9.4916548818124067 21 -20.99378270830891 24 -28.064725223295074;
	setAttr -s 6 ".kit[3:5]"  1 10 9;
	setAttr -s 6 ".kot[3:5]"  1 10 9;
	setAttr -s 6 ".kix[3:5]"  1 0.33535787463188171 0.6295621395111084;
	setAttr -s 6 ".kiy[3:5]"  0 -0.94209080934524536 -0.7769501805305481;
	setAttr -s 6 ".kox[3:5]"  1 0.33535787463188171 0.6295621395111084;
	setAttr -s 6 ".koy[3:5]"  0 -0.94209080934524536 -0.7769501805305481;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1484";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 8.1722234572666252 5 -8.3233981649544031 
		12 8.1722234572666252 17 1.2885593448026365 21 -3.0738517406347574 24 8.1722234572666252;
	setAttr -s 6 ".kit[3:5]"  9 3 3;
	setAttr -s 6 ".kot[3:5]"  9 3 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1485";
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
createNode animCurveTU -n "animCurveTU462";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1 5 1 12 1 17 1 24 1;
	setAttr -s 5 ".kit[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kot[0:4]"  3 10 1 1 1;
	setAttr -s 5 ".kix[2:4]"  1 1 1;
	setAttr -s 5 ".kiy[2:4]"  0 0 0;
	setAttr -s 5 ".kox[2:4]"  1 1 1;
	setAttr -s 5 ".koy[2:4]"  0 0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1486";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.011476194518726878 5 0.20673248545015888 
		12 -0.61014146333917973 17 -0.45775175025518738 20 -0.2505120946420904 24 0.011476194518726878;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 1 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0 0 0;
	setAttr -s 6 ".kox[2:5]"  1 1 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0 0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1487";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -3.621145868974136 5 -6.3080381396646361 
		12 -3.1147285659714736 17 0.55054125045653735 20 -1.2464694009743984 24 -3.621145868974136;
	setAttr -s 6 ".kit[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 1 1 10 1;
	setAttr -s 6 ".kix[2:5]"  1 0.95901620388031006 1 1;
	setAttr -s 6 ".kiy[2:5]"  0 0.28335127234458923 0 0;
	setAttr -s 6 ".kox[2:5]"  1 0.95901620388031006 1 1;
	setAttr -s 6 ".koy[2:5]"  0 0.28335127234458923 0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1488";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 2.5085875540734017 5 -6.3419854861505547 
		12 -3.3938477307730111 17 -1.911597306337917 20 -7.752136323664315 24 2.5085875540734017;
	setAttr -s 6 ".kit[0:5]"  3 9 1 9 10 1;
	setAttr -s 6 ".kot[0:5]"  3 9 1 9 10 1;
	setAttr -s 6 ".kix[2:5]"  1 0.96164202690124512 0.94945073127746582 
		1;
	setAttr -s 6 ".kiy[2:5]"  0 -0.27430769801139832 0.31391596794128418 
		0;
	setAttr -s 6 ".kox[2:5]"  1 0.96164202690124512 0.94945073127746582 
		1;
	setAttr -s 6 ".koy[2:5]"  0 -0.27430769801139832 0.31391596794128418 
		0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU463";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1489";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 1 1.6804832659194908 4 -45.668250305949741 
		10 57.097576736786927 15 -29.508400907571144 22 33.117919348930144 24 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1491";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1492";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 10.793181446349577 7 14.046721903121176 
		10 11.702463324247006 16 32.92067434158794 22 17.521474831547199 24 10.793181446349577;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1493";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -11.069096393638221 7 -23.903907760232382 
		10 -19.764859612267195 16 7.4916139732504314 22 -19.080812397140164 24 -11.069096393638221;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1494";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 46.971202074790767 7 50.752955240080674 
		10 50.898203679118353 16 40.365031568037303 22 45.401965749012383 24 46.971202074790767;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  1;
	setAttr -s 6 ".koy[5]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1495";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -35.396144853650526 5 -52.15683362526444 
		9 -28.154524370782543 12 -23.313587695108044 21 -46.163676364093412 24 -35.396144853650526;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1496";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -34.018174792048853 5 -13.255592122303687 
		9 -35.370771740027557 12 18.513690050077056 21 -61.898631864945571 24 -34.018174792048853;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1497";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.9884446047337234 5 77.02298260713205 
		9 -29.750415807508794 12 54.618393978136346 20 27.924622864682512 21 41.024088698138051 
		24 -1.9884446047337234;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 1 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 1 10 3;
	setAttr -s 7 ".kix[4:6]"  0.056642401963472366 0.24744580686092377 
		1;
	setAttr -s 7 ".kiy[4:6]"  0.99839454889297485 -0.96890169382095337 
		0;
	setAttr -s 7 ".kox[4:6]"  0.056642334908246994 0.24744580686092377 
		1;
	setAttr -s 7 ".koy[4:6]"  0.99839454889297485 -0.96890169382095337 
		0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL448";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL449";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL450";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU464";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2 24 2;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU465";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kot[0:1]"  5 5;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1498";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -24.093441664171177 24 -24.093441664171177;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1499";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 49.48465546224881 24 49.48465546224881;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1500";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 58.801792680015588 24 58.801792680015588;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL451";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.2755255474500937 24 -1.2755255474500937;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL452";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.4392043230118035 24 -1.4392043230118035;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL453";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -2.1802956492995231 24 -2.1802956492995231;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL454";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL455";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL456";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1501";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.1134085745786892 4 -0.26325926875826428 
		10 7.6705304962036198 15 20.318065349478061 19 14.803517654782359 24 1.1134085745786892;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1502";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -5.3180374758492821 4 -19.002407541677474 
		10 -5.9236020533935791 15 -33.378464582425259 19 -15.691036318202608 24 -5.3180374758492821;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1503";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 7.8609313736722894 4 14.337193133013898 
		10 -26.591610350974722 15 3.2098956060354045 19 -22.724881967192733 24 7.8609313736722894;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 3;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL457";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0.0094449017567307929 15 0.060655418864559441 
		24 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL458";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 -0.029396930599450352 15 0.065294107021005118 
		24 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL459";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 4 0.018256166403821682 15 -0.059437140934362184 
		24 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1504";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1505";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1506";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL460";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL461";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL462";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU466";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 5 0 12 0 17 0 22 0 24 0;
	setAttr -s 6 ".kit[0:5]"  9 9 9 9 9 1;
	setAttr -s 6 ".kix[5]"  1;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1507";
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
createNode animCurveTA -n "animCurveTA1508";
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
createNode animCurveTA -n "animCurveTA1509";
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
createNode animCurveTL -n "animCurveTL463";
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
createNode animCurveTL -n "animCurveTL464";
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
createNode animCurveTL -n "animCurveTL465";
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
createNode animCurveTA -n "animCurveTA1510";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.2399711943881462 6 5.8368103675692984 
		8 5.5371717889404417 12 13.701656763438768 18 -1.6578600985338485 20 -0.46947470793843232 
		24 -1.2399711943881462;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.92331308126449585 1 1 0.93579554557800293 
		1 1 1;
	setAttr -s 7 ".kiy[0:6]"  0.38404801487922668 0 0 -0.3525431752204895 
		0 0 0;
	setAttr -s 7 ".kox[0:6]"  0.92331314086914063 1 1 0.93579554557800293 
		1 1 1;
	setAttr -s 7 ".koy[0:6]"  0.38404804468154907 0 0 -0.3525431752204895 
		0 0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1511";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -35.889138953044828 6 11.597858154803525 
		8 9.0436710387620245 12 -40.209706605817473 18 -9.3361108539774662 20 -3.5784081713286326 
		24 -35.889138953044828;
	setAttr -s 7 ".kit[0:6]"  3 10 10 3 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 3 10 10 3;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1512";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -3.5262114410899876 6 -23.5686128677299 
		8 -18.506208401779851 12 -0.7051828133608361 18 7.2421368171988538 20 4.8552604379823228 
		24 -3.5262114410899876;
	setAttr -s 7 ".kit[0:6]"  1 10 10 1 10 10 10;
	setAttr -s 7 ".kot[0:6]"  1 10 10 1 10 10 10;
	setAttr -s 7 ".kix[0:6]"  0.60353332757949829 0.71405631303787231 
		0.44807177782058716 0.70692986249923706 1 1 0.67363381385803223;
	setAttr -s 7 ".kiy[0:6]"  -0.79733783006668091 -0.7000882625579834 
		0.89399755001068115 0.70728373527526855 0 0 -0.73906528949737549;
	setAttr -s 7 ".kox[0:6]"  0.60353332757949829 0.71405631303787231 
		0.44807177782058716 0.70692980289459229 1 1 0.67363381385803223;
	setAttr -s 7 ".koy[0:6]"  -0.79733783006668091 -0.7000882625579834 
		0.89399755001068115 0.70728373527526855 0 0 -0.73906528949737549;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL466";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.013594152923483699 12 0.0012548238460522562 
		18 -0.04715642228085231 24 0;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0 0 0 0;
	setAttr -s 5 ".kox[0:4]"  1 1 1 1 1;
	setAttr -s 5 ".koy[0:4]"  0 0 0 0 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL467";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.067270675684061518 12 -0.056967529699048947 
		18 -0.13879472226747169 24 0;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.85944533348083496 0.99001020193099976 
		0.88897025585174561 0.99001020193099976 0.82155114412307739;
	setAttr -s 5 ".kiy[0:4]"  0.51122772693634033 -0.14099608361721039 
		-0.45796495676040649 0.14099608361721039 0.57013481855392456;
	setAttr -s 5 ".kox[0:4]"  0.85944533348083496 0.99001020193099976 
		0.88897025585174561 0.99001020193099976 0.82155114412307739;
	setAttr -s 5 ".koy[0:4]"  0.51122772693634033 -0.14099608361721039 
		-0.45796495676040649 0.14099608361721039 0.57013481855392456;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL468";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 6 0.088755192096523619 12 0.01199586266937569 
		18 -0.05038854110258565 24 0;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 10;
	setAttr -s 5 ".kix[0:4]"  0.97746771574020386 0.99955052137374878 
		0.94448703527450562 0.99955052137374878 0.96969765424728394;
	setAttr -s 5 ".kiy[0:4]"  0.2110850065946579 0.029976177960634232 
		-0.32854858040809631 -0.029976177960634232 0.24430826306343079;
	setAttr -s 5 ".kox[0:4]"  0.97746771574020386 0.99955052137374878 
		0.94448703527450562 0.99955052137374878 0.96969765424728394;
	setAttr -s 5 ".koy[0:4]"  0.2110850065946579 0.029976177960634232 
		-0.32854858040809631 -0.029976177960634232 0.24430826306343079;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1513";
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
createNode animCurveTA -n "animCurveTA1514";
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
createNode animCurveTA -n "animCurveTA1515";
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
createNode animCurveTL -n "animCurveTL469";
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
createNode animCurveTL -n "animCurveTL470";
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
createNode animCurveTL -n "animCurveTL471";
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
createNode animCurveTA -n "animCurveTA1516";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -3.4820313138629455 24 -3.4820313138629455;
	setAttr -s 2 ".kix[0:1]"  0.99019926786422729 0.99019926786422729;
	setAttr -s 2 ".kiy[0:1]"  0.13966159522533417 0.13966159522533417;
	setAttr -s 2 ".kox[0:1]"  0.99019932746887207 0.99019932746887207;
	setAttr -s 2 ".koy[0:1]"  0.13966159522533417 0.13966159522533417;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1517";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.2721832506814086 3 8.7888541148300821 
		12 2.3939524613330989 16 -1.3713271350058063 24 1.2721832506814086;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  1 0.99880433082580566 0.92550510168075562 
		1 1;
	setAttr -s 5 ".kiy[0:4]"  0 0.048887889832258224 -0.37873506546020508 
		0 0;
	setAttr -s 5 ".kox[0:4]"  1 0.99880433082580566 0.92550510168075562 
		1 1;
	setAttr -s 5 ".koy[0:4]"  0 0.048887889832258224 -0.37873506546020508 
		0 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1518";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 13.092921420682925 24 13.092921420682925;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.189 3 -0.098044318169019318 8 -0.32940724502269875 
		16 -0.13568322892932499 21 -0.31620390592994857 24 -0.189;
	setAttr -s 6 ".kit[0:5]"  1 10 10 10 10 1;
	setAttr -s 6 ".kot[0:5]"  1 10 10 10 10 1;
	setAttr -s 6 ".kix[0:5]"  1 0.88484114408493042 0.99624890089035034 
		0.99953615665435791 0.98059237003326416 1;
	setAttr -s 6 ".kiy[0:5]"  0 -0.46589288115501404 -0.086533203721046448 
		0.030455112457275391 -0.19605758786201477 0;
	setAttr -s 6 ".kox[0:5]"  1 0.88484114408493042 0.99624890089035034 
		0.99953615665435791 0.98059237003326416 1;
	setAttr -s 6 ".koy[0:5]"  0 -0.46589288115501404 -0.086533203721046448 
		0.030455112457275391 -0.19605758786201477 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL473";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.27905490988822479 16 -0.28454345657681379 
		24 -0.27905490988822479;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  1 1 1;
	setAttr -s 3 ".kiy[0:2]"  0 0 0;
	setAttr -s 3 ".kox[0:2]"  1 1 1;
	setAttr -s 3 ".koy[0:2]"  0 0 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL474";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.0035205622938596082 24 -0.0035205622938596082;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU467";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU468";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.084155571970393403 24 0.084155571970393403;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL475";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL476";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.8360926868100278 24 -0.8360926868100278;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL477";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 2.7755575615628914e-017 24 0;
	setAttr -s 2 ".kit[1]"  1;
	setAttr -s 2 ".kot[1]"  1;
	setAttr -s 2 ".kix[1]"  1;
	setAttr -s 2 ".kiy[1]"  0;
	setAttr -s 2 ".kox[1]"  1;
	setAttr -s 2 ".koy[1]"  0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU469";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTU -n "animCurveTU470";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.084155864375844894 24 0.084155864375844894;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL478";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL479";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.8360926868100278 24 -0.8360926868100278;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTL -n "animCurveTL480";
	setAttr ".tan" 1;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -0.073926484418881333 24 -0.073926484418881333;
	setAttr -s 2 ".kix[0:1]"  1 1;
	setAttr -s 2 ".kiy[0:1]"  0 0;
	setAttr -s 2 ".kox[0:1]"  1 1;
	setAttr -s 2 ".koy[0:1]"  0 0;
	setAttr ".pre" 4;
	setAttr ".pst" 4;
createNode animCurveTA -n "animCurveTA1519";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1520";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1521";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1522";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1523";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1524";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1525";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1526";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1527";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1528";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -18.592620239620459 6 -27.693411150845737 
		9 -16.352883697812253 12 -30.791977327368169 18 -26.517352720414316 21 -1.2417990319774348 
		24 -18.592620239620459;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kix[0:6]"  1 0.99161726236343384 0.96533161401748657 
		0.86076217889785767 0.5028039813041687 0.82247859239578247 1;
	setAttr -s 7 ".kiy[0:6]"  0 0.12921027839183807 -0.261026531457901 
		-0.50900727510452271 0.86440044641494751 0.56879609823226929 0;
	setAttr -s 7 ".kox[0:6]"  1 0.99161726236343384 0.96533161401748657 
		0.86076217889785767 0.5028039813041687 0.82247859239578247 1;
	setAttr -s 7 ".koy[0:6]"  0 0.12921027839183807 -0.261026531457901 
		-0.50900727510452271 0.86440044641494751 0.56879609823226929 0;
createNode animCurveTA -n "animCurveTA1529";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -4.0495369920864128 6 -22.142997633643184 
		9 -7.3353380757234845 12 20.12968510428022 18 15.330402064740783 21 -29.232420309652657 
		24 -4.0495369920864128;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 1;
	setAttr -s 7 ".kix[0:6]"  1 0.98221486806869507 0.26163464784622192 
		0.60425341129302979 0.32885006070137024 0.50897198915481567 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.18776035308837891 0.96516698598861694 
		0.79679226875305176 -0.94438213109970093 -0.86078304052352905 0;
	setAttr -s 7 ".kox[0:6]"  1 0.98221486806869507 0.26163464784622192 
		0.60425341129302979 0.32885006070137024 0.50897198915481567 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.18776035308837891 0.96516698598861694 
		0.79679226875305176 -0.94438213109970093 -0.86078304052352905 0;
createNode animCurveTA -n "animCurveTA1530";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -24.718935474963271 6 -11.485218362810704 
		9 -24.999593628058562 12 -15.643437374844828 18 -19.330990231693757 21 -25.994418609467385 
		24 -24.718935474963271;
	setAttr -s 7 ".kit[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  1 10 10 10 10 10 3;
	setAttr -s 7 ".kix[0:6]"  1 0.99986672401428223 0.94002372026443481 
		0.94968914985656738 0.85666197538375854 1 1;
	setAttr -s 7 ".kiy[0:6]"  0 -0.016325853765010834 -0.34110927581787109 
		0.3131941556930542 -0.51587820053100586 0 0;
	setAttr -s 7 ".kox[0:6]"  1 0.99986672401428223 0.94002372026443481 
		0.94968914985656738 0.85666197538375854 1 1;
	setAttr -s 7 ".koy[0:6]"  0 -0.016325853765010834 -0.34110927581787109 
		0.3131941556930542 -0.51587820053100586 0 0;
createNode animCurveTA -n "animCurveTA1531";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1532";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1533";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU471";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU472";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU473";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1534";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1535";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1536";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL481";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL482";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL483";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU474";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU475";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTU -n "animCurveTU476";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 24 1;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1537";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1538";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1539";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL484";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL485";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL486";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1540";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 -2.4377812922280051 10 -1.8073517791331406 
		18 -1.6751470019828847 20 -2.5675316297267399 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1541";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 7 8.2050449992155059 10 12.412071464905081 
		18 -2.8311699708942144 20 -12.588423037331738 24 0;
	setAttr ".pre" 4;
createNode animCurveTA -n "animCurveTA1542";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 7.2644697342894906 3 12.341700545520093 
		7 3.4398700115499641 9 3.9184842300336005 10 5.2095590074123672 13 12.018540414570811 
		18 6.280820685624418 20 16.537682512720792 24 7.2644697342894906;
	setAttr -s 9 ".kit[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kot[0:8]"  1 10 10 10 10 10 10 10 
		1;
	setAttr -s 9 ".kix[0:8]"  0.8445855975151062 0.96143114566802979 
		1 1 1 0.99755102396011353 0.94733971357345581 0.99633598327636719 0.8445855975151062;
	setAttr -s 9 ".kiy[0:8]"  0.53542047739028931 -0.27504563331604004 
		0 0 0 0.069942206144332886 0.32023021578788757 0.085525058209896088 0.53542047739028931;
	setAttr -s 9 ".kox[0:8]"  0.84458565711975098 0.96143114566802979 
		1 1 1 0.99755102396011353 0.94733971357345581 0.99633598327636719 0.84458565711975098;
	setAttr -s 9 ".koy[0:8]"  0.53542053699493408 -0.27504563331604004 
		0 0 0 0.069942206144332886 0.32023021578788757 0.085525058209896088 0.53542053699493408;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL487";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0.017785132642809301 18 0.018186695383913314 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL488";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0.0036959436202005434 18 0.0050592432818263753 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL489";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 7 0.023454462301946092 18 -0.015472781092347567 
		24 0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL490";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.026619555792534968 10 0.065155314019082061 
		16 0.0066826925743769753 24 0.026619555792534968;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL491";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.063502212298763738 10 -0.017537597398515823 
		16 -0.10320689260306296 24 0.063502212298763738;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 4;
createNode animCurveTL -n "animCurveTL492";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.1400224852942063 10 0.23193532092630878 
		16 0.18161390024289795 24 0.1400224852942063;
	setAttr -s 4 ".kit[0:3]"  3 10 10 1;
	setAttr -s 4 ".kot[0:3]"  3 10 10 1;
	setAttr -s 4 ".kix[3]"  1;
	setAttr -s 4 ".kiy[3]"  0;
	setAttr -s 4 ".kox[3]"  1;
	setAttr -s 4 ".koy[3]"  0;
	setAttr ".pre" 4;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 24;
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
	setAttr -s 4 ".sol";
connectAttr "move2Source1.cl" "clipLibrary1.sc[0]";
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
connectAttr "animCurveTA1373.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA1374.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTU437.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU438.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU439.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU440.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTU441.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA1375.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA1376.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA1377.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL439.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL440.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL441.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU442.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA1378.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA1379.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA1380.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTU443.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA1381.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA1382.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA1383.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA1384.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA1385.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA1386.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTU444.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA1387.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA1388.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA1389.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA1390.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA1391.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA1392.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTU445.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA1393.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA1394.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA1395.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA1396.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTA1397.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTA1398.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTU446.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA1399.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA1400.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA1401.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA1402.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA1403.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA1404.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTU447.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTA1405.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA1406.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA1407.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA1408.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTA1409.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTA1410.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA1411.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA1412.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA1413.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTU448.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA1414.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA1415.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA1416.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA1417.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA1418.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA1419.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTU449.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA1420.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTA1421.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTA1422.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA1423.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA1424.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA1425.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTU450.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTA1426.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTA1427.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA1428.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA1429.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA1430.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTA1431.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTU451.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTA1432.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA1433.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA1434.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA1435.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA1436.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA1437.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTU452.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA1438.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA1439.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA1440.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA1441.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA1442.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA1443.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA1444.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA1445.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA1446.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTU453.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTU454.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTU455.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA1447.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA1448.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA1449.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTL442.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTL443.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTL444.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA1450.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA1451.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA1452.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTU456.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA1453.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA1454.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA1455.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA1456.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA1457.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA1458.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA1459.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA1460.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA1461.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTU457.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA1462.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA1463.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA1464.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTU458.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTU459.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTU460.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA1465.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA1466.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA1467.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTL445.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTL446.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTL447.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA1468.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA1469.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA1470.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTU461.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA1471.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA1472.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA1473.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA1474.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA1475.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA1476.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA1477.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA1478.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA1479.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA1480.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA1481.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA1482.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA1483.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA1484.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA1485.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTU462.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA1486.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA1487.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA1488.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTU463.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA1489.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA1490.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA1491.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA1492.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA1493.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA1494.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA1495.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA1496.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA1497.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTL448.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTL449.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTL450.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTU464.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTU465.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTA1498.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTA1499.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTA1500.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL451.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL452.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTL453.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL454.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL455.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL456.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTA1501.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTA1502.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTA1503.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL457.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL458.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL459.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTA1504.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTA1505.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTA1506.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL460.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL461.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL462.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTU466.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTA1507.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTA1508.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTA1509.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL463.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL464.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL465.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTA1510.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTA1511.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTA1512.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTL466.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTL467.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTL468.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA1513.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA1514.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA1515.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTL469.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTL470.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTL471.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA1516.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA1517.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA1518.a" "clipLibrary1.cel[0].cev[258].cevr";
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
connectAttr "animCurveTA1519.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTA1520.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTA1521.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTA1522.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTA1523.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTA1524.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTA1525.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTA1526.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTA1527.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTA1528.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTA1529.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTA1530.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTA1531.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTA1532.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTA1533.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTU471.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTU472.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTU473.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTA1534.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTA1535.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTA1536.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL481.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL482.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL483.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTU474.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTU475.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTU476.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTA1537.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTA1538.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTA1539.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL484.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL485.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL486.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTA1540.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTA1541.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTA1542.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL487.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL488.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL489.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL490.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTL491.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL492.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of move2A.ma
