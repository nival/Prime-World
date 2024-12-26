//Maya ASCII 2008 scene
//Name: walk.ma
//Last modified: Mon, Jan 26, 2009 04:26:31 PM
//Codeset: 1252
requires maya "2008";
currentUnit -l meter -a degree -t ntsc;
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
	setAttr ".se" 40;
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
	setAttr -s 41 ".ktv[0:40]"  0 89.999998000000019 0.99 89.999984000000012 
		1.98 89.999998000000019 3 89.999998000000019 3.99 89.999984000000012 4.98 89.999998000000019 
		6 90.21926000000002 6.99 90.793331000000009 7.98 91.502919 9 92.076983 9.99 92.29625200000001 
		10.98 94.781314000000009 12 97.686385000000016 12.99 101.07915800000002 13.98 104.33019800000001 
		15 107.196036 15.99 106.287594 16.98 103.03663500000002 18 100.067901 18.99 99.724465 
		19.98 103.607899 21 102.92740700000002 21.99 101.159174 22.98 98.943795 24 97.162256 
		24.99 96.481785 25.98 94.702979 27 90.046040000000019 27.99 84.289782 28.98 79.632864000000012 
		30 77.854085 30.99 78.939067 31.98 81.779537 33 85.290535 33.99 88.130998 34.98 89.215953 
		36 89.290826 36.99 89.486832000000021 37.98 89.729112000000015 39 89.925125 39.99 
		89.999998000000019;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Toe0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.0000000000000015e-006 0.99 4.0000000000000015e-006 
		1.98 -3.0000000000000005e-006 3 2.0000000000000008e-006 3.99 -1.0000000000000004e-006 
		4.98 1.0000000000000004e-006 6 -1.0000000000000004e-006 6.99 -4.0000000000000015e-006 
		7.98 -8.000000000000003e-006 9 -1.1000000000000001e-005 9.99 -1.7999999999999997e-005 
		10.98 -0.10381500000000002 12 -0.26648800000000006 12.99 -0.40211200000000008 13.98 
		-0.36210300000000006 15 -0.021326 15.99 0.315405 16.98 0.087562000000000015 18 -0.386262 
		18.99 -0.574002 19.98 3.3000000000000009e-005 21 2.9e-005 21.99 2.7e-005 22.98 3.3000000000000009e-005 
		24 3.4e-005 24.99 2.9e-005 25.98 3.4e-005 27 3.2000000000000012e-005 27.99 3.4e-005 
		28.98 3.5999999999999994e-005 30 2.7999999999999996e-005 30.99 3.5999999999999994e-005 
		31.98 3.1000000000000008e-005 33 3.0000000000000011e-005 33.99 3.2000000000000012e-005 
		34.98 3.500000000000001e-005 36 3.2000000000000012e-005 36.99 2e-005 37.98 1.2000000000000002e-005 
		39 4.0000000000000015e-006 39.99 2.0000000000000008e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Toe0_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 5e-006 0.99 1.0000000000000004e-006 1.98 
		4.0000000000000015e-006 3 1.0000000000000004e-006 3.99 1.0000000000000004e-006 4.98 
		4.0000000000000015e-006 6 3.0000000000000005e-006 6.99 5e-006 7.98 3.0000000000000005e-006 
		9 0 9.99 0 10.98 0.029588999999999997 12 0.133146 12.99 0.19171000000000002 13.98 
		0.164252 15 -0.013629 15.99 0.020750000000000005 16.98 0.197897 18 0.32219300000000006 
		18.99 0.26576000000000005 19.98 1.3000000000000001e-005 21 1.1000000000000001e-005 
		21.99 7.0000000000000024e-006 22.98 8.000000000000003e-006 24 6.000000000000001e-006 
		24.99 6.000000000000001e-006 25.98 8.000000000000003e-006 27 6.000000000000001e-006 
		27.99 0 28.98 -3.0000000000000005e-006 30 -5e-006 30.99 -1.0000000000000004e-006 
		31.98 0 33 5e-006 33.99 5e-006 34.98 2.0000000000000008e-006 36 3.0000000000000005e-006 
		36.99 -1.0000000000000004e-006 37.98 1.0000000000000004e-006 39 5e-006 39.99 -1.0000000000000004e-006;
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
	setAttr ".ktv[0]"  0 0.112377;
createNode animCurveTL -n "Bip01_R_Toe0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.095261;
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
	setAttr -s 41 ".ktv[0:40]"  0 1.8358330000000003 0.99 0.899185 1.98 
		-0.15368800000000002 3 -1.168453 3.99 -1.9887330000000003 4.98 -2.4564670000000004 
		6 -1.169116 6.99 0.702023 7.98 2.189624 9 2.309607 9.99 -0.43609200000000004 10.98 
		-1.585992 12 -3.111102 12.99 -4.8821640000000013 13.98 -5.514509 15 -6.289496 15.99 
		-3.1131380000000006 16.98 1.3227040000000003 18 5.030169 18.99 6.663055 19.98 5.3350810000000006 
		21 4.94731 21.99 4.3392100000000005 22.98 2.766064 24 -0.88119900000000007 24.99 
		-8.4896220000000024 25.98 -8.3857520000000019 27 -6.964139 27.99 -4.944144 28.98 
		-3.065084 30 -2.096339 30.99 -2.451556 31.98 -3.642587 33 -5.103242 33.99 -6.2587050000000009 
		34.98 -6.526091000000001 36 -5.698189 36.99 -4.164144 37.98 -2.22597 39 -0.18264800000000003 
		39.99 1.6652820000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Foot_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.8358290000000004 0.99 -2.1522230000000007 
		1.98 -2.528211 3 -2.923311 3.99 -3.2997450000000006 4.98 -3.6320360000000003 6 -3.9763770000000003 
		6.99 -4.286118 7.98 -4.481309 9 -4.539613 9.99 -4.5168050000000006 10.98 -4.762521 
		12 -5.137117 12.99 -5.554857000000001 13.98 -5.8634310000000012 15 -5.8805360000000011 
		15.99 -5.193445 16.98 -4.050152 18 -2.8255200000000005 18.99 -1.88952 19.98 -1.518615 
		21 -1.125066 21.99 -0.895623 22.98 -0.67702000000000007 24 -0.22739600000000004 24.99 
		0.655859 25.98 1.9350510000000003 27 3.556519 27.99 5.19528 28.98 6.5307970000000006 
		30 7.2550670000000013 30.99 7.210979 31.98 6.5873660000000012 33 5.608244 33.99 4.491183 
		34.98 3.444471 36 2.44087 36.99 1.345681 37.98 0.219562 39 -0.860299 39.99 -1.8247240000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Foot_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 3.723995 0.99 3.0299610000000006 1.98 
		2.463352 3 2.007376 3.99 1.585375 4.98 1.073292 6 0.35822900000000008 6.99 -0.576885 
		7.98 -1.6791110000000002 9 -2.8426100000000005 9.99 -3.9392400000000003 10.98 -5.04556 
		12 -6.255913 12.99 -7.3859160000000008 13.98 -8.313172 15 -8.9402360000000023 15.99 
		-9.295954 16.98 -9.416126 18 -9.290379 18.99 -8.911907 19.98 -8.2371900000000018 
		21 -7.1855480000000007 21.99 -5.801091 22.98 -4.255952 24 -2.8253890000000004 24.99 
		-1.724459 25.98 -0.89363 27 -0.045803 27.99 0.85570400000000013 28.98 1.798299 30 
		2.703092 30.99 3.4862200000000003 31.98 4.14885 33 4.691059 33.99 5.1166980000000013 
		34.98 5.4469730000000007 36 5.6312320000000007 36.99 5.5544270000000004 37.98 5.192209000000001 
		39 4.562155 39.99 3.729442;
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
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Foot_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.431489 0.99 0.431489 1.98 0.431489 
		3 0.431489 3.99 0.431489 4.98 0.431489 6 0.431489 6.99 0.431489 7.98 0.431489 9 0.431489 
		9.99 0.431489 10.98 0.431489 12 0.431489 12.99 0.431489 13.98 0.431489 15 0.431489 
		15.99 0.431489 16.98 0.431489 18 0.431489 18.99 0.431489 19.98 0.431489 21 0.431489 
		21.99 0.431489 22.98 0.431489 24 0.431489 24.99 0.431489 25.98 0.431489 27 0.431489 
		27.99 0.431489 28.98 0.431489 30 0.431489 30.99 0.431489 31.98 0.431489 33 0.431489 
		33.99 0.431489 34.98 0.431489 36 0.431489 36.99 0.431489 37.98 0.431489 39 0.431489 
		39.99 0.431489;
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
	setAttr -s 44 ".ktv[0:43]"  0 -13.587198 0.99 -16.659486000000005 1.98 
		-20.248247 3 -23.578766 3.99 -25.876334000000003 4.98 -26.366221 6 -26.358668000000005 
		6.99 -24.765189000000003 7.98 -21.358079 9 -15.870683 9.48 -11.367996000000002 9.99 
		-6.86531 10.98 -4.233829000000001 12 -1.7907940000000002 12.99 -0.11869600000000002 
		13.98 -0.67840200000000006 15 -0.07662 15.99 -2.8748829999999996 16.98 -7.403435 
		18 -12.872027 18.99 -18.462559000000002 19.98 -23.363062000000003 21 -27.521774000000004 
		21.99 -31.457715 22.98 -35.317694 24 -39.106038 24.99 -42.923389 25.98 -47.193271 
		27 -51.865698 27.99 -56.303391000000005 28.98 -59.869187 30 -61.925879 30.99 -62.553799 
		31.98 -62.177763 33 -60.677239 33.99 -57.931749 34.98 -53.820791 36 -47.830286 36.99 
		-40.040609 37.5 -35.631702 37.98 -31.222794000000004 38.49 -26.685382 39 -22.147968000000002 
		39.99 -13.587201000000002;
	setAttr -s 44 ".kit[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
	setAttr -s 44 ".kot[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
createNode animCurveTA -n "Bip01_R_Calf_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "Bip01_R_Calf_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -1.0000000000000004e-006;
createNode animCurveTL -n "Bip01_R_Calf_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Calf_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Calf_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.361527 0.99 0.361527 1.98 0.361527 
		3 0.361527 3.99 0.361527 4.98 0.361527 6 0.361527 6.99 0.361527 7.98 0.361527 9 0.361527 
		9.99 0.361527 10.98 0.361527 12 0.361527 12.99 0.361527 13.98 0.361527 15 0.361527 
		15.99 0.361527 16.98 0.361527 18 0.361527 18.99 0.361527 19.98 0.361527 21 0.361527 
		21.99 0.361527 22.98 0.361527 24 0.361527 24.99 0.361527 25.98 0.361527 27 0.361527 
		27.99 0.361527 28.98 0.361527 30 0.361527 30.99 0.361526 31.98 0.361527 33 0.361527 
		33.99 0.361527 34.98 0.361527 36 0.361527 36.99 0.361527 37.98 0.361527 39 0.361527 
		39.99 0.361527;
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
	setAttr -s 41 ".ktv[0:40]"  0 151.58399200000002 0.99 150.56010600000002 
		1.98 149.084443 3 147.792486 3.99 147.32306100000002 4.98 148.316607 6 150.448131 
		6.99 153.860466 7.98 158.437144 9 164.08754000000002 9.99 171.37895800000004 10.98 
		175.381667 12 179.30774200000002 12.99 182.754679 13.98 185.00984300000002 15 187.953531 
		15.99 188.931642 16.98 189.09338100000002 18 188.62241200000003 18.99 187.780646 
		19.98 186.83444600000004 21 186.37276600000004 21.99 185.820668 22.98 185.06949800000004 
		24 183.94089100000002 24.99 182.04207100000002 25.98 178.92695900000004 27 175.004231 
		27.99 170.657649 28.98 166.271029 30 162.227926 30.99 158.136424 31.98 153.730338 
		33 149.58262400000004 33.99 146.267168 34.98 144.35690100000002 36 144.228015 36.99 
		145.481177 37.98 147.522584 39 149.756165 39.99 151.583978;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Thigh_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.977789 0.99 -2.6218990000000004 1.98 
		-3.2639840000000007 3 -3.8362850000000006 3.99 -4.287417 4.98 -4.576436 6 -4.852502 
		6.99 -5.067564 7.98 -5.2083410000000008 9 -5.2802370000000005 9.99 -5.321721000000001 
		10.98 -5.3392800000000005 12 -5.270245 12.99 -5.102234000000001 13.98 -4.779094 15 
		-4.411937 15.99 -3.766491 16.98 -2.96669 18 -2.059933 18.99 -1.128888 19.98 -0.287914 
		21 0.57329400000000008 21.99 1.3591460000000002 22.98 2.1090290000000005 24 2.873752 
		24.99 3.7378520000000006 25.98 4.0557000000000007 27 4.178036 27.99 4.171959 28.98 
		4.0936780000000006 30 3.991285 30.99 3.8620320000000006 31.98 3.624174 33 3.225985 
		33.99 2.651769 34.98 1.926154 36 1.099126 36.99 0.24548000000000003 37.98 -0.56611700000000009 
		39 -1.3040560000000003 39.99 -1.977787;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Thigh_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 178.04042800000002 0.99 178.663833 1.98 
		179.30126700000002 3 179.906695 3.99 180.43348000000003 4.98 180.84210300000004 6 
		181.24020700000003 6.99 181.611646 7.98 181.93058900000003 9 182.159223 9.99 182.19870100000003 
		10.98 182.534897 12 182.897566 12.99 183.28187400000002 13.98 183.729811 15 184.06811 
		15.99 184.54946100000004 16.98 185.089538 18 185.614765 18.99 186.041598 19.98 186.288577 
		21 186.28116000000003 21.99 186.14161900000002 22.98 185.931632 24 185.701003 24.99 
		185.454461 25.98 185.412291 27 185.38189700000004 27.99 185.31983800000003 28.98 
		185.17787900000002 30 184.90024600000004 30.99 184.468592 31.98 183.929908 33 183.32229500000003 
		33.99 182.67505200000002 34.98 181.99191 36 181.262392 36.99 180.482316 37.98 179.657502 
		39 178.823277 39.99 178.04042800000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.083325 0.99 -0.084486 1.98 -0.085697 
		3 -0.086906 3.99 -0.088067 4.98 -0.089139 6 -0.090088000000000015 6.99 -0.090877 
		7.98 -0.091469 9 -0.091841 9.99 -0.091975 10.98 -0.091864000000000015 12 -0.091545 
		12.99 -0.091066000000000008 13.98 -0.090451 15 -0.089746 15.99 -0.088997 16.98 -0.088251999999999983 
		18 -0.08756 18.99 -0.08697 19.98 -0.086536000000000016 21 -0.086240000000000011 21.99 
		-0.086004000000000011 22.98 -0.085793 24 -0.085591000000000014 24.99 -0.085391 25.98 
		-0.085201 27 -0.085031 27.99 -0.084883000000000014 28.98 -0.084748 30 -0.084618 30.99 
		-0.0845 31.98 -0.084399 33 -0.084304 33.99 -0.08421 34.98 -0.08411 36 -0.083996 36.99 
		-0.083864000000000008 37.98 -0.083709 39 -0.08353 39.99 -0.083325;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.029011000000000002 0.99 0.028585 1.98 
		0.028181000000000005 3 0.02778 3.99 0.027366 4.98 0.026927 6 0.026451 6.99 0.025926 
		7.98 0.025343 9 0.024694000000000004 9.99 0.023977 10.98 0.023133 12 0.022125 12.99 
		0.021021 13.98 0.019866 15 0.01871 15.99 0.017605 16.98 0.0166 18 0.015749 18.99 
		0.015102 19.98 0.014714000000000001 21 0.014578 21.99 0.014642 22.98 0.014898 24 
		0.015328 24.99 0.015905 25.98 0.016594 27 0.017353 27.99 0.018146 28.98 0.01894 30 
		0.019703 30.99 0.020482 31.98 0.021335000000000003 33 0.022248 33.99 0.023201 34.98 
		0.024181 36 0.025173 36.99 0.026164 37.98 0.027141 39 0.028094 39.99 0.029011000000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Thigh_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.119087 0.99 -0.116968 1.98 -0.11473 
		3 -0.11243300000000002 3.99 -0.11013500000000001 4.98 -0.1079 6 -0.10579100000000001 
		6.99 -0.103771 7.98 -0.10185 9 -0.100155 9.99 -0.098814 10.98 -0.097966 12 -0.097673 
		12.99 -0.097815 13.98 -0.098205000000000015 15 -0.098793 15.99 -0.099528 16.98 -0.100366 
		18 -0.101263 18.99 -0.102178 19.98 -0.103072 21 -0.10418800000000002 21.99 -0.105666 
		22.98 -0.107353 24 -0.10903400000000002 24.99 -0.11053400000000001 25.98 -0.111667 
		27 -0.112396 27.99 -0.112874 28.98 -0.113204 30 -0.113492 30.99 -0.113814 31.98 -0.114247 
		33 -0.114783 33.99 -0.115348 34.98 -0.115938 36 -0.116548 36.99 -0.117174 37.98 -0.11781000000000001 
		39 -0.11845000000000001 39.99 -0.119087;
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
	setAttr -s 42 ".ktv[0:41]"  0 117.41688800000001 0.99 117.18609599999999 
		1.98 116.58187000000001 3 115.83498900000001 3.99 115.230763 4.98 114.99995700000001 
		6 111.227207 6.48 106.288645 6.99 101.350084 7.5 95.245699 7.98 89.141313 8.49 84.202766 
		9 79.26422500000001 9.99 75.491536000000011 10.98 75.679578 12 76.177826 12.99 76.786444 
		13.98 77.275492000000014 15 77.461574000000013 15.99 78.662745 16.98 81.802753 18 
		85.676263 18.99 88.805459 19.98 89.999977000000015 21 89.999977000000015 24 89.999977000000015 
		24.99 89.999977000000015 25.98 90.108905000000007 27 90.394086000000016 27.99 90.746592 
		28.98 91.031766 30 91.140694000000011 30.99 92.514586 31.98 96.111459000000011 33 
		100.557434 33.99 104.154293 34.98 105.528159 36 106.663452 36.99 109.63563600000002 
		37.98 113.309451 39 116.28162800000001 39.99 117.41688800000001;
	setAttr -s 42 ".kit[0:41]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 42 ".kot[0:41]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Toe0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 44 ".ktv[0:43]"  0 -4e-005 0.99 -3.9e-005 1.98 -3.1000000000000008e-005 
		3 -3.1000000000000008e-005 3.99 -3.1000000000000008e-005 4.98 -3.0000000000000011e-005 
		6 -2.6000000000000002e-005 6.48 -2.7e-005 6.99 -2.7999999999999996e-005 7.5 -3.1000000000000008e-005 
		7.98 -3.4e-005 8.49 -3.2000000000000012e-005 9 -2.9e-005 9.99 -3.5999999999999994e-005 
		10.98 0.332365 12 1.218602 12.99 2.3116530000000006 13.98 3.1979590000000004 15 3.5369520000000003 
		15.99 3.208317 16.98 2.337221 18 1.242255 18.99 0.344875 19.98 2.0000000000000008e-006 
		21 2.0000000000000008e-006 21.99 1.0000000000000004e-006 22.98 -1.0000000000000004e-006 
		24 1.0000000000000004e-006 24.99 1.0000000000000004e-006 25.98 1.0000000000000004e-006 
		27 2.0000000000000008e-006 27.99 -3.0000000000000005e-006 28.98 1.0000000000000004e-006 
		30 -3.0000000000000005e-006 30.99 0.00098700000000000025 31.98 0.003519 33 0.006519 
		33.99 0.008835 34.98 0.009689 36 0.008709 36.99 0.0061899999999999993 37.98 0.0031810000000000002 
		39 0.00083400000000000011 39.99 -3.9e-005;
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
	setAttr -s 44 ".ktv[0:43]"  0 -2.9e-005 0.99 -2.7e-005 1.98 -2.5e-005 
		3 -2.2000000000000003e-005 3.99 -1.7999999999999997e-005 4.98 -1.7999999999999997e-005 
		6 -1.3999999999999998e-005 6.48 -1.3000000000000001e-005 6.99 -1.3000000000000001e-005 
		7.5 -8.9999999999999985e-006 7.98 -4.0000000000000015e-006 8.49 1.0000000000000004e-006 
		9 6.000000000000001e-006 9.99 4.0000000000000015e-006 10.98 -0.086224 12 -0.310492 
		12.99 -0.5759780000000001 13.98 -0.78242500000000015 15 -0.859324 15.99 -0.743906 
		16.98 -0.47478100000000006 18 -0.20887900000000004 18.99 -0.048350000000000004 19.98 
		-4.0000000000000015e-006 21 -4.0000000000000015e-006 21.99 -4.0000000000000015e-006 
		22.98 -2.0000000000000008e-006 24 -4.0000000000000015e-006 24.99 -3.0000000000000005e-006 
		25.98 4.0000000000000015e-006 27 2.0000000000000008e-006 27.99 1.0000000000000004e-006 
		28.98 6.000000000000001e-006 30 7.0000000000000024e-006 30.99 0.000477 31.98 0.0018319999999999999 
		33 0.0037220000000000005 33.99 0.0054110000000000009 34.98 0.006095 36 0.005603 36.99 
		0.004211 37.98 0.0023120000000000007 39 0.000642 39.99 -2.3e-005;
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
	setAttr ".ktv[0]"  0 0.112377;
