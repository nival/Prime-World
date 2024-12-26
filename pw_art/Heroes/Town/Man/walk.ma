//Maya ASCII 2008 scene
//Name: walk.ma
//Last modified: Fri, Jan 23, 2009 03:11:34 AM
//Codeset: 1252
requires maya "2008";
currentUnit -l meter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows Vista Service Pack 1 (Build 6001)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 307 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 307 "Bip01_R_Toe0.scaleZ" 0 
		1 "Bip01_R_Toe0.scaleY" 0 2 "Bip01_R_Toe0.scaleX" 0 3 "Bip01_R_Toe0.rotateZ" 
		2 1 "Bip01_R_Toe0.rotateY" 2 2 "Bip01_R_Toe0.rotateX" 2 
		3 "Bip01_R_Toe0.translateZ" 1 1 "Bip01_R_Toe0.translateY" 1 2 "Bip01_R_Toe0.translateX" 
		1 3 "Bip01_R_Foot.scaleZ" 0 4 "Bip01_R_Foot.scaleY" 0 5 "Bip01_R_Foot.scaleX" 
		0 6 "Bip01_R_Foot.rotateZ" 2 4 "Bip01_R_Foot.rotateY" 2 
		5 "Bip01_R_Foot.rotateX" 2 6 "Bip01_R_Foot.translateZ" 1 4 "Bip01_R_Foot.translateY" 
		1 5 "Bip01_R_Foot.translateX" 1 6 "Bip01_R_Calf.scaleZ" 0 
		7 "Bip01_R_Calf.scaleY" 0 8 "Bip01_R_Calf.scaleX" 0 9 "Bip01_R_Calf.rotateZ" 
		2 7 "Bip01_R_Calf.rotateY" 2 8 "Bip01_R_Calf.rotateX" 2 
		9 "Bip01_R_Calf.translateZ" 1 7 "Bip01_R_Calf.translateY" 1 8 "Bip01_R_Calf.translateX" 
		1 9 "Bip01_R_Thigh.scaleZ" 0 10 "Bip01_R_Thigh.scaleY" 0 
		11 "Bip01_R_Thigh.scaleX" 0 12 "Bip01_R_Thigh.rotateZ" 2 10 "Bip01_R_Thigh.rotateY" 
		2 11 "Bip01_R_Thigh.rotateX" 2 12 "Bip01_R_Thigh.translateZ" 1 
		10 "Bip01_R_Thigh.translateY" 1 11 "Bip01_R_Thigh.translateX" 1 
		12 "Bip01_L_Toe0.scaleZ" 0 13 "Bip01_L_Toe0.scaleY" 0 14 "Bip01_L_Toe0.scaleX" 
		0 15 "Bip01_L_Toe0.rotateZ" 2 13 "Bip01_L_Toe0.rotateY" 2 
		14 "Bip01_L_Toe0.rotateX" 2 15 "Bip01_L_Toe0.translateZ" 1 13 "Bip01_L_Toe0.translateY" 
		1 14 "Bip01_L_Toe0.translateX" 1 15 "Bip01_L_Foot.scaleZ" 0 
		16 "Bip01_L_Foot.scaleY" 0 17 "Bip01_L_Foot.scaleX" 0 18 "Bip01_L_Foot.rotateZ" 
		2 16 "Bip01_L_Foot.rotateY" 2 17 "Bip01_L_Foot.rotateX" 2 
		18 "Bip01_L_Foot.translateZ" 1 16 "Bip01_L_Foot.translateY" 1 17 "Bip01_L_Foot.translateX" 
		1 18 "Bip01_L_Calf.scaleZ" 0 19 "Bip01_L_Calf.scaleY" 0 20 "Bip01_L_Calf.scaleX" 
		0 21 "Bip01_L_Calf.rotateZ" 2 19 "Bip01_L_Calf.rotateY" 2 
		20 "Bip01_L_Calf.rotateX" 2 21 "Bip01_L_Calf.translateZ" 1 19 "Bip01_L_Calf.translateY" 
		1 20 "Bip01_L_Calf.translateX" 1 21 "Bip01_L_Thigh.scaleZ" 0 
		22 "Bip01_L_Thigh.scaleY" 0 23 "Bip01_L_Thigh.scaleX" 0 24 "Bip01_L_Thigh.rotateZ" 
		2 22 "Bip01_L_Thigh.rotateY" 2 23 "Bip01_L_Thigh.rotateX" 2 
		24 "Bip01_L_Thigh.translateZ" 1 22 "Bip01_L_Thigh.translateY" 1 
		23 "Bip01_L_Thigh.translateX" 1 24 "Bip01_L_Finger11.scaleZ" 0 
		25 "Bip01_L_Finger11.scaleY" 0 26 "Bip01_L_Finger11.scaleX" 0 27 "Bip01_L_Finger11.rotateZ" 
		2 25 "Bip01_L_Finger11.rotateY" 2 26 "Bip01_L_Finger11.rotateX" 
		2 27 "Bip01_L_Finger11.translateZ" 1 25 "Bip01_L_Finger11.translateY" 
		1 26 "Bip01_L_Finger11.translateX" 1 27 "Bip01_L_Finger1.scaleZ" 
		0 28 "Bip01_L_Finger1.scaleY" 0 29 "Bip01_L_Finger1.scaleX" 0 
		30 "Bip01_L_Finger1.rotateZ" 2 28 "Bip01_L_Finger1.rotateY" 2 29 "Bip01_L_Finger1.rotateX" 
		2 30 "Bip01_L_Finger1.translateZ" 1 28 "Bip01_L_Finger1.translateY" 
		1 29 "Bip01_L_Finger1.translateX" 1 30 "Bip01_L_Finger21.scaleZ" 
		0 31 "Bip01_L_Finger21.scaleY" 0 32 "Bip01_L_Finger21.scaleX" 0 
		33 "Bip01_L_Finger21.rotateZ" 2 31 "Bip01_L_Finger21.rotateY" 2 
		32 "Bip01_L_Finger21.rotateX" 2 33 "Bip01_L_Finger21.translateZ" 1 
		31 "Bip01_L_Finger21.translateY" 1 32 "Bip01_L_Finger21.translateX" 
		1 33 "Bip01_L_Finger2.scaleZ" 0 34 "Bip01_L_Finger2.scaleY" 0 
		35 "Bip01_L_Finger2.scaleX" 0 36 "Bip01_L_Finger2.rotateZ" 2 34 "Bip01_L_Finger2.rotateY" 
		2 35 "Bip01_L_Finger2.rotateX" 2 36 "Bip01_L_Finger2.translateZ" 
		1 34 "Bip01_L_Finger2.translateY" 1 35 "Bip01_L_Finger2.translateX" 
		1 36 "Bip01_L_Finger01.scaleZ" 0 37 "Bip01_L_Finger01.scaleY" 0 
		38 "Bip01_L_Finger01.scaleX" 0 39 "Bip01_L_Finger01.rotateZ" 2 
		37 "Bip01_L_Finger01.rotateY" 2 38 "Bip01_L_Finger01.rotateX" 2 
		39 "Bip01_L_Finger01.translateZ" 1 37 "Bip01_L_Finger01.translateY" 
		1 38 "Bip01_L_Finger01.translateX" 1 39 "Bip01_L_Finger0.scaleZ" 
		0 40 "Bip01_L_Finger0.scaleY" 0 41 "Bip01_L_Finger0.scaleX" 0 
		42 "Bip01_L_Finger0.rotateZ" 2 40 "Bip01_L_Finger0.rotateY" 2 41 "Bip01_L_Finger0.rotateX" 
		2 42 "Bip01_L_Finger0.translateZ" 1 40 "Bip01_L_Finger0.translateY" 
		1 41 "Bip01_L_Finger0.translateX" 1 42 "Bip01_L_Hand.scaleZ" 0 
		43 "Bip01_L_Hand.scaleY" 0 44 "Bip01_L_Hand.scaleX" 0 45 "Bip01_L_Hand.rotateZ" 
		2 43 "Bip01_L_Hand.rotateY" 2 44 "Bip01_L_Hand.rotateX" 2 
		45 "Bip01_L_Hand.translateZ" 1 43 "Bip01_L_Hand.translateY" 1 44 "Bip01_L_Hand.translateX" 
		1 45 "Bip01_L_Forearm.scaleZ" 0 46 "Bip01_L_Forearm.scaleY" 0 
		47 "Bip01_L_Forearm.scaleX" 0 48 "Bip01_L_Forearm.rotateZ" 2 46 "Bip01_L_Forearm.rotateY" 
		2 47 "Bip01_L_Forearm.rotateX" 2 48 "Bip01_L_Forearm.translateZ" 
		1 46 "Bip01_L_Forearm.translateY" 1 47 "Bip01_L_Forearm.translateX" 
		1 48 "Bip01_L_UpperArm.scaleZ" 0 49 "Bip01_L_UpperArm.scaleY" 0 
		50 "Bip01_L_UpperArm.scaleX" 0 51 "Bip01_L_UpperArm.rotateZ" 2 
		49 "Bip01_L_UpperArm.rotateY" 2 50 "Bip01_L_UpperArm.rotateX" 2 
		51 "Bip01_L_UpperArm.translateZ" 1 49 "Bip01_L_UpperArm.translateY" 
		1 50 "Bip01_L_UpperArm.translateX" 1 51 "Bip01_L_Clavicle.scaleZ" 
		0 52 "Bip01_L_Clavicle.scaleY" 0 53 "Bip01_L_Clavicle.scaleX" 0 
		54 "Bip01_L_Clavicle.rotateZ" 2 52 "Bip01_L_Clavicle.rotateY" 2 
		53 "Bip01_L_Clavicle.rotateX" 2 54 "Bip01_L_Clavicle.translateZ" 1 
		52 "Bip01_L_Clavicle.translateY" 1 53 "Bip01_L_Clavicle.translateX" 
		1 54 "Bip01_R_Finger11.scaleZ" 0 55 "Bip01_R_Finger11.scaleY" 0 
		56 "Bip01_R_Finger11.scaleX" 0 57 "Bip01_R_Finger11.rotateZ" 2 
		55 "Bip01_R_Finger11.rotateY" 2 56 "Bip01_R_Finger11.rotateX" 2 
		57 "Bip01_R_Finger11.translateZ" 1 55 "Bip01_R_Finger11.translateY" 
		1 56 "Bip01_R_Finger11.translateX" 1 57 "Bip01_R_Finger1.scaleZ" 
		0 58 "Bip01_R_Finger1.scaleY" 0 59 "Bip01_R_Finger1.scaleX" 0 
		60 "Bip01_R_Finger1.rotateZ" 2 58 "Bip01_R_Finger1.rotateY" 2 59 "Bip01_R_Finger1.rotateX" 
		2 60 "Bip01_R_Finger1.translateZ" 1 58 "Bip01_R_Finger1.translateY" 
		1 59 "Bip01_R_Finger1.translateX" 1 60 "Bip01_R_Finger21.scaleZ" 
		0 61 "Bip01_R_Finger21.scaleY" 0 62 "Bip01_R_Finger21.scaleX" 0 
		63 "Bip01_R_Finger21.rotateZ" 2 61 "Bip01_R_Finger21.rotateY" 2 
		62 "Bip01_R_Finger21.rotateX" 2 63 "Bip01_R_Finger21.translateZ" 1 
		61 "Bip01_R_Finger21.translateY" 1 62 "Bip01_R_Finger21.translateX" 
		1 63 "Bip01_R_Finger2.scaleZ" 0 64 "Bip01_R_Finger2.scaleY" 0 
		65 "Bip01_R_Finger2.scaleX" 0 66 "Bip01_R_Finger2.rotateZ" 2 64 "Bip01_R_Finger2.rotateY" 
		2 65 "Bip01_R_Finger2.rotateX" 2 66 "Bip01_R_Finger2.translateZ" 
		1 64 "Bip01_R_Finger2.translateY" 1 65 "Bip01_R_Finger2.translateX" 
		1 66 "Bip01_R_Finger01.scaleZ" 0 67 "Bip01_R_Finger01.scaleY" 0 
		68 "Bip01_R_Finger01.scaleX" 0 69 "Bip01_R_Finger01.rotateZ" 2 
		67 "Bip01_R_Finger01.rotateY" 2 68 "Bip01_R_Finger01.rotateX" 2 
		69 "Bip01_R_Finger01.translateZ" 1 67 "Bip01_R_Finger01.translateY" 
		1 68 "Bip01_R_Finger01.translateX" 1 69 "Bip01_R_Finger0.scaleZ" 
		0 70 "Bip01_R_Finger0.scaleY" 0 71 "Bip01_R_Finger0.scaleX" 0 
		72 "Bip01_R_Finger0.rotateZ" 2 70 "Bip01_R_Finger0.rotateY" 2 71 "Bip01_R_Finger0.rotateX" 
		2 72 "Bip01_R_Finger0.translateZ" 1 70 "Bip01_R_Finger0.translateY" 
		1 71 "Bip01_R_Finger0.translateX" 1 72 "Bip01_R_Hand.scaleZ" 0 
		73 "Bip01_R_Hand.scaleY" 0 74 "Bip01_R_Hand.scaleX" 0 75 "Bip01_R_Hand.rotateZ" 
		2 73 "Bip01_R_Hand.rotateY" 2 74 "Bip01_R_Hand.rotateX" 2 
		75 "Bip01_R_Hand.translateZ" 1 73 "Bip01_R_Hand.translateY" 1 74 "Bip01_R_Hand.translateX" 
		1 75 "Bip01_R_Forearm.scaleZ" 0 76 "Bip01_R_Forearm.scaleY" 0 
		77 "Bip01_R_Forearm.scaleX" 0 78 "Bip01_R_Forearm.rotateZ" 2 76 "Bip01_R_Forearm.rotateY" 
		2 77 "Bip01_R_Forearm.rotateX" 2 78 "Bip01_R_Forearm.translateZ" 
		1 76 "Bip01_R_Forearm.translateY" 1 77 "Bip01_R_Forearm.translateX" 
		1 78 "Bip01_R_UpperArm.scaleZ" 0 79 "Bip01_R_UpperArm.scaleY" 0 
		80 "Bip01_R_UpperArm.scaleX" 0 81 "Bip01_R_UpperArm.rotateZ" 2 
		79 "Bip01_R_UpperArm.rotateY" 2 80 "Bip01_R_UpperArm.rotateX" 2 
		81 "Bip01_R_UpperArm.translateZ" 1 79 "Bip01_R_UpperArm.translateY" 
		1 80 "Bip01_R_UpperArm.translateX" 1 81 "Bip01_R_Clavicle.scaleZ" 
		0 82 "Bip01_R_Clavicle.scaleY" 0 83 "Bip01_R_Clavicle.scaleX" 0 
		84 "Bip01_R_Clavicle.rotateZ" 2 82 "Bip01_R_Clavicle.rotateY" 2 
		83 "Bip01_R_Clavicle.rotateX" 2 84 "Bip01_R_Clavicle.translateZ" 1 
		82 "Bip01_R_Clavicle.translateY" 1 83 "Bip01_R_Clavicle.translateX" 
		1 84 "Bip01_Head.scaleZ" 0 85 "Bip01_Head.scaleY" 0 86 "Bip01_Head.scaleX" 
		0 87 "Bip01_Head.rotateZ" 2 85 "Bip01_Head.rotateY" 2 86 "Bip01_Head.rotateX" 
		2 87 "Bip01_Head.translateZ" 1 85 "Bip01_Head.translateY" 1 
		86 "Bip01_Head.translateX" 1 87 "Bip01_Neck.scaleZ" 0 88 "Bip01_Neck.scaleY" 
		0 89 "Bip01_Neck.scaleX" 0 90 "Bip01_Neck.rotateZ" 2 88 "Bip01_Neck.rotateY" 
		2 89 "Bip01_Neck.rotateX" 2 90 "Bip01_Neck.translateZ" 1 88 "Bip01_Neck.translateY" 
		1 89 "Bip01_Neck.translateX" 1 90 "Bip01_Spine1.scaleZ" 0 
		91 "Bip01_Spine1.scaleY" 0 92 "Bip01_Spine1.scaleX" 0 93 "Bip01_Spine1.rotateZ" 
		2 91 "Bip01_Spine1.rotateY" 2 92 "Bip01_Spine1.rotateX" 2 
		93 "Bip01_Spine1.translateZ" 1 91 "Bip01_Spine1.translateY" 1 92 "Bip01_Spine1.translateX" 
		1 93 "Bip01_Spine.scaleZ" 0 94 "Bip01_Spine.scaleY" 0 95 "Bip01_Spine.scaleX" 
		0 96 "Bip01_Spine.rotateZ" 2 94 "Bip01_Spine.rotateY" 2 95 "Bip01_Spine.rotateX" 
		2 96 "Bip01_Spine.translateZ" 1 94 "Bip01_Spine.translateY" 1 
		95 "Bip01_Spine.translateX" 1 96 "Bip01_Pelvis.scaleZ" 0 97 "Bip01_Pelvis.scaleY" 
		0 98 "Bip01_Pelvis.scaleX" 0 99 "Bip01_Pelvis.rotateZ" 2 97 "Bip01_Pelvis.rotateY" 
		2 98 "Bip01_Pelvis.rotateX" 2 99 "Bip01_Pelvis.translateZ" 1 
		97 "Bip01_Pelvis.translateY" 1 98 "Bip01_Pelvis.translateX" 1 99 "root.scaleZ" 
		0 100 "root.scaleY" 0 101 "root.scaleX" 0 102 "root.rotateZ" 
		2 100 "root.rotateY" 2 101 "root.rotateX" 2 102 "root.translateZ" 
		1 100 "root.translateY" 1 101 "root.translateX" 1 102 "Fbx_Root.translateY" 
		1 103  ;
	setAttr ".cd[0].cim" -type "Int32Array" 307 0 1 2 3 4
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
		 305 306 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 307 ".ac[0:306]" yes yes yes yes yes yes yes yes yes yes yes 
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
		yes no;
	setAttr ".se" 32;
	setAttr ".ci" no;
createNode animCurveTU -n "Bip01_R_Toe0_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Toe0_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Toe0_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Toe0_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 89.999984000000012 0.792 89.999984000000012 
		1.584 89.999998000000019 2.4 89.999998000000019 3.192 89.999998000000019 3.984 89.999984000000012 
		4.8 90.421748 5.592 91.525916000000009 6.384 92.890738 7.2 93.994907000000012 7.992 
		94.416657 8.784 96.901890000000009 9.6 99.527407000000011 10.392 102.18233600000002 
		11.184 104.79114 12 107.196036 12.792 108.761549 13.584 109.404414 14.4 110.09140100000002 
		15.192 111.67053400000002 15.984 114.99998400000001 16.8 114.11331000000001 17.592 
		111.80931600000001 18.384 108.92269400000002 19.2 106.60137900000001 19.992 105.714725 
		20.784 103.054237 21.6 96.089077 22.392 87.479665000000011 23.184 80.51451800000001 
		24 77.854085 24.792 78.939060000000012 25.584 81.779537 26.4 85.290535 27.192 88.131005 
		27.984 89.21596 28.8 89.290826 29.592 89.486832000000021 30.384 89.729112000000015 
		31.2 89.925125 31.992 89.999998000000019;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Toe0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -2.0000000000000008e-006 0.792 -2.0000000000000008e-006 
		1.584 -2.0000000000000008e-006 2.4 2.0000000000000008e-006 3.192 -1.0000000000000004e-006 
		3.984 -1.0000000000000004e-006 4.8 -3.0000000000000005e-006 5.592 -5e-006 6.384 -7.0000000000000024e-006 
		7.2 -8.9999999999999985e-006 7.992 -1.3000000000000001e-005 8.784 -0.093681000000000014 
		9.6 -0.27219900000000008 10.392 -0.40675700000000004 11.184 -0.368031 12 -0.021322 
		12.792 0.205786 13.584 -0.105972 14.4 -0.57498500000000008 15.192 -0.67517200000000011 
		15.984 2.6000000000000002e-005 16.8 3.0000000000000011e-005 17.592 2.9e-005 18.384 
		2.9e-005 19.2 3.2000000000000012e-005 19.992 3.1000000000000008e-005 20.784 2.7999999999999996e-005 
		21.6 2.9e-005 22.392 3.3000000000000009e-005 23.184 4e-005 24 3.5999999999999994e-005 
		24.792 3.4e-005 25.584 3.4e-005 26.4 3.2000000000000012e-005 27.192 3.2000000000000012e-005 
		27.984 3.4e-005 28.8 3.1000000000000008e-005 29.592 2.4000000000000004e-005 30.384 
		1e-005 31.2 4.0000000000000015e-006 31.992 -1.0000000000000004e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Toe0_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 6.000000000000001e-006 0.792 6.000000000000001e-006 
		1.584 6.000000000000001e-006 2.4 -4.0000000000000015e-006 3.192 1.0000000000000004e-006 
		3.984 1.0000000000000004e-006 4.8 5e-006 5.592 2.0000000000000008e-006 6.384 1.0000000000000004e-006 
		7.2 4.0000000000000015e-006 7.992 2.0000000000000008e-006 8.784 0.04018 9.6 0.12664200000000003 
		10.392 0.18534 11.184 0.15534700000000004 12 -0.01363 12.792 -0.16771 13.584 -0.13897400000000001 
		14.4 -0.032402000000000007 15.192 0.028840999999999995 15.984 1.9000000000000004e-005 
		16.8 2.4000000000000004e-005 17.592 1.6000000000000006e-005 18.384 1.2000000000000002e-005 
		19.2 1.3999999999999998e-005 19.992 8.9999999999999985e-006 20.784 1.3000000000000001e-005 
		21.6 6.000000000000001e-006 22.392 2.0000000000000008e-006 23.184 -1.0000000000000004e-006 
		24 -5e-006 24.792 -3.0000000000000005e-006 25.584 0 26.4 0 27.192 6.000000000000001e-006 
		27.984 3.0000000000000005e-006 28.8 7.0000000000000024e-006 29.592 1.1000000000000001e-005 
		30.384 0 31.2 1.0000000000000004e-006 31.992 4.0000000000000015e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Toe0_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Toe0_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.12389;