createNode animCurveTL -n "Bip01_L_Toe0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.095261;
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
	setAttr -s 41 ".ktv[0:40]"  0 4.161064 0.99 0.14916900000000002 1.98 
		-4.1902380000000008 3 -8.367693 3.99 -11.893031000000002 4.98 -14.276730000000002 
		6 -15.284385000000002 6.99 -15.251694000000002 7.98 -14.532934000000001 9 -13.465388 
		9.99 -12.380877000000002 10.98 -11.219850000000001 12 -9.751096 12.99 -8.124617 13.98 
		-6.430798 15 -4.743570000000001 15.99 -2.7627660000000005 16.98 -0.43319000000000007 
		18 1.8150780000000004 18.99 3.5596980000000005 19.98 4.38956 21 9.76077 21.99 8.973374 
		22.98 4.9983200000000005 24 0.38907000000000008 24.99 -2.327755 25.98 -1.8425220000000002 
		27 -0.88699300000000014 27.99 -0.21319900000000003 28.98 -0.59998300000000016 30 
		-3.1521870000000005 30.99 -2.9535860000000005 31.98 -2.620456 33 -2.1480510000000006 
		33.99 -1.543168 34.98 -0.827851 36 0.024568 36.99 1.015786 37.98 2.0801730000000003 
		39 3.1557090000000003 39.99 4.183504;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Foot_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 1.382994 0.99 0.91654400000000025 1.98 
		0.364399 3 -0.320551 3.99 -1.1409180000000003 4.98 -2.085618 6 -3.3352910000000002 
		6.99 -4.850926 7.98 -6.3281810000000007 9 -7.474538 9.99 -7.9831710000000005 10.98 
		-7.58329 12 -6.4442450000000004 12.99 -4.943462 13.98 -3.43711 15 -2.280974 15.99 
		-1.4500010000000003 16.98 -0.63134 18 0.22184500000000001 18.99 1.0734590000000002 
		19.98 1.7853750000000002 21 2.622204 21.99 2.846277 22.98 2.712119 24 2.5212510000000004 
		24.99 2.604162 25.98 3.083841 27 3.6903530000000004 27.99 4.275914 28.98 4.717894 
		30 4.949334 30.99 5.18777 31.98 5.4340270000000013 33 5.654806 33.99 5.772715 34.98 
		5.666254 36 5.198456 36.99 4.406002 37.98 3.413728 39 2.3605150000000004 39.99 1.39689;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Foot_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 2.2969090000000003 0.99 1.140939 1.98 
		0.08373700000000002 3 -0.767362 3.99 -1.3357840000000003 4.98 -1.587256 6 -1.5116880000000001 
		6.99 -1.206174 7.98 -0.8557720000000002 9 -0.63875000000000015 9.99 -0.6871830000000001 
		10.98 -0.920581 12 -1.163325 12.99 -1.349678 13.98 -1.490519 15 -1.714877 15.99 -2.2168310000000004 
		16.98 -2.9240310000000003 18 -3.6827009999999993 18.99 -4.3049280000000012 19.98 
		-4.5956400000000013 21 -4.734603 21.99 -4.932498 22.98 -5.148677 24 -5.2681390000000006 
		24.99 -5.1853730000000011 25.98 -4.8543020000000006 27 -4.267655 27.99 -3.4403620000000004 
		28.98 -2.457483 30 -1.454142 30.99 -0.240201 31.98 1.214276 33 2.6584550000000005 
		33.99 3.844348 34.98 4.514558000000001 36 4.536051 36.99 4.10678 37.98 3.445854 39 
		2.765604 39.99 2.273238;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.431489 0.99 0.431489 1.98 0.431489 
		3 0.431489 3.99 0.431489 4.98 0.431489 6 0.431489 6.99 0.431489 7.98 0.431489 9 0.431489 
		9.99 0.431489 10.98 0.431489 12 0.431489 12.99 0.431489 13.98 0.431489 15 0.431489 
		15.99 0.431489 16.98 0.431489 18 0.431489 18.99 0.431489 19.98 0.431489 21 0.431489 
		21.99 0.431489 22.98 0.431489 24 0.431489 24.99 0.431489 25.98 0.431489 27 0.431489 
		27.99 0.431489 28.98 0.431489 30 0.431489 30.99 0.431489 31.98 0.431489 33 0.431489 
		33.99 0.431489 34.98 0.431489 36 0.431489 36.99 0.431489 37.98 0.431489 39 0.431489 
		39.99 0.431489;
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
	setAttr -s 44 ".ktv[0:43]"  0 -27.882128000000005 0.99 -31.484910000000003 
		1.98 -35.116101 3 -38.733099 3.99 -42.293297 4.98 -45.754086 6 -49.40825 6.99 -53.284150000000004 
		7.98 -56.942669000000009 9 -59.944715 9.99 -61.851157 10.98 -62.920628000000008 12 
		-63.462242 12.99 -63.063488 13.98 -61.333695000000006 15 -57.876718 15.99 -51.313685 
		16.5 -46.611199000000006 16.98 -41.90871 17.49 -36.819386 18 -31.730066000000004 
		18.48 -27.288059 18.99 -22.846056 19.98 -17.324979 21 -24.646390000000004 21.99 -27.637097 
		22.98 -28.336392000000004 24 -27.571261 24.99 -26.374936000000005 25.98 -25.958477 
		27 -24.065844 27.99 -20.587791 28.98 -15.356944000000002 30 -7.480818 30.99 -7.733508 
		31.98 -9.6526 33 -12.512305 33.99 -15.586834000000001 34.98 -18.15038 36 -20.192099 
		36.99 -22.195856 37.98 -24.177939 39 -26.154586000000002 39.99 -28.142072000000002;
	setAttr -s 44 ".kit[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
	setAttr -s 44 ".kot[0:43]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 2;
createNode animCurveTA -n "Bip01_L_Calf_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_L_Calf_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTL -n "Bip01_L_Calf_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Calf_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Calf_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 39 ".ktv[0:38]"  0 0.361527 0.99 0.361527 1.98 0.361527 
		3 0.361527 6 0.361527 6.99 0.361527 7.98 0.361527 9 0.361527 9.99 0.361527 10.98 
		0.361527 12 0.361527 12.99 0.361527 13.98 0.361527 15 0.361527 15.99 0.361527 16.98 
		0.361527 18 0.361527 18.99 0.361527 19.98 0.361527 21 0.361527 21.99 0.361527 22.98 
		0.361527 24 0.361527 24.99 0.361527 25.98 0.361527 27 0.361527 27.99 0.361527 28.98 
		0.361527 30 0.361527 30.99 0.361527 31.98 0.361527 33 0.361527 33.99 0.361527 34.98 
		0.361527 36 0.361527 36.99 0.361527 37.98 0.361527 39 0.361527 39.99 0.361527;
	setAttr -s 39 ".kit[0:38]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 39 ".kot[0:38]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr -s 41 ".ktv[0:40]"  0 -178.619819 0.99 -178.54241900000002 
		1.98 -178.236413 3 -178.079005 3.99 -178.44702900000001 4.98 -179.716433 6 -182.06679700000004 
		6.99 -185.23310800000002 7.98 -188.920372 9 -192.82999900000002 9.99 -196.661366 
		10.98 -200.81440800000001 12 -205.557797 12.99 -210.138995 13.98 -213.91777 15 -216.222686 
		15.99 -216.65464 16.98 -215.707034 18 -214.04426500000005 18.99 -212.321801 19.98 
		-211.186842 21 -213.462538 21.99 -213.949968 22.98 -213.42077800000004 24 -212.019825 
		24.99 -210.01067 25.98 -207.619926 27 -204.11733700000002 27.99 -199.641514 28.98 
		-194.29778 30 -187.78504400000003 30.99 -185.828591 31.98 -184.928441 33 -184.60887 
		33.99 -184.39537200000004 34.98 -183.818549 36 -182.88663800000003 36.99 -181.91653200000002 
		37.98 -180.912973 39 -179.88739300000003 39.99 -178.85783700000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Thigh_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.452984 0.99 0.25020800000000004 1.98 
		0.089707 3 -0.044769 3.99 -0.15472400000000003 4.98 -0.22767100000000004 6 -0.333171 
		6.99 -0.48357400000000006 7.98 -0.583248 9 -0.55264200000000008 9.99 -0.327047 10.98 
		0.189206 12 0.950198 12.99 1.7632970000000001 13.98 2.463767 15 2.8895720000000003 
		15.99 2.9298250000000006 16.98 2.6949880000000004 18 2.3599390000000002 18.99 2.1314660000000005 
		19.98 2.2493050000000006 21 3.1554720000000005 21.99 4.0345590000000007 22.98 4.918694 
		24 5.780048 24.99 6.6108150000000006 25.98 7.4418910000000009 27 8.125213 27.99 8.5669990000000009 
		28.98 8.6992900000000013 30 8.456764 30.99 8.234058 31.98 7.8428910000000007 33 7.295159 
		33.99 6.6141440000000005 34.98 5.849685 36 4.953873 36.99 3.8850740000000008 37.98 
		2.7251420000000004 39 1.554681 39.99 0.452782;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Thigh_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 174.590677 0.99 175.253151 1.98 175.92694900000004 
		3 176.600405 3.99 177.257374 4.98 177.876366 6 178.47193200000004 6.99 179.05079000000003 
		7.98 179.57484300000002 9 180.00244000000004 9.99 180.28784700000003 10.98 180.354058 
		12 180.212032 12.99 179.97740100000001 13.98 179.805758 15 179.884155 15.99 180.30846000000003 
		16.98 180.93872300000004 18 181.610759 18.99 182.17340200000004 19.98 182.497522 
		21 182.416147 21.99 182.350004 22.98 182.337928 24 182.401995 24.99 182.50868200000002 
		25.98 182.56977200000003 27 182.671801 27.99 182.827338 28.98 183.045959 30 183.375078 
		30.99 182.90232 31.98 182.128883 33 181.16543 33.99 180.119715 34.98 179.090938 36 
		178.12075100000004 36.99 177.188607 37.98 176.292323 39 175.430831 39.99 174.604774;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.085842000000000016 0.99 0.085136 1.98 
		0.08428 3 0.083308000000000007 3.99 0.082258 4.98 0.081174 6 0.080107 6.99 0.079104 
		7.98 0.078214 9 0.077498 9.99 0.077026 10.98 0.076875 12 0.077051 12.99 0.077494 
		13.98 0.078132 15 0.078906 15.99 0.079758 16.98 0.080625 18 0.081446 18.99 0.082161 
		19.98 0.08271 21 0.083141 21.99 0.083519 22.98 0.083830000000000016 24 0.084061000000000011 
		24.99 0.084224 25.98 0.084346 27 0.084458 27.99 0.084581 28.98 0.084730000000000014 
		30 0.084915 30.99 0.085121 31.98 0.085321 33 0.085503 33.99 0.085660000000000014 
		34.98 0.085782 36 0.085864 36.99 0.08590600000000001 37.98 0.085911000000000015 39 
		0.085885 39.99 0.085842000000000016;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.018894 0.99 0.019665 1.98 0.02048 3 
		0.021322 3.99 0.022171 4.98 0.023008 6 0.023812 6.99 0.024564 7.98 0.025246 9 0.025835 
		9.99 0.026309 10.98 0.02662 12 0.026765 12.99 0.026786 13.98 0.026734 15 0.026651000000000005 
		15.99 0.026581 16.98 0.026566000000000003 18 0.026646000000000003 18.99 0.026858 
		19.98 0.027236 21 0.027887 21.99 0.028815 22.98 0.029931000000000003 24 0.031112000000000004 
		24.99 0.03227 25.98 0.033321 27 0.034187 27.99 0.034789 28.98 0.03504 30 0.034855 
		30.99 0.034199 31.98 0.033143 33 0.031757 33.99 0.030117000000000005 34.98 0.028293 
		36 0.026356 36.99 0.024379 37.98 0.02243 39 0.020579 39.99 0.018894;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Thigh_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.101258 0.99 -0.103316 1.98 -0.10546 
		3 -0.10763600000000001 3.99 -0.109789 4.98 -0.11186700000000001 6 -0.11382 6.99 -0.115698 
		7.98 -0.117513 9 -0.11915300000000001 9.99 -0.120509 10.98 -0.12147500000000001 12 
		-0.121994 12.99 -0.122147 13.98 -0.122088 15 -0.12183500000000001 15.99 -0.121409 
		16.98 -0.120832 18 -0.120131 18.99 -0.119329 19.98 -0.118457 21 -0.117255 21.99 -0.115593 
		22.98 -0.11363900000000002 24 -0.11163100000000001 24.99 -0.109764 25.98 -0.108247 
		27 -0.107146 27.99 -0.106339 28.98 -0.105756 30 -0.105325 30.99 -0.104971 31.98 -0.104588 
		33 -0.104167 33.99 -0.103768 34.98 -0.103379 36 -0.102989 36.99 -0.10259 37.98 -0.102172 
		39 -0.10173 39.99 -0.101258;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 31.292937 0.99 30.416743000000007 1.98 
		29.481851000000002 3 28.513426000000003 3.99 27.536618 4.98 26.576570000000004 6 
		25.658456 6.99 24.807413000000004 7.98 24.048601000000005 9 23.407178 9.99 22.908291000000002 
		10.98 22.570366000000003 12 22.371676000000004 12.99 22.292017 13.98 22.3046 15 22.384248 
		15.99 22.505827 16.98 22.64418 18 22.774138000000004 18.99 22.870554 19.98 22.908286 
		21 22.870563 21.99 22.774868 22.98 22.644173000000002 24 22.505831 24.99 22.384253 
		25.98 22.304601000000005 27 22.292027000000004 27.99 22.371676000000004 28.98 22.568711 
		30 22.908293 30.99 23.753254 31.98 24.880745000000005 33 26.147424000000004 33.99 
		27.417942 34.98 28.58282 36 29.567901 36.99 30.334689000000008 37.98 30.87301 39 
		31.18908 39.99 31.292933000000009;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger11_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "Bip01_L_Finger11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.034998 0.99 0.034998 1.98 0.034998 
		3 0.034998 3.99 0.034998 4.98 0.034998 6 0.034998 6.99 0.034998 7.98 0.034998 9 0.034998 
		9.99 0.034998 10.98 0.034998 12 0.034998 12.99 0.034998 13.98 0.034998 15 0.034998 
		15.99 0.034998 16.98 0.034998 18 0.034998 18.99 0.034998 19.98 0.034998 21 0.034998 
		21.99 0.034998 22.98 0.034998 24 0.034998 24.99 0.034998 25.98 0.034998 27 0.034998 
		27.99 0.034998 28.98 0.034998 30 0.034998 30.99 0.034998 31.98 0.034998 33 0.034998 
		33.99 0.034998 34.98 0.034998 36 0.034998 36.99 0.034998 37.98 0.034998 39 0.034998 
		39.99 0.034998;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 36.33771800000001 0.99 35.199467000000006 
		1.98 33.942883 3 32.619042 3.99 31.278846000000005 4.98 29.972962 6 28.751980000000003 
		6.99 27.666371000000005 7.98 26.766610000000004 9 26.103277000000002 9.99 25.727122 
		10.98 25.727643 12 26.107370000000003 12.99 26.775462000000005 13.98 27.646092 15 
		28.631663000000003 15.99 29.643641000000002 16.98 30.592159 18 31.385865 18.99 31.93215 
		19.98 32.137862000000005 21 31.941521000000009 21.99 31.408288 22.98 30.616734000000005 
		24 29.67102 24.99 28.658048 25.98 27.668279000000002 27 26.791410000000003 27.99 
		26.116443 28.98 25.731881000000005 30 25.725985 30.99 26.442004000000004 31.98 27.754366000000005 
		33 29.396532000000004 33.99 31.117234000000003 34.98 32.715955 36 34.06139 36.99 
		35.091697 37.98 35.799185 39 36.205847000000006 39.99 36.337721000000009;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger1_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.7741880000000001 0.99 -0.93722300000000014 
		1.98 -1.1589300000000002 3 -1.416205 3.99 -1.6852020000000003 4.98 -1.9413290000000003 
		6 -2.159386 6.99 -2.3136810000000003 7.98 -2.3782430000000003 9 -2.327123 9.99 -2.134589 
		10.98 -1.739014 12 -1.121534 12.99 -0.350492 13.98 0.51864800000000011 15 1.427814 
		15.99 2.3201720000000003 16.98 3.140472 18 3.8351280000000005 18.99 4.351908 19.98 
		4.6390450000000012 21 4.68988 21.99 4.556867 22.98 4.2698400000000012 24 3.8667330000000004 
		24.99 3.380934 25.98 2.848375 27 2.30631 27.99 1.792992 28.98 1.3473540000000002 
		30 1.00839 30.99 0.625794 31.98 0.32276600000000005 33 0.078616 33.99 -0.12552500000000003 
		34.98 -0.30224100000000004 36 -0.45660300000000004 36.99 -0.587051 37.98 -0.68788100000000008 
		39 -0.752097 39.99 -0.77418700000000007;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger1_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.64367400000000008 0.99 0.51405 1.98 
		0.36397 3 0.205746 3.99 0.050389 4.98 -0.092689 6 -0.21561200000000003 6.99 -0.31183800000000006 
		7.98 -0.375696 9 -0.401709 9.99 -0.383663 10.98 -0.304178 12 -0.155504 12.99 0.05016 
		13.98 0.302807 15 0.588851 15.99 0.89045300000000016 16.98 1.185076 18 1.445852 18.99 
		1.642874 19.98 1.745333 21 1.7410140000000003 21.99 1.6519690000000002 22.98 1.4982 
		24 1.304997 24.99 1.0933590000000002 25.98 0.88274100000000011 27 0.68970000000000009 
		27.99 0.527876 28.98 0.40861000000000003 30 0.34215100000000004 30.99 0.320022 31.98 
		0.35117300000000007 33 0.41118600000000005 33.99 0.47950900000000007 34.98 0.541264 
		36 0.58823200000000009 36.99 0.618528 37.98 0.63483600000000007 39 0.641862 39.99 
		0.64368200000000009;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger1_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.022784;