createNode animCurveTL -n "Bip01_R_Toe0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.077676;
createNode animCurveTU -n "Bip01_R_Foot_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Foot_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Foot_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Foot_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 4.2190000000000012 0.792 5.793142 1.584 
		6.350543 2.4 6.343266 3.192 6.069206 3.984 5.701004 4.8 6.343204000000001 5.592 6.900798 
		6.384 6.9368010000000009 7.2 5.9988730000000006 7.992 3.7026260000000009 8.784 2.8014530000000004 
		9.6 2.366457 10.392 2.181377 11.184 2.046842 12 1.844489 12.792 2.1709720000000003 
		13.584 3.138173 14.4 4.068997 15.192 4.433999 15.984 3.650154 16.8 3.631723 17.592 
		3.909744 18.384 3.1941250000000005 19.2 0.14086400000000002 19.992 -6.6441410000000012 
		20.784 -6.2906500000000012 21.6 -4.8318310000000011 22.392 -2.929756 23.184 -1.2464140000000001 
		24 -0.443758 24.792 -0.902366 25.584 -2.178863 26.4 -3.70009 27.192 -4.899345 27.984 
		-5.206743 28.8 -4.387915 29.592 -2.7819410000000007 30.384 -0.68234500000000009 31.2 
		1.5768690000000003 31.992 3.6330400000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Foot_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.010602 0.792 -0.43925100000000006 
		1.584 -0.863031 2.4 -1.2193240000000003 3.192 -1.464604 3.984 -1.575096 4.8 -1.4819090000000001 
		5.592 -1.315024 6.384 -1.159924 7.2 -1.0695710000000003 7.992 -1.070599 8.784 -1.2224080000000002 
		9.6 -1.43642 10.392 -1.627875 11.184 -1.704817 12 -1.5654800000000002 12.792 -1.11626 
		13.584 -0.41379900000000003 14.4 0.41653800000000007 15.192 1.2521460000000002 15.984 
		1.967914 16.8 2.627762 17.592 3.179705 18.384 3.7254060000000004 19.2 4.3752200000000006 
		19.992 5.2302860000000013 20.784 5.2790740000000005 21.6 5.0906190000000011 22.392 
		4.772422 23.184 4.431454 24 4.174575 24.792 4.178281000000001 25.584 4.3543610000000008 
		26.4 4.431643 27.192 4.180205 27.984 3.444469 28.8 2.261537 29.592 1.008286 30.384 
		0.064727000000000021 31.2 -0.33581700000000003 31.992 -0.16024500000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Foot_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -10.103611000000003 0.792 -9.4573850000000022 
		1.584 -8.790024 2.4 -8.102527 3.192 -7.406432 3.984 -6.7195280000000013 4.8 -6.0660610000000013 
		5.592 -5.4396310000000012 6.384 -4.8482530000000006 7.2 -4.2997010000000007 7.992 
		-3.7941300000000009 8.784 -3.331022 9.6 -2.8704990000000006 10.392 -2.366818 11.184 
		-1.7817270000000003 12 -1.099281 12.792 -0.35556 13.584 0.387636 14.4 1.108704 15.192 
		1.7905620000000002 15.984 2.410524 16.8 2.9910710000000003 17.592 3.5251940000000004 
		18.384 3.943324 19.2 4.146371 19.992 4.024104 20.784 4.1232650000000008 21.6 4.222188 
		22.392 4.311087 23.184 4.390068 24 4.474522 24.792 4.797130000000001 25.584 5.381317000000001 
		26.4 5.9201660000000009 27.192 6.070978 27.984 5.4469760000000012 28.8 3.75749 29.592 
		1.145117 30.384 -2.0788020000000005 31.2 -5.5018960000000012 31.992 -8.661374;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Foot_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Foot_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Foot_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.422138 0.792 0.422138 1.584 0.422138 
		2.4 0.422138 3.192 0.422138 3.984 0.422138 4.8 0.422138 5.592 0.422138 6.384 0.422138 
		7.2 0.422138 7.992 0.422138 8.784 0.422138 9.6 0.422138 10.392 0.422138 11.184 0.422138 
		12 0.422138 12.792 0.422138 13.584 0.422138 14.4 0.422138 15.192 0.422138 15.984 
		0.422138 16.8 0.422138 17.592 0.422138 18.384 0.422138 19.2 0.422138 19.992 0.422138 
		20.784 0.422138 21.6 0.422138 22.392 0.422138 23.184 0.422138 24 0.422138 24.792 
		0.422138 25.584 0.422138 26.4 0.422138 27.192 0.422138 27.984 0.422138 28.8 0.422138 
		29.592 0.422138 30.384 0.422138 31.2 0.422138 31.992 0.422138;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Calf_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Calf_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Calf_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Calf_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -17.753918 0.792 -24.671494 1.584 -29.923959000000004 
		2.4 -33.646634000000006 3.192 -35.677781 3.984 -35.630175 4.8 -35.200075000000005 
		5.592 -32.529406 6.384 -28.004843000000005 7.2 -21.926627 7.992 -14.675794 8.784 
		-13.291136 9.6 -13.052790000000002 10.392 -13.478106 11.184 -14.065241000000002 12 
		-14.320333000000002 12.792 -13.814440000000001 13.584 -12.879219000000003 14.4 -12.157999 
		15.192 -12.28904 15.984 -13.920042000000002 16.8 -17.567736000000004 17.592 -22.768098000000002 
		18.384 -28.850629000000005 19.2 -34.927403 19.992 -40.256105 20.784 -45.189977000000006 
		21.6 -50.248582 22.392 -54.90126200000001 23.184 -58.61737 24 -60.866251000000005 
		24.792 -61.689685000000004 25.584 -61.441373000000006 26.4 -60.058751999999991 27.192 
		-57.479174 27.984 -53.640034 28.8 -48.054189 29.592 -40.763393 30.384 -32.498339 
		31.2 -23.989715 31.992 -15.968314000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Calf_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.0000000000000015e-006;
createNode animCurveTA -n "Bip01_R_Calf_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.0000000000000004e-006;
createNode animCurveTL -n "Bip01_R_Calf_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Calf_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Calf_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.389784 0.792 0.389784 1.584 0.389784 
		2.4 0.389784 3.192 0.389784 3.984 0.389784 4.8 0.389784 5.592 0.389784 6.384 0.389784 
		7.2 0.389784 7.992 0.389784 8.784 0.389784 9.6 0.389784 10.392 0.389784 11.184 0.389784 
		12 0.389784 12.792 0.389784 13.584 0.389784 14.4 0.389784 15.192 0.389784 15.984 
		0.389784 16.8 0.389784 17.592 0.389784 18.384 0.389784 19.2 0.389784 19.992 0.389784 
		20.784 0.389784 21.6 0.389784 22.392 0.389784 23.184 0.389784 24 0.389784 24.792 
		0.389784 25.584 0.389784 26.4 0.389784 27.192 0.389784 27.984 0.389784 28.8 0.389784 
		29.592 0.389784 30.384 0.389784 31.2 0.389784 31.992 0.389784;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Thigh_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Thigh_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Thigh_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Thigh_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 145.759494 0.792 144.114484 1.584 143.336225 
		2.4 143.43779000000004 3.192 144.572475 3.984 146.9914 4.8 149.761206 5.592 153.831752 
		6.384 158.87042400000004 7.2 164.617645 7.992 170.802094 8.784 173.717943 9.6 176.027653 
		10.392 177.90551800000003 11.184 179.592124 12 181.31742900000003 12.792 183.591131 
		13.584 186.188419 14.4 188.669595 15.192 190.61081600000003 15.984 191.56361400000003 
		16.8 191.357001 17.592 190.33740400000002 18.384 188.71974200000002 19.2 186.706858 
		19.992 184.40012600000003 20.784 180.989676 21.6 176.72716000000003 22.392 172.014179 
		23.184 167.256789 24 162.86415800000003 24.792 158.528723 25.584 153.98188 26.4 149.69211200000004 
		27.192 146.127777 27.984 143.757483 28.8 142.93630300000004 29.592 143.353409 30.384 
		144.478888 31.2 145.782757 31.992 146.735132;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Thigh_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.781009 0.792 -0.314573 1.584 0.055879 
		2.4 0.350043 3.192 0.57867700000000011 3.984 0.748863 4.8 0.956167 5.592 1.108703 
		6.384 1.207273 7.2 1.2381020000000003 7.992 1.178883 8.784 1.086568 9.6 0.91348400000000007 
		10.392 0.65911300000000006 11.184 0.33022400000000007 12 -0.056896000000000009 12.792 
		-0.502386 13.584 -0.985247 14.4 -1.4712090000000002 15.192 -1.902613 15.984 -2.204957 
		16.8 -2.2256170000000006 17.592 -2.136015 18.384 -1.924817 19.2 -1.5949260000000003 
		19.992 -1.158572 20.784 -1.036012 21.6 -0.833077 22.392 -0.61416900000000008 23.184 
		-0.425188 24 -0.29701000000000005 24.792 -0.26842700000000008 25.584 -0.32426000000000005 
		26.4 -0.41050100000000006 27.192 -0.481805 27.984 -0.50420000000000009 28.8 -0.50843900000000009 
		29.592 -0.54586900000000016 30.384 -0.617032 31.2 -0.71493300000000015 31.992 -0.82433800000000013;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Thigh_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -176.227217 0.792 -176.59220900000003 
		1.584 -176.980888 2.4 -177.37448400000002 3.192 -177.75493900000004 3.984 -178.100711 
		4.8 -178.43048600000003 5.592 -178.68056700000002 6.384 -178.822047 7.2 -178.846376 
		7.992 -178.76914000000002 8.784 -178.722449 9.6 -178.673654 10.392 -178.59049000000002 
		11.184 -178.432194 12 -178.15304400000002 12.792 -177.701609 13.584 -177.13243600000004 
		14.4 -176.550886 15.192 -176.05317100000002 15.984 -175.720049 16.8 -175.54152100000002 
		17.592 -175.43827600000003 18.384 -175.43249800000004 19.2 -175.561766 19.992 -175.877211 
		20.784 -176.20316100000002 21.6 -176.62328600000004 22.392 -177.05369800000003 23.184 
		-177.418607 24 -177.64976800000002 24.792 -177.738711 25.584 -177.724928 26.4 -177.627515 
		27.192 -177.478153 27.984 -177.31705600000004 28.8 -177.142367 29.592 -176.93593100000004 
		30.384 -176.714046 31.2 -176.489141 31.992 -176.26791200000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.074914 0.792 -0.076409 1.584 -0.077947 
		2.4 -0.079508 3.192 -0.081072 3.984 -0.082620000000000013 4.8 -0.084132 5.592 -0.085589 
		6.384 -0.086974 7.2 -0.088266 7.992 -0.089448000000000014 8.784 -0.090599000000000013 
		9.6 -0.091809 10.392 -0.09300499999999999 11.184 -0.094147 12 -0.095187 12.792 -0.096079 
		13.584 -0.096779000000000018 14.4 -0.097243 15.192 -0.097428000000000015 15.984 -0.097288 
		16.8 -0.096737 17.592 -0.095778 18.384 -0.094464 19.2 -0.092897 19.992 -0.091152 
		20.784 -0.089311000000000015 21.6 -0.087468 22.392 -0.085718 23.184 -0.084156 24 
		-0.082873 24.792 -0.081823000000000021 25.584 -0.080885 26.4 -0.080039 27.192 -0.079262 
		27.984 -0.078535 28.8 -0.077835 29.592 -0.077144 30.384 -0.07644 31.2 -0.075703 31.992 
		-0.074914;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.037198 0.792 0.037242 1.584 0.037284 
		2.4 0.037326 3.192 0.037366 3.984 0.037407 4.8 0.037452 5.592 0.037503 6.384 0.037558 
		7.2 0.037613 7.992 0.037666 8.784 0.037727 9.6 0.037802 10.392 0.037885 11.184 0.037972 
		12 0.038058 12.792 0.038138 13.584 0.038207 14.4 0.038261 15.192 0.038296 15.984 
		0.038306 16.8 0.03829 17.592 0.038251 18.384 0.038188 19.2 0.038102 19.992 0.037997 
		20.784 0.037865 21.6 0.037714 22.392 0.037566 23.184 0.03744 24 0.037356 24.792 0.037308 
		25.584 0.037272 26.4 0.037248 27.192 0.037232 27.984 0.037223 28.8 0.037218 29.592 
		0.037216 30.384 0.037213 31.2 0.037208 31.992 0.037198;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.133001 0.792 -0.132561 1.584 -0.132085 
		2.4 -0.131572 3.192 -0.131025 3.984 -0.130446 4.8 -0.129882 5.592 -0.129354 6.384 
		-0.128821 7.2 -0.128248 7.992 -0.127595 8.784 -0.126838 9.6 -0.125983 10.392 -0.125084 
		11.184 -0.124179 12 -0.12331100000000002 12.792 -0.122527 13.584 -0.121871 14.4 -0.121391 
		15.192 -0.12113200000000002 15.984 -0.12114 16.8 -0.121492 17.592 -0.122152 18.384 
		-0.123014 19.2 -0.12394500000000001 19.992 -0.12483100000000001 20.784 -0.125453 
		21.6 -0.125774 22.392 -0.125958 23.184 -0.126171 24 -0.126586 24.792 -0.127173 25.584 
		-0.127785 26.4 -0.128417 27.192 -0.129066 27.984 -0.129727 28.8 -0.130394 29.592 
		-0.131062 30.384 -0.131723 31.2 -0.132372 31.992 -0.133001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Toe0_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Toe0_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Toe0_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Toe0_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 44 ".ktv[0:43]"  0 117.41688800000001 0.792 117.18608200000001 
		1.584 116.58187000000001 2.4 115.83498900000001 3.192 115.230763 3.984 114.99995700000001 
		4.8 111.227207 5.184 106.288645 5.592 101.350084 6 95.245699 6.384 89.141313 6.792 
		84.202766 7.2 79.264232000000021 7.992 75.491536000000011 8.784 75.679578 9.6 76.177826 
		10.392 76.78643 11.184 77.275492000000014 12 77.461574000000013 12.792 78.662752000000012 
		13.584 81.80276 14.4 85.676263 15.192 88.805459 15.984 89.999977000000015 16.8 89.999977000000015 
		17.592 89.999970000000019 18.384 89.999977000000015 19.2 89.999977000000015 19.992 
		89.999970000000019 20.784 90.108905000000007 21.6 90.394086000000016 22.392 90.746592 
		23.184 91.031773 24 91.140694000000011 24.792 93.758732000000009 25.584 96.645478000000011 
		26.4 99.683491 27.192 102.702591 27.984 105.528159 28.8 109.64795100000002 29.592 
		113.21664300000002 30.384 115.999323 31.2 117.564269 31.992 117.41688800000001;
	setAttr -s 44 ".kit[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
	setAttr -s 44 ".kot[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
createNode animCurveTA -n "Bip01_L_Toe0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 44 ".ktv[0:43]"  0 -4.2000000000000011e-005 0.792 -3.5999999999999994e-005 
		1.584 -3.7e-005 2.4 -3.3000000000000009e-005 3.192 -2.9e-005 3.984 -2.7e-005 4.8 
		-3.3000000000000009e-005 5.184 -3.1000000000000008e-005 5.592 -2.7999999999999996e-005 
		6 -3.1000000000000008e-005 6.384 -3.3000000000000009e-005 6.792 -3.3000000000000009e-005 
		7.2 -3.3000000000000009e-005 7.992 -3.500000000000001e-005 8.784 0.332359 9.6 1.218606 
		10.392 2.311644 11.184 3.1979630000000006 12 3.5369600000000005 12.792 3.208317 13.584 
		2.33722 14.4 1.2422560000000002 15.192 0.344877 15.984 1.0000000000000004e-006 16.8 
		-3.0000000000000005e-006 17.592 -2.0000000000000008e-006 18.384 -2.0000000000000008e-006 
		19.2 -4.0000000000000015e-006 19.992 1.0000000000000004e-006 20.784 0 21.6 0 22.392 
		0 23.184 2.0000000000000008e-006 24 3.0000000000000005e-006 24.792 0.165117 25.584 
		0.48608400000000007 26.4 0.726287 27.192 0.646858 27.984 0.009693000000000002 28.8 
		-0.372882 29.592 0.20388500000000004 30.384 1.029643 31.2 1.1883240000000002 31.992 
		-3.9e-005;
	setAttr -s 44 ".kit[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
	setAttr -s 44 ".kot[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
createNode animCurveTA -n "Bip01_L_Toe0_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 44 ".ktv[0:43]"  0 -2.4000000000000004e-005 0.792 -2.6000000000000002e-005 
		1.584 -2.4000000000000004e-005 2.4 -2.1000000000000006e-005 3.192 -2.1000000000000006e-005 
		3.984 -2.3e-005 4.8 -1.9000000000000004e-005 5.184 -1.6000000000000006e-005 5.592 
		-1.3000000000000001e-005 6 -7.0000000000000024e-006 6.384 0 6.792 2.0000000000000008e-006 
		7.2 4.0000000000000015e-006 7.992 5e-006 8.784 -0.086225 9.6 -0.31049 10.392 -0.57598400000000016 
		11.184 -0.78242100000000014 12 -0.85932000000000008 12.792 -0.743909 13.584 -0.47477700000000006 
		14.4 -0.20888 15.192 -0.048355000000000009 15.984 -4.0000000000000015e-006 16.8 -2.0000000000000008e-006 
		17.592 0 18.384 -1.0000000000000004e-006 19.2 -1.0000000000000004e-006 19.992 -1.0000000000000004e-006 
		20.784 1.0000000000000004e-006 21.6 -2.0000000000000008e-006 22.392 5e-006 23.184 
		7.0000000000000024e-006 24 3.0000000000000005e-006 24.792 -0.028974000000000007 25.584 
		-0.082290000000000016 26.4 -0.10699400000000002 27.192 -0.077823000000000017 27.984 
		0.006099 28.8 0.142992 29.592 0.229663 30.384 0.22428700000000004 31.2 0.13212100000000002 
		31.992 -3.1000000000000008e-005;
	setAttr -s 44 ".kit[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
	setAttr -s 44 ".kot[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
createNode animCurveTL -n "Bip01_L_Toe0_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Toe0_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.12389;
createNode animCurveTL -n "Bip01_L_Toe0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.077676;
createNode animCurveTU -n "Bip01_L_Foot_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Foot_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Foot_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Foot_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 43 ".ktv[0:42]"  0 6.8710140000000006 0.792 5.088249 1.584 
		3.057717 2.4 -0.020074 3.192 -5.254393 3.6 -9.917265 3.984 -14.584941 4.8 -15.514207000000003 
		5.592 -15.088544000000002 6.384 -13.827955000000001 7.2 -12.246797 7.992 -10.854983 
		8.784 -9.6269770000000019 9.6 -8.199082 10.392 -6.6457300000000021 11.184 -5.004102 
		12 -3.30642 12.792 -1.3362480000000003 13.584 0.98110900000000012 14.4 3.3664090000000004 
		15.192 5.4874120000000008 15.984 7.006298000000001 16.392 11.638865 16.8 16.270862000000005 
		17.592 17.13082 18.384 13.685044000000001 19.2 9.333807 19.992 7.438764 20.784 8.849111 
		21.6 10.824864999999999 22.392 12.569472 23.184 13.342993 24 12.55642 24.792 11.012227000000001 
		25.584 9.150552 26.4 7.219396 27.192 5.530935 27.984 4.4086150000000011 28.8 3.4051400000000003 
		29.592 3.166173 30.384 3.60702 31.2 4.797208 31.992 6.8704690000000008;
	setAttr -s 43 ".kit[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
	setAttr -s 43 ".kot[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
createNode animCurveTA -n "Bip01_L_Foot_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 43 ".ktv[0:42]"  0 -1.8993700000000004 0.792 -2.4774280000000006 
		1.584 -3.0274470000000004 2.4 -3.6171820000000006 3.192 -4.2597130000000005 3.6 -4.6084360000000011 
		3.984 -4.920091 4.8 -5.019395 5.592 -5.124527 6.384 -5.174241 7.2 -5.105341 7.992 
		-4.8724370000000006 8.784 -4.576163 9.6 -4.2453950000000011 10.392 -3.779788 11.184 
		-3.1203590000000005 12 -2.280974 12.792 -1.251697 13.584 -0.39707200000000004 14.4 
		-0.073077 15.192 -0.191125 15.984 -0.366932 16.392 -0.537237 16.8 -0.725852 17.592 
		-0.270187 18.384 0.508262 19.2 1.111627 19.992 1.2826910000000002 20.784 1.0923380000000003 
		21.6 0.813184 22.392 0.578075 23.184 0.45723500000000006 24 0.472156 24.792 0.647736 
		25.584 0.8694400000000001 26.4 1.086527 27.192 1.2265640000000002 27.984 1.1991360000000002 
		28.8 0.9324340000000001 29.592 0.349124 30.384 -0.4536730000000001 31.2 -1.2913570000000003 
		31.992 -1.8972190000000002;
	setAttr -s 43 ".kit[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
	setAttr -s 43 ".kot[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
createNode animCurveTA -n "Bip01_L_Foot_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 43 ".ktv[0:42]"  0 -7.6183860000000019 0.792 -6.907335 1.584 
		-6.056437 2.4 -5.1208229999999988 3.192 -4.161239000000001 3.6 -3.7183740000000003 
		3.984 -3.2483100000000005 4.8 -2.9404070000000004 5.592 -2.9657960000000005 6.384 
		-3.151522 7.2 -3.3353300000000004 7.992 -3.351445 8.784 -3.313382 9.6 -3.333382 10.392 
		-3.2155840000000007 11.184 -2.745743 12 -1.714875 12.792 0.265449 13.584 3.0785680000000006 
		14.4 6.042251 15.192 8.4983410000000017 15.984 9.959919 16.392 10.193520000000001 
		16.8 10.412612000000001 17.592 10.156249 18.384 9.365496000000002 19.2 8.293618 19.992 
		7.3086 20.784 6.4949140000000005 21.6 5.687254 22.392 4.9244950000000012 23.184 4.249601 
		24 3.6929990000000004 24.792 3.341643 25.584 3.1411390000000003 26.4 2.897951 27.192 
		2.426681 27.984 1.5515500000000002 28.8 0.158776 29.592 -1.626522 30.384 -3.6281410000000007 
		31.2 -5.674584 31.992 -7.5985940000000012;
	setAttr -s 43 ".kit[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
	setAttr -s 43 ".kot[0:42]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		2;
createNode animCurveTL -n "Bip01_L_Foot_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Foot_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Foot_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.422138 0.792 0.422138 1.584 0.422138 
		2.4 0.422138 3.192 0.422138 3.984 0.422138 4.8 0.422138 5.592 0.422138 6.384 0.422138 
		7.2 0.422138 7.992 0.422138 8.784 0.422138 9.6 0.422138 10.392 0.422138 11.184 0.422138 
		12 0.422138 12.792 0.422138 13.584 0.422138 14.4 0.422138 15.192 0.422138 15.984 
		0.422138 16.8 0.422138 17.592 0.422138 18.384 0.422138 19.2 0.422138 19.992 0.422138 
		20.784 0.422138 21.6 0.422138 22.392 0.422138 23.184 0.422138 24 0.422138 24.792 
		0.422138 25.584 0.422138 26.4 0.422138 27.192 0.422138 27.984 0.422138 28.8 0.422138 
		29.592 0.422138 30.384 0.422138 31.2 0.422138 31.992 0.422138;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Calf_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Calf_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Calf_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Calf_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 45 ".ktv[0:44]"  0 -27.361724 0.792 -30.171051000000002 
		1.584 -32.90397 2.4 -35.675767000000008 3.192 -38.59750600000001 3.984 -41.785859 
		4.8 -45.672926000000004 5.592 -50.183665000000005 6.384 -54.666492000000005 7.2 -58.46979000000001 
		7.992 -60.941963000000015 8.784 -62.307619 9.6 -63.021729 10.392 -62.716515 11.184 
		-61.051629000000013 12 -57.679893000000007 12.792 -51.037028000000007 13.2 -46.19578 
		13.584 -41.354532000000006 13.992 -36.166639000000011 14.4 -30.978745 14.784 -26.617411000000004 
		15.192 -22.256078 15.984 -17.532888 16.392 -22.603036 16.8 -27.673186 17.592 -33.038511 
		18.384 -36.112530000000007 19.2 -37.579999000000008 19.992 -38.266631 20.784 -38.243600000000008 
		21.6 -36.572519000000007 22.392 -33.439757 23.184 -29.121534000000004 24 -24.158431000000004 
		24.792 -21.999814 25.584 -19.949134000000004 26.4 -18.262137000000003 27.192 -17.190887 
		27.984 -16.990504 28.8 -17.943242000000005 29.592 -19.877203000000005 30.384 -22.370308 
		31.2 -25.006342 31.992 -27.361969000000002;
	setAttr -s 45 ".kit[0:44]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 2;
	setAttr -s 45 ".kot[0:44]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 2;
createNode animCurveTA -n "Bip01_L_Calf_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 45 ".ktv[0:44]"  0 7.0000000000000024e-006 0.792 -1.0000000000000004e-006 
		1.584 -4.0000000000000015e-006 2.4 -2.0000000000000008e-006 3.192 -4.0000000000000015e-006 
		3.984 1.0000000000000004e-006 4.8 0 5.592 0 6.384 -1.0000000000000004e-006 7.2 1.0000000000000004e-006 
		7.992 1.0000000000000004e-006 8.784 -2.0000000000000008e-006 9.6 0 10.392 3.0000000000000005e-006 
		11.184 -2.0000000000000008e-006 12 -1.0000000000000004e-006 12.792 2.0000000000000008e-006 
		13.2 -1.0000000000000004e-006 13.584 -4.0000000000000015e-006 13.992 0 14.4 4.0000000000000015e-006 
		14.784 2.0000000000000008e-006 15.192 0 15.984 1.0000000000000004e-006 16.392 3.0000000000000005e-006 
		16.8 6.000000000000001e-006 17.592 0 18.384 -6.000000000000001e-006 19.2 -1.0000000000000004e-006 
		19.992 1.0000000000000004e-006 20.784 4.0000000000000015e-006 21.6 -2.0000000000000008e-006 
		22.392 2.0000000000000008e-006 23.184 2.0000000000000008e-006 24 -3.0000000000000005e-006 
		24.792 1.0000000000000004e-006 25.584 -1.0000000000000004e-006 26.4 4.0000000000000015e-006 
		27.192 7.0000000000000024e-006 27.984 -5e-006 28.8 -2.0000000000000008e-006 29.592 
		-4.0000000000000015e-006 30.384 1.0000000000000004e-006 31.2 -3.0000000000000005e-006 
		31.992 -5e-006;
	setAttr -s 45 ".kit[0:44]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 2;
	setAttr -s 45 ".kot[0:44]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 2;
createNode animCurveTA -n "Bip01_L_Calf_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -4.0000000000000015e-006;
createNode animCurveTL -n "Bip01_L_Calf_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Calf_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Calf_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.389784;
createNode animCurveTU -n "Bip01_L_Thigh_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Thigh_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Thigh_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Thigh_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -177.85419600000003 0.792 -176.955275 
		1.584 -176.08348300000003 2.4 -175.44979200000003 3.192 -175.367064 3.984 -176.388178 
		4.8 -179.10316400000002 5.592 -183.059059 6.384 -187.737779 7.2 -192.618154 7.992 
		-197.17673100000002 8.784 -201.84748800000003 9.6 -207.076913 10.392 -212.07422 11.184 
		-216.170421 12 -218.65860400000003 12.792 -218.90471 13.584 -217.371701 14.4 -214.996995 
		15.192 -212.71787000000003 15.984 -211.469626 16.8 -214.89409100000003 17.592 -216.29378800000003 
		18.384 -216.631759 19.2 -215.96834300000003 19.992 -214.445238 20.784 -211.77642400000002 
		21.6 -207.994439 22.392 -203.412175 23.184 -198.370157 24 -193.31893200000002 24.792 
		-190.103128 25.584 -187.08826900000003 26.4 -184.389621 27.192 -182.10844700000004 
		27.984 -180.34463300000002 28.8 -178.37387700000002 29.592 -177.26177200000004 30.384 
		-176.879842 31.2 -177.118202 31.992 -177.85403200000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Thigh_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 2.4842360000000006 0.792 2.5589350000000004 
		1.584 2.578326 2.4 2.5341180000000003 3.192 2.4272240000000003 3.984 2.2642810000000004 
		4.8 2.052427 5.592 1.729877 6.384 1.4116150000000003 7.2 1.196602 7.992 1.1680850000000003 
		8.784 1.44438 9.6 1.9675900000000002 10.392 2.535579 11.184 2.9898780000000005 12 
		3.2096350000000005 12.792 3.1478330000000003 13.584 2.8922230000000004 14.4 2.5271620000000006 
		15.192 2.1291700000000002 15.984 1.7820900000000002 16.8 1.294343 17.592 0.93430300000000011 
		18.384 0.62626 19.2 0.34350500000000006 19.992 0.065341 20.784 -0.212377 21.6 -0.45166700000000004 
		22.392 -0.64093300000000009 23.184 -0.763163 24 -0.79989500000000013 24.792 -0.75702 
		25.584 -0.646742 26.4 -0.458709 27.192 -0.185437 27.984 0.17583600000000002 28.8 
		0.64857400000000009 29.592 1.1526190000000003 30.384 1.643754 31.2 2.0911770000000005 
		31.992 2.4793370000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Thigh_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 176.91206700000004 0.792 176.894718 1.584 
		176.85492500000004 2.4 176.85518500000003 3.192 176.935713 3.984 177.108981 4.8 177.346166 
		5.592 177.653019 6.384 177.967509 7.2 178.221469 7.992 178.339289 8.784 178.25277800000003 
		9.6 177.9524 10.392 177.500433 11.184 177.01207400000004 12 176.645416 12.792 176.508594 
		13.584 176.559219 14.4 176.726777 15.192 176.938909 15.984 177.136438 16.8 177.25712800000002 
		17.592 177.520705 18.384 177.877855 19.2 178.29589 19.992 178.733897 20.784 179.156863 
		21.6 179.50883600000003 22.392 179.74432700000003 23.184 179.85124700000003 24 179.852613 
		24.792 179.84436200000002 25.584 179.82790200000002 26.4 179.77063700000002 27.192 
		179.63861000000003 27.984 179.39526400000003 28.8 179.01892 29.592 178.546558 30.384 
		178.016877 31.2 177.45879600000004 31.992 176.892833;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.095144 0.792 0.093716 1.584 0.092241 
		2.4 0.090736 3.192 0.089221000000000009 3.984 0.087713 4.8 0.08623 5.592 0.084793 
		6.384 0.083421000000000009 7.2 0.082133 7.992 0.080949 8.784 0.079784 9.6 0.078545 
		10.392 0.077303 11.184 0.076101 12 0.07499 12.792 0.074022 13.584 0.07325 14.4 0.072729 
		15.192 0.072511 15.984 0.072651 16.8 0.073244 17.592 0.074278 18.384 0.07568 19.2 
		0.077327 19.992 0.079135 20.784 0.081011000000000014 21.6 0.082867 22.392 0.084623 
		23.184 0.086194 24 0.087493 24.792 0.08856 25.584 0.089507000000000017 26.4 0.090352 
		27.192 0.091117 27.984 0.091821 28.8 0.092484 29.592 0.093128000000000016 30.384 
		0.093771 31.2 0.094437 31.992 0.095144;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.039682 0.792 0.039583 1.584 0.039478 
		2.4 0.039369 3.192 0.039261 3.984 0.039157 4.8 0.039058 5.592 0.038966 6.384 0.038889 
		7.2 0.038833 7.992 0.038805 8.784 0.038808 9.6 0.038839 10.392 0.038891 11.184 0.038958 
		12 0.039033 12.792 0.039111 13.584 0.039184 14.4 0.039245 15.192 0.039289 15.984 
		0.039308 16.8 0.039297 17.592 0.039263 18.384 0.039213 19.2 0.03916 19.992 0.039111 
		20.784 0.039084 21.6 0.039083 22.392 0.039099 23.184 0.039121 24 0.039142 24.792 
		0.039166 25.584 0.039203 26.4 0.03925 27.192 0.039304 27.984 0.039365 28.8 0.039429 
		29.592 0.039495 30.384 0.039561 31.2 0.039623 31.992 0.039682;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.122438 0.792 -0.12310800000000001 
		1.584 -0.12379 2.4 -0.124475 3.192 -0.125159 3.984 -0.125836 4.8 -0.126458 5.592 
		-0.127006 6.384 -0.127521 7.2 -0.128047 7.992 -0.128624 8.784 -0.129275 9.6 -0.129983 
		10.392 -0.130704 11.184 -0.131408 12 -0.132066 12.792 -0.13265 13.584 -0.133131 14.4 
		-0.133483 15.192 -0.133679 15.984 -0.13369 16.8 -0.133454 17.592 -0.132992 18.384 
		-0.132378 19.2 -0.131705 19.992 -0.131057 20.784 -0.13063 21.6 -0.130447 22.392 -0.130343 
		23.184 -0.130154 24 -0.129724 24.792 -0.129097 25.584 -0.128429 26.4 -0.127727 27.192 
		-0.127 27.984 -0.126254 28.8 -0.125494 29.592 -0.12472800000000002 30.384 -0.12396000000000001 
		31.2 -0.123195 31.992 -0.122438;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Finger11_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger11_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger11_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger11_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 30.522184;
createNode animCurveTA -n "Bip01_L_Finger11_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -2.0000000000000008e-006 0.792 -3.0000000000000005e-006 
		1.584 1.0000000000000004e-006 2.4 -2.0000000000000008e-006 3.192 -2.0000000000000008e-006 
		3.984 5e-006 4.8 -4.0000000000000015e-006 5.592 -4.0000000000000015e-006 6.384 -6.000000000000001e-006 
		7.2 -1.0000000000000004e-006 7.992 -3.0000000000000005e-006 8.784 2.0000000000000008e-006 
		9.6 -2.0000000000000008e-006 10.392 -4.0000000000000015e-006 11.184 -1.0000000000000004e-006 
		12 -2.0000000000000008e-006 12.792 -2.0000000000000008e-006 13.584 -1.0000000000000004e-006 
		14.4 -1.0000000000000004e-006 15.192 3.0000000000000005e-006 15.984 3.0000000000000005e-006 
		16.8 1.0000000000000004e-006 17.592 -2.0000000000000008e-006 18.384 0 19.2 -2.0000000000000008e-006 
		19.992 -1.0000000000000004e-006 20.784 0 21.6 -1.0000000000000004e-006 22.392 -3.0000000000000005e-006 
		23.184 8.000000000000003e-006 24 4.0000000000000015e-006 24.792 -3.0000000000000005e-006 
		25.584 1.0000000000000004e-006 26.4 0 27.192 3.0000000000000005e-006 27.984 -4.0000000000000015e-006 
		28.8 -5e-006 29.592 5e-006 30.384 -2.0000000000000008e-006 31.2 5e-006 31.992 -1.0000000000000004e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.0000000000000004e-006;
createNode animCurveTL -n "Bip01_L_Finger11_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger11_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger11_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.046167 0.792 0.046167 1.584 0.046167 
		2.4 0.046167 3.192 0.046167 3.984 0.046167 4.8 0.046167 5.592 0.046167 6.384 0.046167 
		7.2 0.046167 7.992 0.046167 8.784 0.046167 9.6 0.046167 10.392 0.046167 11.184 0.046167 
		12 0.046167 12.792 0.046167 13.584 0.046167 14.4 0.046167 15.192 0.046167 15.984 
		0.046167 16.8 0.046167 17.592 0.046167 18.384 0.046167 19.2 0.046167 19.992 0.046167 
		20.784 0.046167 21.6 0.046167 22.392 0.046167 23.184 0.046167 24 0.046167 24.792 
		0.046167 25.584 0.046167 26.4 0.046167 27.192 0.046167 27.984 0.046167 28.8 0.046167 
		29.592 0.046167 30.384 0.046167 31.2 0.046167 31.992 0.046167;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Finger1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 18.172223000000002;
createNode animCurveTA -n "Bip01_L_Finger1_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 6.98037;
createNode animCurveTA -n "Bip01_L_Finger1_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.316989 0.792 0.316992 1.584 0.31699600000000006 
		2.4 0.31699 3.192 0.31699600000000006 3.984 0.31699600000000006 4.8 0.316994 5.592 
		0.316994 6.384 0.316991 7.2 0.316995 7.992 0.31699800000000006 8.784 0.316995 9.6 
		0.316994 10.392 0.316994 11.184 0.316993 12 0.316991 12.792 0.316993 13.584 0.31699800000000006 
		14.4 0.31699 15.192 0.316993 15.984 0.316993 16.8 0.316992 17.592 0.316991 18.384 
		0.31699800000000006 19.2 0.316995 19.992 0.31699800000000006 20.784 0.316999 21.6 
		0.316993 22.392 0.316993 23.184 0.31699700000000003 24 0.31699600000000006 24.792 
		0.316993 25.584 0.316988 26.4 0.316995 27.192 0.31699800000000006 27.984 0.316989 
		28.8 0.316993 29.592 0.316999 30.384 0.316989 31.2 0.31699600000000006 31.992 0.316992;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger1_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.033041 0.792 -0.033041 1.584 -0.033041 
		2.4 -0.033041 3.192 -0.033041 3.984 -0.033041 4.8 -0.033041 5.592 -0.033041 6.384 
		-0.033041 7.2 -0.033041 7.992 -0.033041 8.784 -0.033041 9.6 -0.033041 10.392 -0.033041 
		11.184 -0.033041 12 -0.033041 12.792 -0.033041 13.584 -0.033041 14.4 -0.033041 15.192 
		-0.033041 15.984 -0.033041 16.8 -0.033041 17.592 -0.033041 18.384 -0.033041 19.2 
		-0.033041 19.992 -0.033041 20.784 -0.033041 21.6 -0.033041 22.392 -0.033041 23.184 
		-0.033041 24 -0.033041 24.792 -0.033041 25.584 -0.033041 26.4 -0.033041 27.192 -0.033041 
		27.984 -0.033041 28.8 -0.033041 29.592 -0.033041 30.384 -0.033041 31.2 -0.033041 
		31.992 -0.033041;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger1_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.0012200000000000002 0.792 0.0012200000000000002 
		1.584 0.0012200000000000002 2.4 0.0012200000000000002 3.192 0.0012200000000000002 
		3.984 0.0012200000000000002 4.8 0.0012200000000000002 5.592 0.0012200000000000002 
		6.384 0.0012200000000000002 7.2 0.0012200000000000002 7.992 0.0012200000000000002 
		8.784 0.0012200000000000002 9.6 0.0012200000000000002 10.392 0.0012200000000000002 
		11.184 0.0012200000000000002 12 0.0012200000000000002 12.792 0.0012200000000000002 
		13.584 0.0012200000000000002 14.4 0.0012200000000000002 15.192 0.0012200000000000002 
		15.984 0.0012200000000000002 16.8 0.0012200000000000002 17.592 0.0012200000000000002 
		18.384 0.0012200000000000002 19.2 0.0012200000000000002 19.992 0.0012200000000000002 
		20.784 0.0012200000000000002 21.6 0.0012200000000000002 22.392 0.0012200000000000002 
		23.184 0.0012200000000000002 24 0.0012200000000000002 24.792 0.0012200000000000002 
		25.584 0.0012200000000000002 26.4 0.0012200000000000002 27.192 0.0012200000000000002 
		27.984 0.0012200000000000002 28.8 0.0012200000000000002 29.592 0.0012200000000000002 
		30.384 0.0012200000000000002 31.2 0.0012200000000000002 31.992 0.0012200000000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.094277;