createNode animCurveTL -n "Bip01_L_Finger1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.00211;
createNode animCurveTL -n "Bip01_L_Finger1_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.073263;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 35.355803 0.99 34.479599 1.98 33.544717 
		3 32.576285 3.99 31.599472000000006 4.98 30.639438000000002 6 29.721314 6.99 28.870279 
		7.98 28.111471 9 27.470037000000005 9.99 26.971155000000003 10.98 26.633228 12 26.434542 
		12.99 26.354888000000003 13.98 26.367459 15 26.447119000000004 15.99 26.568687000000004 
		16.98 26.707037000000003 18 26.836999000000006 18.99 26.933424000000002 19.98 26.971155000000003 
		21 26.93342 21.99 26.837734000000005 22.98 26.707039 24 26.568690000000004 24.99 
		26.447118000000003 25.98 26.367457000000005 27 26.354881000000002 27.99 26.434538 
		28.98 26.631582000000005 30 26.971154 30.99 27.816115 31.98 28.943598 33 30.210284 
		33.99 31.480801000000007 34.98 32.645686 36 33.630757 36.99 34.397551 37.98 34.935873000000008 
		39 35.251943 39.99 35.3558;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger21_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_L_Finger21_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 4.0000000000000015e-006 0.99 3.0000000000000005e-006 
		1.98 1.0000000000000004e-006 3 1.0000000000000004e-006 3.99 -6.000000000000001e-006 
		4.98 2.0000000000000008e-006 6 -2.0000000000000008e-006 6.99 1.0000000000000004e-006 
		7.98 1.0000000000000004e-006 9 0 9.99 -1.0000000000000004e-006 10.98 -3.0000000000000005e-006 
		12 -3.0000000000000005e-006 12.99 1.0000000000000004e-006 13.98 -1.0000000000000004e-006 
		15 -7.0000000000000024e-006 15.99 3.0000000000000005e-006 16.98 -1.0000000000000004e-006 
		18 5e-006 18.99 -1.0000000000000004e-006 19.98 0 21 -2.0000000000000008e-006 21.99 
		1.0000000000000004e-006 22.98 7.0000000000000024e-006 24 -1.0000000000000004e-006 
		24.99 4.0000000000000015e-006 25.98 6.000000000000001e-006 27 1.0000000000000004e-006 
		27.99 2.0000000000000008e-006 28.98 0 30 3.0000000000000005e-006 30.99 3.0000000000000005e-006 
		31.98 0 33 5e-006 33.99 3.0000000000000005e-006 34.98 1.0000000000000004e-006 36 
		0 36.99 -2.0000000000000008e-006 37.98 -1.0000000000000004e-006 39 3.0000000000000005e-006 
		39.99 -2.0000000000000008e-006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger21_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger21_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger21_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.036722 0.99 0.036722 1.98 0.036722 
		3 0.036722 3.99 0.036722 4.98 0.036722 6 0.036722 6.99 0.036722 7.98 0.036722 9 0.036722 
		9.99 0.036722 10.98 0.036722 12 0.036722 12.99 0.036722 13.98 0.036722 15 0.036722 
		15.99 0.036722 16.98 0.036722 18 0.036722 18.99 0.036722 19.98 0.036722 21 0.036722 
		21.99 0.036722 22.98 0.036722 24 0.036722 24.99 0.036722 25.98 0.036722 27 0.036722 
		27.99 0.036722 28.98 0.036722 30 0.036722 30.99 0.036722 31.98 0.036722 33 0.036722 
		33.99 0.036722 34.98 0.036722 36 0.036722 36.99 0.036722 37.98 0.036722 39 0.036722 
		39.99 0.036722;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 35.475587 0.99 33.846656 1.98 32.073416 
		3 30.217028 3.99 28.338467 4.98 26.498790000000003 6 24.759451000000002 6.99 23.182465000000004 
		7.98 21.830573 9 20.767148 9.99 20.055915000000002 10.98 19.789179000000004 12 19.953027 
		12.99 20.453407 13.98 21.195094 15 22.083078 15.99 23.022285000000004 16.98 23.917185000000003 
		18 24.671417000000005 18.99 25.187697 19.98 25.368206 21 25.143926000000004 21.99 
		24.581363000000003 22.98 23.766559000000004 24 22.812033000000003 24.99 21.812428000000004 
		25.98 20.866461 27 20.072588000000003 27.99 19.52919 28.98 19.334589000000005 30 
		19.586941 30.99 20.871857000000002 31.98 22.908976 33 25.347403000000003 33.99 27.857323000000004 
		34.98 30.175607000000003 36 32.128931 36.99 33.633431000000009 37.98 34.675127 39 
		35.278816 39.99 35.475598000000005;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger2_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -2.463173 0.99 -3.05514 1.98 -3.7388530000000006 
		3 -4.4756430000000007 3.99 -5.226125 4.98 -5.9504410000000005 6 -6.6085580000000013 
		6.99 -7.160597 7.98 -7.5670940000000009 9 -7.7891860000000008 9.99 -7.7886370000000005 
		10.98 -7.4875010000000009 12 -6.873125 12.99 -6.0319150000000006 13.98 -5.0382110000000013 
		15 -3.968839 15.99 -2.899889 16.98 -1.9065120000000002 18 -1.0627690000000003 18.99 
		-0.44172800000000007 19.98 -0.11606799999999999 21 -0.106499 21.99 -0.34618400000000005 
		22.98 -0.78682500000000011 24 -1.3670060000000002 24.99 -2.0335610000000006 25.98 
		-2.730462 27 -3.401016 27.99 -3.9880300000000006 28.98 -4.4338500000000005 30 -4.6804140000000007 
		30.99 -4.7280690000000005 31.98 -4.527125 33 -4.171686 33.99 -3.754247 34.98 -3.3504210000000003 
		36 -3.0098060000000006 36.99 -2.7547030000000006 37.98 -2.585893 39 -2.492636 39.99 
		-2.463176;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger2_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -9.222951 0.99 -9.26959 1.98 -9.316025 
		3 -9.3493810000000011 3.99 -9.360437000000001 4.98 -9.3441140000000011 6 -9.299344 
		6.99 -9.228712 7.98 -9.137506 9 -9.032406 9.99 -8.919672 10.98 -8.7959360000000011 
		12 -8.653574 12.99 -8.494807 13.98 -8.317566 15 -8.123215 15.99 -7.917917 16.98 -7.7136050000000012 
		18 -7.527747 18.99 -7.3817850000000007 19.98 -7.298408000000002 21 -7.284256 21.99 
		-7.3228040000000005 22.98 -7.4003230000000011 24 -7.5006790000000017 24.99 -7.611608 
		25.98 -7.724166 27 -7.833655 27.99 -7.939109 28.98 -8.0418340000000015 30 -8.142922 
		30.99 -8.317188 31.98 -8.509521 33 -8.693804 33.99 -8.851554 34.98 -8.9761740000000021 
		36 -9.0698820000000016 36.99 -9.138148 37.98 -9.185373000000002 39 -9.213534000000001 
		39.99 -9.222939000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger2_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.0076;
createNode animCurveTL -n "Bip01_L_Finger2_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.005223;
createNode animCurveTL -n "Bip01_L_Finger2_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.07178 0.99 0.07178 1.98 0.07178 3 0.07178 
		3.99 0.07178 4.98 0.07178 6 0.07178 6.99 0.07178 7.98 0.07178 9 0.07178 9.99 0.07178 
		10.98 0.07178 12 0.07178 12.99 0.07178 13.98 0.07178 15 0.07178 15.99 0.07178 16.98 
		0.07178 18 0.07178 18.99 0.07178 19.98 0.07178 21 0.07178 21.99 0.07178 22.98 0.07178 
		24 0.07178 24.99 0.07178 25.98 0.07178 27 0.07178 27.99 0.07178 28.98 0.07178 30 
		0.07178 30.99 0.07178 31.98 0.07178 33 0.07178 33.99 0.07178 34.98 0.07178 36 0.07178 
		36.99 0.07178 37.98 0.07178 39 0.07178 39.99 0.07178;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 20.809587 0.99 19.220389 1.98 17.524741000000002 
		3 15.768261000000003 3.99 13.996571 4.98 12.255304000000002 6 10.590071 6.99 9.046498 
		7.98 7.6702090000000007 9 6.506828 9.99 5.6019740000000011 10.98 4.989065 12 4.628684 
		12.99 4.484212 13.98 4.507022 15 4.6514960000000007 15.99 4.872007 16.98 5.122931 
		18 5.3586520000000011 18.99 5.533538 19.98 5.601971 21 5.5335370000000008 21.99 5.3599820000000005 
		22.98 5.122932 24 4.872007 24.99 4.6514950000000006 25.98 4.507024 27 4.484214 27.99 
		4.628686 28.98 4.986065 30 5.6019740000000011 30.99 7.134517 31.98 9.1794950000000011 
		33 11.476934000000002 33.99 13.781334 34.98 15.894123 36 17.680808000000003 36.99 
		19.071566000000004 37.98 20.047945000000002 39 20.621214000000002 39.99 20.809586;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger01_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
createNode animCurveTA -n "Bip01_L_Finger01_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 4.0000000000000015e-006;
createNode animCurveTL -n "Bip01_L_Finger01_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger01_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Finger01_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.04028700000000001 0.99 0.04028700000000001 
		1.98 0.04028700000000001 3 0.04028700000000001 3.99 0.04028700000000001 4.98 0.04028700000000001 
		6 0.04028700000000001 6.99 0.04028700000000001 7.98 0.04028700000000001 9 0.04028700000000001 
		9.99 0.04028700000000001 10.98 0.04028700000000001 12 0.04028700000000001 12.99 0.04028700000000001 
		13.98 0.04028700000000001 15 0.04028700000000001 15.99 0.04028700000000001 16.98 
		0.04028700000000001 18 0.04028700000000001 18.99 0.04028700000000001 19.98 0.04028700000000001 
		21 0.04028700000000001 21.99 0.04028700000000001 22.98 0.04028700000000001 24 0.04028700000000001 
		24.99 0.04028700000000001 25.98 0.04028700000000001 27 0.04028700000000001 27.99 
		0.04028700000000001 28.98 0.04028700000000001 30 0.04028700000000001 30.99 0.04028700000000001 
		31.98 0.04028700000000001 33 0.04028700000000001 33.99 0.04028700000000001 34.98 
		0.04028700000000001 36 0.04028700000000001 36.99 0.04028700000000001 37.98 0.04028700000000001 
		39 0.04028700000000001 39.99 0.04028700000000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 15.324819000000002 0.99 15.322102999999998 
		1.98 15.303497 3 15.267289999999997 3.99 15.213477000000001 4.98 15.143789000000002 
		6 15.061760000000001 6.99 14.972377000000002 7.98 14.881965000000003 9 14.797710000000002 
		9.99 14.72725 10.98 14.677092000000002 12 14.646689 12.99 14.634303000000001 13.98 
		14.636266000000003 15 14.648626000000002 15.99 14.667287000000002 16.98 14.688215000000001 
		18 14.707574000000001 18.99 14.721751 19.98 14.72725 21 14.721745000000002 21.99 
		14.707683 22.98 14.688217 24 14.667289000000002 24.99 14.648624 25.98 14.636265000000002 
		27 14.634303000000001 27.99 14.646677000000002 28.98 14.676841 30 14.727253 30.99 
		14.844051 31.98 14.980583 33 15.107317 33.99 15.205754000000002 34.98 15.270456000000001 
		36 15.305891 36.99 15.321111000000002 37.98 15.325303 39 15.325255 39.99 15.324828000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 15.702785000000004 0.99 15.153757 1.98 
		14.568239000000002 3 13.962433000000003 3.99 13.352596000000002 4.98 12.754883 6 
		12.185187000000003 6.99 11.659136000000002 7.98 11.191995 9 10.798670000000001 9.99 
		10.493827 10.98 10.287903000000002 12 10.167047 12.99 10.118643000000002 13.98 10.126285 
		15 10.174690000000002 15.99 10.248627000000003 16.98 10.332839 18 10.41202 18.99 
		10.470810000000002 19.98 10.493823 21 10.470812000000002 21.99 10.412468000000002 
		22.98 10.332838000000002 24 10.24863 24.99 10.174692 25.98 10.126285 27 10.118647000000001 
		27.99 10.167047 28.98 10.286896000000002 30 10.493826000000002 30.99 11.010701000000001 
		31.98 11.704374000000001 33 12.488338000000002 33.99 13.278622 34.98 14.005809000000001 
		36 14.622111000000002 36.99 15.102359000000002 37.98 15.439654000000003 39 15.63771 
		39.99 15.702787000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Finger0_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 79.276868 0.99 80.715237 1.98 82.245964 
		3 83.827631000000011 3.99 85.419284 4.98 86.980357000000012 6 88.470595 6.99 89.849918 
		7.98 91.0783 9 92.115737 9.99 92.922103000000021 10.98 93.468081000000012 12 93.789011000000016 
		12.99 93.917657 13.98 93.897351000000015 15 93.768704000000014 15.99 93.572330000000008 
		16.98 93.348839000000012 18 93.138872 18.99 92.983069 19.98 92.922103000000021 21 
		92.983069 21.99 93.137691 22.98 93.348839000000012 24 93.572330000000008 24.99 93.768704000000014 
		25.98 93.897351000000015 27 93.917657 27.99 93.789011000000016 28.98 93.470744 30 
		92.922103000000021 30.99 91.556099 31.98 89.731141 33 87.677242000000021 33.99 85.612421 
		34.98 83.714428000000012 36 82.105242 36.99 80.849751 37.98 79.966689000000017 39 
		79.447561000000007 39.99 79.276874;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Finger0_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.029222;