createNode animCurveTU -n "Bip01_L_Finger21_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger21_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger21_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger21_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 34.58505;
createNode animCurveTA -n "Bip01_L_Finger21_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_L_Finger21_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
createNode animCurveTL -n "Bip01_L_Finger21_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger21_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger21_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.047592 0.792 0.047592 1.584 0.047592 
		2.4 0.047592 3.192 0.047592 3.984 0.047592 4.8 0.047592 5.592 0.047592 6.384 0.047592 
		7.2 0.047592 7.992 0.047592 8.784 0.047592 9.6 0.047592 10.392 0.047592 11.184 0.047592 
		12 0.047592 12.792 0.047592 13.584 0.047592 14.4 0.047592 15.192 0.047592 15.984 
		0.047592 16.8 0.047592 17.592 0.047592 18.384 0.047592 19.2 0.047592 19.992 0.047592 
		20.784 0.047592 21.6 0.047592 22.392 0.047592 23.184 0.047592 24 0.047592 24.792 
		0.047592 25.584 0.047592 26.4 0.047592 27.192 0.047592 27.984 0.047592 28.8 0.047592 
		29.592 0.047592 30.384 0.047592 31.2 0.047592 31.992 0.047592;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Finger2_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger2_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger2_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger2_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 26.614676000000003;
createNode animCurveTA -n "Bip01_L_Finger2_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.492356 0.792 -4.4923600000000006 1.584 
		-4.492357 2.4 -4.492354 3.192 -4.492353 3.984 -4.492353 4.8 -4.492351 5.592 -4.492353 
		6.384 -4.492351 7.2 -4.492344000000001 7.992 -4.4923490000000008 8.784 -4.492356 
		9.6 -4.492353 10.392 -4.492348 11.184 -4.492353 12 -4.492348 12.792 -4.4923490000000008 
		13.584 -4.492348 14.4 -4.492347 15.192 -4.492347 15.984 -4.4923490000000008 16.8 
		-4.492352 17.592 -4.492350000000001 18.384 -4.492352 19.2 -4.492344000000001 19.992 
		-4.492353 20.784 -4.492348 21.6 -4.492353 22.392 -4.492352 23.184 -4.492351 24 -4.492352 
		24.792 -4.492353 25.584 -4.492352 26.4 -4.4923490000000008 27.192 -4.492351 27.984 
		-4.492351 28.8 -4.492356 29.592 -4.492348 30.384 -4.492350000000001 31.2 -4.492345 
		31.992 -4.492353;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger2_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.1001960000000002 0.792 -1.100192 1.584 
		-1.100192 2.4 -1.1001960000000002 3.192 -1.100191 3.984 -1.100189 4.8 -1.100191 5.592 
		-1.1001930000000002 6.384 -1.1001930000000002 7.2 -1.100186 7.992 -1.1001880000000002 
		8.784 -1.1001930000000002 9.6 -1.1001900000000002 10.392 -1.100192 11.184 -1.100191 
		12 -1.1001960000000002 12.792 -1.100192 13.584 -1.100191 14.4 -1.1001930000000002 
		15.192 -1.1001930000000002 15.984 -1.100192 16.8 -1.1001970000000003 17.592 -1.100192 
		18.384 -1.100189 19.2 -1.1001900000000002 19.992 -1.100192 20.784 -1.1001900000000002 
		21.6 -1.1001880000000002 22.392 -1.100191 23.184 -1.100194 24 -1.100192 24.792 -1.1001960000000002 
		25.584 -1.1001900000000002 26.4 -1.100191 27.192 -1.100186 27.984 -1.1001930000000002 
		28.8 -1.1001930000000002 29.592 -1.100189 30.384 -1.1001970000000003 31.2 -1.1001900000000002 
		31.992 -1.100191;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger2_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.013128000000000003;
createNode animCurveTL -n "Bip01_L_Finger2_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.006931 0.792 -0.006931 1.584 -0.006931 
		2.4 -0.006931 3.192 -0.006931 3.984 -0.006931 4.8 -0.006931 5.592 -0.006931 6.384 
		-0.006931 7.2 -0.006931 7.992 -0.006931 8.784 -0.006931 9.6 -0.006931 10.392 -0.006931 
		11.184 -0.006931 12 -0.006931 12.792 -0.006931 13.584 -0.006931 14.4 -0.006931 15.192 
		-0.006931 15.984 -0.006931 16.8 -0.006931 17.592 -0.006931 18.384 -0.006931 19.2 
		-0.006931 19.992 -0.006931 20.784 -0.006931 21.6 -0.006931 22.392 -0.006931 23.184 
		-0.006931 24 -0.00693 24.792 -0.00693 25.584 -0.006931 26.4 -0.00693 27.192 -0.006931 
		27.984 -0.00693 28.8 -0.00693 29.592 -0.00693 30.384 -0.006931 31.2 -0.006931 31.992 
		-0.006931;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger2_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.094671;
createNode animCurveTU -n "Bip01_L_Finger01_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger01_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger01_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger01_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 27.538836000000003;
createNode animCurveTA -n "Bip01_L_Finger01_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_L_Finger01_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
createNode animCurveTL -n "Bip01_L_Finger01_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger01_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger01_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.051997;
createNode animCurveTU -n "Bip01_L_Finger0_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger0_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Finger0_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Finger0_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 20.062802000000005;
createNode animCurveTA -n "Bip01_L_Finger0_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 27.870976000000002;
createNode animCurveTA -n "Bip01_L_Finger0_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 82.611694000000014;
createNode animCurveTL -n "Bip01_L_Finger0_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.042679;
createNode animCurveTL -n "Bip01_L_Finger0_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.018544 0.792 0.018544 1.584 0.018544 
		2.4 0.018544 3.192 0.018544 3.984 0.018544 4.8 0.018544 5.592 0.018544 6.384 0.018544 
		7.2 0.018544 7.992 0.018544 8.784 0.018544 9.6 0.018544 10.392 0.018544 11.184 0.018544 
		12 0.018544 12.792 0.018544 13.584 0.018544 14.4 0.018544 15.192 0.018544 15.984 
		0.018544 16.8 0.018544 17.592 0.018544 18.384 0.018544 19.2 0.018544 19.992 0.018544 
		20.784 0.018544 21.6 0.018544 22.392 0.018544 23.184 0.018544 24 0.018544 24.792 
		0.018544 25.584 0.018544 26.4 0.018544 27.192 0.018544 27.984 0.018544 28.8 0.018544 
		29.592 0.018544 30.384 0.018544 31.2 0.018544 31.992 0.018544;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.030412000000000005;
createNode animCurveTU -n "Bip01_L_Hand_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Hand_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Hand_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Hand_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.012679000000000001 0.792 0.039436000000000006 
		1.584 0.119584 2.4 0.252836 3.192 0.43867600000000007 3.984 0.676419 4.8 0.96517300000000006 
		5.592 1.3038450000000001 6.384 1.691128 7.2 2.1254760000000004 7.992 2.605068 8.784 
		3.124379 9.6 3.6911549999999997 10.392 4.292379 11.184 4.928272 12 5.5952970000000013 
		12.792 6.289549 13.584 7.0067670000000009 14.4 7.7423050000000009 15.192 8.4910940000000021 
		15.984 9.2475630000000013 16.8 9.8165560000000021 17.592 10.513918000000002 18.384 
		11.293727000000002 19.2 12.081768 19.992 12.823144000000001 20.784 13.459465 21.6 
		13.93393 22.392 14.191642000000002 23.184 14.179773 24 13.847616 24.792 13.160126 
		25.584 12.157187000000002 26.4 10.901872 27.192 9.456266 27.984 7.880743 28.8 6.2334960000000006 
		29.592 4.570379 30.384 2.945006 31.2 1.409071 31.992 0.012684000000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Hand_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.339822 0.792 -0.323818 1.584 -0.276139 
		2.4 -0.19782200000000003 3.192 -0.090505 3.984 0.043576000000000004 4.8 0.20172 5.592 
		0.38086400000000004 6.384 0.577773 7.2 0.78914700000000015 7.992 1.011938 8.784 1.24201 
		9.6 1.4817400000000003 10.392 1.7256010000000002 11.184 1.9749720000000002 12 2.230969 
		12.792 2.4960310000000003 13.584 2.7738340000000004 14.4 3.069281 15.192 3.3881950000000005 
		15.984 3.737043 16.8 4.052572 17.592 4.502957 18.384 5.057878 19.2 5.667488 19.992 
		6.293163 20.784 6.8909130000000012 21.6 7.414238000000001 22.392 7.8140630000000009 
		23.184 8.039083 24 8.036228 24.792 7.785859 25.584 7.321658 26.4 6.6706580000000013 
		27.192 5.8618820000000005 27.984 4.926903 28.8 3.9001619999999995 29.592 2.8189820000000005 
		30.384 1.723389 31.2 0.655697 31.992 -0.33982500000000004;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Hand_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -72.945187 0.792 -72.902123 1.584 -72.772206 
		2.4 -72.5534 3.192 -72.242702 3.984 -71.836634 4.8 -71.332033 5.592 -70.726803 6.384 
		-70.020787 7.2 -69.216607 7.992 -68.320432 8.784 -67.348885 9.6 -66.297794 10.392 
		-65.205661 11.184 -64.090114000000014 12 -62.97917600000001 12.792 -61.904146 13.584 
		-60.898564 14.4 -59.996925 15.192 -59.233282 15.984 -58.639684000000017 16.8 -58.457407 
		17.592 -58.518380000000008 18.384 -58.78740100000001 19.2 -59.224506000000012 19.992 
		-59.796227 20.784 -60.47025 21.6 -61.216141000000007 22.392 -62.00446800000001 23.184 
		-62.805396 24 -63.58692700000001 24.792 -64.399036000000009 25.584 -65.298463 26.4 
		-66.259573 27.192 -67.257012 27.984 -68.267348000000013 28.8 -69.270272 29.592 -70.249380000000016 
		30.384 -71.192656 31.2 -72.092438 31.992 -72.945187;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Hand_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Hand_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Hand_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.283498 0.792 0.283498 1.584 0.283498 
		2.4 0.283498 3.192 0.283498 3.984 0.283498 4.8 0.283498 5.592 0.283498 6.384 0.283498 
		7.2 0.283498 7.992 0.283498 8.784 0.283498 9.6 0.283498 10.392 0.283498 11.184 0.283498 
		12 0.283498 12.792 0.283498 13.584 0.283498 14.4 0.283498 15.192 0.283498 15.984 
		0.283498 16.8 0.283498 17.592 0.283498 18.384 0.283498 19.2 0.283498 19.992 0.283498 
		20.784 0.283498 21.6 0.283498 22.392 0.283498 23.184 0.283498 24 0.283498 24.792 
		0.283498 25.584 0.283498 26.4 0.283498 27.192 0.283498 27.984 0.283498 28.8 0.283498 
		29.592 0.283498 30.384 0.283498 31.2 0.283498 31.992 0.283498;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_Forearm_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Forearm_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Forearm_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Forearm_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -35.161972000000006 0.792 -35.126643000000008 
		1.584 -35.021298 2.4 -34.848009 3.192 -34.609916000000005 3.984 -34.311088000000005 
		4.8 -33.956068 5.592 -33.549495000000007 6.384 -33.095625000000005 7.2 -32.597937000000009 
		7.992 -32.058652 8.784 -31.482201000000003 9.6 -30.856201000000006 10.392 -30.188898 
		11.184 -29.471647000000004 12 -28.697878000000003 12.792 -27.859626000000002 13.584 
		-26.948028 14.4 -25.953932000000002 15.192 -24.868509 15.984 -23.684023000000003 
		16.8 -22.655272 17.592 -21.241313 18.384 -19.545389 19.2 -17.729831000000004 19.992 
		-15.917562000000002 20.784 -14.241379000000002 21.6 -12.834074 22.392 -11.828424000000002 
		23.184 -11.357211 24 -11.553236 24.792 -12.466652 25.584 -13.987654000000001 26.4 
		-16.00901 27.192 -18.423480000000005 27.984 -21.123887 28.8 -24.002984000000005 29.592 
		-26.953561000000004 30.384 -29.868405000000003 31.2 -32.640267000000009 31.992 -35.16197600000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Forearm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -6.000000000000001e-006 0.792 2.0000000000000008e-006 
		1.584 -2.0000000000000008e-006 2.4 -1.0000000000000004e-006 3.192 -2.0000000000000008e-006 
		3.984 2.0000000000000008e-006 4.8 0 5.592 3.0000000000000005e-006 6.384 -5e-006 7.2 
		-3.0000000000000005e-006 7.992 0 8.784 -5e-006 9.6 0 10.392 2.0000000000000008e-006 
		11.184 -1.0000000000000004e-006 12 3.0000000000000005e-006 12.792 -3.0000000000000005e-006 
		13.584 4.0000000000000015e-006 14.4 0 15.192 -1.0000000000000004e-006 15.984 3.0000000000000005e-006 
		16.8 2.0000000000000008e-006 17.592 3.0000000000000005e-006 18.384 1.0000000000000004e-006 
		19.2 1.0000000000000004e-006 19.992 1.0000000000000004e-006 20.784 -5e-006 21.6 -6.000000000000001e-006 
		22.392 -1.0000000000000004e-006 23.184 -6.000000000000001e-006 24 3.0000000000000005e-006 
		24.792 7.0000000000000024e-006 25.584 0 26.4 4.0000000000000015e-006 27.192 4.0000000000000015e-006 
		27.984 0 28.8 0 29.592 1.0000000000000004e-006 30.384 -4.0000000000000015e-006 31.2 
		4.0000000000000015e-006 31.992 1.0000000000000004e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Forearm_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Forearm_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Forearm_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Forearm_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.280821 0.792 0.280821 1.584 0.280821 
		2.4 0.280821 3.192 0.280821 3.984 0.280821 4.8 0.280821 5.592 0.280821 6.384 0.280821 
		7.2 0.280821 7.992 0.280821 8.784 0.280821 9.6 0.280821 10.392 0.280821 11.184 0.280821 
		12 0.280821 12.792 0.280821 13.584 0.280821 14.4 0.280821 15.192 0.280821 15.984 
		0.280821 16.8 0.280821 17.592 0.280821 18.384 0.280821 19.2 0.280821 19.992 0.280821 
		20.784 0.280821 21.6 0.280821 22.392 0.280821 23.184 0.280821 24 0.280821 24.792 
		0.280821 25.584 0.280821 26.4 0.280821 27.192 0.280821 27.984 0.280821 28.8 0.280821 
		29.592 0.280821 30.384 0.280821 31.2 0.280821 31.992 0.280821;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_L_UpperArm_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_UpperArm_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_UpperArm_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_UpperArm_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 49 ".ktv[0:48]"  0 -13.330061000000002 0.792 -13.759382000000002 
		1.584 -13.892521 2.4 -13.692691 3.192 -13.108969000000002 3.984 -12.076475000000002 
		4.8 -10.517764 5.592 -8.346282 6.384 -5.4735070000000006 7.2 -1.8220680000000002 
		7.992 2.6525480000000003 8.784 7.8940790000000005 9.6 13.987435000000001 10.392 20.729787 
		10.8 24.283509000000002 11.184 27.904583 11.592 31.500411000000003 12 35.117972 12.384 
		38.525536 12.792 41.912371000000007 13.584 47.872790000000009 14.4 52.695969 15.192 
		56.19043700000001 15.984 58.226690000000005 16.8 57.776403000000009 17.592 55.263317 
		18.384 50.721474 18.792 47.580021000000009 19.2 44.307626 19.584 40.35797 19.992 
		36.283435000000004 20.4 31.810976000000004 20.784 27.290513000000004 21.192 22.756118000000004 
		21.6 18.286895000000005 21.984 14.194112000000002 22.392 10.244408000000002 23.184 
		3.8387760000000006 24 -0.60766 24.792 -3.5874600000000005 25.584 -5.813984 26.4 -7.4671840000000005 
		27.192 -8.703089 27.984 -9.652658 28.8 -10.424512 29.592 -11.108704000000001 30.384 
		-11.780342 31.2 -12.502719000000003 31.992 -13.330057;
	setAttr -s 49 ".kit[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
	setAttr -s 49 ".kot[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_UpperArm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 49 ".ktv[0:48]"  0 51.44725 0.792 52.570771000000008 1.584 
		53.770241 2.4 55.038334 3.192 56.366225000000007 3.984 57.742143 4.8 59.149435000000004 
		5.592 60.56413100000001 6.384 61.952462000000004 7.2 63.269070000000006 7.992 64.457079 
		8.784 65.535805000000011 9.6 66.521142000000012 10.392 67.289729 10.8 67.562622 11.184 
		67.767159000000021 11.592 67.876750000000015 12 67.91754 12.384 67.87175 12.792 67.765049 
		13.584 67.392209 14.4 66.921008 15.192 66.485700000000008 15.984 66.205887000000018 
		16.8 66.35803700000001 17.592 66.996038 18.384 67.919206000000017 18.792 68.416765 
		19.2 68.854068000000012 19.584 69.24338800000001 19.992 69.542803000000021 20.4 69.713497000000018 
		20.784 69.774873 21.192 69.669879 21.6 69.456928 21.984 69.092469 22.392 68.642038000000014 
		23.184 67.49611 24 66.228536 24.792 64.904736000000014 25.584 63.487950000000005 
		26.4 62.014268999999992 27.192 60.506983000000005 27.984 58.981781000000005 28.8 
		57.450262000000009 29.592 55.922126000000006 30.384 54.406422000000006 31.2 52.911939 
		31.992 51.447246;
	setAttr -s 49 ".kit[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
	setAttr -s 49 ".kot[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_UpperArm_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 49 ".ktv[0:48]"  0 5.344673 0.792 4.953625 1.584 4.6809500000000011 
		2.4 4.568414 3.192 4.670397 3.984 5.054651 4.8 5.802108 5.592 7.0046050000000006 
		6.384 8.7588370000000015 7.2 11.15419 7.992 14.251745000000001 8.784 18.052356 9.6 
		22.660729000000003 10.392 27.923121 10.8 30.746409 11.184 33.637655000000009 11.592 
		36.525565000000007 12 39.435389 12.384 42.170163000000009 12.792 44.884029000000005 
		13.584 49.593574000000004 14.4 53.28515800000001 15.192 55.790854 15.984 57.003851000000004 
		16.8 56.243439 17.592 53.7422 18.384 49.50527300000001 18.792 46.645985 19.2 43.655316000000006 
		19.584 40.100752 19.992 36.420868000000006 20.4 32.436034000000006 20.784 28.403016000000004 
		21.192 24.423835 21.6 20.510102000000003 21.984 17.009709 22.392 13.653173000000002 
		23.184 8.435 24 5.093404 24.792 3.191846 25.584 2.12429 26.4 1.6966880000000002 27.192 
		1.7400960000000003 27.984 2.1118280000000005 28.8 2.692727 29.592 3.3834190000000004 
		30.384 4.10071 31.2 4.7744230000000005 31.992 5.34467;
	setAttr -s 49 ".kit[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
	setAttr -s 49 ".kot[0:48]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_UpperArm_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_UpperArm_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_UpperArm_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.145397;