createNode animCurveTL -n "Bip01_L_Finger0_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.013941000000000002;
createNode animCurveTL -n "Bip01_L_Finger0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.023036000000000004;
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
	setAttr -s 41 ".ktv[0:40]"  0 -6.196285 0.99 -5.5512500000000005 1.98 
		-4.8815370000000007 3 -4.203451 3.99 -3.531554 4.98 -2.8783240000000005 6 -2.2540560000000003 
		6.99 -1.667072 7.98 -1.124298 9 -0.632283 9.99 -0.198532 10.98 0.18272 12 0.529809 
		12.99 0.83043300000000009 13.98 1.081112 15 1.2775040000000002 15.99 1.4180910000000002 
		16.98 1.5052010000000002 18 1.5455890000000003 18.99 1.550566 19.98 1.535652 21 1.512317 
		21.99 1.48119 22.98 1.443675 24 1.40067 24.99 1.348321 25.98 1.277858 27 1.1750710000000002 
		27.99 1.0209480000000002 28.98 0.793418 30 0.47013900000000003 30.99 -0.263002 31.98 
		-1.2001910000000002 33 -2.2221380000000006 33.99 -3.2225830000000006 34.98 -4.123415 
		36 -4.877191 36.99 -5.462052 37.98 -5.8735750000000007 39 -6.1162680000000007 39.99 
		-6.1962860000000006;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Hand_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -7.3667040000000013 0.99 -7.09402 1.98 
		-6.7638220000000011 3 -6.3917290000000007 3.99 -5.9958220000000013 4.98 -5.596696 
		6 -5.21732 6.99 -4.882654 7.98 -4.61927 9 -4.454882 9.99 -4.417786 10.98 -4.5133730000000005 
		12 -4.726592 12.99 -5.044059 13.98 -5.4534100000000008 15 -5.938914 15.99 -6.483173 
		16.98 -7.0678980000000013 18 -7.6747590000000008 18.99 -8.286033 19.98 -8.884813 
		21 -9.566986 21.99 -10.396720000000002 22.98 -11.335526000000002 24 -12.311678000000002 
		24.99 -13.275992000000002 25.98 -14.174017000000001 27 -14.951635000000001 27.99 
		-15.554985 28.98 -15.930121 30 -16.022238 30.99 -15.561672000000002 31.98 -14.541081000000002 
		33 -13.197676000000001 33.99 -11.758883 34.98 -10.409427000000003 36 -9.2718620000000023 
		36.99 -8.404122 37.98 -7.8126800000000012 39 -7.475468000000002 39.99 -7.366702000000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Hand_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -63.582316 0.99 -64.763372 1.98 -66.126077000000009 
		3 -67.589609 3.99 -69.073911 4.98 -70.499788000000009 6 -71.788986 6.99 -72.863996000000014 
		7.98 -73.647931 9 -74.064354 9.99 -74.03703400000002 10.98 -73.419407 12 -72.189884 
		12.99 -70.512485000000012 13.98 -68.527045 15 -66.378951 15.99 -64.213426 16.98 -62.175803000000009 
		18 -60.411763000000008 18.99 -59.067678000000008 19.98 -58.290737 21 -58.099751000000005 
		21.99 -58.350691999999995 22.98 -58.959733 24 -59.826156000000012 24.99 -60.859598000000005 
		25.98 -61.965720000000012 27 -63.048701 27.99 -64.011334 28.98 -64.755709 30 -65.184549000000018 
		30.99 -65.356629 31.98 -65.212259 33 -64.89307 33.99 -64.521768 34.98 -64.183318 
		36 -63.921558 36.99 -63.746179000000012 37.98 -63.64477200000001 39 -63.596188000000005 
		39.99 -63.582330000000006;
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
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_L_Hand_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.249881 0.99 0.249881 1.98 0.249881 
		3 0.249881 3.99 0.249881 4.98 0.249881 6 0.249881 6.99 0.249881 7.98 0.249881 9 0.249881 
		9.99 0.249881 10.98 0.249881 12 0.249881 12.99 0.249881 13.98 0.249881 15 0.249881 
		15.99 0.249881 16.98 0.249881 18 0.249881 18.99 0.249881 19.98 0.249881 21 0.249881 
		21.99 0.249881 22.98 0.249881 24 0.249881 24.99 0.249881 25.98 0.249881 27 0.249881 
		27.99 0.249881 28.98 0.249881 30 0.249881 30.99 0.249881 31.98 0.249881 33 0.249881 
		33.99 0.249881 34.98 0.249881 36 0.249881 36.99 0.249881 37.98 0.249881 39 0.249881 
		39.99 0.249881;
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
	setAttr -s 41 ".ktv[0:40]"  0 -29.564595 0.99 -28.363481000000004 1.98 
		-27.053186000000004 3 -25.680547000000004 3.99 -24.292277000000002 4.98 -22.935216000000004 
		6 -21.656126 6.99 -20.501799 7.98 -19.518991000000003 9 -18.75451 9.99 -18.255141000000002 
		10.98 -18.089238 12 -18.246409 12.99 -18.654951 13.98 -19.243309 15 -19.939859 15.99 
		-20.673038 16.98 -21.371249 18 -21.962882 18.99 -22.376351 19.98 -22.540058000000002 
		21 -22.408977000000004 21.99 -22.035280000000004 22.98 -21.479882 24 -20.821472 24.99 
		-20.1269 25.98 -19.465942 27 -18.908423 27.99 -18.524116 28.98 -18.382840000000005 
		30 -18.554387 30.99 -19.442090000000004 31.98 -20.850464 33 -22.538096 33.99 -24.277145000000004 
		34.98 -25.884961 36 -27.240574 36.99 -28.285188000000005 37.98 -29.008628 39 -29.427926 
		39.99 -29.564595;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Forearm_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_L_Forearm_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.253374 0.99 0.253374 1.98 0.253375 
		3 0.253375 3.99 0.253375 4.98 0.253375 6 0.253374 6.99 0.253374 7.98 0.253375 9 0.253374 
		9.99 0.253375 10.98 0.253375 12 0.253375 12.99 0.253375 13.98 0.253374 15 0.253375 
		15.99 0.253375 16.98 0.253375 18 0.253374 18.99 0.253375 19.98 0.253375 21 0.253375 
		21.99 0.253375 22.98 0.253374 24 0.253375 24.99 0.253374 25.98 0.253375 27 0.253375 
		27.99 0.253374 28.98 0.253374 30 0.253374 30.99 0.253375 31.98 0.253375 33 0.253375 
		33.99 0.253375 34.98 0.253375 36 0.253375 36.99 0.253375 37.98 0.253375 39 0.253375 
		39.99 0.253375;
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
	setAttr -s 41 ".ktv[0:40]"  0 -31.923055999999995 0.99 -29.019922000000005 
		1.98 -25.714199 3 -21.946968 3.99 -17.673653 4.98 -12.881957 6 -7.6151160000000013 
		6.99 -1.9941280000000001 7.98 3.773187000000001 9 9.408187 9.99 14.602411 10.98 19.559738000000003 
		12 24.562744 12.99 29.184116 13.98 33.201053000000009 15 36.442315 15.99 38.800667000000004 
		16.98 40.206292 18 40.603936000000004 18.99 39.936735 19.98 38.135546000000005 21 
		34.725797000000007 21.99 29.643525 22.98 23.307147 24 16.405980000000003 24.99 9.465778 
		25.98 2.93907 27 -2.8775110000000006 27.99 -7.8276300000000019 28.98 -11.844218000000001 
		30 -14.894697000000003 30.99 -18.729675000000004 31.98 -22.116435000000003 33 -25.062288000000002 
		33.99 -27.557112000000007 34.98 -29.583856000000004 36 -31.122326000000005 36.99 
		-32.149606 37.98 -32.640478000000009 39 -32.570510000000006 39.99 -31.923053000000003;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_UpperArm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 64.444689 0.99 65.706949 1.98 67.006215 
		3 68.295529 3.99 69.524191 4.98 70.640087 6 71.59371800000001 6.99 72.343837 7.98 
		72.864297000000008 9 73.149662000000021 9.99 73.217192 10.98 73.106263 12 72.84481 
		12.99 72.475413000000017 13.98 72.050138 15 71.624829 15.99 71.247052000000011 16.98 
		70.948436000000015 18 70.741174 18.99 70.617739000000014 19.98 70.552865000000011 
		21 70.491646000000017 21.99 70.334463 22.98 69.978570000000019 24 69.366817000000012 
		24.99 68.49342 25.98 67.413847000000018 27 66.22967 27.99 65.068292 28.98 64.065197 
		30 63.352398000000008 30.99 62.750700000000009 31.98 62.338812 33 62.10718700000001 
		33.99 62.049649000000009 34.98 62.159061999999992 36 62.42244800000001 36.99 62.8178 
		37.98 63.313576 39 63.870591000000005 39.99 64.444682;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_UpperArm_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.3508910000000007 0.99 -3.086894 1.98 
		-1.358417 3 0.89060400000000017 3.99 3.69745 4.98 7.062411 6 10.925506 6.99 15.144494 
		7.98 19.486344 9 23.644128000000002 9.99 27.279246000000004 10.98 30.38499 12 33.093153 
		12.99 35.155873000000007 13.98 36.482091 15 37.051145 15.99 36.911969 16.98 36.155358000000007 
		18 34.889117 18.99 33.219603 19.98 31.238944 21 28.632486000000004 21.99 25.254603 
		22.98 21.378284 24 17.467151 24.99 13.872578000000003 25.98 10.857152 27 8.523724 
		27.99 6.8298220000000009 28.98 5.63818 30 4.7723110000000011 30.99 3.888107 31.98 
		2.865978 33 1.7539650000000002 33.99 0.619254 34.98 -0.477666 36 -1.4943490000000001 
		36.99 -2.40579 37.98 -3.1965940000000006 39 -3.8517420000000011 39.99 -4.350887;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_UpperArm_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
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
	setAttr ".ktv[0]"  0 0.106745;
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
	setAttr -s 41 ".ktv[0:40]"  0 -153.50432700000002 0.99 -152.71016700000004 
		1.98 -151.85408500000003 3 -150.940684 3.99 -149.976083 4.98 -148.96831600000002 
		6 -147.927614 6.99 -146.86673600000003 7.98 -145.801213 9 -144.74944500000004 9.99 
		-143.73269 10.98 -142.701946 12 -141.583844 12.99 -140.430061 13.98 -139.27141500000002 
		15 -138.151975 15.99 -137.121873 16.98 -136.23638 18 -135.553812 18.99 -135.132649 
		19.98 -135.02795600000002 21 -135.28482500000004 21.99 -135.86821900000004 22.98 
		-136.723618 24 -137.767258 24.99 -138.935889 25.98 -140.16719500000002 27 -141.40638200000004 
		27.99 -142.606829 28.98 -143.729876 30 -144.743886 30.99 -145.700563 31.98 -146.661789 
		33 -147.616595 33.99 -148.55559500000004 34.98 -149.470895 36 -150.355965 36.99 -151.205558 
		37.98 -152.01549600000004 39 -152.782553 39.99 -153.50432700000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Clavicle_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -71.23391 0.99 -71.661473 1.98 -72.096802000000011 
		3 -72.534344 3.99 -72.96869 4.98 -73.394600000000011 6 -73.807047000000011 6.99 -74.201272 
		7.98 -74.572794000000016 9 -74.917445000000015 9.99 -75.23138800000001 10.98 -75.531779000000014 
		12 -75.83879 12.99 -76.136552 13.98 -76.41758 15 -76.673220000000015 15.99 -76.895604 
		16.98 -77.077513 18 -77.212204 18.99 -77.292991000000015 19.98 -77.31281300000002 
		21 -77.264004000000014 21.99 -77.150746000000012 22.98 -76.978441000000018 24 -76.757662 
		24.99 -76.495792000000009 25.98 -76.201848000000012 27 -75.885809 27.99 -75.558636 
		28.98 -75.232228 30 -74.919207 30.99 -74.606692 31.98 -74.274567000000019 33 -73.925264000000013 
		33.99 -73.561366 34.98 -73.18561 36 -72.800879000000009 36.99 -72.410199 37.98 -72.016657 
		39 -71.623477 39.99 -71.23391;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_L_Clavicle_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -28.084515000000003 0.99 -28.922189 1.98 
		-29.82294 3 -30.781632000000002 3.99 -31.791647000000005 4.98 -32.844435000000004 
		6 -33.929253 6.99 -35.032851 7.98 -36.139191 9 -37.229368 9.99 -38.281617 10.98 -39.346850000000011 
		12 -40.500749000000006 12.99 -41.689919 13.98 -42.882592 15 -44.033623000000006 15.99 
		-45.091745 16.98 -46.000577000000007 18 -46.700682 18.99 -47.132483 19.98 -47.239812000000008 
		21 -46.976488 21.99 -46.378256 22.98 -45.50057000000001 24 -44.428903000000005 24.99 
		-43.227729000000004 25.98 -41.960626000000005 27 -40.68377000000001 27.99 -39.445057 
		28.98 -38.284523 30 -37.235109 30.99 -36.243581000000006 31.98 -35.245793 33 -34.253025 
		33.99 -33.274931 34.98 -32.319699000000007 36 -31.394157 36.99 -30.503859000000002 
		37.98 -29.653282 39 -28.845919000000002 39.99 -28.084512;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.038459 0.99 0.038551 1.98 0.038642 
		3 0.038731 3.99 0.038818 4.98 0.0389 6 0.038978 6.99 0.039051 7.98 0.039117 9 0.039178 
		9.99 0.039231 10.98 0.039281 12 0.039331 12.99 0.039379 13.98 0.039422 15 0.039461 
		15.99 0.039494 16.98 0.039521 18 0.03954 18.99 0.039551 19.98 0.039554 21 0.039547 
		21.99 0.039531 22.98 0.039506 24 0.039474 24.99 0.039434 25.98 0.039389 27 0.039339 
		27.99 0.039286 28.98 0.039231 30 0.039178 30.99 0.039123 31.98 0.039064 33 0.039 
		33.99 0.038932 34.98 0.03886 36 0.038785 36.99 0.038706 37.98 0.038625 39 0.038543 
		39.99 0.038459;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.006397 0.99 -0.0064269999999999996 
		1.98 -0.0064570000000000009 3 -0.0064890000000000008 3.99 -0.0065200000000000006 
		4.98 -0.0065509999999999995 6 -0.006582 6.99 -0.006612 7.98 -0.00664 9 -0.0066669999999999993 
		9.99 -0.0066919999999999992 10.98 -0.006716 12 -0.0067420000000000006 12.99 -0.006767 
		13.98 -0.006791 15 -0.0068130000000000005 15.99 -0.0068330000000000005 16.98 -0.0068500000000000011 
		18 -0.006862 18.99 -0.0068699999999999994 19.98 -0.0068720000000000005 21 -0.006867 
		21.99 -0.006857 22.98 -0.006841 24 -0.0068210000000000007 24.99 -0.0067980000000000011 
		25.98 -0.006772 27 -0.006746 27.99 -0.006719000000000001 28.98 -0.0066919999999999992 
		30 -0.0066669999999999993 30.99 -0.0066430000000000005 31.98 -0.0066170000000000005 
		33 -0.0065910000000000005 33.99 -0.0065629999999999994 34.98 -0.006536 36 -0.0065080000000000008 
		36.99 -0.00648 37.98 -0.006452 39 -0.0064240000000000009 39.99 -0.006397;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_L_Clavicle_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.011226 0.99 -0.010889 1.98 -0.010541 
		3 -0.010188 3.99 -0.009832 4.98 -0.009478 6 -0.009131 6.99 -0.0087929999999999987 
		7.98 -0.008469 9 -0.0081640000000000011 9.99 -0.007882 10.98 -0.007606 12 -0.00732 
		12.99 -0.007037 13.98 -0.0067640000000000009 15 -0.00651 15.99 -0.006284 16.98 -0.0060960000000000007 
		18 -0.005954000000000001 18.99 -0.005869 19.98 -0.005848 21 -0.0059 21.99 -0.006019 
		22.98 -0.0061990000000000005 24 -0.006425000000000001 24.99 -0.006686 25.98 -0.0069739999999999993 
		27 -0.007276 27.99 -0.007582 28.98 -0.007881 30 -0.008163 30.99 -0.00844 31.98 -0.008729 
		33 -0.00903 33.99 -0.009338 34.98 -0.009653 36 -0.00997 36.99 -0.010289 37.98 -0.010606 
		39 -0.010919000000000002 39.99 -0.011226;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 22.908288 0.99 22.907666000000003 1.98 
		22.898739000000003 3 22.863915 3.99 22.784577000000002 4.98 22.653984 6 22.489575000000002 
		6.99 22.340876000000005 7.98 22.289742000000004 9 22.441601000000002 9.99 22.908293 
		10.98 23.478164000000003 12 24.31691 12.99 25.335648000000003 13.98 26.463380000000004 
		15 27.624654000000003 15.99 28.744003000000003 16.98 29.745971000000004 18 30.555085000000002 
		18.99 31.095896 19.98 31.292933000000009 21 31.095893 21.99 30.559381000000002 22.98 
		29.745971000000004 24 28.744003000000003 24.99 27.624658 25.98 26.463377 27 25.335646 
		27.99 24.316918 28.98 23.482642 30 22.908294000000005 30.99 22.441605000000003 31.98 
		22.289747 33 22.340878 33.99 22.489571 34.98 22.653983 36 22.784583000000005 36.99 
		22.863915 37.98 22.898741000000005 39 22.907666000000003 39.99 22.908291000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger11_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 3.0000000000000005e-006;
createNode animCurveTA -n "Bip01_R_Finger11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTL -n "Bip01_R_Finger11_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger11_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger11_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.034998 0.99 0.034998 1.98 0.034998 
		3 0.034998 3.99 0.034998 4.98 0.034998 6 0.034998 6.99 0.034998 7.98 0.034998 9 0.034998 
		9.99 0.034998 10.98 0.034998 12 0.034998 12.99 0.034998 13.98 0.034998 15 0.034998 
		15.99 0.034998 16.98 0.034998 18 0.034998 18.99 0.034998 19.98 0.034998 21 0.034998 
		21.99 0.034998 22.98 0.034998 24 0.034998 24.99 0.034998 25.98 0.034998 27 0.034998 
		27.99 0.034998 28.98 0.034998 30 0.034998 30.99 0.034998 31.98 0.034998 33 0.034998 
		33.99 0.034998 34.98 0.034998 36 0.034998 36.99 0.034998 37.98 0.034998 39 0.034998 
		39.99 0.034998;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 32.137865 0.99 32.056938 1.98 31.801868000000002 
		3 31.343006 3.99 30.652612999999995 4.98 29.730876 6 28.630391 6.99 27.471375000000002 
		7.98 26.441343000000003 9 25.776374000000004 9.99 25.725985 10.98 26.191394000000003 
		12 27.102899000000004 12.99 28.332419 13.98 29.769651 15 31.299941 15.99 32.808703 
		16.98 34.181383 18 35.303446 18.99 36.060388 19.98 36.337731000000005 21 36.059227000000007 
		21.99 35.307469 22.98 34.179276 24 32.80721 24.99 31.299678 25.98 29.770908000000002 
		27 28.335057 27.99 27.106274 28.98 26.198811000000003 30 25.72713 30.99 25.771469000000003 
		31.98 26.428850000000004 33 27.452796 33.99 28.609378000000003 34.98 29.711540000000003 
		36 30.637871 36.99 31.333836 37.98 31.797592 39 32.055842 39.99 32.137869;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger1_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -4.6390450000000012 0.99 -4.5952270000000013 
		1.98 -4.463295 3 -4.242426 3.99 -3.933061 4.98 -3.5394390000000002 6 -3.07237 6.99 
		-2.5517990000000004 7.98 -2.007861 9 -1.4792650000000003 9.99 -1.0083930000000003 
		10.98 -0.754107 12 -0.527306 12.99 -0.326932 13.98 -0.14596 15 0.020712000000000005 
		15.99 0.17751100000000003 16.98 0.32818100000000006 18 0.47588000000000008 18.99 
		0.62353 19.98 0.77419100000000007 21 0.95832300000000015 21.99 1.1886760000000003 
		22.98 1.4493960000000001 24 1.714881 24.99 1.9647160000000001 25.98 2.1757050000000002 
		27 2.323507 27.99 2.382928 28.98 2.328394 30 2.134589 30.99 1.5214230000000002 31.98 
		0.62372800000000006 33 -0.41790100000000008 33.99 -1.472521 34.98 -2.4376050000000005 
		36 -3.2473950000000005 36.99 -3.871187 37.98 -4.3044520000000013 39 -4.5566050000000011 
		39.99 -4.639041;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger1_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.745335 0.99 -1.7253860000000003 1.98 
		-1.664505 3 -1.5606 3.99 -1.413401 4.98 -1.227688 6 -1.0156650000000003 6.99 -0.79691500000000015 
		7.98 -0.595793 9 -0.43712100000000004 9.99 -0.342143 10.98 -0.327737 12 -0.349576 
		12.99 -0.39633400000000008 13.98 -0.45786800000000005 15 -0.524773 15.99 -0.58816500000000016 
		16.98 -0.63960700000000015 18 -0.671016 18.99 -0.674758 19.98 -0.64367500000000011 
		21 -0.56490600000000013 21.99 -0.442718 22.98 -0.29197 24 -0.13158700000000004 24.99 
		0.024882 25.98 0.165276 27 0.279589 27.99 0.359464 28.98 0.39709700000000003 30 0.383667 
		30.99 0.257114 31.98 0.029156000000000005 33 -0.269665 33.99 -0.60283000000000009 
		34.98 -0.93171900000000007 36 -1.223057 36.99 -1.455015 37.98 -1.6185930000000002 
		39 -1.7141250000000001 39.99 -1.7453370000000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger1_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.022784 0.99 0.022784 1.98 0.022784 
		3 0.022784 3.99 0.022784 4.98 0.022784 6 0.022784 6.99 0.022784 7.98 0.022784 9 0.022784 
		9.99 0.022784 10.98 0.022784 12 0.022784 12.99 0.022784 13.98 0.022784 15 0.022784 
		15.99 0.022784 16.98 0.022784 18 0.022784 18.99 0.022784 19.98 0.022784 21 0.022784 
		21.99 0.022784 22.98 0.022784 24 0.022784 24.99 0.022784 25.98 0.022784 27 0.022784 
		27.99 0.022784 28.98 0.022784 30 0.022784 30.99 0.022784 31.98 0.022784 33 0.022784 
		33.99 0.022784 34.98 0.022784 36 0.022784 36.99 0.022784 37.98 0.022784 39 0.022784 
		39.99 0.022784;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger1_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.00211;
createNode animCurveTL -n "Bip01_R_Finger1_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.073263 0.99 0.073263 1.98 0.073263 
		3 0.073263 3.99 0.073263 4.98 0.073263 6 0.073263 6.99 0.073263 7.98 0.073263 9 0.073263 
		9.99 0.073263 10.98 0.073263 12 0.073263 12.99 0.073263 13.98 0.073263 15 0.073263 
		15.99 0.073263 16.98 0.073263 18 0.073263 18.99 0.073263 19.98 0.073263 21 0.073263 
		21.99 0.073263 22.98 0.073263 24 0.073263 24.99 0.073263 25.98 0.073263 27 0.073263 
		27.99 0.073263 28.98 0.073263 30 0.073263 30.99 0.073263 31.98 0.073263 33 0.073263 
		33.99 0.073263 34.98 0.073263 36 0.073263 36.99 0.073263 37.98 0.073263 39 0.073263 
		39.99 0.073263;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 26.971159 0.99 26.970529 1.98 26.961603 
		3 26.926785000000002 3.99 26.847444 4.98 26.716849000000003 6 26.552439000000003 
		6.99 26.403741 7.98 26.352610000000002 9 26.504464000000002 9.99 26.971154 10.98 
		27.541027 12 28.379774000000005 12.99 29.398508999999997 13.98 30.526248000000002 
		15 31.687524 15.99 32.806869 16.98 33.808833 18 34.617948 18.99 35.158759 19.98 35.355806 
		21 35.158759 21.99 34.622244 22.98 33.808827 24 32.806869 24.99 31.687517 25.98 30.526245000000003 
		27 29.398512000000004 27.99 28.379774000000005 28.98 27.545503000000004 30 26.971159 
		30.99 26.504467 31.98 26.352605 33 26.403748000000004 33.99 26.552441000000005 34.98 
		26.71685 36 26.847445000000004 36.99 26.926783000000004 37.98 26.961605 39 26.970522000000003 
		39.99 26.971161;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger21_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_R_Finger21_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTL -n "Bip01_R_Finger21_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger21_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_R_Finger21_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.036722 0.99 0.036722 1.98 0.036722 
		3 0.036722 3.99 0.036722 4.98 0.036722 6 0.036722 6.99 0.036722 7.98 0.036722 9 0.036722 
		9.99 0.036722 10.98 0.036722 12 0.036722 12.99 0.036722 13.98 0.036722 15 0.036722 
		15.99 0.036722 16.98 0.036722 18 0.036722 18.99 0.036722 19.98 0.036722 21 0.036722 
		21.99 0.036722 22.98 0.036722 24 0.036722 24.99 0.036722 25.98 0.036722 27 0.036722 
		27.99 0.036722 28.98 0.036722 30 0.036722 30.99 0.036722 31.98 0.036722 33 0.036722 
		33.99 0.036722 34.98 0.036722 36 0.036722 36.99 0.036722 37.98 0.036722 39 0.036722 
		39.99 0.036722;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 25.368213000000004 0.99 25.295048000000005 
		1.98 25.059179 3 24.620537 3.99 23.939909 4.98 23.011915000000002 6 21.896469000000003 
		6.99 20.738606 7.98 19.76907 9 19.281369 9.99 19.586941 10.98 20.435559 12 21.887082 
		12.99 23.759097 13.98 25.898918000000002 15 28.147147000000004 15.99 30.345117999999996 
		16.98 32.334722000000006 18 33.958155 18.99 35.057713000000007 19.98 35.475591 21 
		35.111265 21.99 34.08116 22.98 32.51522 24 30.592368000000004 24.99 28.458176000000005 
		25.98 26.266777000000005 27 24.173358 27.99 22.334675000000004 28.98 20.909086 30 
		20.05592 30.99 19.72114 31.98 20.148301 33 21.040822000000002 33.99 22.118815 34.98 
		23.16207 36 24.031615 36.99 24.669407000000003 37.98 25.079852000000002 39 25.300042000000005 
		39.99 25.368211;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger2_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.11606500000000002 0.99 0.17218100000000003 
		1.98 0.344721 3 0.64360000000000006 3.99 1.077228 4.98 1.6425380000000003 6 2.3153570000000006 
		6.99 3.04398 7.98 3.7489770000000004 9 4.33027 9.99 4.6804130000000006 10.98 4.71178 
		12 4.5753420000000009 12.99 4.3115660000000009 13.98 3.960784 15 3.565238 15.99 3.168537 
		16.98 2.815187 18 2.55 18.99 2.4177870000000006 19.98 2.463174 21 2.7437090000000004 
		21.99 3.242985 22.98 3.911049 24 4.674633 24.99 5.474074 25.98 6.24526 27 6.92422 
		27.99 7.448165 28.98 7.756047 30 7.7886400000000018 30.99 7.300014 31.98 6.354559000000001 
		33 5.1573940000000009 33.99 3.90024 34.98 2.734353 36 1.756856 36.99 1.011681 37.98 
		0.502256 39 0.21049500000000002 39.99 0.11606799999999999;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger2_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 7.2984050000000016 0.99 7.3116240000000019 
		1.98 7.3508190000000013 3 7.414223 3.99 7.497719 4.98 7.594364 6 7.695648 6.99 7.7953670000000006 
		7.98 7.894704 9 8.004855 9.99 8.142921 10.98 8.2586040000000018 12 8.400465 12.99 
		8.551285 13.98 8.6977090000000015 15 8.828957 15.99 8.93928 16.98 9.028401 18 9.100767 
		18.99 9.163451 19.98 9.222948 21 9.291342 21.99 9.3665880000000019 22.98 9.430724 
		24 9.464488 24.99 9.45604 25.98 9.401232 27 9.3048840000000013 27.99 9.1800050000000013 
		28.98 9.0450720000000011 30 8.919678 30.99 8.73563 31.98 8.543521 33 8.3367290000000018 
		33.99 8.115774 34.98 7.8933790000000013 36 7.688880000000001 36.99 7.5197510000000012 
		37.98 7.396535 39 7.322813 39.99 7.298406;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger2_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.0076 0.99 -0.0076 1.98 -0.0076 3 -0.0076 
		3.99 -0.0076 4.98 -0.0076 6 -0.0076 6.99 -0.0076 7.98 -0.0076 9 -0.0076 9.99 -0.0076 
		10.98 -0.0076 12 -0.0076 12.99 -0.0076 13.98 -0.0076 15 -0.0076 15.99 -0.0076 16.98 
		-0.0076 18 -0.0076 18.99 -0.0076 19.98 -0.0076 21 -0.0076 21.99 -0.0076 22.98 -0.0076 
		24 -0.0076 24.99 -0.0076 25.98 -0.0076 27 -0.0076 27.99 -0.0076 28.98 -0.0076 30 
		-0.0076 30.99 -0.0076 31.98 -0.0076 33 -0.0076 33.99 -0.0076 34.98 -0.0076 36 -0.0076 
		36.99 -0.0076 37.98 -0.0076 39 -0.0076 39.99 -0.0076;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger2_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -0.005223;
createNode animCurveTL -n "Bip01_R_Finger2_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.07178;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 5.6019740000000011 0.99 5.600835 1.98 
		5.584649 3 5.5214890000000008 3.99 5.377593000000001 4.98 5.140726 6 4.842527 6.99 
		4.572825 7.98 4.4800890000000013 9 4.7555210000000008 9.99 5.601973000000001 10.98 
		6.635578 12 8.156851 12.99 10.004575 13.98 12.050003 15 14.156256000000003 15.99 
		16.186475 16.98 18.00378 18 19.471326 18.99 20.452205 19.98 20.809591 21 20.45221 
		21.99 19.479096000000002 22.98 18.003785 24 16.186472000000002 24.99 14.156254000000002 
		25.98 12.05 27 10.004578 27.99 8.156851 28.98 6.643696 30 5.6019740000000011 30.99 
		4.755525 31.98 4.48009 33 4.572823 33.99 4.842524 34.98 5.1407230000000013 36 5.377593000000001 
		36.99 5.5214890000000008 37.98 5.584649 39 5.600834 39.99 5.601972;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger01_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004e-006;
createNode animCurveTA -n "Bip01_R_Finger01_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 1.0000000000000004e-006;
createNode animCurveTL -n "Bip01_R_Finger01_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger01_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger01_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.04028700000000001 0.99 0.04028700000000001 
		1.98 0.04028700000000001 3 0.04028700000000001 3.99 0.04028700000000001 4.98 0.04028700000000001 
		6 0.04028700000000001 6.99 0.04028700000000001 7.98 0.04028700000000001 9 0.04028700000000001 
		9.99 0.04028700000000001 10.98 0.04028700000000001 12 0.04028700000000001 12.99 0.04028700000000001 
		13.98 0.04028700000000001 15 0.04028700000000001 15.99 0.04028700000000001 16.98 
		0.04028700000000001 18 0.04028700000000001 18.99 0.04028700000000001 19.98 0.04028700000000001 
		21 0.04028700000000001 21.99 0.04028700000000001 22.98 0.04028700000000001 24 0.04028700000000001 
		24.99 0.04028700000000001 25.98 0.04028700000000001 27 0.04028700000000001 27.99 
		0.04028700000000001 28.98 0.04028700000000001 30 0.04028700000000001 30.99 0.04028700000000001 
		31.98 0.04028700000000001 33 0.04028700000000001 33.99 0.04028700000000001 34.98 
		0.04028700000000001 36 0.04028700000000001 36.99 0.04028700000000001 37.98 0.04028700000000001 
		39 0.04028700000000001 39.99 0.04028700000000001;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 14.727255000000001 0.99 14.727161000000002 
		1.98 14.725861000000002 3 14.720778000000001 3.99 14.709110000000003 4.98 14.689685000000004 
		6 14.664811 6.99 14.641905 7.98 14.633948 9 14.657461000000003 9.99 14.72725 10.98 
		14.807385000000002 12 14.915088000000003 12.99 15.029363 13.98 15.134503 15 15.219027000000002 
		15.99 15.277464000000002 16.98 15.310387000000002 18 15.323482000000004 18.99 15.325468 
		19.98 15.32483 21 15.325463 21.99 15.323513000000002 22.98 15.310385999999998 24 
		15.277462000000003 24.99 15.219025 25.98 15.134495000000001 27 15.029369000000003 
		27.99 14.915086999999998 28.98 14.807986000000001 30 14.727253 30.99 14.657462 31.98 
		14.633954000000001 33 14.641910000000001 33.99 14.66481 34.98 14.689685000000004 
		36 14.709117000000003 36.99 14.720778000000001 37.98 14.725863 39 14.727157000000002 
		39.99 14.727253;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger0_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -10.493831000000002 0.99 -10.493448 1.98 
		-10.488002 3 -10.466765000000002 3.99 -10.418386 4.98 -10.338817000000002 6 -10.238740000000002 
		6.99 -10.148332000000002 7.98 -10.117269000000002 9 -10.20957 9.99 -10.493829000000002 
		10.98 -10.842127000000001 12 -11.356960000000003 12.99 -11.985409 13.98 -12.684537 
		15 -13.407507 15.99 -14.106585 16.98 -14.733603 18 -15.240456 18.99 -15.579319000000002 
		19.98 -15.702790000000002 21 -15.579331000000002 21.99 -15.243137000000003 22.98 
		-14.733607000000001 24 -14.106584000000002 24.99 -13.4075 25.98 -12.684531000000002 
		27 -11.985407 27.99 -11.356960000000003 28.98 -10.844868 30 -10.493829000000002 30.99 
		-10.209566 31.98 -10.117264 33 -10.148331000000002 33.99 -10.238745 34.98 -10.338819000000003 
		36 -10.418388 36.99 -10.466764000000001 37.98 -10.488003000000003 39 -10.493443000000001 
		39.99 -10.493827;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Finger0_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -92.922103000000021 0.99 -92.923113 1.98 
		-92.937532000000019 3 -92.993806000000021 3.99 -93.121995000000013 4.98 -93.332986 
		6 -93.598578 6.99 -93.838755 7.98 -93.921332 9 -93.676067 9.99 -92.922103000000021 
		10.98 -92.000963 12 -90.644098 12.99 -88.994006 13.98 -87.164219000000017 15 -85.275973000000008 
		15.99 -83.451390000000018 16.98 -81.813914000000011 18 -80.488372000000012 18.99 
		-79.600659000000007 19.98 -79.276874 21 -79.600666 21.99 -80.481344000000021 22.98 
		-81.813914000000011 24 -83.451390000000018 24.99 -85.275973000000008 25.98 -87.164219000000017 
		27 -88.994006 27.99 -90.64410500000001 28.98 -91.993723000000017 30 -92.92209600000001 
		30.99 -93.67606 31.98 -93.921332 33 -93.838755 33.99 -93.598578 34.98 -93.332993000000016 
		36 -93.121995000000013 36.99 -92.993806000000021 37.98 -92.937539000000015 39 -92.923113 
		39.99 -92.922103000000021;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger0_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.029222 0.99 0.029222 1.98 0.029222 
		3 0.029222 3.99 0.029222 4.98 0.029222 6 0.029222 6.99 0.029222 7.98 0.029222 9 0.029222 
		9.99 0.029222 10.98 0.029222 12 0.029222 12.99 0.029222 13.98 0.029222 15 0.029222 
		15.99 0.029222 16.98 0.029222 18 0.029222 18.99 0.029222 19.98 0.029222 21 0.029222 
		21.99 0.029222 22.98 0.029222 24 0.029222 24.99 0.029222 25.98 0.029222 27 0.029222 
		27.99 0.029222 28.98 0.029222 30 0.029222 30.99 0.029222 31.98 0.029222 33 0.029222 
		33.99 0.029222 34.98 0.029222 36 0.029222 36.99 0.029222 37.98 0.029222 39 0.029222 
		39.99 0.029222;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Finger0_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.013941000000000002;