createNode animCurveTU -n "Bip01_L_Clavicle_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Clavicle_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_L_Clavicle_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_L_Clavicle_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 177.346317 0.792 177.27067900000003 1.584 
		177.190329 2.4 177.104746 3.192 177.01339900000002 3.984 176.91570000000002 4.8 176.81100700000002 
		5.592 176.698664 6.384 176.57787900000002 7.2 176.44792800000002 7.992 176.307882 
		8.784 176.143684 9.6 175.937699 10.392 175.69470900000002 11.184 175.416515 12 175.109334 
		12.792 174.784654 13.584 174.461368 14.4 174.16758800000002 15.192 173.940648 15.984 
		173.82352400000002 16.8 173.85305700000004 17.592 173.99089100000003 18.384 174.219825 
		19.2 174.511611 19.992 174.841468 20.784 175.184439 21.6 175.518585 22.392 175.82582100000002 
		23.184 176.09228 24 176.30810000000002 24.792 176.48594500000002 25.584 176.642534 
		26.4 176.778318 27.192 176.895155 27.984 176.99562700000004 28.8 177.082535 29.592 
		177.15862300000003 30.384 177.22643300000001 31.2 177.28830100000002 31.992 177.34630300000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Clavicle_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -72.776741 0.792 -73.276185 1.584 -73.775383 
		2.4 -74.273741 3.192 -74.770405000000011 3.984 -75.264323 4.8 -75.754403 5.592 -76.239687000000018 
		6.384 -76.719536 7.2 -77.193790000000021 7.992 -77.662935 8.784 -78.169701000000018 
		9.6 -78.751435000000015 10.392 -79.370906 11.184 -80.005457 12 -80.62988 12.792 -81.219612 
		13.584 -81.750591000000014 14.4 -82.19902 15.192 -82.541076000000018 15.984 -82.752505000000014 
		16.8 -82.802857000000017 17.592 -82.781062 18.384 -82.689448 19.2 -82.532470000000018 
		19.992 -82.31319400000001 20.784 -82.035075 21.6 -81.701612000000011 22.392 -81.316369 
		23.184 -80.882945 24 -80.405010000000019 24.792 -79.85589 25.584 -79.21709 26.4 -78.504421000000008 
		27.192 -77.733716000000015 27.984 -76.920794000000015 28.8 -76.081493 29.592 -75.231627000000017 
		30.384 -74.386999 31.2 -73.563442 31.992 -72.776741;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Clavicle_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.073432 0.792 -0.99436400000000025 
		1.584 -0.9105660000000001 2.4 -0.82154900000000008 3.192 -0.726777 3.984 -0.625661 
		4.8 -0.517559 5.592 -0.40178100000000005 6.384 -0.27759700000000004 7.2 -0.14421500000000004 
		7.992 -0.000747 8.784 0.167191 9.6 0.37744900000000003 10.392 0.624997 11.184 0.907832 
		12 1.2194940000000003 12.792 1.5482960000000001 13.584 1.8750990000000005 14.4 2.171571 
		15.192 2.400118 15.984 2.5175630000000004 16.8 2.4869860000000004 17.592 2.3467790000000006 
		18.384 2.114439 19.2 1.818613 19.992 1.484434 20.784 1.137083 21.6 0.79875400000000008 
		22.392 0.48767200000000005 23.184 0.217795 24 -0.000958 24.792 -0.181491 25.584 -0.34084800000000004 
		26.4 -0.479538 27.192 -0.599469 27.984 -0.703254 28.8 -0.793704 29.592 -0.87353500000000006 
		30.384 -0.94529400000000008 31.2 -1.011252 31.992 -1.073433;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.038277 0.792 0.038379 1.584 0.038478 
		2.4 0.038574 3.192 0.038667 3.984 0.038758 4.8 0.038845 5.592 0.03893 6.384 0.039011 
		7.2 0.03909 7.992 0.039165 8.784 0.039244 9.6 0.039329 10.392 0.039414 11.184 0.039496 
		12 0.03957 12.792 0.039633 13.584 0.039685 14.4 0.039724 15.192 0.039748 15.984 0.039756 
		16.8 0.039748 17.592 0.039724 18.384 0.039685 19.2 0.039633 19.992 0.03957 20.784 
		0.039496 21.6 0.039414 22.392 0.039329 23.184 0.039244 24 0.039165 24.792 0.03909 
		25.584 0.039011 26.4 0.03893 27.192 0.038845 27.984 0.038758 28.8 0.038667 29.592 
		0.038574 30.384 0.038478 31.2 0.038379 31.992 0.038277;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.005354 0.792 -0.0053550000000000013 
		1.584 -0.0053550000000000013 2.4 -0.0053550000000000013 3.192 -0.0053550000000000013 
		3.984 -0.0053560000000000005 4.8 -0.0053560000000000005 5.592 -0.0053560000000000005 
		6.384 -0.0053560000000000005 7.2 -0.005357 7.992 -0.005357 8.784 -0.005357 9.6 -0.005358 
		10.392 -0.005358 11.184 -0.005358 12 -0.0053590000000000009 12.792 -0.0053590000000000009 
		13.584 -0.0053590000000000009 14.4 -0.0053590000000000009 15.192 -0.00536 15.984 
		-0.00536 16.8 -0.00536 17.592 -0.0053590000000000009 18.384 -0.0053590000000000009 
		19.2 -0.0053590000000000009 19.992 -0.0053590000000000009 20.784 -0.005358 21.6 -0.005358 
		22.392 -0.005358 23.184 -0.005357 24 -0.005357 24.792 -0.005357 25.584 -0.0053560000000000005 
		26.4 -0.0053560000000000005 27.192 -0.0053560000000000005 27.984 -0.0053560000000000005 
		28.8 -0.0053550000000000013 29.592 -0.0053550000000000013 30.384 -0.0053550000000000013 
		31.2 -0.0053550000000000013 31.992 -0.005354;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.011873 0.792 -0.011538 1.584 -0.011203 
		2.4 -0.010867 3.192 -0.01053 3.984 -0.010192 4.8 -0.009853 5.592 -0.009514 6.384 
		-0.009174 7.2 -0.008833 7.992 -0.008492 8.784 -0.008121 9.6 -0.007697 10.392 -0.0072470000000000017 
		11.184 -0.0067890000000000008 12 -0.006344 12.792 -0.005933 13.584 -0.005576 14.4 
		-0.0052960000000000012 15.192 -0.005112 15.984 -0.005046000000000001 16.8 -0.005112 
		17.592 -0.005294 18.384 -0.005576 19.2 -0.005933 19.992 -0.006344 20.784 -0.0067890000000000008 
		21.6 -0.0072470000000000017 22.392 -0.007697 23.184 -0.008119 24 -0.008492 24.792 
		-0.008833 25.584 -0.009174 26.4 -0.009514 27.192 -0.009853 27.984 -0.010192 28.8 
		-0.01053 29.592 -0.010867 30.384 -0.011203 31.2 -0.011538 31.992 -0.011873;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Finger11_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger11_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger11_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger11_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 30.522184;
createNode animCurveTA -n "Bip01_R_Finger11_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_R_Finger11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.0000000000000004e-006;
createNode animCurveTL -n "Bip01_R_Finger11_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger11_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger11_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.046167;
createNode animCurveTU -n "Bip01_R_Finger1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger1_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 18.172223000000002;
createNode animCurveTA -n "Bip01_R_Finger1_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -6.9803670000000011 0.792 -6.9803720000000009 
		1.584 -6.980374 2.4 -6.980374 3.192 -6.9803710000000008 3.984 -6.9803720000000009 
		4.8 -6.9803720000000009 5.592 -6.9803680000000012 6.384 -6.980378 7.2 -6.98037 7.992 
		-6.9803680000000012 8.784 -6.980373 9.6 -6.9803720000000009 10.392 -6.9803760000000006 
		11.184 -6.9803710000000008 12 -6.980369 12.792 -6.9803710000000008 13.584 -6.980374 
		14.4 -6.9803710000000008 15.192 -6.9803710000000008 15.984 -6.980374 16.8 -6.9803710000000008 
		17.592 -6.9803710000000008 18.384 -6.980374 19.2 -6.980374 19.992 -6.9803670000000011 
		20.784 -6.980364 21.6 -6.980375 22.392 -6.980374 23.184 -6.980375 24 -6.980374 24.792 
		-6.9803720000000009 25.584 -6.9803670000000011 26.4 -6.980374 27.192 -6.980375 27.984 
		-6.980374 28.8 -6.980369 29.592 -6.9803710000000008 30.384 -6.980373 31.2 -6.9803710000000008 
		31.992 -6.980373;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger1_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.316994;
createNode animCurveTL -n "Bip01_R_Finger1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.033041;
createNode animCurveTL -n "Bip01_R_Finger1_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.0012200000000000002 0.792 0.0012200000000000002 
		1.584 0.0012200000000000002 2.4 0.0012200000000000002 3.192 0.0012200000000000002 
		3.984 0.0012200000000000002 4.8 0.0012200000000000002 5.592 0.0012200000000000002 
		6.384 0.0012200000000000002 7.2 0.0012200000000000002 7.992 0.0012200000000000002 
		8.784 0.0012200000000000002 9.6 0.0012200000000000002 10.392 0.0012200000000000002 
		11.184 0.0012200000000000002 12 0.0012200000000000002 12.792 0.0012200000000000002 
		13.584 0.0012200000000000002 14.4 0.0012200000000000002 15.192 0.0012200000000000002 
		15.984 0.0012200000000000002 16.8 0.0012200000000000002 17.592 0.0012200000000000002 
		18.384 0.0012200000000000002 19.2 0.0012200000000000002 19.992 0.0012200000000000002 
		20.784 0.0012200000000000002 21.6 0.0012200000000000002 22.392 0.0012200000000000002 
		23.184 0.0012200000000000002 24 0.0012200000000000002 24.792 0.0012200000000000002 
		25.584 0.0012200000000000002 26.4 0.0012200000000000002 27.192 0.0012200000000000002 
		27.984 0.0012200000000000002 28.8 0.0012200000000000002 29.592 0.0012200000000000002 
		30.384 0.0012200000000000002 31.2 0.0012200000000000002 31.992 0.0012200000000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger1_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.094277 0.792 0.094277 1.584 0.094277 
		2.4 0.094277 3.192 0.094277 3.984 0.094277 4.8 0.094277 5.592 0.094277 6.384 0.094277 
		7.2 0.094277 7.992 0.094277 8.784 0.094277 9.6 0.094277 10.392 0.094277 11.184 0.094277 
		12 0.094277 12.792 0.094277 13.584 0.094277 14.4 0.094277 15.192 0.094277 15.984 
		0.094277 16.8 0.094277 17.592 0.094277 18.384 0.094277 19.2 0.094277 19.992 0.094277 
		20.784 0.094277 21.6 0.094277 22.392 0.094277 23.184 0.094277 24 0.094277 24.792 
		0.094277 25.584 0.094277 26.4 0.094277 27.192 0.094277 27.984 0.094277 28.8 0.094277 
		29.592 0.094277 30.384 0.094277 31.2 0.094277 31.992 0.094277;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Finger21_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger21_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger21_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger21_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 34.58505;
createNode animCurveTA -n "Bip01_R_Finger21_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "Bip01_R_Finger21_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
createNode animCurveTL -n "Bip01_R_Finger21_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger21_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger21_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.047592;
createNode animCurveTU -n "Bip01_R_Finger2_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger2_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger2_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger2_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 26.614676000000003;
createNode animCurveTA -n "Bip01_R_Finger2_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.492352;
createNode animCurveTA -n "Bip01_R_Finger2_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.100191;
createNode animCurveTL -n "Bip01_R_Finger2_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.013128000000000003;
createNode animCurveTL -n "Bip01_R_Finger2_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.006931 0.792 -0.006931 1.584 -0.006931 
		2.4 -0.006931 3.192 -0.006931 3.984 -0.006931 4.8 -0.006931 5.592 -0.006931 6.384 
		-0.006931 7.2 -0.006931 7.992 -0.006931 8.784 -0.006931 9.6 -0.006931 10.392 -0.006931 
		11.184 -0.006931 12 -0.00693 12.792 -0.00693 13.584 -0.006931 14.4 -0.00693 15.192 
		-0.00693 15.984 -0.00693 16.8 -0.006931 17.592 -0.006931 18.384 -0.006931 19.2 -0.00693 
		19.992 -0.00693 20.784 -0.006931 21.6 -0.006931 22.392 -0.00693 23.184 -0.00693 24 
		-0.006931 24.792 -0.00693 25.584 -0.00693 26.4 -0.006931 27.192 -0.006931 27.984 
		-0.00693 28.8 -0.00693 29.592 -0.00693 30.384 -0.00693 31.2 -0.006931 31.992 -0.00693;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger2_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.094671 0.792 0.094671 1.584 0.094671 
		2.4 0.094671 3.192 0.094671 3.984 0.094671 4.8 0.094671 5.592 0.094671 6.384 0.094671 
		7.2 0.094671 7.992 0.094671 8.784 0.094671 9.6 0.094671 10.392 0.094671 11.184 0.094671 
		12 0.094671 12.792 0.094671 13.584 0.094671 14.4 0.094671 15.192 0.094671 15.984 
		0.094671 16.8 0.094671 17.592 0.094671 18.384 0.094671 19.2 0.094671 19.992 0.094671 
		20.784 0.094671 21.6 0.094671 22.392 0.094671 23.184 0.094671 24 0.094671 24.792 
		0.094671 25.584 0.094671 26.4 0.094671 27.192 0.094671 27.984 0.094671 28.8 0.094671 
		29.592 0.094671 30.384 0.094671 31.2 0.094671 31.992 0.094671;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Finger01_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger01_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger01_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger01_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 27.538836000000003;
createNode animCurveTA -n "Bip01_R_Finger01_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_R_Finger01_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger01_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger01_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger01_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.051997 0.792 0.051997 1.584 0.051997 
		2.4 0.051997 3.192 0.051997 3.984 0.051997 4.8 0.051997 5.592 0.051997 6.384 0.051997 
		7.2 0.051997 7.992 0.051997 8.784 0.051997 9.6 0.051997 10.392 0.051997 11.184 0.051997 
		12 0.051997 12.792 0.051997 13.584 0.051997 14.4 0.051997 15.192 0.051997 15.984 
		0.051997 16.8 0.051997 17.592 0.051997 18.384 0.051997 19.2 0.051997 19.992 0.051997 
		20.784 0.051997 21.6 0.051997 22.392 0.051997 23.184 0.051997 24 0.051997 24.792 
		0.051997 25.584 0.051997 26.4 0.051997 27.192 0.051997 27.984 0.051997 28.8 0.051997 
		29.592 0.051997 30.384 0.051997 31.2 0.051997 31.992 0.051997;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Finger0_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger0_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Finger0_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Finger0_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 20.062802000000005;
createNode animCurveTA -n "Bip01_R_Finger0_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -27.870976000000002;
createNode animCurveTA -n "Bip01_R_Finger0_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -82.611707;
createNode animCurveTL -n "Bip01_R_Finger0_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.042679 0.792 0.042679 1.584 0.042679 
		2.4 0.042679 3.192 0.042679 3.984 0.042679 4.8 0.042679 5.592 0.042679 6.384 0.042679 
		7.2 0.042679 7.992 0.042679 8.784 0.042679 9.6 0.042679 10.392 0.042679 11.184 0.042679 
		12 0.042679 12.792 0.042679 13.584 0.042679 14.4 0.042679 15.192 0.042679 15.984 
		0.042679 16.8 0.042679 17.592 0.042679 18.384 0.042679 19.2 0.042679 19.992 0.042679 
		20.784 0.042679 21.6 0.042679 22.392 0.042679 23.184 0.042679 24 0.042679 24.792 
		0.042679 25.584 0.042679 26.4 0.042679 27.192 0.042679 27.984 0.042679 28.8 0.042679 
		29.592 0.042679 30.384 0.042679 31.2 0.042679 31.992 0.042679;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger0_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.018544;
createNode animCurveTL -n "Bip01_R_Finger0_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.030413000000000003 0.792 0.030412000000000005 
		1.584 0.030412000000000005 2.4 0.030413000000000003 3.192 0.030412000000000005 3.984 
		0.030412000000000005 4.8 0.030412000000000005 5.592 0.030412000000000005 6.384 0.030412000000000005 
		7.2 0.030412000000000005 7.992 0.030412000000000005 8.784 0.030412000000000005 9.6 
		0.030412000000000005 10.392 0.030412000000000005 11.184 0.030413000000000003 12 0.030412000000000005 
		12.792 0.030412000000000005 13.584 0.030413000000000003 14.4 0.030412000000000005 
		15.192 0.030412000000000005 15.984 0.030413000000000003 16.8 0.030412000000000005 
		17.592 0.030413000000000003 18.384 0.030412000000000005 19.2 0.030412000000000005 
		19.992 0.030412000000000005 20.784 0.030412000000000005 21.6 0.030412000000000005 
		22.392 0.030413000000000003 23.184 0.030412000000000005 24 0.030412000000000005 24.792 
		0.030412000000000005 25.584 0.030412000000000005 26.4 0.030412000000000005 27.192 
		0.030413000000000003 27.984 0.030412000000000005 28.8 0.030413000000000003 29.592 
		0.030412000000000005 30.384 0.030412000000000005 31.2 0.030412000000000005 31.992 
		0.030413000000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Hand_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Hand_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Hand_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Hand_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 9.247562 0.792 9.307701 1.584 9.502501 
		2.4 9.867066 3.192 10.435453 3.984 11.21168 4.8 12.142012000000001 5.592 13.097557 
		6.384 13.874088000000002 7.2 14.213563000000002 7.992 13.847621 8.784 13.085867000000002 
		9.6 11.873428000000002 10.392 10.349752 11.184 8.6263210000000026 12 6.815896 12.792 
		5.025136 13.584 3.354742 14.4 1.900616 15.192 0.755766 15.984 0.012689000000000002 
		16.8 -0.359558 17.592 -0.48122700000000007 18.384 -0.391414 19.2 -0.127715 19.992 
		0.272377 20.784 0.771187 21.6 1.330306 22.392 1.9103360000000003 23.184 2.470789 
		24 2.9700940000000005 24.792 3.4551200000000004 25.584 3.9953580000000004 26.4 4.5824 
		27.192 5.207611 27.984 5.8621450000000008 28.8 6.536907 29.592 7.2225459999999995 
		30.384 7.9094590000000009 31.2 8.587817 31.992 9.2475630000000013;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Hand_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -3.737042 0.792 -3.7883450000000005 1.584 
		-3.9506990000000006 2.4 -4.2449630000000012 3.192 -4.69196 3.984 -5.295357000000001 
		4.8 -6.0246070000000005 5.592 -6.803632 6.384 -7.5091620000000008 7.2 -7.9801750000000018 
		7.992 -8.03623 8.784 -7.7525140000000006 9.6 -7.1885220000000016 10.392 -6.3971150000000012 
		11.184 -5.426275 12 -4.3347740000000012 12.792 -3.1900630000000003 13.584 -2.067455 
		14.4 -1.048282 15.192 -0.21739000000000003 15.984 0.33983000000000008 16.8 0.636555 
		17.592 0.758557 18.384 0.73432500000000012 19.2 0.592338 19.992 0.36279400000000006 
		20.784 0.075278 21.6 -0.24164800000000003 22.392 -0.560931 23.184 -0.85731500000000016 
		24 -1.107326 24.792 -1.3406590000000003 25.584 -1.5971560000000002 26.4 -1.869954 
		27.192 -2.152522 27.984 -2.4386560000000004 28.8 -2.722582 29.592 -2.998964 30.384 
		-3.2629840000000003 31.2 -3.510284 31.992 -3.7370390000000011;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Hand_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 58.639684000000017 0.792 58.702153 1.584 
		58.883890999999991 2.4 59.169523000000005 3.192 59.538619000000011 3.984 59.972691000000005 
		4.8 60.463980000000006 5.592 61.024417000000007 6.384 61.691310000000009 7.2 62.524156 
		7.992 63.58692700000001 8.784 64.466935 9.6 65.559144 10.392 66.765116 11.184 68.013552 
		12 69.232672 12.792 70.358615 13.584 71.336445 14.4 72.119601 15.192 72.668031000000013 
		15.984 72.945187 16.8 72.951976 17.592 72.740684000000016 18.384 72.341036 19.2 71.792688 
		19.992 71.12667 20.784 70.375882 21.6 69.573642 22.392 68.754067 23.184 67.952203000000011 
		24 67.20399 24.792 66.468775000000008 25.584 65.686356000000018 26.4 64.864015000000009 
		27.192 64.009189 27.984 63.129502000000009 28.8 62.23276700000001 29.592 61.327043 
		30.384 60.420588 31.2 59.521912 31.992 58.639684000000017;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Hand_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Hand_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Hand_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.283498 0.792 0.283498 1.584 0.283498 
		2.4 0.283498 3.192 0.283498 3.984 0.283498 4.8 0.283498 5.592 0.283498 6.384 0.283498 
		7.2 0.283498 7.992 0.283498 8.784 0.283498 9.6 0.283498 10.392 0.283498 11.184 0.283498 
		12 0.283498 12.792 0.283498 13.584 0.283498 14.4 0.283498 15.192 0.283498 15.984 
		0.283498 16.8 0.283498 17.592 0.283498 18.384 0.283498 19.2 0.283498 19.992 0.283498 
		20.784 0.283498 21.6 0.283498 22.392 0.283498 23.184 0.283498 24 0.283498 24.792 
		0.283498 25.584 0.283498 26.4 0.283498 27.192 0.283498 27.984 0.283498 28.8 0.283498 
		29.592 0.283498 30.384 0.283498 31.2 0.283498 31.992 0.283498;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_Forearm_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Forearm_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Forearm_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Forearm_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -23.684021000000005 0.792 -23.531990000000004 
		1.584 -23.049587 2.4 -22.172705000000004 3.192 -20.839941 3.984 -19.047015000000002 
		4.8 -16.898761 5.592 -14.641901 6.384 -12.665313 7.2 -11.461672000000002 7.992 -11.553236 
		8.784 -12.578584 9.6 -14.418090999999999 10.392 -16.856416 11.184 -19.714778000000003 
		12 -22.805268000000005 12.792 -25.939940000000004 13.584 -28.930859 14.4 -31.590125 
		15.192 -33.729808 15.984 -35.161972000000006 16.8 -35.944183 17.592 -36.302231 18.384 
		-36.305346 19.2 -36.01637800000001 19.992 -35.502392000000007 20.784 -34.82943800000001 
		21.6 -34.063579 22.392 -33.270782000000004 23.184 -32.517122 24 -31.86864 24.792 
		-31.248264000000002 25.584 -30.544755 26.4 -29.772749000000005 27.192 -28.946951000000006 
		27.984 -28.082034 28.8 -27.192645 29.592 -26.293483 30.384 -25.399208000000005 31.2 
		-24.52449 31.992 -23.684019;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Forearm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.0000000000000015e-006 0.792 0 1.584 
		1.0000000000000004e-006 2.4 1.0000000000000004e-006 3.192 -3.0000000000000005e-006 
		3.984 7.0000000000000024e-006 4.8 4.0000000000000015e-006 5.592 -3.0000000000000005e-006 
		6.384 5e-006 7.2 2.0000000000000008e-006 7.992 -2.0000000000000008e-006 8.784 4.0000000000000015e-006 
		9.6 0 10.392 4.0000000000000015e-006 11.184 -3.0000000000000005e-006 12 -1.0000000000000004e-006 
		12.792 -7.0000000000000024e-006 13.584 -2.0000000000000008e-006 14.4 0 15.192 0 15.984 
		0 16.8 -2.0000000000000008e-006 17.592 0 18.384 0 19.2 0 19.992 3.0000000000000005e-006 
		20.784 -2.0000000000000008e-006 21.6 5e-006 22.392 -1.0000000000000004e-006 23.184 
		-5e-006 24 2.0000000000000008e-006 24.792 -4.0000000000000015e-006 25.584 4.0000000000000015e-006 
		26.4 -7.0000000000000024e-006 27.192 3.0000000000000005e-006 27.984 1.0000000000000004e-006 
		28.8 -1.0000000000000004e-006 29.592 2.0000000000000008e-006 30.384 0 31.2 1.0000000000000004e-006 
		31.992 -2.0000000000000008e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Forearm_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.0000000000000008e-006;