createNode animCurveTL -n "Bip01_R_Finger0_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0.023036000000000004;
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
	setAttr -s 41 ".ktv[0:40]"  0 1.5356500000000002 0.99 1.517759 1.98 
		1.4693250000000002 3 1.404399 3.99 1.341041 4.98 1.293829 6 1.264335 6.99 1.2312580000000002 
		7.98 1.1433670000000002 9 0.9208 9.99 0.47013900000000003 10.98 -0.027126000000000004 
		12 -0.73510700000000007 12.99 -1.5757290000000002 13.98 -2.48679 15 -3.4053120000000003 
		15.99 -4.2726780000000009 16.98 -5.034813 18 -5.641408 18.99 -6.0444870000000011 
		19.98 -6.196291 21 -6.067652 21.99 -5.70243 22.98 -5.145612 24 -4.457379 24.99 -3.6843800000000004 
		25.98 -2.8747050000000005 27 -2.0752010000000003 27.99 -1.331907 28.98 -0.69072000000000011 
		30 -0.19853500000000002 30.99 0.35241699999999992 31.98 0.75358100000000006 33 1.024639 
		33.99 1.195301 34.98 1.301337 36 1.3746670000000003 36.99 1.4346680000000003 37.98 
		1.4858390000000001 39 1.5222740000000001 39.99 1.535649;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Hand_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 8.8848270000000014 0.99 8.973026 1.98 
		9.2490840000000016 3 9.74056 3.99 10.472834 4.98 11.444657000000001 6 12.604985 6.99 
		13.839154000000002 7.98 14.970029 9 15.775883000000004 9.99 16.022236000000003 10.98 
		15.783154000000001 12 15.232105000000002 12.99 14.436473 13.98 13.454634 15 12.349874000000002 
		15.99 11.188314 16.98 10.038668 18 8.971374 18.99 8.057427 19.98 7.366709000000002 
		21 6.8425380000000011 21.99 6.3806350000000007 22.98 5.964018 24 5.5932880000000011 
		24.99 5.261786 25.98 4.9707540000000012 27 4.727078 27.99 4.5428060000000006 28.98 
		4.4338650000000008 30 4.4177930000000005 30.99 4.65225 31.98 5.1737990000000007 33 
		5.863537 33.99 6.603527 34.98 7.2983700000000011 36 7.885967 36.99 8.337211 37.98 
		8.6478000000000019 39 8.826716 39.99 8.884822;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Hand_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 58.290757000000006 0.99 58.376155000000004 
		1.98 58.637430000000009 3 59.086392 3.99 59.732364 4.98 60.569643 6 61.564897 6.99 
		62.647796000000007 7.98 63.708279 9 64.604475 9.99 65.184569 10.98 65.27873 12 65.131232000000011 
		12.99 64.81772 13.98 64.411433 15 63.982019000000008 15.99 63.594016 16.98 63.306745000000014 
		18 63.174889000000007 18.99 63.250000000000007 19.98 63.582350000000005 21 64.290334 
		21.99 65.371819000000016 22.98 66.733048 24 68.235355000000013 24.99 69.77223 25.98 
		71.230420000000009 27 72.497509 27.99 73.461768000000021 28.98 74.011987 30 74.037054000000012 
		30.99 73.021432000000019 31.98 71.092184000000017 33 68.654114 33.99 66.088155 34.98 
		63.69901 36 61.687171 36.99 60.14764 37.98 59.092259000000006 39 58.486832000000007 
		39.99 58.290757000000006;
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
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Hand_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.249881 0.99 0.249881 1.98 0.249881 
		3 0.249881 3.99 0.249881 4.98 0.249881 6 0.249881 6.99 0.249881 7.98 0.249881 9 0.249881 
		9.99 0.249881 10.98 0.249881 12 0.249881 12.99 0.249881 13.98 0.249881 15 0.249881 
		15.99 0.249881 16.98 0.249881 18 0.249881 18.99 0.249881 19.98 0.249881 21 0.249881 
		21.99 0.249881 22.98 0.249881 24 0.249881 24.99 0.249881 25.98 0.249881 27 0.249881 
		27.99 0.249881 28.98 0.249881 30 0.249881 30.99 0.249881 31.98 0.249881 33 0.249881 
		33.99 0.249881 34.98 0.249881 36 0.249881 36.99 0.249881 37.98 0.249881 39 0.249881 
		39.99 0.249881;
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
	setAttr -s 41 ".ktv[0:40]"  0 -22.540062000000002 0.99 -22.489874 1.98 
		-22.327903000000003 3 -22.026281 3.99 -21.557619000000003 4.98 -20.917858000000003 
		6 -20.148237000000005 6.99 -19.349032000000005 7.98 -18.679774 9 -18.343222000000004 
		9.99 -18.554387 10.98 -19.143406 12 -20.153801 12.99 -21.458327 13.98 -22.950102000000005 
		15 -24.517227000000002 15.99 -26.047716000000005 16.98 -27.429659 18 -28.551079000000005 
		18.99 -29.300038 19.98 -29.564592 21 -29.267420000000008 21.99 -28.487841 22.98 -27.321022 
		24 -25.899301 24.99 -24.330198 25.98 -22.727463 27 -21.204856 27.99 -19.876111 28.98 
		-18.854956 30 -18.255140000000004 30.99 -18.057476000000005 31.98 -18.428845 33 -19.145127 
		33.99 -19.994995 34.98 -20.812059999999995 36 -21.491631000000005 36.99 -21.990498 
		37.98 -22.312576 39 -22.486144000000003 39.99 -22.540058000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Forearm_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -2.0000000000000008e-006;