createNode animCurveTL -n "Bip01_R_Forearm_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Forearm_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Forearm_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.280821 0.792 0.280821 1.584 0.280821 
		2.4 0.280821 3.192 0.280821 3.984 0.280821 4.8 0.280821 5.592 0.280821 6.384 0.280821 
		7.2 0.280821 7.992 0.280821 8.784 0.280821 9.6 0.280821 10.392 0.280821 11.184 0.280821 
		12 0.280821 12.792 0.280821 13.584 0.280821 14.4 0.280821 15.192 0.280821 15.984 
		0.280821 16.8 0.280821 17.592 0.280821 18.384 0.280821 19.2 0.280821 19.992 0.280821 
		20.784 0.280821 21.6 0.280821 22.392 0.280821 23.184 0.280821 24 0.280821 24.792 
		0.280821 25.584 0.280821 26.4 0.280821 27.192 0.280821 27.984 0.280821 28.8 0.280821 
		29.592 0.280821 30.384 0.280821 31.2 0.280821 31.992 0.280821;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_R_UpperArm_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_UpperArm_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_UpperArm_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_UpperArm_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  0 54.308832 0.792 52.092607 1.584 49.169180000000004 
		2.4 45.443521000000004 3.192 40.782586 3.984 35.025229 4.392 31.602624 4.8 28.045699000000003 
		5.184 24.043547 5.592 19.908754000000002 6 15.531622000000002 6.384 11.091126 6.792 
		6.801235000000001 7.2 2.5666670000000003 7.584 -1.035159 7.992 -4.496874 8.784 -7.9600570000000008 
		9.6 -10.850149 10.392 -13.113744000000002 11.184 -14.840783 12 -16.116937000000004 
		12.792 -17.018614 13.584 -17.603681 14.4 -17.909851000000003 15.192 -17.955977 15.984 
		-17.743266000000002 16.8 -17.194271 17.592 -16.256956 18.384 -14.910750000000002 
		19.2 -13.162625000000002 19.992 -10.981685 20.784 -8.3439000000000014 21.6 -5.240979 
		22.392 -1.7054180000000003 23.184 2.156993 24 6.1377800000000011 24.792 10.285120000000001 
		25.584 14.801656000000001 26.4 19.612793000000003 27.192 24.630373 27.984 29.759891000000003 
		28.8 34.90915 29.592 39.996141000000009 30.384 44.954469 31.2 49.735717000000008 
		31.992 54.308832;
	setAttr -s 46 ".kit[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
	setAttr -s 46 ".kot[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
createNode animCurveTA -n "Bip01_R_UpperArm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  0 -65.035849 0.792 -64.666042 1.584 -64.670557 
		2.4 -65.028773000000015 3.192 -65.700843 3.984 -66.597988000000015 4.392 -67.113428 
		4.8 -67.557042 5.184 -67.99496000000002 5.592 -68.33927 6 -68.561114000000018 6.384 
		-68.676906 6.792 -68.570273000000014 7.2 -68.367601000000008 7.584 -67.893251000000021 
		7.992 -67.356125 8.784 -65.938376 9.6 -64.136579 10.392 -62.12069000000001 11.184 
		-60.011787 12 -57.931571 12.792 -55.992990000000006 13.584 -54.302098000000008 14.4 
		-52.960198 15.192 -52.06620800000001 15.984 -51.719125 16.8 -51.977826000000007 17.592 
		-52.759059 18.384 -53.978811 19.2 -55.512814 19.992 -57.258251000000008 20.784 -59.101111 
		21.6 -60.923495 22.392 -62.606904000000007 23.184 -64.038587 24 -65.120284000000012 
		24.792 -65.908057 25.584 -66.508916 26.4 -66.919567 27.192 -67.140551000000016 27.984 
		-67.176888000000019 28.8 -67.038125 29.592 -66.737700000000018 30.384 -66.291866000000013 
		31.2 -65.718512 31.992 -65.035849;
	setAttr -s 46 ".kit[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
	setAttr -s 46 ".kot[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
createNode animCurveTA -n "Bip01_R_UpperArm_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  0 -58.868154000000004 0.792 -56.367687000000004 
		1.584 -53.421864 2.4 -49.933355000000006 3.192 -45.756715000000007 3.984 -40.711754 
		4.392 -37.74934 4.8 -34.651822 5.184 -31.204804 5.592 -27.624407 6 -23.892658000000004 
		6.384 -20.097182000000004 6.792 -16.542664 7.2 -13.043847000000001 7.584 -10.268691999999998 
		7.992 -7.6350780000000009 8.784 -5.3192790000000008 9.6 -3.8057970000000005 10.392 
		-3.062728 11.184 -2.9405240000000004 12 -3.2798020000000006 12.792 -3.9245750000000004 
		13.584 -4.732592 14.4 -5.57857 15.192 -6.3554800000000009 15.984 -6.9766470000000007 
		16.8 -7.4974890000000007 17.592 -8.0494480000000017 18.384 -8.712961 19.2 -9.5625760000000017 
		19.992 -10.694114000000003 20.784 -12.193930000000002 21.6 -14.124795000000002 22.392 
		-16.500102 23.184 -19.251550000000005 24 -22.200748 24.792 -25.326943000000004 25.584 
		-28.755788 26.4 -32.426157000000011 27.192 -36.263655 27.984 -40.187868 28.8 -44.121257 
		29.592 -47.997113 30.384 -51.764997000000008 31.2 -55.393220000000007 31.992 -58.868154000000004;
	setAttr -s 46 ".kit[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
	setAttr -s 46 ".kot[0:45]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
createNode animCurveTL -n "Bip01_R_UpperArm_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_UpperArm_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_UpperArm_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.145397;
createNode animCurveTU -n "Bip01_R_Clavicle_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Clavicle_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_R_Clavicle_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_R_Clavicle_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 173.821024 0.792 174.203487 1.584 174.52482 
		2.4 174.800855 3.192 175.04376400000004 3.984 175.26439300000004 4.8 175.47316500000002 
		5.592 175.6793 6.384 175.888686 7.2 176.100668 7.992 176.306174 8.784 176.50646300000002 
		9.6 176.701957 10.392 176.873831 11.184 177.017306 12 177.13178000000002 12.792 177.21924800000002 
		13.584 177.282386 14.4 177.32361300000002 15.192 177.34448600000002 15.984 177.345278 
		16.8 177.32372200000003 17.592 177.28021400000003 18.384 177.215423 19.2 177.131193 
		19.992 177.027784 20.784 176.906097 21.6 176.76799100000002 22.392 176.61716700000002 
		23.184 176.459963 24 176.30642 24.792 176.15270000000004 25.584 175.985251 26.4 175.80220200000002 
		27.192 175.60136700000004 27.984 175.38008300000004 28.8 175.135084 29.592 174.86239500000002 
		30.384 174.55697700000002 31.2 174.21254400000004 31.992 173.821038;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Clavicle_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 82.752477 0.792 82.293468000000018 1.584 
		81.915001 2.4 81.627347 3.192 81.439613 3.984 81.350636 4.8 81.339885 5.592 81.362015 
		6.384 81.34682500000001 7.2 81.205979 7.992 80.845837000000017 8.784 80.233886000000012 
		9.6 79.416415 10.392 78.464772 11.184 77.43225200000002 12 76.376681000000019 12.792 
		75.355875000000012 13.584 74.427666 14.4 73.649864000000008 15.192 73.080288 15.984 
		72.776727 16.8 72.75052 17.592 72.946116 18.384 73.329426 19.2 73.855221000000014 
		19.992 74.485681 20.784 75.181145 21.6 75.901948 22.392 76.608443000000008 23.184 
		77.260992 24 77.819947000000013 24.792 78.317943 25.584 78.814115 26.4 79.308771000000007 
		27.192 79.802198000000018 27.984 80.294682 28.8 80.786496 29.592 81.277908000000011 
		30.384 81.769210000000015 31.2 82.260656000000012 31.992 82.752477;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Clavicle_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -2.520079 0.792 -2.13415 1.584 -1.8091790000000003 
		2.4 -1.529357 3.192 -1.282661 3.984 -1.058263 4.8 -0.84585700000000008 5.592 -0.636318 
		6.384 -0.423841 7.2 -0.20908400000000002 7.992 -0.001001 8.784 0.20207400000000003 
		9.6 0.40087400000000006 10.392 0.57649400000000006 11.184 0.72408600000000012 12 
		0.84292500000000015 12.792 0.934782 13.584 1.002071 14.4 1.046864 15.192 1.0703320000000003 
		15.984 1.072361 16.8 1.050473 17.592 1.005326 18.384 0.93774200000000008 19.2 0.84988800000000009 
		19.992 0.742259 20.784 0.61602 21.6 0.473275 22.392 0.317905 23.184 0.15650400000000003 
		24 -0.000754 24.792 -0.15786300000000003 25.584 -0.32871200000000006 26.4 -0.5151420000000001 
		27.192 -0.71936000000000011 27.984 -0.944043 28.8 -1.192437 29.592 -1.4685230000000002 
		30.384 -1.7773330000000003 31.2 -2.125158 31.992 -2.520071;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.039756 0.792 -0.039711 1.584 -0.039662 
		2.4 -0.03961 3.192 -0.039556 3.984 -0.039498 4.8 -0.039438 5.592 -0.039374 6.384 
		-0.039307 7.2 -0.039238 7.992 -0.039165 8.784 -0.039083 9.6 -0.038985 10.392 -0.038877 
		11.184 -0.038761 12 -0.038644 12.792 -0.038532 13.584 -0.038432 14.4 -0.03835 15.192 
		-0.038296 15.984 -0.038277 16.8 -0.038296 17.592 -0.03835 18.384 -0.038432 19.2 -0.038532 
		19.992 -0.038644 20.784 -0.038761 21.6 -0.038877 22.392 -0.038985 23.184 -0.039083 
		24 -0.039165 24.792 -0.039238 25.584 -0.039307 26.4 -0.039374 27.192 -0.039438 27.984 
		-0.039498 28.8 -0.039556 29.592 -0.03961 30.384 -0.039662 31.2 -0.039711 31.992 -0.039756;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.0053590000000000009 0.792 -0.0053590000000000009 
		1.584 -0.0053590000000000009 2.4 -0.0053590000000000009 3.192 -0.005358 3.984 -0.005358 
		4.8 -0.005358 5.592 -0.005358 6.384 -0.005357 7.2 -0.005357 7.992 -0.005357 8.784 
		-0.0053560000000000005 9.6 -0.0053560000000000005 10.392 -0.0053560000000000005 11.184 
		-0.0053550000000000013 12 -0.0053550000000000013 12.792 -0.0053550000000000013 13.584 
		-0.005354 14.4 -0.005354 15.192 -0.005354 15.984 -0.005354 16.8 -0.005354 17.592 
		-0.005354 18.384 -0.005354 19.2 -0.0053550000000000013 19.992 -0.0053550000000000013 
		20.784 -0.0053550000000000013 21.6 -0.0053560000000000005 22.392 -0.0053560000000000005 
		23.184 -0.0053560000000000005 24 -0.005357 24.792 -0.005357 25.584 -0.005357 26.4 
		-0.005358 27.192 -0.005358 27.984 -0.005358 28.8 -0.005358 29.592 -0.0053590000000000009 
		30.384 -0.0053590000000000009 31.2 -0.0053590000000000009 31.992 -0.00536;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.005046000000000001 0.792 -0.005393 
		1.584 -0.005739 2.4 -0.006085 3.192 -0.00643 3.984 -0.0067750000000000015 4.8 -0.00712 
		5.592 -0.007463 6.384 -0.007807 7.2 -0.008149 7.992 -0.008492 8.784 -0.0088609999999999991 
		9.6 -0.009283 10.392 -0.009728 11.184 -0.010178000000000001 12 -0.010614000000000002 
		12.792 -0.011015000000000002 13.584 -0.011361 14.4 -0.011632 15.192 -0.01181 15.984 
		-0.011873 16.8 -0.011809 17.592 -0.011634 18.384 -0.011361 19.2 -0.011015000000000002 
		19.992 -0.010614000000000002 20.784 -0.010178000000000001 21.6 -0.009728 22.392 -0.009283 
		23.184 -0.008864 24 -0.008492 24.792 -0.008150000000000001 25.584 -0.007807 26.4 
		-0.007464000000000001 27.192 -0.00712 27.984 -0.0067750000000000015 28.8 -0.00643 
		29.592 -0.006085 30.384 -0.005739 31.2 -0.005393 31.992 -0.005046000000000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_Head_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Head_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Head_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_Head_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.06502 0.792 -3.8394099999999995 1.584 
		-3.580085 2.4 -3.2992900000000005 3.192 -3.00982 3.984 -2.725074 4.8 -2.459033 5.592 
		-2.226299 6.384 -2.0420960000000004 7.2 -1.9222490000000003 7.992 -1.8831540000000002 
		8.784 -1.9601250000000001 9.6 -2.163582 10.392 -2.464126 11.184 -2.8344140000000007 
		12 -3.244261 12.792 -3.661379 13.584 -4.051483 14.4 -4.378565 15.192 -4.605294 15.984 
		-4.693619 16.8 -4.618014 17.592 -4.400135 18.384 -4.065132 19.2 -3.649899 19.992 
		-3.186008 20.784 -2.7087740000000005 21.6 -2.2554460000000005 22.392 -1.8648800000000003 
		23.184 -1.5769130000000002 24 -1.4315620000000002 24.792 -1.427106 25.584 -1.5257670000000003 
		26.4 -1.7123070000000002 27.192 -1.9706960000000002 27.984 -2.2842880000000005 28.8 
		-2.635947 29.592 -3.008097 30.384 -3.3827290000000003 31.2 -3.7413670000000003 31.992 
		-4.0650210000000007;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Head_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.50721 0.792 -0.8849800000000001 1.584 
		-1.31292 2.4 -1.7668930000000003 3.192 -2.223111 3.984 -2.658255 4.8 -3.049422 5.592 
		-3.3742040000000006 6.384 -3.610712 7.2 -3.7375950000000002 7.992 -3.734036000000001 
		8.784 -3.586484 9.6 -3.308231 10.392 -2.930978 11.184 -2.479744 12 -1.9789130000000001 
		12.792 -1.450601 13.584 -0.91466200000000009 14.4 -0.389 15.192 0.109551 15.984 0.564059 
		16.8 1.039326 17.592 1.5863340000000001 18.384 2.181394 19.2 2.7789280000000005 19.992 
		3.3488700000000002 20.784 3.859539 21.6 4.281878 22.392 4.589615 23.184 4.758925 
		24 4.767737 24.792 4.5999440000000007 25.584 4.274278 26.4 3.820888 27.192 3.269334 
		27.984 2.648635 28.8 1.9873610000000002 29.592 1.313643 30.384 0.655194 31.2 0.0393 
		31.992 -0.50721100000000008;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Head_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 10.48709 0.792 9.7447580000000009 1.584 
		8.998982 2.4 8.247914 3.192 7.4905220000000012 3.984 6.726641 4.8 5.956984 5.592 
		5.183052 6.384 4.4069780000000005 7.2 3.631284 7.992 2.858545 8.784 2.025184 9.6 
		1.0752600000000003 10.392 0.072445 11.184 -0.942831 12 -1.9249830000000003 12.792 
		-2.8286070000000003 13.584 -3.6081900000000009 14.4 -4.217811 15.192 -4.610838 15.984 
		-4.739609 16.8 -4.567274 17.592 -4.123401 18.384 -3.4428450000000006 19.2 -2.582704 
		19.992 -1.5877950000000003 20.784 -0.50902800000000015 21.6 0.600059 22.392 1.6836610000000003 
		23.184 2.684498 24 3.5449880000000005 24.792 4.30028 25.584 5.02671 26.4 5.7298950000000008 
		27.192 6.416024 27.984 7.0913570000000012 28.8 7.7617920000000016 29.592 8.4325810000000025 
		30.384 9.108158 31.2 9.792083 31.992 10.48709;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Head_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_Head_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 0 1.584 0 2.4 0 3.192 0 3.984 
		0 4.8 0 5.592 0 6.384 0 7.2 0 7.992 0 8.784 0 9.6 0 10.392 0 11.184 0 12 0 12.792 
		0 13.584 0 14.4 0 15.192 0 15.984 0 16.8 0 17.592 0 18.384 0 19.2 0 19.992 0 20.784 
		0 21.6 0 22.392 0 23.184 0 24 0 24.792 0 25.584 0 26.4 0 27.192 0 27.984 0 28.8 0 
		29.592 0 30.384 0 31.2 0 31.992 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Head_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.103006 0.792 0.103006 1.584 0.103006 
		2.4 0.103006 3.192 0.103006 3.984 0.103006 4.8 0.103006 5.592 0.103006 6.384 0.103006 
		7.2 0.103006 7.992 0.103006 8.784 0.103006 9.6 0.103006 10.392 0.103006 11.184 0.103006 
		12 0.103006 12.792 0.103006 13.584 0.103006 14.4 0.103006 15.192 0.103006 15.984 
		0.103006 16.8 0.103006 17.592 0.103006 18.384 0.103006 19.2 0.103006 19.992 0.103006 
		20.784 0.103006 21.6 0.103006 22.392 0.103006 23.184 0.103006 24 0.103006 24.792 
		0.103006 25.584 0.103006 26.4 0.103006 27.192 0.103006 27.984 0.103006 28.8 0.103006 
		29.592 0.103006 30.384 0.103006 31.2 0.103006 31.992 0.103006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_Neck_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Neck_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Neck_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_Neck_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 3.6473960000000005 0.792 3.6473630000000004 
		1.584 3.64733 2.4 3.647303 3.192 3.6472780000000005 3.984 3.6472580000000003 4.8 
		3.6472410000000006 5.592 3.647227 6.384 3.6472170000000004 7.2 3.6472120000000006 
		7.992 3.6472080000000004 8.784 3.6472090000000006 9.6 3.6472150000000005 10.392 3.6472260000000003 
		11.184 3.6472430000000005 12 3.647268 12.792 3.647294 13.584 3.6473210000000003 14.4 
		3.6473450000000005 15.192 3.6473610000000005 15.984 3.6473690000000003 16.8 3.647362 
		17.592 3.6473450000000005 18.384 3.6473210000000003 19.2 3.647294 19.992 3.647266000000001 
		20.784 3.6472440000000006 21.6 3.647227 22.392 3.6472150000000005 23.184 3.6472080000000004 
		24 3.6472080000000004 24.792 3.6472120000000006 25.584 3.6472170000000004 26.4 3.647228 
		27.192 3.6472410000000006 27.984 3.6472580000000003 28.8 3.6472790000000006 29.592 
		3.647303 30.384 3.647332 31.2 3.6473610000000005 31.992 3.6473960000000005;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Neck_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 4.9999840000000013 0.792 4.49999 1.584 
		3.9999840000000004 2.4 3.499989 3.192 2.9999880000000005 3.984 2.499985 4.8 1.9999910000000003 
		5.592 1.499987 6.384 0.99999000000000027 7.2 0.49999300000000008 7.992 -1.6000000000000006e-005 
		8.784 -0.54135600000000006 9.6 -1.160002 10.392 -1.815012 11.184 -2.480004 12 -3.1250100000000005 
		12.792 -3.7200119999999997 13.584 -4.23501 14.4 -4.640008 15.192 -4.905005 15.984 
		-5.0000060000000008 16.8 -4.9050010000000013 17.592 -4.64213 18.384 -4.2350120000000011 
		19.2 -3.720002 19.992 -3.1250090000000004 20.784 -2.48001 21.6 -1.8150020000000004 
		22.392 -1.160011 23.184 -0.545005 24 -1.3000000000000001e-005 24.792 0.49999300000000008 
		25.584 0.999991 26.4 1.499991 27.192 1.999987 27.984 2.499985 28.8 2.999991 29.592 
		3.49999 30.384 3.9999900000000004 31.2 4.499988 31.992 4.9999850000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Neck_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.0039920000000000008 0.792 0.0035920000000000006 
		1.584 0.0031890000000000004 2.4 0.00279 3.192 0.002391 3.984 0.0019920000000000003 
		4.8 0.001593 5.592 0.0011940000000000002 6.384 0.000797 7.2 0.00039800000000000008 
		7.992 -1.0000000000000004e-006 8.784 -0.000432 9.6 -0.000924 10.392 -0.0014460000000000002 
		11.184 -0.001976 12 -0.0024910000000000006 12.792 -0.0029670000000000005 13.584 -0.003379 
		14.4 -0.0037030000000000006 15.192 -0.0039150000000000009 15.984 -0.003991 16.8 -0.0039150000000000009 
		17.592 -0.0037040000000000003 18.384 -0.003378 19.2 -0.002966 19.992 -0.0024910000000000006 
		20.784 -0.001976 21.6 -0.0014449999999999999 22.392 -0.000924 23.184 -0.000433 24 
		-1.0000000000000004e-006 24.792 0.00039800000000000008 25.584 0.00079600000000000016 
		26.4 0.001195 27.192 0.001593 27.984 0.0019910000000000006 28.8 0.00239 29.592 0.002791 
		30.384 0.0031899999999999997 31.2 0.003591 31.992 0.003991;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Neck_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_Neck_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -8.2000000000000015e-005;