createNode animCurveTA -n "Bip01_R_Forearm_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.253375 0.99 0.253374 1.98 0.253374 
		3 0.253374 3.99 0.253375 4.98 0.253374 6 0.253375 6.99 0.253375 7.98 0.253375 9 0.253375 
		9.99 0.253375 10.98 0.253375 12 0.253374 12.99 0.253375 13.98 0.253374 15 0.253374 
		15.99 0.253374 16.98 0.253374 18 0.253375 18.99 0.253374 19.98 0.253375 21 0.253374 
		21.99 0.253375 22.98 0.253375 24 0.253374 24.99 0.253374 25.98 0.253374 27 0.253374 
		27.99 0.253374 28.98 0.253374 30 0.253374 30.99 0.253374 31.98 0.253375 33 0.253375 
		33.99 0.253375 34.98 0.253375 36 0.253375 36.99 0.253375 37.98 0.253375 39 0.253375 
		39.99 0.253375;
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
	setAttr -s 41 ".ktv[0:40]"  0 35.509851 0.99 32.62368 1.98 28.931751000000002 
		3 24.714517000000004 3.99 20.231313000000004 4.98 15.684996000000002 6 11.204252000000002 
		6.99 6.8467700000000011 7.98 2.6161960000000004 9 -1.514521 9.99 -5.5773150000000005 
		10.98 -8.138675000000001 12 -11.022608 12.99 -14.099472 13.98 -17.295841 15 -20.500907 
		15.99 -23.578076000000003 16.98 -26.363009000000005 18 -28.665401 18.99 -30.273111 
		19.98 -30.956376000000002 21 -30.554938000000003 21.99 -29.137466 22.98 -26.726069000000003 
		24 -23.386582 24.99 -19.123998000000004 25.98 -13.975833000000002 27 -8.061217 27.99 
		-1.664401 28.98 4.6992980000000006 30 10.306328 30.99 17.597331000000004 31.98 23.375525 
		33 27.881661 33.99 31.32997 34.98 33.868973 36 35.589368 36.99 36.551533000000006 
		37.98 36.811968 39 36.437753000000008 39.99 35.509848000000005;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_UpperArm_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -71.608 0.99 -70.951994 1.98 -70.255260000000021 
		3 -69.506112000000016 3.99 -68.715811000000016 4.98 -67.915286 6 -67.143474000000012 
		6.99 -66.432889000000017 7.98 -65.798583 9 -65.234997 9.99 -64.721981 10.98 -64.423133 
		12 -64.283859 12.99 -64.281024 13.98 -64.385021 15 -64.568438 15.99 -64.808178 16.98 
		-65.089117 18 -65.406933 18.99 -65.768475000000009 19.98 -66.188914 21 -66.768927000000019 
		21.99 -67.575654000000014 22.98 -68.594425000000015 24 -69.76013300000001 24.99 -71.010707 
		25.98 -72.25880100000002 27 -73.404401 27.99 -74.349890000000016 28.98 -75.02154400000002 
		30 -75.38855 30.99 -75.594644000000017 31.98 -75.75027 33 -75.821345 33.99 -75.742033000000021 
		34.98 -75.456326000000018 36 -74.94482 36.99 -74.233074 37.98 -73.384061 39 -72.48100700000002 
		39.99 -71.608;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_UpperArm_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -27.907871 0.99 -24.374222 1.98 -20.724528000000003 
		3 -17.250427 3.99 -14.205613 4.98 -11.757648 6 -9.95862 6.99 -8.742005 7.98 -7.9418090000000019 
		9 -7.3275390000000007 9.99 -6.6495880000000005 10.98 -5.966797 12 -5.141578 12.99 
		-4.164404 13.98 -3.0202890000000004 15 -1.7221840000000002 15.99 -0.3131 16.98 1.131204 
		18 2.503923 18.99 3.6719600000000003 19.98 4.48146 21 4.895429 21.99 4.94494 22.98 
		4.534918 24 3.5503990000000005 24.99 1.8646210000000003 25.98 -0.62011 27 -3.910917 
		27.99 -7.8406930000000008 28.98 -12.003865 30 -15.782434 30.99 -20.160438 31.98 -23.191817 
		33 -25.204766 33.99 -26.497878000000004 34.98 -27.292936 36 -27.738990000000005 36.99 
		-27.939190000000004 37.98 -27.978625000000005 39 -27.940127000000004 39.99 -27.907871;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_UpperArm_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
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
	setAttr ".ktv[0]"  0 0.106745;
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
	setAttr -s 41 ".ktv[0:40]"  0 -131.94347000000002 0.99 -133.77953400000004 
		1.98 -135.57051900000002 3 -137.293721 3.99 -138.931422 4.98 -140.470141 6 -141.900259 
		6.99 -143.21518000000003 7.98 -144.41065400000002 9 -145.48406 9.99 -146.43393400000002 
		10.98 -147.31955 12 -148.20281600000004 12.99 -149.040074 13.98 -149.81426300000004 
		15 -150.506325 15.99 -151.099936 16.98 -151.580386 18 -151.933479 18.99 -152.144313 
		19.98 -152.195922 21 -152.06873 21.99 -151.772628 22.98 -151.319267 24 -150.732609 
		24.99 -150.027146 25.98 -149.22127900000004 27 -148.336264 27.99 -147.39768700000002 
		28.98 -146.436434 30 -145.489469 30.99 -144.51769700000003 31.98 -143.454305 33 -142.29977100000002 
		33.99 -141.05531000000002 34.98 -139.72317800000002 36 -138.307075 36.99 -136.812397 
		37.98 -135.246617 39 -133.619489 39.99 -131.94347000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Clavicle_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 77.923035 0.99 77.614092 1.98 77.283873000000014 
		3 76.936346000000015 3.99 76.576054000000013 4.98 76.208002000000008 6 75.837574000000018 
		6.99 75.470403000000019 7.98 75.112331 9 74.769325000000009 9.99 74.447405 10.98 
		74.130464 12 73.797014000000019 12.99 73.463728 13.98 73.139547 15 72.83584900000001 
		15.99 72.564219 16.98 72.336439000000013 18 72.164305 18.99 72.059544000000017 19.98 
		72.033664 21 72.097274 21.99 72.243221 22.98 72.46113800000002 24 72.733547000000016 
		24.99 73.04756500000002 25.98 73.389272 27 73.745043 27.99 74.101695000000021 28.98 
		74.446538 30 74.767550000000014 30.99 75.079068000000021 31.98 75.400701 33 75.728824000000017 
		33.99 76.059903 34.98 76.390437 36 76.717056000000014 36.99 77.036531 37.98 77.345837000000017 
		39 77.642178 39.99 77.923035;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_R_Clavicle_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 50.393621 0.99 48.514930000000007 1.98 
		46.680116000000005 3 44.912371000000007 3.99 43.229955000000004 4.98 41.646776 6 
		40.173043 6.99 38.815813 7.98 37.579846 9 36.46827 9.99 35.483070000000005 10.98 
		34.563078 12 33.644059 12.99 32.771434 13.98 31.963163000000005 15 31.239436000000005 
		15.99 30.617698000000004 16.98 30.113783000000005 18 29.743054000000004 18.99 29.52151 
		19.98 29.467258 21 29.600949000000004 21.99 29.911985 22.98 30.387739000000003 24 
		31.002534 24.99 31.740656 25.98 32.582388 27 33.505074 27.99 34.481846 28.98 35.480464 
		30 36.462673000000009 30.99 37.469077 31.98 38.568754000000006 33 39.76092 33.99 
		41.044073000000004 34.98 42.41564 36 43.871624 36.99 45.406381 37.98 47.012125000000005 
		39 48.678773 39.99 50.393621;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.039639 0.99 -0.039598 1.98 -0.039551 
		3 -0.039501 3.99 -0.039447 4.98 -0.039391 6 -0.039332 6.99 -0.039272 7.98 -0.039212 
		9 -0.039153 9.99 -0.039096 10.98 -0.039039 12 -0.038977 12.99 -0.038915 13.98 -0.038852 
		15 -0.038793 15.99 -0.038738 16.98 -0.038692 18 -0.038657 18.99 -0.038635 19.98 -0.03863 
		21 -0.038643 21.99 -0.038673 22.98 -0.038718 24 -0.038772 24.99 -0.038834 25.98 -0.0389 
		27 -0.038968 27.99 -0.039034 28.98 -0.039096 30 -0.039153 30.99 -0.039206 31.98 -0.039261 
		33 -0.039314 33.99 -0.039368 34.98 -0.039419 36 -0.039469 36.99 -0.039516 37.98 -0.03956 
		39 -0.039601 39.99 -0.039639;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.006888 0.99 -0.006857 1.98 -0.0068260000000000013 
		3 -0.0067940000000000006 3.99 -0.0067620000000000006 4.98 -0.0067300000000000007 
		6 -0.0066989999999999992 6.99 -0.006669 7.98 -0.0066409999999999993 9 -0.006614 9.99 
		-0.006589 10.98 -0.0065640000000000013 12 -0.0065390000000000005 12.99 -0.006515 
		13.98 -0.0064909999999999994 15 -0.0064690000000000008 15.99 -0.0064490000000000007 
		16.98 -0.006433 18 -0.0064210000000000005 18.99 -0.006413 19.98 -0.006411 21 -0.006416 
		21.99 -0.0064259999999999994 22.98 -0.0064420000000000015 24 -0.0064610000000000006 
		24.99 -0.006484 25.98 -0.0065089999999999992 27 -0.006536 27.99 -0.006562 28.98 -0.006589 
		30 -0.0066129999999999991 30.99 -0.006638 31.98 -0.0066640000000000015 33 -0.00669 
		33.99 -0.006718 34.98 -0.006746 36 -0.0067740000000000005 36.99 -0.0068029999999999992 
		37.98 -0.006832 39 -0.00686 39.99 -0.006888;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_R_Clavicle_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.0052179999999999995 0.99 -0.005565 
		1.98 -0.005921 3 -0.006282 3.99 -0.006644 4.98 -0.007003 6 -0.007355 6.99 -0.0076950000000000013 
		7.98 -0.00802 9 -0.008325 9.99 -0.008607 10.98 -0.008881 12 -0.009165 12.99 -0.009446 
		13.98 -0.009715 15 -0.009965 15.99 -0.010187 16.98 -0.010371 18 -0.010509 18.99 -0.010593 
		19.98 -0.010614000000000002 21 -0.010563000000000001 21.99 -0.010446 22.98 -0.01027 
		24 -0.010049 24.99 -0.009791 25.98 -0.0095079999999999991 27 -0.009209 27.99 -0.008906 
		28.98 -0.0086080000000000011 30 -0.008327 30.99 -0.008049 31.98 -0.007759 33 -0.0074560000000000008 
		33.99 -0.007145 34.98 -0.006827 36 -0.006504 36.99 -0.0061790000000000005 37.98 -0.005855 
		39 -0.005534 39.99 -0.0052179999999999995;
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
	setAttr -s 41 ".ktv[0:40]"  0 1.7250450000000002 0.99 1.572395 1.98 
		1.4004840000000003 3 1.2223970000000002 3.99 1.050462 4.98 0.896211 6 0.77035900000000013 
		6.99 0.68281400000000014 7.98 0.64266900000000016 9 0.658233 9.99 0.7370850000000001 
		10.98 0.92118200000000006 12 1.2271150000000002 12.99 1.6100150000000002 13.98 2.032246 
		15 2.456068 15.99 2.845451 16.98 3.1660750000000006 18 3.3851090000000004 18.99 3.4708 
		19.98 3.3919260000000007 21 3.097756 21.99 2.6005560000000005 22.98 1.9465810000000001 
		24 1.202964 24.99 0.42088200000000003 25.98 -0.346317 27 -1.0467430000000002 27.99 
		-1.6297940000000002 28.98 -2.0458020000000006 30 -2.2455130000000003 30.99 -2.232166 
		31.98 -2.060551 33 -1.758202 33.99 -1.352295 34.98 -0.86991200000000013 36 -0.33825300000000008 
		36.99 0.215192 37.98 0.762534 39 1.2754190000000003 39.99 1.725044;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Head_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.566008 0.99 -1.847518 1.98 -2.1879090000000003 
		3 -2.5638 3.99 -2.9512010000000006 4.98 -3.3255970000000006 6 -3.66193 6.99 -3.9346620000000003 
		7.98 -4.1178600000000012 9 -4.185302 9.99 -4.110529 10.98 -3.865641 12 -3.4520920000000004 
		12.99 -2.907217 13.98 -2.261484 15 -1.548884 15.99 -0.804657 16.98 -0.064943 18 0.633649 
		18.99 1.2545750000000002 19.98 1.7618330000000002 21 2.2112470000000006 21.99 2.668776 
		22.98 3.127847 24 3.5645980000000006 24.99 3.9659750000000003 25.98 4.314911 27 4.592838 
		27.99 4.7795500000000013 28.98 4.8530940000000005 30 4.789729 30.99 4.560849 31.98 
		4.1711550000000006 33 3.645748 33.99 3.010195 34.98 2.290819 36 1.514988 36.99 0.711201 
		37.98 -0.090897000000000019 39 -0.86054700000000006 39.99 -1.566008;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Head_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -1.3213550000000003 0.99 -1.377353 1.98 
		-1.451001 3 -1.5333800000000002 3.99 -1.616237 4.98 -1.692055 6 -1.753977 6.99 -1.795608 
		7.98 -1.8106860000000002 9 -1.792637 9.99 -1.7340410000000002 10.98 -1.617975 12 
		-1.435605 12.99 -1.198985 13.98 -0.91784800000000022 15 -0.605746 15.99 -0.27988400000000008 
		16.98 0.038733 18 0.32573 18.99 0.554305 19.98 0.6966190000000001 21 0.74834400000000012 
		21.99 0.72720600000000013 22.98 0.639053 24 0.494892 24.99 0.307621 25.98 0.093630000000000019 
		27 -0.128085 27.99 -0.33686100000000008 28.98 -0.511681 30 -0.632936 30.99 -0.70725100000000007 
		31.98 -0.758334 33 -0.79588400000000015 33.99 -0.830133 34.98 -0.87046900000000016 
		36 -0.92435900000000015 36.99 -0.996542 37.98 -1.088535 39 -1.198483 39.99 -1.3213550000000003;
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
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTL -n "Bip01_Head_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.099829000000000015 0.99 0.099829000000000015 
		1.98 0.099829000000000015 3 0.099829000000000015 3.99 0.099829000000000015 4.98 0.099829000000000015 
		6 0.099829000000000015 6.99 0.099829000000000015 7.98 0.099829000000000015 9 0.099829000000000015 
		9.99 0.099829000000000015 10.98 0.099829000000000015 12 0.099829000000000015 12.99 
		0.099829000000000015 13.98 0.099829000000000015 15 0.099829000000000015 15.99 0.099829000000000015 
		16.98 0.099829000000000015 18 0.099829000000000015 18.99 0.099829000000000015 19.98 
		0.099829000000000015 21 0.099829000000000015 21.99 0.099829000000000015 22.98 0.099829000000000015 
		24 0.099829000000000015 24.99 0.099829000000000015 25.98 0.099829000000000015 27 
		0.099829000000000015 27.99 0.099829000000000015 28.98 0.099829000000000015 30 0.099829000000000015 
		30.99 0.099829000000000015 31.98 0.099829000000000015 33 0.099829000000000015 33.99 
		0.099829000000000015 34.98 0.099829000000000015 36 0.099829000000000015 36.99 0.099829000000000015 
		37.98 0.099829000000000015 39 0.099829000000000015 39.99 0.099829000000000015;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.964256 0.99 0.96128499999999983 1.98 
		0.958641 3 0.95638100000000015 3.99 0.95453800000000011 4.98 0.95313100000000006 
		6 0.952159 6.99 0.951602 7.98 0.951426 9 0.951575 9.99 0.95198700000000014 10.98 
		0.95264000000000015 12 0.95358300000000018 12.99 0.954779 13.98 0.95617800000000008 
		15 0.957696 15.99 0.9592210000000001 16.98 0.960617 18 0.961744 18.99 0.96245900000000006 
		19.98 0.96263900000000013 21 0.96219899999999992 21.99 0.96121900000000016 22.98 
		0.959839 24 0.9582520000000001 24.99 0.95661800000000008 25.98 0.95507900000000012 
		27 0.95375300000000007 27.99 0.952712 28.98 0.951989 30 0.9515760000000002 30.99 
		0.95142700000000024 31.98 0.95154000000000016 33 0.95195300000000016 33.99 0.95269100000000007 
		34.98 0.95376899999999987 36 0.95520100000000008 36.99 0.956981 37.98 0.95909900000000015 
		39 0.961534 39.99 0.964256;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Neck_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 4.39908 0.99 3.8972350000000002 1.98 
		3.3815680000000006 3 2.858025 3.99 2.3325010000000006 4.98 1.8109180000000002 6 1.299198 
		6.99 0.80324800000000007 7.98 0.32898900000000003 9 -0.117656 9.99 -0.530783 10.98 
		-0.93233200000000016 12 -1.349799 12.99 -1.7623930000000003 13.98 -2.159616 15 -2.5284 
		15.99 -2.8557020000000004 16.98 -3.1284490000000003 18 -3.3335680000000005 18.99 
		-3.458004 19.98 -3.4886920000000003 21 -3.4132310000000006 21.99 -3.2396250000000006 
		22.98 -2.9793200000000004 24 -2.65194 24.99 -2.271643 25.98 -1.853959 27 -1.414428 
		27.99 -0.968557 28.98 -0.53189300000000006 30 -0.11995300000000002 30.99 0.28536000000000006 
		31.98 0.71023800000000015 33 1.151214 33.99 1.604841 34.98 2.0676790000000005 36 
		2.536267 36.99 3.007152 37.98 3.4768850000000002 39 3.9420120000000005 39.99 4.399081;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Neck_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.360364 0.99 0.31583900000000004 1.98 
		0.270142 3 0.22379300000000005 3.99 0.17731 4.98 0.131208 6 0.086000000000000007 
		6.99 0.042202 7.98 0.00032800000000000006 9 -0.039107 9.99 -0.075585 10.98 -0.11104700000000002 
		12 -0.14792400000000003 12.99 -0.184385 13.98 -0.21950500000000003 15 -0.252128 15.99 
		-0.281098 16.98 -0.30525200000000008 18 -0.323426 18.99 -0.33445600000000003 19.98 
		-0.337176 21 -0.33048600000000006 21.99 -0.315102 22.98 -0.292044 24 -0.26306100000000004 
		24.99 -0.229413 25.98 -0.19248 27 -0.15363400000000002 27.99 -0.114246 28.98 -0.075683 
		30 -0.03931 30.99 -0.0035240000000000002 31.98 0.03399 33 0.07293100000000001 33.99 
		0.11300000000000002 34.98 0.15390000000000004 36 0.19532900000000003 36.99 0.23699100000000003 
		37.98 0.27858400000000005 39 0.31981000000000004 39.99 0.360364;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Neck_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 0 1.98 0 3 0 3.99 0 4.98 0 6 0 
		6.99 0 7.98 0 9 0 9.99 0 10.98 0 12 0 12.99 0 13.98 0 15 0 15.99 0 16.98 0 18 0 18.99 
		0 19.98 0 21 0 21.99 0 22.98 0 24 0 24.99 0 25.98 0 27 0 27.99 0 28.98 0 30 0 30.99 
		0 31.98 0 33 0 33.99 0 34.98 0 36 0 36.99 0 37.98 0 39 0 39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Neck_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr ".ktv[0]"  0 -7.9000000000000009e-005;