createNode animCurveTL -n "Bip01_Neck_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.243291 0.792 0.243291 1.584 0.243291 
		2.4 0.243291 3.192 0.243291 3.984 0.243291 4.8 0.243291 5.592 0.243291 6.384 0.243291 
		7.2 0.243291 7.992 0.243291 8.784 0.243291 9.6 0.243291 10.392 0.243291 11.184 0.243291 
		12 0.243291 12.792 0.243291 13.584 0.243291 14.4 0.243291 15.192 0.243291 15.984 
		0.243291 16.8 0.243291 17.592 0.243291 18.384 0.243291 19.2 0.243291 19.992 0.243291 
		20.784 0.243291 21.6 0.243291 22.392 0.243291 23.184 0.243291 24 0.243291 24.792 
		0.243291 25.584 0.243291 26.4 0.243291 27.192 0.243291 27.984 0.243291 28.8 0.243291 
		29.592 0.243291 30.384 0.243291 31.2 0.243291 31.992 0.243291;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_Spine1_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Spine1_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Spine1_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_Spine1_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 2.576433 0.792 2.535217 1.584 2.493812 
		2.4 2.45307 3.192 2.4138390000000003 3.984 2.3769680000000006 4.8 2.343308 5.592 
		2.3137090000000002 6.384 2.2890220000000006 7.2 2.2700980000000004 7.992 2.2577880000000006 
		8.784 2.253102 9.6 2.256373 10.392 2.2671350000000006 11.184 2.284377 12 2.306497 
		12.792 2.3313170000000003 13.584 2.3561550000000007 14.4 2.37799 15.192 2.393682 
		15.984 2.4002870000000005 16.8 2.396356 17.592 2.3841260000000006 18.384 2.3664320000000005 
		19.2 2.346789 19.992 2.328059 20.784 2.3126830000000003 21.6 2.302428 22.392 2.298313 
		23.184 2.3006330000000004 24 2.309068 24.792 2.322879 25.584 2.3412440000000005 26.4 
		2.363433 27.192 2.388773 27.984 2.4166530000000006 28.8 2.446514 29.592 2.4778500000000006 
		30.384 2.510206 31.2 2.5431860000000004 31.992 2.576433;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine1_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.642427 0.792 -4.173079 1.584 -3.6991050000000008 
		2.4 -3.2224120000000003 3.192 -2.74493 3.984 -2.26859 4.8 -1.795328 5.592 -1.3270690000000003 
		6.384 -0.865767 7.2 -0.41338 7.992 0.028159000000000003 8.784 0.49627099999999996 
		9.6 1.0249200000000003 10.392 1.578616 11.184 2.134439 12 2.666366 12.792 3.148382 
		13.584 3.5545340000000003 14.4 3.8588800000000005 15.192 4.0355320000000008 15.984 
		4.058572 16.8 3.8995000000000006 17.592 3.5718930000000007 18.384 3.1015620000000004 
		19.2 2.529481 19.992 1.8865710000000002 20.784 1.206262 21.6 0.522049 22.392 -0.132554 
		23.184 -0.72402500000000014 24 -1.218849 24.792 -1.6365850000000002 25.584 -2.022801 
		26.4 -2.3830170000000006 27.192 -2.7227820000000005 27.984 -3.047632 28.8 -3.363126 
		29.592 -3.674794 30.384 -3.988203 31.2 -4.30889 31.992 -4.642427;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine1_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -5.801993 0.792 -5.5842690000000008 1.584 
		-5.369086 2.4 -5.1555460000000011 3.192 -4.94274 3.984 -4.729735 4.8 -4.5155860000000008 
		5.592 -4.299332 6.384 -4.079996 7.2 -3.856588 7.992 -3.6281070000000004 8.784 -3.3733560000000002 
		9.6 -3.075263 10.392 -2.7546790000000003 11.184 -2.4255010000000006 12 -2.1034180000000005 
		12.792 -1.804205 13.584 -1.5437360000000002 14.4 -1.337979 15.192 -1.2029570000000003 
		15.984 -1.154685 16.8 -1.203867 17.592 -1.33878 18.384 -1.5465960000000003 19.2 -1.8079870000000002 
		19.992 -2.108063 20.784 -2.43096 21.6 -2.7609150000000002 22.392 -3.0822310000000006 
		23.184 -3.379226 24 -3.6361850000000002 24.792 -3.8648820000000006 25.584 -4.088262 
		26.4 -4.3073210000000008 27.192 -4.5230390000000007 27.984 -4.736397 28.8 -4.9483680000000012 
		29.592 -5.1599310000000012 30.384 -5.372066 31.2 -5.585757 31.992 -5.801993;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 2e-005 0.792 1.9e-005 1.584 1.7999999999999997e-005 
		2.4 1.7e-005 3.192 1.7e-005 3.984 1.6000000000000003e-005 4.8 1.5000000000000002e-005 
		5.592 1.5000000000000002e-005 6.384 1.3999999999999998e-005 7.2 1.3e-005 7.992 1.2000000000000002e-005 
		8.784 1.1000000000000001e-005 9.6 1e-005 10.392 8.9999999999999985e-006 11.184 8.0000000000000013e-006 
		12 7.0000000000000007e-006 12.792 6.000000000000001e-006 13.584 5e-006 14.4 5e-006 
		15.192 4.0000000000000007e-006 15.984 4.0000000000000007e-006 16.8 4.0000000000000007e-006 
		17.592 5e-006 18.384 5e-006 19.2 6.000000000000001e-006 19.992 7.0000000000000007e-006 
		20.784 8.0000000000000013e-006 21.6 8.9999999999999985e-006 22.392 1e-005 23.184 
		1.1000000000000001e-005 24 1.2000000000000002e-005 24.792 1.3e-005 25.584 1.3999999999999998e-005 
		26.4 1.5000000000000002e-005 27.192 1.5000000000000002e-005 27.984 1.6000000000000003e-005 
		28.8 1.7e-005 29.592 1.7e-005 30.384 1.7999999999999997e-005 31.2 1.9e-005 31.992 
		2e-005;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.00019300000000000003 0.792 -0.00019300000000000003 
		1.584 -0.00019300000000000003 2.4 -0.00019300000000000003 3.192 -0.00019300000000000003 
		3.984 -0.00019300000000000003 4.8 -0.00019300000000000003 5.592 -0.00019300000000000003 
		6.384 -0.00019300000000000003 7.2 -0.00019300000000000003 7.992 -0.00019300000000000003 
		8.784 -0.00019300000000000003 9.6 -0.00019300000000000003 10.392 -0.00019300000000000003 
		11.184 -0.00019300000000000003 12 -0.00019300000000000003 12.792 -0.00019300000000000003 
		13.584 -0.000194 14.4 -0.00019300000000000003 15.192 -0.00019300000000000003 15.984 
		-0.000194 16.8 -0.00019300000000000003 17.592 -0.000194 18.384 -0.000194 19.2 -0.00019300000000000003 
		19.992 -0.000194 20.784 -0.00019300000000000003 21.6 -0.00019300000000000003 22.392 
		-0.00019300000000000003 23.184 -0.00019300000000000003 24 -0.00019300000000000003 
		24.792 -0.00019300000000000003 25.584 -0.00019300000000000003 26.4 -0.00019300000000000003 
		27.192 -0.00019300000000000003 27.984 -0.00019300000000000003 28.8 -0.00019300000000000003 
		29.592 -0.00019300000000000003 30.384 -0.00019300000000000003 31.2 -0.00019300000000000003 
		31.992 -0.00019300000000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.218613 0.792 0.218613 1.584 0.218613 
		2.4 0.218613 3.192 0.218613 3.984 0.218613 4.8 0.218613 5.592 0.218614 6.384 0.218614 
		7.2 0.218614 7.992 0.218614 8.784 0.218614 9.6 0.218614 10.392 0.218614 11.184 0.218614 
		12 0.218614 12.792 0.218614 13.584 0.218614 14.4 0.218614 15.192 0.218615 15.984 
		0.218614 16.8 0.218614 17.592 0.218614 18.384 0.218614 19.2 0.218614 19.992 0.218614 
		20.784 0.218614 21.6 0.218614 22.392 0.218614 23.184 0.218614 24 0.218614 24.792 
		0.218614 25.584 0.218614 26.4 0.218613 27.192 0.218613 27.984 0.218613 28.8 0.218613 
		29.592 0.218613 30.384 0.218613 31.2 0.218613 31.992 0.218613;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_Spine_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Spine_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Spine_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_Spine_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 3.9992070000000006 0.792 3.9998090000000004 
		1.584 3.9976600000000007 2.4 3.9935700000000005 3.192 3.9883990000000002 3.984 3.9830560000000004 
		4.8 3.9785350000000004 5.592 3.9758030000000009 6.384 3.9758280000000004 7.2 3.9796700000000005 
		7.992 3.9884680000000006 8.784 4.005467 9.6 4.031945 10.392 4.064922000000001 11.184 
		4.101969 12 4.140516 12.792 4.177956 13.584 4.2116630000000006 14.4 4.238971 15.192 
		4.257192 15.984 4.263615 16.8 4.256277 17.592 4.2370880000000009 18.384 4.208425 
		19.2 4.173465 19.992 4.13466 20.784 4.094691000000001 21.6 4.055943000000001 22.392 
		4.0208140000000006 23.184 3.9919640000000003 24 3.9722710000000006 24.792 3.961337 
		25.584 3.956084000000001 26.4 3.9555510000000003 27.192 3.958762000000001 27.984 
		3.9647190000000005 28.8 3.972406 29.592 3.9807770000000002 30.384 3.9887680000000003 
		31.2 3.9952830000000006 31.992 3.9992070000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -3.5539270000000003 0.792 -3.1801760000000003 
		1.584 -2.790327 2.4 -2.386996 3.192 -1.9727529999999998 3.984 -1.550172 4.8 -1.1515620000000002 
		5.592 -0.78955700000000006 6.384 -0.43724000000000007 7.2 -0.067697000000000007 7.992 
		0.34597100000000003 8.784 0.819122 9.6 1.3451650000000002 10.392 1.889827 11.184 
		2.4313830000000003 12 2.9449680000000003 12.792 3.4057200000000005 13.584 3.7887770000000005 
		14.4 4.069289 15.192 4.222388 15.984 4.2232360000000009 16.8 4.025306 17.592 3.647336000000001 
		18.384 3.149751 19.2 2.6098030000000003 19.992 2.093523 20.784 1.7406860000000002 
		21.6 1.5712870000000003 22.392 1.474483 23.184 1.3393750000000002 24 1.0550560000000002 
		24.792 0.646823 25.584 0.216488 26.4 -0.232055 27.192 -0.6949 27.984 -1.1681500000000002 
		28.8 -1.647899 29.592 -2.130256 30.384 -2.611314 31.2 -3.0871760000000004 31.992 
		-3.5539270000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.83680800000000011 0.792 0.788378 1.584 
		0.738313 2.4 0.68762200000000007 3.192 0.63731 3.984 0.588386 4.8 0.539791 5.592 
		0.49184600000000006 6.384 0.44762399999999997 7.2 0.410196 7.992 0.382659 8.784 0.36360600000000004 
		9.6 0.34888800000000003 10.392 0.338463 11.184 0.331806 12 0.32841900000000007 12.792 
		0.327719 13.584 0.329038 14.4 0.33164900000000008 15.192 0.33478600000000003 15.984 
		0.337699 16.8 0.339266 17.592 0.340804 18.384 0.345345 19.2 0.35574300000000003 19.992 
		0.37476400000000004 20.784 0.41006100000000006 21.6 0.46043900000000004 22.392 0.5155630000000001 
		23.184 0.56549700000000014 24 0.60058600000000006 24.792 0.62495200000000006 25.584 
		0.64911600000000014 26.4 0.67307800000000007 27.192 0.696838 27.984 0.72039600000000015 
		28.8 0.743775 29.592 0.767017 30.384 0.790198 31.2 0.813419 31.992 0.83680900000000014;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.002738 0.792 -0.002075 1.584 -0.001404 
		2.4 -0.000737 3.192 -8.8000000000000011e-005 3.984 0.000528 4.8 0.001167 5.592 0.0018360000000000002 
		6.384 0.002456 7.2 0.002944 7.992 0.0032199999999999998 8.784 0.003333 9.6 0.003392 
		10.392 0.003402 11.184 0.0033710000000000003 12 0.0033040000000000005 12.792 0.003209 
		13.584 0.0030920000000000006 14.4 0.0029590000000000007 15.192 0.002818 15.984 0.002674 
		16.8 0.0025399999999999997 17.592 0.002382 18.384 0.002129 19.2 0.0017170000000000002 
		19.992 0.001078 20.784 -1.6000000000000003e-005 21.6 -0.0015220000000000001 22.392 
		-0.0030949999999999997 23.184 -0.004392 24 -0.00507 24.792 -0.005232 25.584 -0.0052280000000000009 
		26.4 -0.0050869999999999995 27.192 -0.004839 27.984 -0.0045130000000000005 28.8 -0.004139 
		29.592 -0.0037449999999999996 30.384 -0.0033599999999999997 31.2 -0.003015 31.992 
		-0.002738;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.029258 0.792 -0.029258 1.584 -0.029258 
		2.4 -0.029258 3.192 -0.029258 3.984 -0.029258 4.8 -0.029258 5.592 -0.029258 6.384 
		-0.029258 7.2 -0.029258 7.992 -0.029258 8.784 -0.029258 9.6 -0.029258 10.392 -0.029258 
		11.184 -0.029258 12 -0.029258 12.792 -0.029258 13.584 -0.029258 14.4 -0.029258 15.192 
		-0.029258 15.984 -0.029258 16.8 -0.029258 17.592 -0.029258 18.384 -0.029258 19.2 
		-0.029258 19.992 -0.029258 20.784 -0.029258 21.6 -0.029258 22.392 -0.029258 23.184 
		-0.029258 24 -0.029258 24.792 -0.029258 25.584 -0.029258 26.4 -0.029258 27.192 -0.029258 
		27.984 -0.029258 28.8 -0.029258 29.592 -0.029258 30.384 -0.029258 31.2 -0.029258 
		31.992 -0.029258;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.130494 0.792 0.130506 1.584 0.130515 
		2.4 0.13052 3.192 0.130522 3.984 0.130521 4.8 0.130517 5.592 0.130509 6.384 0.130499 
		7.2 0.130489 7.992 0.130482 8.784 0.13048 9.6 0.130478 10.392 0.130478 11.184 0.130479 
		12 0.130481 12.792 0.130483 13.584 0.130486 14.4 0.130489 15.192 0.130492 15.984 
		0.130496 16.8 0.130498 17.592 0.130501 18.384 0.130505 19.2 0.130511 19.992 0.130518 
		20.784 0.130522 21.6 0.130513 22.392 0.130486 23.184 0.130448 24 0.130424 24.792 
		0.130417 25.584 0.130417 26.4 0.130423 27.192 0.130432 27.984 0.130444 28.8 0.130457 
		29.592 0.130468 30.384 0.130479 31.2 0.130487 31.992 0.130494;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTU -n "Bip01_Pelvis_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Pelvis_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_Pelvis_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_Pelvis_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 38 ".ktv[0:37]"  0 90.000093000000021 0.792 90.000052 1.584 
		90.000066000000018 2.4 90.000032000000019 3.192 90.000039 3.984 90.000086 4.8 90.000073 
		5.592 90.000086 6.384 90.000080000000011 7.2 90.000073 7.992 90.000073 9.6 90.000073 
		10.392 90.000073 11.184 90.000080000000011 12 90.000080000000011 12.792 90.000086 
		13.584 90.000080000000011 14.4 90.000073 15.192 90.000080000000011 15.984 90.000086 
		16.8 90.000093000000021 17.592 90.000066000000018 18.384 90.000066000000018 19.2 
		90.000086 19.992 90.000080000000011 20.784 90.000080000000011 21.6 90.000080000000011 
		22.392 90.000080000000011 23.184 90.000073 24 90.000073 26.4 90.000073 27.192 90.000073 
		27.984 90.000080000000011 28.8 90.000080000000011 29.592 90.000080000000011 30.384 
		90.000086 31.2 90.000080000000011 31.992 90.000066000000018;
	setAttr -s 38 ".kit[0:37]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 38 ".kot[0:37]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Pelvis_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -88.7991 0.792 -89.089861 1.584 -89.384652000000017 
		2.4 -89.677428 3.192 -89.999998000000019 3.984 -90.232742999999985 4.8 -90.512965 
		5.592 -90.806848000000016 6.384 -91.078778000000014 7.2 -91.293150000000011 7.992 
		-91.414373 8.784 -91.463891000000018 9.6 -91.489812 10.392 -91.494279 11.184 -91.480441 
		12 -91.451167000000012 12.792 -91.409339 13.584 -91.35786 14.4 -91.299591 15.192 
		-91.237436999999986 15.984 -91.174271 16.8 -91.115682000000021 17.592 -91.04626 18.384 
		-90.935016 19.2 -90.754153000000017 19.992 -90.473733 20.784 -89.999998000000019 
		21.6 -89.332347 22.392 -88.641719 23.184 -88.072143000000011 24 -87.77436 24.792 
		-87.703394000000017 25.584 -87.705232000000009 26.4 -87.767031000000017 27.192 -87.875925 
		27.984 -88.019086 28.8 -88.183652000000009 29.592 -88.356777000000008 30.384 -88.52564000000001 
		31.2 -88.677345000000017 31.992 -88.7991;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Pelvis_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 29 ".ktv[0:28]"  0 179.99996800000002 0.792 179.99999500000004 
		1.584 179.99999500000004 2.4 180.000022 3.192 180.000022 3.984 180.000009 4.8 180.000009 
		5.592 179.99999500000004 6.384 179.99999500000004 11.184 179.99999500000004 12 179.99999500000004 
		12.792 179.99996800000002 13.584 180.000009 14.4 179.99999500000004 15.192 179.99999500000004 
		15.984 179.99999500000004 16.8 179.99996800000002 17.592 180.000009 18.384 180.000009 
		19.2 179.99996800000002 19.992 179.99999500000004 20.784 179.99999500000004 27.192 
		179.99999500000004 27.984 179.99999500000004 28.8 179.99996800000002 29.592 179.99999500000004 
		30.384 179.99996800000002 31.2 179.99999500000004 31.992 180.000009;
	setAttr -s 29 ".kit[0:28]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
	setAttr -s 29 ".kot[0:28]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 2;