createNode animCurveTL -n "Bip01_Neck_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.204456 0.99 0.204456 1.98 0.204456 
		3 0.204456 3.99 0.204456 4.98 0.204456 6 0.204456 6.99 0.204456 7.98 0.204456 9 0.204456 
		9.99 0.204456 10.98 0.204456 12 0.204456 12.99 0.204456 13.98 0.204456 15 0.204456 
		15.99 0.204456 16.98 0.204456 18 0.204456 18.99 0.204456 19.98 0.204456 21 0.204456 
		21.99 0.204456 22.98 0.204456 24 0.204456 24.99 0.204456 25.98 0.204456 27 0.204456 
		27.99 0.204456 28.98 0.204456 30 0.204456 30.99 0.204456 31.98 0.204456 33 0.204456 
		33.99 0.204456 34.98 0.204456 36 0.204456 36.99 0.204456 37.98 0.204456 39 0.204456 
		39.99 0.204456;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.07513800000000001 0.99 0.074244 1.98 
		0.085392 3 0.10805400000000001 3.99 0.140835 4.98 0.181433 6 0.22664200000000004 
		6.99 0.27238 7.98 0.313764 9 0.34524200000000005 9.99 0.36078200000000005 10.98 0.34256900000000007 
		12 0.282849 12.99 0.19300300000000004 13.98 0.083867000000000011 15 -0.032887 15.99 
		-0.144935 16.98 -0.23927400000000001 18 -0.30224500000000004 18.99 -0.31959100000000007 
		19.98 -0.276574 21 -0.148358 21.99 0.065236 22.98 0.349341 24 0.679131 24.99 1.034929 
		25.98 1.3938580000000003 27 1.7311060000000003 27.99 2.0198620000000003 28.98 2.231536 
		30 2.336304 30.99 2.329699 31.98 2.2360090000000006 33 2.06868 33.99 1.8417940000000002 
		34.98 1.5699440000000002 36 1.2681350000000002 36.99 0.951758 37.98 0.63658700000000012 
		39 0.33882200000000007 39.99 0.07513800000000001;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine1_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -2.631808 0.99 -1.7572490000000003 1.98 
		-0.794872 3 0.21753900000000004 3.99 1.242243 4.98 2.241515 6 3.177722 6.99 4.013282 
		7.98 4.71069 9 5.2325470000000012 9.99 5.541517 10.98 5.6321580000000013 12 5.5405250000000006 
		12.99 5.291629 13.98 4.910218 15 4.420855 15.99 3.847882 16.98 3.215474 18 2.547685 
		18.99 1.868577 19.98 1.2023300000000001 21 0.44800000000000006 21.99 -0.46898200000000012 
		22.98 -1.5123040000000003 24 -2.6086170000000006 24.99 -3.70962 25.98 -4.761368 27 
		-5.7105680000000012 27.99 -6.5047380000000006 28.98 -7.09208 30 -7.4213900000000015 
		30.99 -7.477558000000001 31.98 -7.3068180000000007 33 -6.9499750000000011 33.99 -6.4476660000000008 
		34.98 -5.8403350000000005 36 -5.168258 36.99 -4.471537 37.98 -3.7900970000000007 
		39 -3.1636770000000003 39.99 -2.6318070000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine1_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -3.8312910000000002 0.99 -3.32624 1.98 
		-2.8064350000000005 3 -2.277912 3.99 -1.7467070000000002 4.98 -1.218956 6 -0.700979 
		6.99 -0.19935200000000003 7.98 0.27906700000000007 9 0.72716400000000014 9.99 1.13765 
		10.98 1.5327150000000003 12 1.940744 12.99 2.341265 13.98 2.7241030000000004 15 3.076565 
		15.99 3.3858070000000002 16.98 3.6387010000000006 18 3.8217550000000005 18.99 3.921077 
		19.98 3.922398 21 3.806076 21.99 3.575427 22.98 3.242599 24 2.8311100000000002 24.99 
		2.358573 25.98 1.845917 27 1.315766 27.99 0.792353 28.98 0.301156 30 -0.131823 30.99 
		-0.520898 31.98 -0.89874200000000015 33 -1.267842 33.99 -1.6312220000000002 34.98 
		-1.9919720000000005 36 -2.3528770000000003 36.99 -2.7161540000000004 37.98 -3.0832890000000006 
		39 -3.455 39.99 -3.8312910000000002;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 1.1000000000000001e-005 0.99 8.9999999999999985e-006 
		1.98 8.0000000000000013e-006 3 6.000000000000001e-006 3.99 5e-006 4.98 3.0000000000000005e-006 
		6 2.0000000000000003e-006 6.99 1.0000000000000002e-006 7.98 -1.0000000000000002e-006 
		9 -2.0000000000000003e-006 9.99 -3.0000000000000005e-006 10.98 -4.0000000000000007e-006 
		12 -5e-006 12.99 -7.0000000000000007e-006 13.98 -8.0000000000000013e-006 15 -8.9999999999999985e-006 
		15.99 -1e-005 16.98 -1e-005 18 -1.1000000000000001e-005 18.99 -1.1000000000000001e-005 
		19.98 -1.1000000000000001e-005 21 -1.1000000000000001e-005 21.99 -1e-005 22.98 -8.9999999999999985e-006 
		24 -8.0000000000000013e-006 24.99 -7.0000000000000007e-006 25.98 -5e-006 27 -4.0000000000000007e-006 
		27.99 -2.0000000000000003e-006 28.98 -1.0000000000000002e-006 30 0 30.99 1.0000000000000002e-006 
		31.98 3.0000000000000005e-006 33 4.0000000000000007e-006 33.99 5e-006 34.98 6.000000000000001e-006 
		36 7.0000000000000007e-006 36.99 8.0000000000000013e-006 37.98 8.9999999999999985e-006 
		39 1e-005 39.99 1.1000000000000001e-005;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.000162 0.99 -0.00016300000000000003 
		1.98 -0.00016300000000000003 3 -0.00016300000000000003 3.99 -0.00016300000000000003 
		4.98 -0.00016300000000000003 6 -0.00016300000000000003 6.99 -0.00016300000000000003 
		7.98 -0.00016300000000000003 9 -0.00016300000000000003 9.99 -0.00016300000000000003 
		10.98 -0.00016300000000000003 12 -0.00016300000000000003 12.99 -0.00016300000000000003 
		13.98 -0.00016300000000000003 15 -0.00016300000000000003 15.99 -0.000162 16.98 -0.000162 
		18 -0.000162 18.99 -0.000162 19.98 -0.000162 21 -0.000162 21.99 -0.000162 22.98 -0.00016300000000000003 
		24 -0.00016300000000000003 24.99 -0.00016300000000000003 25.98 -0.00016300000000000003 
		27 -0.00016300000000000003 27.99 -0.00016300000000000003 28.98 -0.00016300000000000003 
		30 -0.00016300000000000003 30.99 -0.00016300000000000003 31.98 -0.00016300000000000003 
		33 -0.00016300000000000003 33.99 -0.00016300000000000003 34.98 -0.00016300000000000003 
		36 -0.00016300000000000003 36.99 -0.00016300000000000003 37.98 -0.00016300000000000003 
		39 -0.00016300000000000003 39.99 -0.000162;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine1_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.197495 0.99 0.197496 1.98 0.197496 
		3 0.197496 3.99 0.197496 4.98 0.197496 6 0.197496 6.99 0.197496 7.98 0.197496 9 0.197496 
		9.99 0.197496 10.98 0.197496 12 0.197496 12.99 0.197495 13.98 0.197495 15 0.197495 
		15.99 0.197495 16.98 0.19749400000000003 18 0.19749400000000003 18.99 0.19749400000000003 
		19.98 0.197495 21 0.197495 21.99 0.197496 22.98 0.197497 24 0.197498 24.99 0.197499 
		25.98 0.1975 27 0.197501 27.99 0.197502 28.98 0.197502 30 0.197502 30.99 0.197502 
		31.98 0.197502 33 0.197501 33.99 0.1975 34.98 0.197499 36 0.197499 36.99 0.197498 
		37.98 0.197497 39 0.197496 39.99 0.197495;
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
	setAttr -s 41 ".ktv[0:40]"  0 0.75120100000000012 0.99 0.81455500000000014 
		1.98 0.89922200000000008 3 0.997963 3.99 1.1032760000000001 4.98 1.207321 6 1.3018430000000003 
		6.99 1.378224 7.98 1.427438 9 1.439806 9.99 1.4050690000000001 10.98 1.29231 12 1.088765 
		12.99 0.82123100000000016 13.98 0.513198 15 0.189432 15.99 -0.12486899999999998 16.98 
		-0.404173 18 -0.622698 18.99 -0.75447700000000006 19.98 -0.773423 21 -0.653736 21.99 
		-0.41020800000000007 22.98 -0.068666 24 0.334704 24.99 0.77170500000000009 25.98 
		1.212343 27 1.6263160000000003 27.99 1.9831690000000002 28.98 2.25233 30 2.4030920000000004 
		30.99 2.4395900000000004 31.98 2.395408 33 2.283609 33.99 2.117186 34.98 1.909504 
		36 1.6743310000000002 36.99 1.425913 37.98 1.179006 39 0.94886800000000027 39.99 
		0.75120000000000009;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -6.0057980000000013 0.99 -4.595435 1.98 
		-3.11865 3 -1.6131490000000002 3.99 -0.11650700000000001 4.98 1.333835 6 2.700537 
		6.99 4.013465 7.98 5.273655 9 6.400742000000001 9.99 7.3145179999999987 10.98 7.9295290000000014 
		12 8.205299 12.99 8.209349 13.98 8.056652 15 7.7713950000000009 15.99 7.377396 16.98 
		6.8981580000000005 18 6.3568860000000011 18.99 5.776518 19.98 5.1798280000000005 
		21 4.397722 21.99 3.3397070000000006 22.98 2.1140220000000003 24 0.87310500000000013 
		24.99 -0.258936 25.98 -1.150163 27 -1.765741 27.99 -2.1979400000000004 28.98 -2.50535 
		30 -2.7470010000000005 30.99 -2.974761 31.98 -3.249343 33 -3.5719160000000003 33.99 
		-3.896799000000001 34.98 -4.226704 36 -4.563852 36.99 -4.909852 37.98 -5.2655500000000011 
		39 -5.631058 39.99 -6.0057980000000013;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Spine_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -3.422391 0.99 -3.010476 1.98 -2.5941050000000003 
		3 -2.1729110000000005 3.99 -1.7472930000000002 4.98 -1.31851 6 -0.8887 6.99 -0.459209 
		7.98 -0.032553000000000006 9 0.38600600000000007 9.99 0.79061500000000007 10.98 1.1835510000000002 
		12 1.576267 12.99 1.9589120000000002 13.98 2.332868 15 2.695625 15.99 3.044702 16.98 
		3.377174 18 3.6892890000000005 18.99 3.9761620000000004 19.98 4.23156 21 4.4928 21.99 
		4.779136 22.98 5.0646110000000011 24 5.3155290000000006 24.99 5.510906 25.98 5.6342620000000005 
		27 5.672241 27.99 5.6087500000000006 28.98 5.4265730000000012 30 5.106976 30.99 4.623412 
		31.98 3.9797160000000003 33 3.2052230000000006 33.99 2.331133 34.98 1.3862590000000001 
		36 0.39902700000000008 36.99 -0.60260500000000006 37.98 -1.5912020000000002 39 -2.539892 
		39.99 -3.422391;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.0117 0.99 0.009764 1.98 0.007796 3 
		0.005825 3.99 0.003882 4.98 0.001997 6 0.0002 6.99 -0.0016060000000000002 7.98 -0.003467 
		9 -0.005267 9.99 -0.0068930000000000007 10.98 -0.008225 12 -0.009171 12.99 -0.009801 
		13.98 -0.010283 15 -0.01061 15.99 -0.010773 16.98 -0.010766 18 -0.01058 18.99 -0.010208 
		19.98 -0.0096420000000000013 21 -0.0086080000000000011 21.99 -0.0070160000000000005 
		22.98 -0.005076 24 -0.0030700000000000007 24.99 -0.001235 25.98 0.000182 27 0.0011220000000000002 
		27.99 0.0017690000000000004 28.98 0.002245 30 0.00267 30.99 0.0031669999999999997 
		31.98 0.0038550000000000004 33 0.004716 33.99 0.005641 34.98 0.0066159999999999995 
		36 0.0076240000000000006 36.99 0.008652 37.98 0.009684 39 0.010705000000000001 39.99 
		0.0117;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -0.022547 0.99 -0.022547 1.98 -0.022547 
		3 -0.022547 3.99 -0.022547 4.98 -0.022547 6 -0.022547 6.99 -0.022547 7.98 -0.022547 
		9 -0.022547 9.99 -0.022547 10.98 -0.022547 12 -0.022547 12.99 -0.022547 13.98 -0.022547 
		15 -0.022547 15.99 -0.022547 16.98 -0.022547 18 -0.022547 18.99 -0.022547 19.98 -0.022546 
		21 -0.022546 21.99 -0.022546 22.98 -0.022546 24 -0.022546 24.99 -0.022546 25.98 -0.022546 
		27 -0.022546 27.99 -0.022546 28.98 -0.022546 30 -0.022546 30.99 -0.022546 31.98 -0.022546 
		33 -0.022547 33.99 -0.022547 34.98 -0.022547 36 -0.022547 36.99 -0.022547 37.98 -0.022547 
		39 -0.022547 39.99 -0.022547;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_Spine_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.10985500000000001 0.99 0.110044 1.98 
		0.110201 3 0.11032300000000002 3.99 0.110409 4.98 0.11046 6 0.110477 6.99 0.110466 
		7.98 0.110424 9 0.110352 9.99 0.110262 10.98 0.11017100000000002 12 0.110095 12.99 
		0.11004 13.98 0.109995 15 0.10996400000000002 15.99 0.109947 16.98 0.109947 18 0.10996400000000002 
		18.99 0.109999 19.98 0.11005 21 0.11013600000000001 21.99 0.11025 22.98 0.11035700000000001 
		24 0.110432 24.99 0.11047000000000001 25.98 0.110477 27 0.110473 27.99 0.110466 28.98 
		0.110458 30 0.110449 30.99 0.110435 31.98 0.110413 33 0.11038 33.99 0.110336 34.98 
		0.110281 36 0.110215 36.99 0.110138 37.98 0.11005200000000001 39 0.109957 39.99 0.10985500000000001;
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
	setAttr -s 33 ".ktv[0:32]"  0 -89.999916 0.99 -89.999916 1.98 -89.999916 
		3 -89.999922000000012 3.99 -89.999916 4.98 -89.999916 6 -89.999656 6.99 -89.999888 
		7.98 -89.999916 9 -89.999909 9.99 -89.999916 10.98 -89.999916 12 -89.999909 12.99 
		-89.999909 15.99 -89.999909 16.98 -89.999909 18 -89.999916 18.99 -89.999916 19.98 
		-89.999916 21 -89.999916 21.99 -89.999909 22.98 -89.999909 24 -89.999916 24.99 -89.99995 
		25.98 -90.000066000000018 27 -89.999895000000009 27.99 -89.999916 28.98 -89.999916 
		30 -89.999922000000012 30.99 -89.999909 31.98 -89.999916 33 -89.999916 39.99 -89.999916;
	setAttr -s 33 ".kit[0:32]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 2;
	setAttr -s 33 ".kot[0:32]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Pelvis_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 -83.925371 0.99 -84.933555000000013 1.98 
		-85.957154000000017 3 -86.980754 3.99 -87.98893 4.98 -88.966289 6 -89.897394 6.99 
		-90.833895000000012 7.98 -91.798455000000018 9 -92.732182 9.99 -93.576189 10.98 -94.267827000000011 
		12 -94.759499 12.99 -95.086945000000014 13.98 -95.337531000000013 15 -95.507227000000015 
		15.99 -95.591982 16.98 -95.587755 18 -95.49052 18.99 -95.296215000000018 19.98 -95.000809000000018 
		21 -94.462693 21.99 -93.634355 22.98 -92.626519000000016 24 -91.585120000000018 24.99 
		-90.632637 25.98 -89.897394 27 -89.410245 27.99 -89.074691 28.98 -88.828053000000011 
		30 -88.607623000000018 30.99 -88.350719 31.98 -87.994634000000019 33 -87.548820000000021 
		33.99 -87.069669000000019 34.98 -86.564850000000021 36 -86.042094 36.99 -85.50906 
		37.98 -84.973477 39 -84.443017000000012 39.99 -83.925371;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_Pelvis_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 31 ".ktv[0:30]"  0 6.000000000000001e-006 0.99 -1.0000000000000004e-006 
		1.98 5e-006 3 1e-005 3.99 6.000000000000001e-006 4.98 -5e-006 6 -0.000151 6.99 0 
		7.98 0 9 -1.5000000000000005e-005 9.99 1.5000000000000005e-005 10.98 0 12 0 22.98 
		0 24 0 24.99 3.1000000000000008e-005 25.98 0.00022 27 -4e-005 27.99 -7.0000000000000024e-006 
		28.98 7.0000000000000024e-006 30 1.1000000000000001e-005 30.99 -3.0000000000000005e-006 
		31.98 1.0000000000000004e-006 33 2.0000000000000008e-006 33.99 2.0000000000000008e-006 
		34.98 -2.0000000000000008e-006 36 3.0000000000000005e-006 36.99 -1.0000000000000004e-006 
		37.98 0 39 1.0000000000000004e-006 39.99 5e-006;
	setAttr -s 31 ".kit[0:30]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 2;
	setAttr -s 31 ".kot[0:30]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 2;
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
	setAttr -s 41 ".ktv[0:40]"  0 -82.316103 0.99 -83.089889 1.98 -83.858551 
		3 -84.625185000000016 3.99 -85.392646000000013 4.98 -86.163521 6 -86.940155000000019 
		6.99 -87.724732000000017 7.98 -88.519247000000007 9 -89.325714000000019 9.99 -90.146129 
		10.98 -91.033275 12 -92.03514100000001 12.99 -93.093096000000017 13.98 -94.172362000000021 
		15 -95.232332000000014 15.99 -96.232524 16.98 -97.132600000000011 18 -97.892486000000019 
		18.99 -98.472246000000013 19.98 -98.832060000000013 21 -98.988273000000021 21.99 
		-98.992740000000012 22.98 -98.856963 24 -98.594554000000016 24.99 -98.216865 25.98 
		-97.735152 27 -97.16005 27.99 -96.501757 28.98 -95.770209 30 -94.975360000000009 
		30.99 -94.067307000000014 31.98 -93.00735 33 -91.822613 33.99 -90.540429 34.98 -89.188148 
		36 -87.792965000000009 36.99 -86.381767000000011 37.98 -84.981182000000018 39 -83.617357 
		39.99 -82.316097;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 1.512197 0.99 1.6608410000000002 1.98 
		1.8131960000000003 3 1.963432 3.99 2.106461 4.98 2.2379260000000003 6 2.3542220000000005 
		6.99 2.4525160000000006 7.98 2.530778 9 2.5878270000000003 9.99 2.6233840000000006 
		10.98 2.648578 12 2.675773 12.99 2.705386 13.98 2.737338 15 2.769675 15.99 2.7984030000000004 
		16.98 2.817384 18 2.8184610000000005 18.99 2.79181 19.98 2.726509 21 2.598186 21.99 
		2.4021710000000005 22.98 2.150242 24 1.8627790000000002 24.99 1.5548890000000002 
		25.98 1.2437100000000003 27 0.94717700000000016 27.99 0.684155 28.98 0.47452800000000006 
		30 0.33924600000000005 30.99 0.279746 31.98 0.279232 33 0.33205300000000004 33.99 
		0.43202200000000007 34.98 0.57192 36 0.74315000000000009 36.99 0.93551400000000007 
		37.98 1.1371130000000003 39 1.334376 39.99 1.512198;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTA -n "Bip01_rotateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 -0.53174600000000016 1.98 -1.1348040000000001 
		3 -1.7795450000000002 3.99 -2.436214 4.98 -3.0749400000000002 6 -3.665752 6.99 -4.178593 
		7.98 -4.583332 9 -4.8497790000000007 9.99 -4.9477090000000006 10.98 -4.8542420000000011 
		12 -4.583578 12.99 -4.171591 13.98 -3.6494480000000005 15 -3.049402 15.99 -2.4035690000000005 
		16.98 -1.7438980000000002 18 -1.102204 18.99 -0.5102620000000001 19.98 0 21 0.48964400000000008 
		21.99 1.022229 22.98 1.584484 24 2.142262 24.99 2.6752330000000004 25.98 3.159849 
		27 3.5729600000000006 27.99 3.8919560000000004 28.98 4.0948930000000008 30 4.1605930000000013 
		30.99 4.0711400000000006 31.98 3.8397370000000004 33 3.4927180000000004 33.99 3.056478 
		34.98 2.557254 36 2.020914 36.99 1.4727770000000002 37.98 0.937479 39 0.43887000000000004 
		39.99 0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateZ";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0.865833 0.99 0.863236 1.98 0.860006 
		3 0.857092 3.99 0.855445 4.98 0.85601400000000016 6 0.859764 6.99 0.866062 7.98 0.87346 
		9 0.880511 9.99 0.88576700000000008 10.98 0.889517 12 0.892793 12.99 0.89506200000000014 
		13.98 0.89587900000000009 15 0.894777 15.99 0.89073100000000016 16.98 0.884053 18 
		0.87628000000000006 18.99 0.86895 19.98 0.863601 21 0.859948 21.99 0.856968 22.98 
		0.855024 24 0.854575 24.99 0.85601400000000016 25.98 0.860329 27 0.867246 27.99 0.875286 
		28.98 0.88296700000000006 30 0.88881 30.99 0.89321 31.98 0.897154 33 0.900048 33.99 
		0.901301 34.98 0.900318 36 0.896365 36.99 0.889836 37.98 0.88183500000000015 39 0.873466 
		39.99 0.865833;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 -0.022937 1.98 -0.045091 3 -0.067636 
		3.99 -0.091748 4.98 -0.11860200000000001 6 -0.149304 6.99 -0.18307000000000004 7.98 
		-0.218241 9 -0.253158 9.99 -0.286162 10.98 -0.31735 12 -0.348714 12.99 -0.379672 
		13.98 -0.410427 15 -0.440984 15.99 -0.471349 16.98 -0.501528 18 -0.531528 18.99 -0.561354 
		19.98 -0.591012 21 -0.619465 21.99 -0.646264 22.98 -0.673048 24 -0.700461 24.99 -0.729809 
		25.98 -0.76214 27 -0.796693 27.99 -0.831896 28.98 -0.866179 30 -0.89797000000000016 
		30.99 -0.92764700000000011 31.98 -0.956711 33 -0.985269 33.99 -1.01343 34.98 -1.041301 
		36 -1.068992 36.99 -1.096611 37.98 -1.124266 39 -1.152066 39.99 -1.180118;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Bip01_translateX";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 41 ".ktv[0:40]"  0 0 0.99 -0.003195 1.98 -0.00651 3 -0.009765 
		3.99 -0.012781 4.98 -0.015377000000000002 6 -0.017849 6.99 -0.020319 7.98 -0.022340999999999996 
		9 -0.02347 9.99 -0.023261 10.98 -0.022025000000000003 12 -0.02037 12.99 -0.018384 
		13.98 -0.016118 15 -0.013632 15.99 -0.010986000000000001 16.98 -0.008239 18 -0.005453 
		18.99 -0.002686 19.98 0 21 0.0029370000000000004 21.99 0.0062829999999999995 22.98 
		0.009817 24 0.013188 24.99 0.016131 25.98 0.019052 27 0.022141 27.99 0.024791 28.98 
		0.026395000000000002 30 0.026348 30.99 0.024976 31.98 0.023074 33 0.020736 33.99 
		0.018054 34.98 0.015123 36 0.012036 36.99 0.008887 37.98 0.005769 39 0.002775 39.99 
		0;
	setAttr -s 41 ".kit[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
	setAttr -s 41 ".kot[0:40]"  10 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 2;
createNode animCurveTL -n "Fbx_Root_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 1.18;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
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
	setAttr -s 4 ".st";
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
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
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
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
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
	setAttr ".hwfr" 30;
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
select -ne :ikSystem;
	setAttr -s 4 ".sol";
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
connectAttr "Fbx_Root_translateY.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[3].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[3].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[4].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of walk.ma