createNode animCurveTL -n "Bip01_Pelvis_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_Pelvis_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_Pelvis_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTU -n "Bip01_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTU -n "Bip01_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1;
createNode animCurveTA -n "Bip01_rotateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -94.980988000000011 0.792 -94.488285 
		1.584 -93.994791 2.4 -93.500176 3.192 -93.004188 3.984 -92.506718 4.8 -92.007732 
		5.592 -91.507304 6.384 -91.005627000000018 7.2 -90.503014 7.992 -89.999902 8.784 
		-89.455215 9.6 -88.83362 10.392 -88.177088000000012 11.184 -87.512620000000013 12 
		-86.870446 12.792 -86.280284 13.584 -85.771353 14.4 -85.372408 15.192 -85.112055000000012 
		15.984 -85.018850000000015 16.8 -85.112041000000019 17.592 -85.370325 18.384 -85.771353 
		19.2 -86.280284 19.992 -86.870446 20.784 -87.512614 21.6 -88.177088000000012 22.392 
		-88.833613000000014 23.184 -89.451547000000019 24 -89.999902 24.792 -90.503014 25.584 
		-91.005620000000008 26.4 -91.507297000000008 27.192 -92.007725000000008 27.984 -92.506718 
		28.8 -93.004181 29.592 -93.500155000000021 30.384 -93.99478400000001 31.2 -94.48827900000002 
		31.992 -94.980981;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.43523000000000006 0.792 0.28328500000000006 
		1.584 0.12137000000000002 2.4 -0.044410000000000005 3.192 -0.20793800000000004 3.984 
		-0.36309600000000003 4.8 -0.50375800000000015 5.592 -0.62380400000000014 6.384 -0.717112 
		7.2 -0.77757100000000012 7.992 -0.79907800000000007 8.784 -0.768399 9.6 -0.68158400000000008 
		10.392 -0.550659 11.184 -0.38740800000000003 12 -0.20537500000000003 12.792 -0.01943 
		13.584 0.15443700000000002 14.4 0.299468 15.192 0.39862700000000006 15.984 0.43523000000000006 
		16.8 0.39862700000000006 17.592 0.30024800000000007 18.384 0.15443700000000002 19.2 
		-0.01943 19.992 -0.20537500000000003 20.784 -0.38740800000000003 21.6 -0.550659 22.392 
		-0.68158400000000008 23.184 -0.76802200000000009 24 -0.79907800000000007 24.792 -0.77757100000000012 
		25.584 -0.717112 26.4 -0.62380400000000014 27.192 -0.50375800000000015 27.984 -0.36309600000000003 
		28.8 -0.20793900000000004 29.592 -0.044410000000000005 30.384 0.12137000000000002 
		31.2 0.28328500000000006 31.992 0.43523000000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 4.9810690000000006 0.792 4.4883640000000007 
		1.584 3.994874 2.4 3.5002590000000002 3.192 3.0042810000000006 3.984 2.506809 4.8 
		2.007818 5.592 1.5073920000000003 6.384 1.0057230000000001 7.2 0.50312 7.992 0 8.784 
		-0.54468 9.6 -1.1662870000000003 10.392 -1.8228210000000002 11.184 -2.4872900000000002 
		12 -3.1294630000000003 12.792 -3.719624 13.584 -4.2285700000000013 14.4 -4.627507 
		15.192 -4.8878730000000008 15.984 -4.9810680000000005 16.8 -4.8878720000000007 17.592 
		-4.6295940000000009 18.384 -4.2285700000000013 19.2 -3.719624 19.992 -3.1294630000000003 
		20.784 -2.487291 21.6 -1.8228210000000002 22.392 -1.1662870000000003 23.184 -0.548355 
		24 0 24.792 0.50311900000000009 25.584 1.0057230000000001 26.4 1.507391 27.192 2.007819 
		27.984 2.50681 28.8 3.0042810000000006 29.592 3.5002590000000002 30.384 3.994874 
		31.2 4.4883640000000007 31.992 4.9810690000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.860637 0.792 0.85595 1.584 0.85013 
		2.4 0.84487600000000007 3.192 0.841891 3.984 0.84287400000000012 4.8 0.849814 5.592 
		0.861576 6.384 0.87518000000000007 7.2 0.887642 7.992 0.895982 8.784 0.899893 9.6 
		0.901413 10.392 0.90092600000000012 11.184 0.898883 12 0.895716 12.792 0.890562 13.584 
		0.88313200000000014 14.4 0.874721 15.192 0.866628 15.984 0.86014700000000011 16.8 
		0.854614 17.592 0.849181 18.384 0.844722 19.2 0.842306 19.992 0.84287400000000012 
		20.784 0.84790600000000016 21.6 0.856754 22.392 0.867196 23.184 0.877012 24 0.883978 
		24.792 0.888144 25.584 0.89099 26.4 0.892444 27.192 0.892435 27.984 0.890892 28.8 
		0.88722 29.592 0.881466 30.384 0.874523 31.2 0.867283 31.992 0.860637;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.792 -0.031243 1.584 -0.062258000000000008 
		2.4 -0.093387 3.192 -0.124971 3.984 -0.15735 4.8 -0.19073 5.592 -0.224884 6.384 -0.259503 
		7.2 -0.294279 7.992 -0.32890500000000006 8.784 -0.36371900000000007 9.6 -0.399593 
		10.392 -0.435019 11.184 -0.469377 12 -0.501825 12.792 -0.531776 13.584 -0.559792 
		14.4 -0.586753 15.192 -0.613537 15.984 -0.641023 16.8 -0.668777 17.592 -0.696041 
		18.384 -0.723982 19.2 -0.7527370000000001 19.992 -0.783129 20.784 -0.81591100000000016 
		21.6 -0.850648 22.392 -0.886212 23.184 -0.921472 24 -0.955299 24.792 -0.987764 25.584 
		-1.019619 26.4 -1.050759 27.192 -1.081077 27.984 -1.110465 28.8 -1.153366 29.592 
		-1.190128 30.384 -1.218954 31.2 -1.237654 31.992 -1.244174;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "char_Fbx_Root_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 32 1.244;
createNode lightLinker -n "lightLinker1";
	setAttr -s 3 ".lnk";
	setAttr -s 3 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
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
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
select -ne :lambert1;
	setAttr ".miic" -type "float3" 3.1415927 3.1415927 3.1415927 ;
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
	setAttr ".w" 320;
	setAttr ".h" 240;
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
	setAttr ".enpt" no;
	setAttr -k off ".clmt";
	setAttr -k off -cb on ".tcov";
	setAttr -k off -cb on ".lith";
	setAttr -k off -cb on ".sobc";
	setAttr -k off -cb on ".cuth";
	setAttr ".hgcd" no;
	setAttr ".hgci" no;
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
	setAttr -av ".ef";
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
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "Bip01_R_Toe0_scaleZ.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "Bip01_R_Toe0_scaleY.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "Bip01_R_Toe0_scaleX.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "Bip01_R_Toe0_rotateZ.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "Bip01_R_Toe0_rotateY.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "Bip01_R_Toe0_rotateX.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "Bip01_R_Toe0_translateZ.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "Bip01_R_Toe0_translateY.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "Bip01_R_Toe0_translateX.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "Bip01_R_Foot_scaleZ.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "Bip01_R_Foot_scaleY.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "Bip01_R_Foot_scaleX.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "Bip01_R_Foot_rotateZ.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "Bip01_R_Foot_rotateY.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "Bip01_R_Foot_rotateX.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "Bip01_R_Foot_translateZ.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "Bip01_R_Foot_translateY.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "Bip01_R_Foot_translateX.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "Bip01_R_Calf_scaleZ.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "Bip01_R_Calf_scaleY.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "Bip01_R_Calf_scaleX.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "Bip01_R_Calf_rotateZ.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "Bip01_R_Calf_rotateY.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "Bip01_R_Calf_rotateX.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "Bip01_R_Calf_translateZ.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "Bip01_R_Calf_translateY.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "Bip01_R_Calf_translateX.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "Bip01_R_Thigh_scaleZ.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "Bip01_R_Thigh_scaleY.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "Bip01_R_Thigh_scaleX.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "Bip01_R_Thigh_rotateZ.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "Bip01_R_Thigh_rotateY.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "Bip01_R_Thigh_rotateX.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "Bip01_R_Thigh_translateZ.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "Bip01_R_Thigh_translateY.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "Bip01_R_Thigh_translateX.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "Bip01_L_Toe0_scaleZ.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "Bip01_L_Toe0_scaleY.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "Bip01_L_Toe0_scaleX.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "Bip01_L_Toe0_rotateZ.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "Bip01_L_Toe0_rotateY.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "Bip01_L_Toe0_rotateX.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "Bip01_L_Toe0_translateZ.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "Bip01_L_Toe0_translateY.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "Bip01_L_Toe0_translateX.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "Bip01_L_Foot_scaleZ.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "Bip01_L_Foot_scaleY.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "Bip01_L_Foot_scaleX.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "Bip01_L_Foot_rotateZ.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "Bip01_L_Foot_rotateY.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "Bip01_L_Foot_rotateX.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "Bip01_L_Foot_translateZ.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "Bip01_L_Foot_translateY.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "Bip01_L_Foot_translateX.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "Bip01_L_Calf_scaleZ.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "Bip01_L_Calf_scaleY.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "Bip01_L_Calf_scaleX.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "Bip01_L_Calf_rotateZ.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "Bip01_L_Calf_rotateY.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "Bip01_L_Calf_rotateX.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "Bip01_L_Calf_translateZ.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "Bip01_L_Calf_translateY.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "Bip01_L_Calf_translateX.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "Bip01_L_Thigh_scaleZ.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "Bip01_L_Thigh_scaleY.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "Bip01_L_Thigh_scaleX.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "Bip01_L_Thigh_rotateZ.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "Bip01_L_Thigh_rotateY.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "Bip01_L_Thigh_rotateX.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "Bip01_L_Thigh_translateZ.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "Bip01_L_Thigh_translateY.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "Bip01_L_Thigh_translateX.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "Bip01_L_Finger11_scaleZ.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "Bip01_L_Finger11_scaleY.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "Bip01_L_Finger11_scaleX.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "Bip01_L_Finger11_rotateZ.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "Bip01_L_Finger11_rotateY.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "Bip01_L_Finger11_rotateX.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "Bip01_L_Finger11_translateZ.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "Bip01_L_Finger11_translateY.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "Bip01_L_Finger11_translateX.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "Bip01_L_Finger1_scaleZ.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "Bip01_L_Finger1_scaleY.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "Bip01_L_Finger1_scaleX.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "Bip01_L_Finger1_rotateZ.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "Bip01_L_Finger1_rotateY.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "Bip01_L_Finger1_rotateX.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "Bip01_L_Finger1_translateZ.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "Bip01_L_Finger1_translateY.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "Bip01_L_Finger1_translateX.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "Bip01_L_Finger21_scaleZ.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "Bip01_L_Finger21_scaleY.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "Bip01_L_Finger21_scaleX.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "Bip01_L_Finger21_rotateZ.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "Bip01_L_Finger21_rotateY.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "Bip01_L_Finger21_rotateX.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "Bip01_L_Finger21_translateZ.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "Bip01_L_Finger21_translateY.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "Bip01_L_Finger21_translateX.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "Bip01_L_Finger2_scaleZ.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "Bip01_L_Finger2_scaleY.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "Bip01_L_Finger2_scaleX.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "Bip01_L_Finger2_rotateZ.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "Bip01_L_Finger2_rotateY.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "Bip01_L_Finger2_rotateX.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "Bip01_L_Finger2_translateZ.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "Bip01_L_Finger2_translateY.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "Bip01_L_Finger2_translateX.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "Bip01_L_Finger01_scaleZ.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "Bip01_L_Finger01_scaleY.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "Bip01_L_Finger01_scaleX.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "Bip01_L_Finger01_rotateZ.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "Bip01_L_Finger01_rotateY.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "Bip01_L_Finger01_rotateX.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "Bip01_L_Finger01_translateZ.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "Bip01_L_Finger01_translateY.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "Bip01_L_Finger01_translateX.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "Bip01_L_Finger0_scaleZ.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "Bip01_L_Finger0_scaleY.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "Bip01_L_Finger0_scaleX.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "Bip01_L_Finger0_rotateZ.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "Bip01_L_Finger0_rotateY.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "Bip01_L_Finger0_rotateX.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "Bip01_L_Finger0_translateZ.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "Bip01_L_Finger0_translateY.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "Bip01_L_Finger0_translateX.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "Bip01_L_Hand_scaleZ.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "Bip01_L_Hand_scaleY.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "Bip01_L_Hand_scaleX.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "Bip01_L_Hand_rotateZ.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "Bip01_L_Hand_rotateY.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "Bip01_L_Hand_rotateX.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "Bip01_L_Hand_translateZ.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "Bip01_L_Hand_translateY.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "Bip01_L_Hand_translateX.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "Bip01_L_Forearm_scaleZ.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "Bip01_L_Forearm_scaleY.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "Bip01_L_Forearm_scaleX.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "Bip01_L_Forearm_rotateZ.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "Bip01_L_Forearm_rotateY.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "Bip01_L_Forearm_rotateX.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "Bip01_L_Forearm_translateZ.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "Bip01_L_Forearm_translateY.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "Bip01_L_Forearm_translateX.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "Bip01_L_UpperArm_scaleZ.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "Bip01_L_UpperArm_scaleY.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "Bip01_L_UpperArm_scaleX.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "Bip01_L_UpperArm_rotateZ.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "Bip01_L_UpperArm_rotateY.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "Bip01_L_UpperArm_rotateX.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "Bip01_L_UpperArm_translateZ.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "Bip01_L_UpperArm_translateY.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "Bip01_L_UpperArm_translateX.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "Bip01_L_Clavicle_scaleZ.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "Bip01_L_Clavicle_scaleY.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "Bip01_L_Clavicle_scaleX.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "Bip01_L_Clavicle_rotateZ.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "Bip01_L_Clavicle_rotateY.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "Bip01_L_Clavicle_rotateX.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "Bip01_L_Clavicle_translateZ.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "Bip01_L_Clavicle_translateY.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "Bip01_L_Clavicle_translateX.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "Bip01_R_Finger11_scaleZ.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "Bip01_R_Finger11_scaleY.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "Bip01_R_Finger11_scaleX.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "Bip01_R_Finger11_rotateZ.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "Bip01_R_Finger11_rotateY.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "Bip01_R_Finger11_rotateX.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "Bip01_R_Finger11_translateZ.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "Bip01_R_Finger11_translateY.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "Bip01_R_Finger11_translateX.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "Bip01_R_Finger1_scaleZ.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "Bip01_R_Finger1_scaleY.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "Bip01_R_Finger1_scaleX.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "Bip01_R_Finger1_rotateZ.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "Bip01_R_Finger1_rotateY.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "Bip01_R_Finger1_rotateX.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "Bip01_R_Finger1_translateZ.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "Bip01_R_Finger1_translateY.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "Bip01_R_Finger1_translateX.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "Bip01_R_Finger21_scaleZ.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "Bip01_R_Finger21_scaleY.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "Bip01_R_Finger21_scaleX.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "Bip01_R_Finger21_rotateZ.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "Bip01_R_Finger21_rotateY.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "Bip01_R_Finger21_rotateX.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "Bip01_R_Finger21_translateZ.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "Bip01_R_Finger21_translateY.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "Bip01_R_Finger21_translateX.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "Bip01_R_Finger2_scaleZ.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "Bip01_R_Finger2_scaleY.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "Bip01_R_Finger2_scaleX.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "Bip01_R_Finger2_rotateZ.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "Bip01_R_Finger2_rotateY.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "Bip01_R_Finger2_rotateX.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "Bip01_R_Finger2_translateZ.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "Bip01_R_Finger2_translateY.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "Bip01_R_Finger2_translateX.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "Bip01_R_Finger01_scaleZ.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "Bip01_R_Finger01_scaleY.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "Bip01_R_Finger01_scaleX.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "Bip01_R_Finger01_rotateZ.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "Bip01_R_Finger01_rotateY.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "Bip01_R_Finger01_rotateX.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "Bip01_R_Finger01_translateZ.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "Bip01_R_Finger01_translateY.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "Bip01_R_Finger01_translateX.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "Bip01_R_Finger0_scaleZ.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "Bip01_R_Finger0_scaleY.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "Bip01_R_Finger0_scaleX.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "Bip01_R_Finger0_rotateZ.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "Bip01_R_Finger0_rotateY.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "Bip01_R_Finger0_rotateX.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "Bip01_R_Finger0_translateZ.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "Bip01_R_Finger0_translateY.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "Bip01_R_Finger0_translateX.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "Bip01_R_Hand_scaleZ.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "Bip01_R_Hand_scaleY.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "Bip01_R_Hand_scaleX.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "Bip01_R_Hand_rotateZ.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "Bip01_R_Hand_rotateY.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "Bip01_R_Hand_rotateX.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "Bip01_R_Hand_translateZ.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "Bip01_R_Hand_translateY.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "Bip01_R_Hand_translateX.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "Bip01_R_Forearm_scaleZ.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "Bip01_R_Forearm_scaleY.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "Bip01_R_Forearm_scaleX.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "Bip01_R_Forearm_rotateZ.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "Bip01_R_Forearm_rotateY.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "Bip01_R_Forearm_rotateX.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "Bip01_R_Forearm_translateZ.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "Bip01_R_Forearm_translateY.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "Bip01_R_Forearm_translateX.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "Bip01_R_UpperArm_scaleZ.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "Bip01_R_UpperArm_scaleY.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "Bip01_R_UpperArm_scaleX.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "Bip01_R_UpperArm_rotateZ.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "Bip01_R_UpperArm_rotateY.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "Bip01_R_UpperArm_rotateX.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "Bip01_R_UpperArm_translateZ.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "Bip01_R_UpperArm_translateY.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "Bip01_R_UpperArm_translateX.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "Bip01_R_Clavicle_scaleZ.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "Bip01_R_Clavicle_scaleY.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "Bip01_R_Clavicle_scaleX.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "Bip01_R_Clavicle_rotateZ.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "Bip01_R_Clavicle_rotateY.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "Bip01_R_Clavicle_rotateX.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "Bip01_R_Clavicle_translateZ.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "Bip01_R_Clavicle_translateY.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "Bip01_R_Clavicle_translateX.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "Bip01_Head_scaleZ.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "Bip01_Head_scaleY.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "Bip01_Head_scaleX.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "Bip01_Head_rotateZ.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "Bip01_Head_rotateY.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "Bip01_Head_rotateX.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "Bip01_Head_translateZ.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "Bip01_Head_translateY.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "Bip01_Head_translateX.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "Bip01_Neck_scaleZ.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "Bip01_Neck_scaleY.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "Bip01_Neck_scaleX.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "Bip01_Neck_rotateZ.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "Bip01_Neck_rotateY.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "Bip01_Neck_rotateX.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "Bip01_Neck_translateZ.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "Bip01_Neck_translateY.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "Bip01_Neck_translateX.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "Bip01_Spine1_scaleZ.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "Bip01_Spine1_scaleY.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "Bip01_Spine1_scaleX.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "Bip01_Spine1_rotateZ.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "Bip01_Spine1_rotateY.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "Bip01_Spine1_rotateX.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "Bip01_Spine1_translateZ.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "Bip01_Spine1_translateY.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "Bip01_Spine1_translateX.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "Bip01_Spine_scaleZ.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "Bip01_Spine_scaleY.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "Bip01_Spine_scaleX.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "Bip01_Spine_rotateZ.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "Bip01_Spine_rotateY.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "Bip01_Spine_rotateX.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "Bip01_Spine_translateZ.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "Bip01_Spine_translateY.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "Bip01_Spine_translateX.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "Bip01_Pelvis_scaleZ.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "Bip01_Pelvis_scaleY.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "Bip01_Pelvis_scaleX.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "Bip01_Pelvis_rotateZ.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "Bip01_Pelvis_rotateY.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "Bip01_Pelvis_rotateX.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "Bip01_Pelvis_translateZ.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "Bip01_Pelvis_translateY.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "Bip01_Pelvis_translateX.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "Bip01_scaleZ.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "Bip01_scaleY.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "Bip01_scaleX.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "Bip01_rotateZ.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "Bip01_rotateY.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "Bip01_rotateX.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "Bip01_translateZ.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "Bip01_translateY.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "Bip01_translateX.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "char_Fbx_Root_translateY.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[2].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[2].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[3].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[3].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of walk.ma
