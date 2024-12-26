//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Fri, Oct 24, 2008 04:07:59 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 464 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 465 "From_Ear_HairL_locator1.rotateZ" 
		2 1 "From_Ear_HairL_locator1.rotateY" 2 2 "From_Ear_HairL_locator1.rotateX" 
		2 3 "From_Ear_HairL_locator.rotateZ" 2 4 "From_Ear_HairL_locator.rotateY" 
		2 5 "From_Ear_HairL_locator.rotateX" 2 6 "Liana3_1_main_locator.rotateZ" 
		2 7 "Liana3_1_main_locator.rotateY" 2 8 "Liana3_1_main_locator.rotateX" 
		2 9 "Liana2_1_main_locator.rotateZ" 2 10 "Liana2_1_main_locator.rotateY" 
		2 11 "Liana2_1_main_locator.rotateX" 2 12 "Liana1_1_main_locator.rotateZ" 
		2 13 "Liana1_1_main_locator.rotateY" 2 14 "Liana1_1_main_locator.rotateX" 
		2 15 "TPilat4_locator.rotateZ" 2 16 "TPilat4_locator.rotateY" 2 
		17 "TPilat4_locator.rotateX" 2 18 "TPilat3_locator.rotateZ" 2 19 "TPilat3_locator.rotateY" 
		2 20 "TPilat3_locator.rotateX" 2 21 "TPilat2_locator.rotateZ" 2 
		22 "TPilat2_locator.rotateY" 2 23 "TPilat2_locator.rotateX" 2 24 "TPilat1_locator.rotateZ" 
		2 25 "TPilat1_locator.rotateY" 2 26 "TPilat1_locator.rotateX" 2 
		27 "Plait6_locator.rotateZ" 2 28 "Plait6_locator.rotateY" 2 29 "Plait6_locator.rotateX" 
		2 30 "Plait5_locator.rotateZ" 2 31 "Plait5_locator.rotateY" 2 
		32 "Plait5_locator.rotateX" 2 33 "Plait4_locator.rotateZ" 2 34 "Plait4_locator.rotateY" 
		2 35 "Plait4_locator.rotateX" 2 36 "Plait3_locator.rotateZ" 2 
		37 "Plait3_locator.rotateY" 2 38 "Plait3_locator.rotateX" 2 39 "Plait2_locator.rotateZ" 
		2 40 "Plait2_locator.rotateY" 2 41 "Plait2_locator.rotateX" 2 
		42 "Plait1_locator.rotateZ" 2 43 "Plait1_locator.rotateY" 2 44 "Plait1_locator.rotateX" 
		2 45 "Butterfly2_locator.WingL" 0 1 "Butterfly2_locator.WingR" 
		0 2 "Butterfly2_locator.rotateZ" 2 46 "Butterfly2_locator.rotateY" 
		2 47 "Butterfly2_locator.rotateX" 2 48 "Butterfly2_locator.translateZ" 
		1 1 "Butterfly2_locator.translateY" 1 2 "Butterfly2_locator.translateX" 
		1 3 "Butterfly1_locator.WingL" 0 3 "Butterfly1_locator.WingR" 
		0 4 "Butterfly1_locator.rotateZ" 2 49 "Butterfly1_locator.rotateY" 
		2 50 "Butterfly1_locator.rotateX" 2 51 "Butterfly1_locator.translateZ" 
		1 4 "Butterfly1_locator.translateY" 1 5 "Butterfly1_locator.translateX" 
		1 6 "Butterfly_locator.wingL" 0 5 "Butterfly_locator.WingR" 0 
		6 "Butterfly_locator.rotateZ" 2 52 "Butterfly_locator.rotateY" 2 
		53 "Butterfly_locator.rotateX" 2 54 "Butterfly_locator.translateZ" 1 
		7 "Butterfly_locator.translateY" 1 8 "Butterfly_locator.translateX" 
		1 9 "Chest_locator.rotateZ" 2 55 "Chest_locator.rotateY" 2 
		56 "Chest_locator.rotateX" 2 57 "Spine_locator.rotateZ" 2 58 "Spine_locator.rotateY" 
		2 59 "Spine_locator.rotateX" 2 60 "Head_locator.Jaw" 0 7 "Head_locator.translateZ" 
		1 10 "Head_locator.translateY" 1 11 "Head_locator.translateX" 1 
		12 "Head_Top_locator.NeckRZ" 0 8 "Head_Top_locator.NeckRX" 0 9 "Head_Top_locator.translateZ" 
		1 13 "Head_Top_locator.translateY" 1 14 "Head_Top_locator.translateX" 
		1 15 "L_Elbow_locator.translateZ" 1 16 "L_Elbow_locator.translateY" 
		1 17 "L_Elbow_locator.translateX" 1 18 "R_Elbow_locator.translateZ" 
		1 19 "R_Elbow_locator.translateY" 1 20 "R_Elbow_locator.translateX" 
		1 21 "L_Knee_locator.translateZ" 1 22 "L_Knee_locator.translateY" 
		1 23 "L_Knee_locator.translateX" 1 24 "R_Knee_locator.translateZ" 
		1 25 "R_Knee_locator.translateY" 1 26 "R_Knee_locator.translateX" 
		1 27 "L_Leg_locator.Toe" 0 10 "L_Leg_locator.rotateZ" 2 61 "L_Leg_locator.rotateY" 
		2 62 "L_Leg_locator.rotateX" 2 63 "L_Leg_locator.translateZ" 1 
		28 "L_Leg_locator.translateY" 1 29 "L_Leg_locator.translateX" 1 
		30 "R_Leg_locator.Toe" 0 11 "R_Leg_locator.rotateZ" 2 64 "R_Leg_locator.rotateY" 
		2 65 "R_Leg_locator.rotateX" 2 66 "R_Leg_locator.translateZ" 1 
		31 "R_Leg_locator.translateY" 1 32 "R_Leg_locator.translateX" 1 
		33 "L_Hand_locator.rotateZ" 2 67 "L_Hand_locator.rotateY" 2 68 "L_Hand_locator.rotateX" 
		2 69 "L_Hand_locator.translateZ" 1 34 "L_Hand_locator.translateY" 
		1 35 "L_Hand_locator.translateX" 1 36 "R_Hand_locator.rotateZ" 
		2 70 "R_Hand_locator.rotateY" 2 71 "R_Hand_locator.rotateX" 2 
		72 "R_Hand_locator.translateZ" 1 37 "R_Hand_locator.translateY" 1 
		38 "R_Hand_locator.translateX" 1 39 "Hip_locator.rotateZ" 2 73 "Hip_locator.rotateY" 
		2 74 "Hip_locator.rotateX" 2 75 "Hip_locator.translateZ" 1 
		40 "Hip_locator.translateY" 1 41 "Hip_locator.translateX" 1 42 "Foliage3_locator.rotateZ" 
		2 76 "Foliage3_locator.rotateY" 2 77 "Foliage3_locator.rotateX" 
		2 78 "Liana_locator.rotateZ" 2 79 "Liana_locator.rotateY" 2 
		80 "Liana_locator.rotateX" 2 81 "Liana1_locator.rotateZ" 2 82 "Liana1_locator.rotateY" 
		2 83 "Liana1_locator.rotateX" 2 84 "Liana_01_locator.rotateZ" 2 
		85 "Liana_01_locator.rotateY" 2 86 "Liana_01_locator.rotateX" 2 
		87 "Liana_02_locator.rotateZ" 2 88 "Liana_02_locator.rotateY" 2 
		89 "Liana_02_locator.rotateX" 2 90 "Liana_03_locator.rotateZ" 2 
		91 "Liana_03_locator.rotateY" 2 92 "Liana_03_locator.rotateX" 2 
		93 "Liana_04_locator.rotateZ" 2 94 "Liana_04_locator.rotateY" 2 
		95 "Liana_04_locator.rotateX" 2 96 "Liana_4_locator.rotateZ" 2 
		97 "Liana_4_locator.rotateY" 2 98 "Liana_4_locator.rotateX" 2 99 "Liana_05_locator.rotateZ" 
		2 100 "Liana_05_locator.rotateY" 2 101 "Liana_05_locator.rotateX" 
		2 102 "Liana_06_locator.rotateZ" 2 103 "Liana_06_locator.rotateY" 
		2 104 "Liana_06_locator.rotateX" 2 105 "Liana1_01_locator.rotateZ" 
		2 106 "Liana1_01_locator.rotateY" 2 107 "Liana1_01_locator.rotateX" 
		2 108 "Liana1_02_locator.rotateZ" 2 109 "Liana1_02_locator.rotateY" 
		2 110 "Liana1_02_locator.rotateX" 2 111 "Liana1_03_locator.rotateZ" 
		2 112 "Liana1_03_locator.rotateY" 2 113 "Liana1_03_locator.rotateX" 
		2 114 "Liana1_04_locator.rotateZ" 2 115 "Liana1_04_locator.rotateY" 
		2 116 "Liana1_04_locator.rotateX" 2 117 "Liana1_08_locator.rotateZ" 
		2 118 "Liana1_08_locator.rotateY" 2 119 "Liana1_08_locator.rotateX" 
		2 120 "Liana1_05_locator.rotateZ" 2 121 "Liana1_05_locator.rotateY" 
		2 122 "Liana1_05_locator.rotateX" 2 123 "Liana1_06_locator.rotateZ" 
		2 124 "Liana1_06_locator.rotateY" 2 125 "Liana1_06_locator.rotateX" 
		2 126 "Liana2_2_locator.rotateZ" 2 127 "Liana2_2_locator.rotateY" 
		2 128 "Liana2_2_locator.rotateX" 2 129 "Liana2_3_locator.rotateZ" 
		2 130 "Liana2_3_locator.rotateY" 2 131 "Liana2_3_locator.rotateX" 
		2 132 "Liana2_4_locator.rotateZ" 2 133 "Liana2_4_locator.rotateY" 
		2 134 "Liana2_4_locator.rotateX" 2 135 "Liana2_5_locator.rotateZ" 
		2 136 "Liana2_5_locator.rotateY" 2 137 "Liana2_5_locator.rotateX" 
		2 138 "Liana2_6_locator.rotateZ" 2 139 "Liana2_6_locator.rotateY" 
		2 140 "Liana2_6_locator.rotateX" 2 141 "Liana2_7_locator.rotateZ" 
		2 142 "Liana2_7_locator.rotateY" 2 143 "Liana2_7_locator.rotateX" 
		2 144 "Liana3_2_locator.rotateZ" 2 145 "Liana3_2_locator.rotateY" 
		2 146 "Liana3_2_locator.rotateX" 2 147 "Liana3_3_locator.rotateZ" 
		2 148 "Liana3_3_locator.rotateY" 2 149 "Liana3_3_locator.rotateX" 
		2 150 "Liana3_4_locator.rotateZ" 2 151 "Liana3_4_locator.rotateY" 
		2 152 "Liana3_4_locator.rotateX" 2 153 "Liana3_6_locator.rotateZ" 
		2 154 "Liana3_6_locator.rotateY" 2 155 "Liana3_6_locator.rotateX" 
		2 156 "Liana3_5_locator.rotateZ" 2 157 "Liana3_5_locator.rotateY" 
		2 158 "Liana3_5_locator.rotateX" 2 159 "Liana3_7_locator.rotateZ" 
		2 160 "Liana3_7_locator.rotateY" 2 161 "Liana3_7_locator.rotateX" 
		2 162 "LiansL_IK_locator.translateZ" 1 43 "LiansL_IK_locator.translateY" 
		1 44 "LiansL_IK_locator.translateX" 1 45 "LiansR_IK_locator.translateZ" 
		1 46 "LiansR_IK_locator.translateY" 1 47 "LiansR_IK_locator.translateX" 
		1 48 "cluster52Handle.Twist" 0 12 "cluster52Handle.translateZ" 
		1 49 "cluster52Handle.translateY" 1 50 "cluster52Handle.translateX" 
		1 51 "cluster51Handle.translateZ" 1 52 "cluster51Handle.translateY" 
		1 53 "cluster51Handle.translateX" 1 54 "cluster50Handle.translateZ" 
		1 55 "cluster50Handle.translateY" 1 56 "cluster50Handle.translateX" 
		1 57 "cluster49Handle.translateZ" 1 58 "cluster49Handle.translateY" 
		1 59 "cluster49Handle.translateX" 1 60 "cluster48Handle.translateZ" 
		1 61 "cluster48Handle.translateY" 1 62 "cluster48Handle.translateX" 
		1 63 "cluster47Handle.translateZ" 1 64 "cluster47Handle.translateY" 
		1 65 "cluster47Handle.translateX" 1 66 "cluster46Handle.Twist" 
		0 13 "cluster46Handle.translateZ" 1 67 "cluster46Handle.translateY" 
		1 68 "cluster46Handle.translateX" 1 69 "cluster45Handle.translateZ" 
		1 70 "cluster45Handle.translateY" 1 71 "cluster45Handle.translateX" 
		1 72 "R_lock1_locator.rotateZ" 2 163 "R_lock1_locator.rotateY" 2 
		164 "R_lock1_locator.rotateX" 2 165 "C_lock1_locator.rotateZ" 2 166 "C_lock1_locator.rotateY" 
		2 167 "C_lock1_locator.rotateX" 2 168 "R1_lock1_locator.rotateZ" 
		2 169 "R1_lock1_locator.rotateY" 2 170 "R1_lock1_locator.rotateX" 
		2 171 "L_Lock1_locator.rotateZ" 2 172 "L_Lock1_locator.rotateY" 2 
		173 "L_Lock1_locator.rotateX" 2 174 "Flower_Head_locator.rotateZ" 2 
		175 "Flower_Head_locator.rotateY" 2 176 "Flower_Head_locator.rotateX" 
		2 177 "EarR_locator.rotateZ" 2 178 "EarR_locator.rotateY" 2 
		179 "EarR_locator.rotateX" 2 180 "EarL_locator.rotateZ" 2 181 "EarL_locator.rotateY" 
		2 182 "EarL_locator.rotateX" 2 183 "cluster44Handle.Twist" 0 
		14 "cluster44Handle.translateZ" 1 73 "cluster44Handle.translateY" 1 
		74 "cluster44Handle.translateX" 1 75 "cluster43Handle.translateZ" 1 
		76 "cluster43Handle.translateY" 1 77 "cluster43Handle.translateX" 1 
		78 "cluster42Handle.translateZ" 1 79 "cluster42Handle.translateY" 1 
		80 "cluster42Handle.translateX" 1 81 "cluster41Handle.translateZ" 1 
		82 "cluster41Handle.translateY" 1 83 "cluster41Handle.translateX" 1 
		84 "cluster40Handle.translateZ" 1 85 "cluster40Handle.translateY" 1 
		86 "cluster40Handle.translateX" 1 87 "cluster39Handle.Twist" 0 
		15 "cluster39Handle.translateZ" 1 88 "cluster39Handle.translateY" 1 
		89 "cluster39Handle.translateX" 1 90 "cluster38Handle.translateZ" 1 
		91 "cluster38Handle.translateY" 1 92 "cluster38Handle.translateX" 1 
		93 "cluster37Handle.translateZ" 1 94 "cluster37Handle.translateY" 1 
		95 "cluster37Handle.translateX" 1 96 "cluster36Handle.translateZ" 1 
		97 "cluster36Handle.translateY" 1 98 "cluster36Handle.translateX" 1 
		99 "cluster35Handle.translateZ" 1 100 "cluster35Handle.translateY" 1 
		101 "cluster35Handle.translateX" 1 102 "cluster34Handle.translateZ" 1 
		103 "cluster34Handle.translateY" 1 104 "cluster34Handle.translateX" 1 
		105 "cluster33Handle.translateZ" 1 106 "cluster33Handle.translateY" 1 
		107 "cluster33Handle.translateX" 1 108 "cluster32Handle.translateZ" 1 
		109 "cluster32Handle.translateY" 1 110 "cluster32Handle.translateX" 1 
		111 "cluster31Handle.translateZ" 1 112 "cluster31Handle.translateY" 1 
		113 "cluster31Handle.translateX" 1 114 "cluster30Handle.Twist" 0 
		16 "cluster30Handle.translateZ" 1 115 "cluster30Handle.translateY" 1 
		116 "cluster30Handle.translateX" 1 117 "cluster29Handle.Twist" 0 
		17 "cluster29Handle.translateZ" 1 118 "cluster29Handle.translateY" 1 
		119 "cluster29Handle.translateX" 1 120 "cluster28Handle.translateZ" 1 
		121 "cluster28Handle.translateY" 1 122 "cluster28Handle.translateX" 1 
		123 "cluster27Handle.translateZ" 1 124 "cluster27Handle.translateY" 1 
		125 "cluster27Handle.translateX" 1 126 "cluster26Handle.translateZ" 1 
		127 "cluster26Handle.translateY" 1 128 "cluster26Handle.translateX" 1 
		129 "cluster25Handle.translateZ" 1 130 "cluster25Handle.translateY" 1 
		131 "cluster25Handle.translateX" 1 132 "cluster24Handle.Twist" 0 
		18 "cluster24Handle.translateZ" 1 133 "cluster24Handle.translateY" 1 
		134 "cluster24Handle.translateX" 1 135 "cluster23Handle.translateZ" 1 
		136 "cluster23Handle.translateY" 1 137 "cluster23Handle.translateX" 1 
		138 "cluster22Handle.translateZ" 1 139 "cluster22Handle.translateY" 1 
		140 "cluster22Handle.translateX" 1 141 "cluster21Handle.translateZ" 1 
		142 "cluster21Handle.translateY" 1 143 "cluster21Handle.translateX" 1 
		144 "cluster12Handle.Twist" 0 19 "cluster12Handle.translateZ" 1 
		145 "cluster12Handle.translateY" 1 146 "cluster12Handle.translateX" 1 
		147 "cluster11Handle.translateZ" 1 148 "cluster11Handle.translateY" 1 
		149 "cluster11Handle.translateX" 1 150 "cluster10Handle.translateZ" 1 
		151 "cluster10Handle.translateY" 1 152 "cluster10Handle.translateX" 1 
		153 "cluster9Handle.translateZ" 1 154 "cluster9Handle.translateY" 1 
		155 "cluster9Handle.translateX" 1 156 "cluster8Handle.Twist" 0 20 "cluster8Handle.translateZ" 
		1 157 "cluster8Handle.translateY" 1 158 "cluster8Handle.translateX" 
		1 159 "cluster7Handle.translateZ" 1 160 "cluster7Handle.translateY" 
		1 161 "cluster7Handle.translateX" 1 162 "cluster6Handle.translateZ" 
		1 163 "cluster6Handle.translateY" 1 164 "cluster6Handle.translateX" 
		1 165 "cluster5Handle.translateZ" 1 166 "cluster5Handle.translateY" 
		1 167 "cluster5Handle.translateX" 1 168 "cluster4Handle.Twist" 0 
		21 "cluster4Handle.translateZ" 1 169 "cluster4Handle.translateY" 1 
		170 "cluster4Handle.translateX" 1 171 "cluster3Handle.translateZ" 1 
		172 "cluster3Handle.translateY" 1 173 "cluster3Handle.translateX" 1 
		174 "cluster2Handle.translateZ" 1 175 "cluster2Handle.translateY" 1 
		176 "cluster2Handle.translateX" 1 177 "cluster1Handle.translateZ" 1 
		178 "cluster1Handle.translateY" 1 179 "cluster1Handle.translateX" 1 
		180 "R1_lock1_locator1.rotateZ" 2 184 "R1_lock1_locator1.rotateY" 2 
		185 "R1_lock1_locator1.rotateX" 2 186 "C_lock2_locator.rotateZ" 2 
		187 "C_lock2_locator.rotateY" 2 188 "C_lock2_locator.rotateX" 2 189 "R_lock2_locator.rotateZ" 
		2 190 "R_lock2_locator.rotateY" 2 191 "R_lock2_locator.rotateX" 2 
		192 "L_Lock2_locator.rotateZ" 2 193 "L_Lock2_locator.rotateY" 2 194 "L_Lock2_locator.rotateX" 
		2 195 "EarL_locator1.rotateZ" 2 196 "EarL_locator1.rotateY" 2 
		197 "EarL_locator1.rotateX" 2 198 "EarR_locator1.rotateZ" 2 199 "EarR_locator1.rotateY" 
		2 200 "EarR_locator1.rotateX" 2 201 "Foliage5_locator.rotateZ" 2 
		202 "Foliage5_locator.rotateY" 2 203 "Foliage5_locator.rotateX" 2 
		204 "Flower_locator.rotateZ" 2 205 "Flower_locator.rotateY" 2 206 "Flower_locator.rotateX" 
		2 207 "R_Finger3_locator.Finger_2" 0 22 "R_Finger3_locator.Finger_1" 
		0 23 "R_Finger3_locator.rotateZ" 2 208 "R_Finger3_locator.rotateY" 
		2 209 "R_Finger3_locator.rotateX" 2 210 "R_Finger1_locator.Finger_2" 
		0 24 "R_Finger1_locator.Finger_1" 0 25 "R_Finger1_locator.rotateZ" 
		2 211 "R_Finger1_locator.rotateY" 2 212 "R_Finger1_locator.rotateX" 
		2 213 "R_Thumb_locator.Thumb_2" 0 26 "R_Thumb_locator.Thumb_1" 0 
		27 "R_Thumb_locator.rotateZ" 2 214 "R_Thumb_locator.rotateY" 2 215 "R_Thumb_locator.rotateX" 
		2 216 "R_Finger2_locator.Finger_2" 0 28 "R_Finger2_locator.Finger_1" 
		0 29 "R_Finger2_locator.rotateZ" 2 217 "R_Finger2_locator.rotateY" 
		2 218 "R_Finger2_locator.rotateX" 2 219 "Foliage4_locator.rotateZ" 
		2 220 "Foliage4_locator.rotateY" 2 221 "Foliage4_locator.rotateX" 
		2 222 "L_Finge3_locator.Finger_2" 0 30 "L_Finge3_locator.Finger_1" 
		0 31 "L_Finge3_locator.rotateZ" 2 223 "L_Finge3_locator.rotateY" 
		2 224 "L_Finge3_locator.rotateX" 2 225 "L_Finger3_locator.Finger_2" 
		0 32 "L_Finger3_locator.Finger_1" 0 33 "L_Finger3_locator.rotateZ" 
		2 226 "L_Finger3_locator.rotateY" 2 227 "L_Finger3_locator.rotateX" 
		2 228 "L_Finger2_locator.Finger_2" 0 34 "L_Finger2_locator.Finger_1" 
		0 35 "L_Finger2_locator.rotateZ" 2 229 "L_Finger2_locator.rotateY" 
		2 230 "L_Finger2_locator.rotateX" 2 231 "L_Thumb_locator.Thumb_2" 
		0 36 "L_Thumb_locator.Thumb_1" 0 37 "L_Thumb_locator.rotateZ" 2 
		232 "L_Thumb_locator.rotateY" 2 233 "L_Thumb_locator.rotateX" 2 234 "L_Clavicle_locator.rotateZ" 
		2 235 "L_Clavicle_locator.rotateY" 2 236 "L_Clavicle_locator.rotateX" 
		2 237 "R_Clavicle_locator.rotateZ" 2 238 "R_Clavicle_locator.rotateY" 
		2 239 "R_Clavicle_locator.rotateX" 2 240 "Foliage2_locator.rotateZ" 
		2 241 "Foliage2_locator.rotateY" 2 242 "Foliage2_locator.rotateX" 
		2 243 "Foliage1_locator.rotateZ" 2 244 "Foliage1_locator.rotateY" 
		2 245 "Foliage1_locator.rotateX" 2 246 "Global.Mark" 0 38 "Global.translateY" 
		1 181  ;
	setAttr ".cd[0].cim" -type "Int32Array" 465 0 1 2 3 4
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
		 317 318 319 320 321 322 323 324 325 326 327 328
		 329 330 331 332 333 334 335 336 337 338 339 340
		 341 342 343 344 345 346 347 348 349 350 351 352
		 353 354 355 356 357 358 359 360 361 362 363 364
		 365 366 367 368 369 370 371 372 373 374 375 376
		 377 378 379 380 381 382 383 384 385 386 387 388
		 389 390 391 392 393 394 395 396 397 398 399 400
		 401 402 403 404 405 406 407 408 409 410 411 412
		 413 414 415 416 417 418 419 420 421 422 423 424
		 425 426 427 428 429 430 431 432 433 434 435 436
		 437 438 439 440 441 442 443 444 445 446 447 448
		 449 450 451 452 453 454 455 456 457 458 459 460
		 461 462 463 464 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 464 ".ac";
	setAttr ".ac[0:462]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
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
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[464]" no;
	setAttr ".ss" 6;
	setAttr ".se" 75;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA1951";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -9.8990418096808135 75 -9.8990418096808135;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1952";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 4.3611497398181784 75 4.3611497398181784;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1953";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 2.255233912871252 75 2.255233912871252;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1954";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1955";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1956";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 11.849753893711128 75 11.849753893711128;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1957";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1958";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 52.171881391999825 75 52.171881391999825;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1959";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1960";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 0 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1961";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 0 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1962";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 6.8530139373108252 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1963";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 0 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1964";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 0 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1965";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 -1.9120853967665554 41 -12.301220958149282 
		75 -1.9120853967665554;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA1966";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1967";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1968";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1969";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1970";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1971";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1972";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1973";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1974";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1975";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1976";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1977";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1978";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1979";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1980";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1981";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1982";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1983";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1984";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1985";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1986";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1987";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1988";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1989";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1990";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1991";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1992";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1993";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1994";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA1995";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU297";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 88.813719211561661 6 37.491739985227781 
		8 -84.060317840737127 10 61.802150922139987 11 88.813719211561661 13 -23.208656798327937 
		14 -66.081417987298039 15 -84.060317840737127 17 61.802150922139987 19 2.3767006854122879 
		20 -57.048749551315446 22 2.3767006854122519 24 70.834819358122573 25 27.962058169152478 
		27 -84.060317840737127 28 -57.048749551315446 29 2.3767006854122519 31 61.802150922139987 
		33 -84.060317840737127 34 -57.048749551315446 36 88.813719211561661 38 -57.048749551315446 
		39 -84.060317840737127 40 -66.081417987298039 42 70.834819358122573 43 88.813719211561661 
		45 -57.048749551315446 47 2.3767006854122519 48 61.802150922139987 50 2.3767006854122879 
		52 -57.048749551315446 53 2.3767006854122519 54 61.802150922139987 56 27.962058169152478 
		57 -23.208656798327937 59 -57.048749551315446 61 88.813719211561661 62 61.802150922139987 
		64 -84.060317840737127 66 61.802150922139987 67 88.813719211561661 68 70.834819358122573 
		70 -66.081417987298039 71 -84.060317840737127 73 -19.232553480731909 75 88.813719211561661;
createNode animCurveTU -n "animCurveTU298";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 88.813719211561661 6 37.491739985227781 
		8 -84.060317840737127 10 61.802150922139987 11 88.813719211561661 13 -23.208656798327937 
		14 -66.081417987298039 15 -84.060317840737127 17 61.802150922139987 19 2.3767006854122879 
		20 -57.048749551315446 22 2.3767006854122519 24 70.834819358122573 25 27.962058169152478 
		27 -84.060317840737127 28 -57.048749551315446 29 2.3767006854122519 31 61.802150922139987 
		33 -84.060317840737127 34 -57.048749551315446 36 88.813719211561661 38 -57.048749551315446 
		39 -84.060317840737127 40 -66.081417987298039 42 70.834819358122573 43 88.813719211561661 
		45 -57.048749551315446 47 2.3767006854122519 48 61.802150922139987 50 2.3767006854122879 
		52 -57.048749551315446 53 2.3767006854122519 54 61.802150922139987 56 27.962058169152478 
		57 -23.208656798327937 59 -57.048749551315446 61 88.813719211561661 62 61.802150922139987 
		64 -84.060317840737127 66 61.802150922139987 67 88.813719211561661 68 70.834819358122573 
		70 -66.081417987298039 71 -84.060317840737127 73 -19.232553480731909 75 88.813719211561661;
createNode animCurveTA -n "animCurveTA1996";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 -1.8616855638872325e-015 6 0 8 0 10 0 
		11 0 13 0 14 0 15 0 17 0 19 0 20 0 22 0 24 0 25 0 27 0 28 0 29 0 31 0 33 0 34 0 36 
		0 38 0 39 -180 40 -180 42 180 43 180 45 180 47 -180 48 -180 50 -180 52 -180 53 -180 
		54 180 56 -180 57 -180 59 -180 61 180 62 -180 64 -180 66 -180 67 -180 68 180 70 -180 
		71 -180 73 0 75 0;
createNode animCurveTA -n "animCurveTA1997";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 83.357210555627788 6 79.256684161455127 
		8 67.520171222727313 10 56.285913715318202 11 52.567507882564115 13 41.240370937978817 
		14 37.356142718825737 15 33.5133150066033 17 22.511871758579353 19 11.894818665211101 
		20 8.3458847896720947 22 -2.6114178642764747 24 -13.923209368501535 25 -17.590304894370412 
		27 -28.473537062243491 28 -32.126374413757951 29 -35.824640533559034 31 -47.380937580427144 
		33 -59.390759006985228 34 -63.28929831901015 36 -74.835645126300108 38 -86.509390106076921 
		39 -89.495102402942038 40 -85.424265933431343 42 -73.296250060731609 43 -69.428477632526381 
		45 -58.144246017888641 47 -46.951902480022525 48 -43.158115372803444 50 -31.630423586700132 
		52 -20.73042581624145 53 -17.189601093551467 54 -13.660997535249512 56 -2.9434070360523963 
		57 0.73910146935944099 59 12.071949216338808 61 23.036220788615715 62 26.657982129678608 
		64 37.696891704455993 66 49.396754641643987 67 53.443930277965499 68 57.423382919282162 
		70 69.075101876663638 71 72.914740989608134 73 95.464109700786636 75 83.357210555627788;
createNode animCurveTA -n "animCurveTA1998";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 163.56807394983284 6 163.89412609708009 
		8 165.26274578713202 10 167.14998842635001 11 167.89074229239313 13 170.46726998660222 
		14 171.45035547157201 15 172.46626586670723 17 175.56971633682721 19 178.74577339278764 
		20 179.82516997872716 22 -176.85868179000246 24 -173.57749782875499 25 -172.5687677799051 
		27 -169.79392174628936 28 -168.94821314014825 29 -168.1413001586138 31 -165.96901918744811 
		33 -164.32392089793564 34 -163.93238840856702 36 -163.19692792940657 38 -163.10867732989195 
		39 16.769438863569121 40 16.565836930854694 42 15.490393732717536 43 15.002868471609306 
		45 13.1992395297186 47 10.889298271302362 48 10.000525372604725 50 7.0216353590542626 
		52 3.9063980459977961 53 2.8525552776372898 54 1.7895866108158256 56 -1.4682002514619397 
		57 -2.5803465840549316 59 -5.9015122010092922 61 -8.8642807028048907 62 -9.7686714722081529 
		64 -12.247367289381959 66 -14.35224016284128 67 -14.942935568919198 68 -15.451550415358676 
		70 -16.516078779401898 71 -16.725170683290276 73 163.07706574999145 75 163.56807394983284;
createNode animCurveTL -n "animCurveTL1423";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 0.013725900265284308 24 0.90786252239047549 
		40 2.2522843449585586 61 4.7023913116675429 75 6.6450780617976504;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  0.93689745664596558 0.4621683657169342 
		0.30911135673522949 0.25668784976005554 0.91743868589401245;
	setAttr -s 5 ".kiy[0:4]"  0.34960421919822693 0.88679218292236328 
		0.95102584362030029 0.96649438142776489 0.39787724614143372;
	setAttr -s 5 ".kox[0:4]"  0.93689751625061035 0.4621683657169342 
		0.30911135673522949 0.25668784976005554 0.91743868589401245;
	setAttr -s 5 ".koy[0:4]"  0.34960418939590454 0.88679218292236328 
		0.95102584362030029 0.96649438142776489 0.39787724614143372;
createNode animCurveTL -n "animCurveTL1424";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 0.058100552598793383 24 -0.24958616470789102 
		40 0.25789303082000414 61 0.54605237493938341 75 0.058100552598793383;
createNode animCurveTL -n "animCurveTL1425";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 -0.46312997091817443 24 -1.0627217077376478 
		40 0.46426888783705539 61 0.48704498295227783 75 -0.46312997091817443;
createNode animCurveTU -n "animCurveTU299";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 -81.249274014770705 6 -13.502399975692173 
		8 146.95072072464399 10 -45.593024836737186 11 -81.249274014770705 13 66.624322576369963 
		14 123.21792127174477 15 146.95072072464399 17 -45.593024836737186 19 32.850723354936648 
		20 111.29447154661044 22 32.850723354936598 24 -57.516474561871561 25 -0.92287586649673825 
		27 146.95072072464399 28 111.29447154661044 29 32.850723354936598 31 -45.593024836737186 
		33 146.95072072464399 34 111.29447154661044 36 -81.249274014770705 38 111.06111687625723 
		39 146.95072072464399 40 88.725019475074873 42 -61.616376386093329 43 -19.806157946602259 
		45 130.46379094133954 47 32.705524863342816 48 -45.647474271084882 50 32.850723354936648 
		52 111.29447154661044 53 32.850723354936598 54 -45.593024836737186 56 -1.1943147959388727 
		57 66.217164182206858 59 112.3285192650179 61 -76.16157413341648 62 -40.94580870765683 
		64 146.95072072464399 66 -45.712168862862846 67 -81.249274014770705 68 -57.516474561871561 
		70 123.21792127174477 71 146.95072072464399 73 61.375723231421091 75 -81.249274014770705;
createNode animCurveTU -n "animCurveTU300";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 -81.249274014770705 6 -13.502399975692173 
		8 146.95072072464399 10 -45.593024836737186 11 -81.249274014770705 13 66.624322576369963 
		14 123.21792127174477 15 146.95072072464399 17 -42.727790136185483 19 34.888227351546114 
		20 111.29447154661044 22 13.596351202057731 24 -57.516474561871561 25 -0.92287586649673825 
		27 146.95072072464399 28 111.29447154661044 29 32.850723354936598 31 -45.593024836737186 
		33 146.95072072464399 34 111.29447154661044 36 -81.249274014770705 38 97.431327652037552 
		39 146.95072072464399 40 112.94892614676144 42 121.02526797643411 43 146.95072072464399 
		45 165.14763538809063 47 18.588225819953596 48 -50.941461412355778 50 32.850723354936648 
		52 111.29447154661044 53 32.850723354936598 54 -45.593024836737186 56 -0.92287586649673825 
		57 66.624322576369963 59 32.850723354936598 61 146.95072072464399 62 173.69289278807065 
		64 146.95072072464399 66 -50.941464116022431 67 -81.249274014770705 68 -57.516474561871561 
		70 123.21792127174477 71 146.95072072464399 73 61.375723231421091 75 -81.249274014770705;
createNode animCurveTA -n "animCurveTA1999";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 0 6 0 8 -180 10 -180 11 -180 13 -180 
		14 -180 15 180 17 -180 19 0 20 0 22 0 24 0 25 0 27 0 28 0 29 0 31 0 33 0 34 0 36 
		0 38 0 39 0 40 0 42 0 43 0 45 0 47 0 48 0 50 0 52 0 53 0 54 0 56 0 57 0 59 0 61 0 
		62 0 64 0 66 0 67 0 68 0 70 0 71 0 73 0 75 0;
createNode animCurveTA -n "animCurveTA2000";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 204.62730539856361 6 208.40241278299774 
		8 -39.283373882686682 10 -49.896600237349901 11 -53.469547849462387 13 -64.577574446400433 
		14 -68.470685101163468 15 -72.366056551361837 17 -83.752845944278718 19 -84.967607058467536 
		20 -81.14816795078336 22 -69.266699757627748 24 -56.985983550506127 25 -53.02953753293707 
		27 -41.429935030089936 28 -37.5976382016702 29 -33.754010472893604 31 -21.996731704593362 
		33 -10.186950590776618 34 -6.4358356795207197 36 4.4789719512516122 38 15.303757787380382 
		39 18.982600143849712 40 22.726273008432884 42 33.909496685123997 43 37.502928136731846 
		45 48.123176099041459 47 58.932319325957309 48 62.671691780485205 50 74.290539800956921 
		52 85.627448434065471 53 89.376210247055852 54 93.139539500585329 56 104.69816874577243 
		57 108.69760178476777 59 121.01024933758107 61 132.80552514220491 62 136.65284923400506 
		64 148.17722558441253 66 160.01397830625766 67 164.01552511696946 68 167.90552320012583 
		70 179.06651959990322 71 182.68062731908211 73 193.48335183981689 75 204.62730539856361;
createNode animCurveTA -n "animCurveTA2001";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 2.566059288965084 6 1.3970657929252781 
		8 178.00861258986217 10 174.78419366970638 11 173.73956584913688 13 170.69069145585087 
		14 169.70888132003043 15 168.7788051020639 17 166.39421142914711 19 -15.422832350774051 
		20 -15.906098118879678 22 -16.963326826472649 24 -17.329058990053905 25 -17.28769893283739 
		27 -16.720479469393709 28 -16.388316149593905 29 -15.98410394819456 31 -14.317654163182674 
		33 -12.029051218684419 34 -11.184172939524888 36 -8.4431020473630554 38 -5.3842524770887534 
		39 -4.2874992993543737 40 -3.1500922194166243 42 0.3195446791705166 43 1.4389349307578452 
		45 4.6882124748868756 47 7.8016147147005306 48 8.8108821216375137 50 11.660189832174858 
		52 13.946941983932183 53 14.583006550616819 54 15.15810783664103 56 16.511643634667312 
		57 16.830840101977518 59 17.320376319841422 61 17.085198498668856 62 16.859849461102097 
		64 15.754449359212236 66 13.969897383677303 67 13.225671505043264 68 12.437772171352817 
		70 9.8518378786595058 71 8.9212421581127934 73 5.9176840907313935 75 2.566059288965084;
createNode animCurveTL -n "animCurveTL1426";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  5 -0.9637966704735671 40 2.3798931101717917 
		61 4.8532777796546496 75 5.6673780617976499;
	setAttr -s 4 ".kit[0:3]"  1 9 9 1;
	setAttr -s 4 ".kot[0:3]"  1 9 9 1;
	setAttr -s 4 ".kix[0:3]"  0.79504507780075073 0.30554816126823425 
		0.33444541692733765 0.75855761766433716;
	setAttr -s 4 ".kiy[0:3]"  -0.60655033588409424 0.95217663049697876 
		0.94241511821746826 -0.65160596370697021;
	setAttr -s 4 ".kox[0:3]"  0.79504507780075073 0.30554816126823425 
		0.33444541692733765 0.75855761766433716;
	setAttr -s 4 ".koy[0:3]"  -0.60655033588409424 0.95217663049697876 
		0.94241511821746826 -0.65160596370697021;
createNode animCurveTL -n "animCurveTL1427";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 -0.40632599795206492 6 -0.40860609427474137 
		8 -0.40752430477168888 10 -0.39500382623886887 11 -0.38838716442594989 13 -0.36150395785704659 
		14 -0.35026904392150082 15 -0.33794536232763839 17 -0.29516159723395052 19 -0.24524714840551121 
		20 -0.22737737946020264 22 -0.17113214575836122 24 -0.11254071986202974 25 -0.092869990129410329 
		27 -0.034637591781144117 28 -0.015772739046768791 29 0.0026761321144406214 31 0.054668806867052 
		33 0.099918195088711137 34 0.11322003869774377 36 0.14714016080403081 38 0.17112229012603386 
		39 0.17669458379136915 40 0.18097982180659256 42 0.18583026175282624 43 0.18481390112911278 
		45 0.17416019001564487 47 0.15254396364259915 48 0.14300120226092727 50 0.10769610468273405 
		52 0.063582071813193641 53 0.047267585130731593 54 0.030274257146670536 56 -0.024022395245441475 
		57 -0.042974709065790151 59 -0.10132392702069126 61 -0.16017334551508655 62 -0.17950128647344599 
		64 -0.23541824469756911 66 -0.28643300238577196 67 -0.30195259760769455 68 -0.31661938152784264 
		70 -0.35504570156288395 71 -0.36584410246467769 73 -0.39156826798875732 75 -0.40632599795206492;
createNode animCurveTL -n "animCurveTL1428";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 1.0203515878616467 6 0.99679382485437074 
		8 0.90851165200961648 10 0.79740074821674745 11 0.75608730557628656 13 0.62170728333927716 
		14 0.57400304691867221 15 0.5251417636474166 17 0.37387133631557273 19 0.22039076402663144 
		20 0.16981047911650277 22 0.023022489456102579 24 -0.11166005754965941 25 -0.15300244967011206 
		27 -0.26421459072164527 28 -0.29650068620047315 29 -0.32613800269283738 31 -0.39761845894866543 
		33 -0.44009027863158623 34 -0.44756945391239811 36 -0.45013238138643963 38 -0.42313307233505182 
		39 -0.40761939698327476 40 -0.38886858316353778 42 -0.31372575531595231 43 -0.282866519363623 
		45 -0.17524035272105254 47 -0.048626092430641144 48 -0.0029983391964332751 50 0.14172212715729909 
		52 0.29379124317278577 53 0.34504859547999217 54 0.39620725371374527 56 0.54679595862083741 
		57 0.59526473520540302 59 0.73234309595445779 61 0.85322422053790736 62 0.88919495639915136 
		64 0.98198389987197732 66 1.0488564264847069 67 1.064688458109206 68 1.0771704632876657 
		70 1.0946348825246015 71 1.0938354522197304 73 1.0717408917553102 75 1.0203515878616467;
createNode animCurveTU -n "animCurveTU301";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 85.987010599621669 6 58.975444782844029 
		8 -86.887010627755018 10 58.975444782844093 11 85.987010599621669 13 -26.035355155718452 
		14 -68.908112420107926 15 -86.887010627755018 17 58.975444782844093 19 -0.45000001406670581 
		20 -59.87544481097747 22 -0.45000001406668971 24 68.008112391974478 25 25.135355127585047 
		27 -86.887010627755018 28 -59.875444810977392 29 -0.45000001406668971 31 58.975444782844029 
		33 -86.887010627755018 34 -59.875444810977392 36 85.987010599621669 38 -52.92961659138242 
		39 -86.887010627755018 40 -77.648770140626041 42 55.013753352189205 43 85.987010599621669 
		45 -62.5766009118841 47 -0.45000001406668971 48 58.975444782844093 50 -0.45000001406670581 
		52 -59.875444810977392 53 -0.45000001406668971 54 58.975444782844093 56 25.135355127585047 
		57 -26.035355155718452 59 -59.875444810977392 61 85.987010599621669 62 58.975444782844029 
		64 -86.887010627755018 66 58.975444782844093 67 85.987010599621669 68 68.008112391974478 
		70 -68.908112420107926 71 -86.887010627755018 73 -0.45000001406668971 75 85.987010599621669;
	setAttr -s 46 ".kit[0:45]"  3 9 3 9 3 9 9 3 
		9 9 9 9 9 9 3 9 9 9 3 9 3 9 3 9 9 
		3 9 9 9 9 9 9 9 9 9 9 3 9 3 9 3 9 
		9 3 9 3;
	setAttr -s 46 ".kot[0:45]"  3 9 3 9 3 9 9 3 
		9 9 9 9 9 9 3 9 9 9 3 9 3 9 3 9 9 
		3 9 9 9 9 9 9 9 9 9 9 3 9 3 9 3 9 
		9 3 9 3;
createNode animCurveTU -n "animCurveTU302";
	setAttr ".tan" 9;
	setAttr -s 46 ".ktv[0:45]"  5 85.987010599621669 6 58.975444782844029 
		8 -86.887010627755018 10 58.975444782844093 11 85.987010599621669 13 -26.035355155718452 
		14 -68.908112420107926 15 -86.887010627755018 17 58.975444782844093 19 -0.45000001406670581 
		20 -59.87544481097747 22 -0.45000001406668971 24 68.008112391974478 25 25.135355127585047 
		27 -86.887010627755018 28 -59.875444810977392 29 -0.45000001406668971 31 58.975444782844029 
		33 -86.887010627755018 34 -59.875444810977392 36 85.987010599621669 38 -52.92961659138242 
		39 -86.887010627755018 40 -77.648770140626041 42 55.013753352189205 43 85.987010599621669 
		45 -62.5766009118841 47 -0.45000001406668971 48 58.975444782844093 50 -0.45000001406670581 
		52 -59.875444810977392 53 -0.45000001406668971 54 58.975444782844093 56 25.135355127585047 
		57 -26.035355155718452 59 -59.875444810977392 61 85.987010599621669 62 58.975444782844029 
		64 -86.887010627755018 66 58.975444782844093 67 85.987010599621669 68 68.008112391974478 
		70 -68.908112420107926 71 -86.887010627755018 73 -0.45000001406668971 75 85.987010599621669;
	setAttr -s 46 ".kit[0:45]"  3 9 3 9 3 9 9 3 
		9 9 9 9 9 9 3 9 9 9 3 9 3 9 3 9 9 
		3 9 9 9 9 9 9 9 9 9 9 3 9 3 9 3 9 
		9 3 9 3;
	setAttr -s 46 ".kot[0:45]"  3 9 3 9 3 9 9 3 
		9 9 9 9 9 9 3 9 9 9 3 9 3 9 3 9 9 
		3 9 9 9 9 9 9 9 9 9 9 3 9 3 9 3 9 
		9 3 9 3;
createNode animCurveTA -n "animCurveTA2002";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 -1.7404386282316208e-016 6 0 8 0 10 0 
		11 0 13 0 14 0 15 0 17 0 19 0 20 0 22 0 24 0 25 0 27 0 28 0 29 -180 31 180 33 -180 
		34 -180 36 -180 38 -180 39 180 40 -180 42 -180 43 -180 45 -180 47 -180 48 -180 50 
		-180 52 -180 53 180 54 -180 56 -180 57 -180 59 0 61 0 62 0 64 0 66 0 67 0 68 0 70 
		0 71 0 73 0 75 0;
	setAttr -s 46 ".kit[16:45]"  3 9 3 3 3 3 9 3 
		3 3 3 3 3 3 3 9 3 3 3 9 9 9 9 9 9 
		9 9 9 9 9;
	setAttr -s 46 ".kot[16:45]"  3 9 3 3 3 3 9 3 
		3 3 3 3 3 3 3 9 3 3 3 9 9 9 9 9 9 
		9 9 9 9 9;
createNode animCurveTA -n "animCurveTA2003";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 27.605341343377447 6 23.650344165180027 
		8 12.241403784322344 10 1.1597727751053966 11 -2.5482167699285254 13 -13.97140898539033 
		14 -17.931516306728383 15 -21.86928644863157 17 -33.235614457241063 19 -44.293656757748998 
		20 -47.998605669827867 22 -59.427222962513717 24 -71.150379727961791 25 -74.923146342813666 
		27 -86.016639114760508 28 -89.701937620256061 29 -86.58736092322917 31 -75.123103412132963 
		33 -63.398555898244915 34 -59.626390028241616 36 -48.52007433199676 38 -37.335825611092936 
		39 -33.504656952749606 40 -29.594448250686032 42 -17.87488562799744 43 -14.106993965173654 
		45 -3.0051991103698921 47 8.1875313098242284 48 12.024051243928779 50 23.805430816416653 
		52 35.086590527692834 53 38.771839154041089 54 42.450672385826209 56 53.637961212367458 
		57 57.477499620285535 59 110.76003915646382 61 99.505242500039927 62 95.822407789947917 
		64 84.716676709772827 66 73.142708131110822 67 69.182531866850042 68 65.30777956122995 
		70 54.051108155381655 71 50.36277251597172 73 39.226637888561903 75 27.605341343377447;
createNode animCurveTA -n "animCurveTA2004";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 46 ".ktv[0:45]"  5 2.9601131537732388 6 2.9524096098040862 
		8 2.8519426936585024 10 2.6465216096083708 11 2.5552736925225386 13 2.2088106591616423 
		14 2.067444804264376 15 1.9170676079379454 17 1.4347943524573596 19 0.91121775846984543 
		20 0.72718270047342537 22 0.14369870027420953 24 -0.46056376005199917 25 -0.65212628161132513 
		27 -1.1958804332228374 28 -1.36754927316089 29 178.46533636301459 31 177.99274744266205 
		33 177.59256578217264 34 177.48450193854532 36 177.23115596185775 38 177.08076423459792 
		39 177.05454242340093 40 177.04133184681297 42 177.08403122444443 43 177.12377189437754 
		45 177.31217163072253 47 177.60387096453536 48 177.72550774881978 50 178.16024350036332 
		52 178.649626288642 53 178.82182960280696 54 178.99861371808572 56 179.55854070243953 
		57 179.75570354181849 59 0.36274407966411221 61 0.92959093261120285 62 1.1083109852968183 
		64 1.6165062365745877 66 2.081240530277531 67 2.2216383761753469 68 2.3487300695503674 
		70 2.6551300940187481 71 2.7337741941763172 73 2.90148389345701 75 2.9601131537732388;
	setAttr -s 46 ".kit[15:45]"  3 3 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9;
	setAttr -s 46 ".kot[15:45]"  3 3 9 9 9 9 9 9 
		9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 9 
		9 9 9 9 9 9;
createNode animCurveTL -n "animCurveTL1429";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 -0.61037919723816003 24 1.5085618801490619 
		47 2.6404796550629199 61 4.2527391747563241 75 6.0213780617976509;
	setAttr -s 5 ".kit[2:4]"  10 9 1;
	setAttr -s 5 ".kot[2:4]"  10 9 1;
	setAttr -s 5 ".kix[4]"  0.36789241433143616;
	setAttr -s 5 ".kiy[4]"  0.92986834049224854;
	setAttr -s 5 ".kox[4]"  0.36789250373840332;
	setAttr -s 5 ".koy[4]"  0.92986834049224854;
createNode animCurveTL -n "animCurveTL1430";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 0.90157131781952105 24 0.74061255252437874 
		47 0.99859413243201067 61 1.0572248489791434 75 0.90157131781952493;
createNode animCurveTL -n "animCurveTL1431";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  5 0.4499152846001821 24 0.77512021415758203 
		47 -0.51194431528520989 61 0.45566661796446967 75 0.4499152846001821;
createNode animCurveTA -n "animCurveTA2005";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 22 0 41 0 62 0 75 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2006";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 22 0 41 0 62 0 75 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2007";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 39.486026745984788 22 41.263858804786601 
		41 36.566668209784879 62 41.310327810052918 75 39.486026745984788;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA2008";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -4.5510191082802542 41 2.897101910828026 
		75 -4.5510191082802542;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2009";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 0 75 0;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2010";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 37.849697412531377 19 39.62752947133319 
		41 34.930338876331469 59 39.673998476599515 75 37.849697412531377;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTU -n "animCurveTU303";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 23 0 41 0 62 0 75 0;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTL -n "animCurveTL1432";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.62780348808471875 75 7.2609056792536535;
createNode animCurveTL -n "animCurveTL1433";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.025594732497964401 23 0.10255882680680495 
		41 0.025594732497964401 62 0.11471105222399025 75 0.025594732497964401;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTL -n "animCurveTL1434";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  7 0.037326905884083786 23 0.065815281873751269 
		41 0.098670522108498138 62 0.065815281873751269 77 0.037326905884083786;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTU -n "animCurveTU304";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 30 0 47 0 75 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 10;
	setAttr -s 4 ".kot[0:3]"  2 10 10 10;
createNode animCurveTU -n "animCurveTU305";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -17.1 30 -17.1 47 -17.1 75 -17.1;
	setAttr -s 4 ".kit[0:3]"  2 10 10 10;
	setAttr -s 4 ".kot[0:3]"  2 10 10 10;
createNode animCurveTL -n "animCurveTL1435";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 6.6331021911689341;
createNode animCurveTL -n "animCurveTL1436";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0.1956231580988268 30 0.1956231580988268 
		47 0.1956231580988268 75 0.1956231580988268;
	setAttr -s 4 ".kit[0:3]"  2 10 10 10;
	setAttr -s 4 ".kot[0:3]"  2 10 10 10;
createNode animCurveTL -n "animCurveTL1437";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 -0.07064701299733929 30 0.068284062362892306 
		47 0.086267214427350122 75 -0.07064701299733929;
	setAttr -s 4 ".kit[1:3]"  9 10 3;
	setAttr -s 4 ".kot[1:3]"  9 10 3;
createNode animCurveTL -n "animCurveTL1438";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.20663381060377561 75 6.8397360017727102;
createNode animCurveTL -n "animCurveTL1439";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0.027620072214915803 47 0.093548104429469259 
		75 0.027620072214915803;
	setAttr -s 3 ".kit[0:2]"  2 10 10;
	setAttr -s 3 ".kot[0:2]"  2 10 10;
createNode animCurveTL -n "animCurveTL1440";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -0.22397890675237225 20 -0.14164996924797427 
		47 -0.13845628725170872 75 -0.22397890675237225;
	setAttr -s 4 ".kit[0:3]"  2 10 10 1;
	setAttr -s 4 ".kot[0:3]"  2 10 10 1;
	setAttr -s 4 ".kix[3]"  0.43445673584938049;
	setAttr -s 4 ".kiy[3]"  0.055785030126571655;
	setAttr -s 4 ".kox[3]"  0.37807145714759827;
	setAttr -s 4 ".koy[3]"  0.057805407792329788;
createNode animCurveTL -n "animCurveTL1441";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.15485543404848087 75 6.7879576252174143;
createNode animCurveTL -n "animCurveTL1442";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0.03184367882336181 41 0.15756219174424557 
		75 0.03184367882336181;
	setAttr -s 3 ".kit[0:2]"  2 10 10;
	setAttr -s 3 ".kot[0:2]"  2 10 10;
createNode animCurveTL -n "animCurveTL1443";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  7 0.12679816594525539 41 0.2420530621772076 
		77 0.12679816594525539;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1444";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 -0.076440821788187896 75 6.5566613693807456;
createNode animCurveTL -n "animCurveTL1445";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.19236900548799163 75 0.19236900548799163;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL1446";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 -0.0059267714287712936 33 0.058991322867921581 
		55 0.024726170731391252 75 -0.0059267714287712936;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.28835669159889221 0.66666668653488159;
	setAttr -s 4 ".kiy[2:3]"  -0.021152138710021973 0;
	setAttr -s 4 ".kox[2:3]"  0.31719234585762024 0.66666668653488159;
	setAttr -s 4 ".koy[2:3]"  -0.023267358541488647 0;
createNode animCurveTL -n "animCurveTL1447";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.086792070123406395 75 6.7198942612923407;
createNode animCurveTL -n "animCurveTL1448";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0.23334284039033726 41 0.23334284039033726 
		75 0.23334284039033726;
	setAttr -s 3 ".kit[0:2]"  2 10 10;
	setAttr -s 3 ".kot[0:2]"  2 10 10;
createNode animCurveTL -n "animCurveTL1449";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -0.035514283071923516 41 0.088070460083953611 
		75 -0.035514283071923516;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "animCurveTU306";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 9.7000000000000028 23 9.7000000000000028 
		41 9.7000000000000028 55 9.7000000000000028 75 9.7000000000000028;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTA -n "animCurveTA2011";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.14345027747839903 23 4.0170418644440984 
		41 -13.1637879666381 55 -10.523348273538501 75 1.2605042741701009;
	setAttr -s 5 ".kit[0:4]"  1 10 10 9 10;
	setAttr -s 5 ".kot[0:4]"  1 10 10 9 10;
	setAttr -s 5 ".kix[0:4]"  0.91469728946685791 0.59999996423721313 
		0.59999996423721313 0.46666672825813293 0.66666668653488159;
	setAttr -s 5 ".kiy[0:4]"  0.085231557488441467 -0.11612755805253983 
		0 0.10366234928369522 0.20566701889038086;
	setAttr -s 5 ".kox[0:4]"  0.51468366384506226 0.60000002384185791 
		0.46666666865348816 0.66666662693023682 0.66666668653488159;
	setAttr -s 5 ".koy[0:4]"  0.10595674067735672 -0.11612756550312042 
		0 0.14808903634548187 0.20566701889038086;
createNode animCurveTA -n "animCurveTA2012";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.41169017415957476 23 -0.94765938384855353 
		41 -0.079459978176737833 55 -1.371440810200236 75 -0.36903586371297309;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA2013";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 87.815281327692858 23 98.853195064873248 
		41 89.943919962604312 55 82.915786264814059 75 87.807413547702822;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.96988850831985474 0.59999996423721313 
		0.60000002384185791 0.46666672825813293 0.50806885957717896;
	setAttr -s 5 ".kiy[0:4]"  0.090638495981693268 0.018575876951217651 
		-0.15646515786647797 -0.01535432506352663 0.16987833380699158;
	setAttr -s 5 ".kox[0:4]"  0.80321401357650757 0.60000002384185791 
		0.46666663885116577 0.66666662693023682 0.50510185956954956;
	setAttr -s 5 ".koy[0:4]"  0.27569255232810974 0.018575876951217651 
		-0.12169510871171951 -0.021934745833277702 0.17838451266288757;
createNode animCurveTL -n "animCurveTL1450";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 -0.33313572274360931 75 6.2999664684253247;
createNode animCurveTL -n "animCurveTL1451";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0.4174466225770227 23 0.38935638807570128 
		41 0.37379933258364589 55 0.40114888194377468 75 0.4174466225770227;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTL -n "animCurveTL1452";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  5 0.019068847352743411 23 -0.0033772573935193853 
		41 0.040607908204199086 55 0.069318559103574914 75 0.019068847352743411;
	setAttr -s 5 ".kit[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kot[0:4]"  1 3 9 3 1;
	setAttr -s 5 ".kix[0:4]"  0.5400460958480835 0.59999996423721313 
		0.60000002384185791 0.46666666865348816 0.61163604259490967;
	setAttr -s 5 ".kiy[0:4]"  -0.041598204523324966 0 0.040891397744417191 
		0 -0.042201079428195953;
	setAttr -s 5 ".kox[0:4]"  0.54004603624343872 0.59999996423721313 
		0.46666663885116577 0.66666668653488159 0.61163604259490967;
	setAttr -s 5 ".koy[0:4]"  -0.041598208248615265 0 0.031804416328668594 
		0 -0.042201075702905655;
createNode animCurveTU -n "animCurveTU307";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 12.400000000000002 23 12.400000000000002 
		41 12.400000000000002 55 12.400000000000002 75 12.400000000000002;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTA -n "animCurveTA2014";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -9.6501004808312416 23 -9.6501004808312469 
		41 -15.916936765958301 55 -9.6501004808312416 75 -9.6501004808312416;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTA -n "animCurveTA2015";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -23.349574682323034 23 -23.34957468232302 
		41 -23.34957468232302 55 -23.349574682323034 75 -23.349574682323034;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTA -n "animCurveTA2016";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 110.92835018862139 23 123.02041662255118 
		41 106.38585113343923 55 99.386933805092923 75 110.92835018862139;
	setAttr -s 5 ".kit[0:4]"  1 10 10 9 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 9 1;
	setAttr -s 5 ".kix[0:4]"  0.47914654016494751 0.59999996423721313 
		0.60000002384185791 0.46666672825813293 0.55794179439544678;
	setAttr -s 5 ".kiy[0:4]"  0.15547128021717072 -0.039640780538320541 
		-0.23202118277549744 0.03264535591006279 0.15708816051483154;
	setAttr -s 5 ".kox[0:4]"  0.47914651036262512 0.60000002384185791 
		0.46666663885116577 0.66666662693023682 0.55794179439544678;
	setAttr -s 5 ".koy[0:4]"  0.15547126531600952 -0.03964078426361084 
		-0.18046090006828308 0.046636208891868591 0.15708817541599274;
createNode animCurveTL -n "animCurveTL1453";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 -0.33730781672450594 75 6.2957943744444265;
createNode animCurveTL -n "animCurveTL1454";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  5 0.60077889205439194 23 0.62273261457311002 
		41 0.60203832202181207 55 0.5789252258210944 75 0.60077889205439194;
	setAttr -s 5 ".kit[1:4]"  10 9 1 1;
	setAttr -s 5 ".kot[1:4]"  10 9 1 1;
	setAttr -s 5 ".kix[0:4]"  0.41283199191093445 0.59999996423721313 
		0.60000002384185791 0.46555119752883911 0.50002372264862061;
	setAttr -s 5 ".kiy[0:4]"  0.015411100350320339 0 -0.024641657248139381 
		-0.019813407212495804 0.015607050620019436;
	setAttr -s 5 ".kox[0:4]"  0.41283205151557922 0.59999996423721313 
		0.46666663885116577 0.34485268592834473 0.50002366304397583;
	setAttr -s 5 ".koy[0:4]"  0.015411103144288063 0 -0.019165731966495514 
		-0.014676599763333797 0.015607048757374287;
createNode animCurveTL -n "animCurveTL1455";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 -0.056576479348580511 23 -0.042365525870275797 
		41 -0.028764960397832301 55 -0.045084449671817219 75 -0.056576479348580511;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2017";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -28.42668290016633 20 -4.7510161864714684 
		50 -50.842637481330264 59 -47.927155822677157 75 -28.42668290016633;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 1;
	setAttr -s 5 ".kix[4]"  0.61119329929351807;
	setAttr -s 5 ".kiy[4]"  0.51092958450317383;
	setAttr -s 5 ".kox[4]"  0.58835005760192871;
	setAttr -s 5 ".koy[4]"  0.50881779193878174;
createNode animCurveTA -n "animCurveTA2018";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 42.175573880105709 20 50.889554309942255 
		50 53.750071172229092 59 48.31613659901361 75 42.175573880105709;
	setAttr -s 5 ".kit[0:4]"  3 9 9 10 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 10 3;
createNode animCurveTA -n "animCurveTA2019";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -4.1794693758466543 20 4.0295347920613986 
		50 -25.109869138128619 59 -19.909056126079683 75 -4.1794693758466543;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTL -n "animCurveTL1456";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 -0.040650706860034275 75 6.5924514843089002;
createNode animCurveTL -n "animCurveTL1457";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  5 -0.096491022397273252 20 -0.11312049053386961 
		33 -0.11179705438054784 50 -0.08298073669510582 59 -0.084429297016261048 75 -0.096491022397273252;
	setAttr -s 6 ".kit[0:5]"  2 1 1 10 9 1;
	setAttr -s 6 ".kot[0:5]"  2 1 1 10 9 1;
	setAttr -s 6 ".kix[1:5]"  0.35996735095977783 0.25959545373916626 
		0.56666666269302368 0.30000004172325134 0.46517360210418701;
	setAttr -s 6 ".kiy[1:5]"  -0.0054206550121307373 0.0074002314358949661 
		0 -0.0048637036234140396 -0.011124227195978165;
	setAttr -s 6 ".kox[1:5]"  0.35996738076210022 0.25959554314613342 
		0.29999998211860657 0.53333330154418945 0.45496198534965515;
	setAttr -s 6 ".koy[1:5]"  -0.0054206559434533119 0.0074002319015562534 
		0 -0.0086465822532773018 -0.011224649846553802;
createNode animCurveTL -n "animCurveTL1458";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 -0.32491266308786626 50 -0.2093009394690532 
		59 -0.24497896592091273 75 -0.32491266308786626;
	setAttr -s 4 ".kit[2:3]"  9 3;
	setAttr -s 4 ".kot[2:3]"  9 3;
createNode animCurveTA -n "animCurveTA2020";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  5 44.198201992424075 20 24.567661352639437 
		33 8.3397835234772764 59 41.0662309179896 75 44.198201992424075;
	setAttr -s 5 ".kit[1:4]"  9 10 1 3;
	setAttr -s 5 ".kot[1:4]"  9 10 1 3;
	setAttr -s 5 ".kix[3:4]"  1.0593267679214478 0.53333330154418945;
	setAttr -s 5 ".kiy[3:4]"  0.20857976377010345 0;
	setAttr -s 5 ".kox[3:4]"  0.79260963201522827 0.53333330154418945;
	setAttr -s 5 ".koy[3:4]"  0.15606360137462616 0;
createNode animCurveTA -n "animCurveTA2021";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -64.049139665329676 20 -57.544517204614202 
		33 -49.131738423600737 59 -45.170393740976252 75 -64.049139665329676;
	setAttr -s 5 ".kit[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 1 10 3;
	setAttr -s 5 ".kix[2:4]"  0.83587843179702759 0.86666673421859741 
		0.53333330154418945;
	setAttr -s 5 ".kiy[2:4]"  0.19406697154045105 -0.16117386519908905 
		0;
	setAttr -s 5 ".kox[2:4]"  0.73588526248931885 0.53333330154418945 
		0.53333330154418945;
	setAttr -s 5 ".koy[2:4]"  0.17085142433643341 -0.099183902144432068 
		0;
createNode animCurveTA -n "animCurveTA2022";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -52.828725932699903 20 -28.848970284017348 
		33 -21.16063293641783 59 -66.280970303269896 75 -52.828725932699903;
	setAttr -s 5 ".kit[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 10 10 1;
	setAttr -s 5 ".kix[0:4]"  0.70470136404037476 0.5 0.43333336710929871 
		0.86666673421859741 0.26065310835838318;
	setAttr -s 5 ".kiy[0:4]"  0.29566943645477295 0.29609599709510803 
		-0.21777056157588959 -0.34215536713600159 0.34035393595695496;
	setAttr -s 5 ".kox[0:4]"  0.63790637254714966 0.43333330750465393 
		0.86666661500930786 0.53333330154418945 0.23756161332130432;
	setAttr -s 5 ".koy[0:4]"  0.64561134576797485 0.2566165030002594 
		-0.43554109334945679 -0.21055711805820465 0.31998148560523987;
createNode animCurveTL -n "animCurveTL1459";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 -0.03798712688368186 75 6.5951150642852516;
createNode animCurveTL -n "animCurveTL1460";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 -0.10845703091427281 20 -0.10167892208157289 
		38 -0.094283249290222387 55 -0.078842722102808432 75 -0.10845703091427281;
	setAttr -s 5 ".kit[0:4]"  3 9 9 10 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 10 3;
createNode animCurveTL -n "animCurveTL1461";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 0.32759598950653745 20 0.33793433970476161 
		38 0.35261306486165667 75 0.32759598950653745;
	setAttr -s 4 ".kit[1:3]"  9 10 3;
	setAttr -s 4 ".kot[1:3]"  9 10 3;
createNode animCurveTA -n "animCurveTA2023";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 5.1593123884932233 41 -5.1961155146858564 
		75 5.1593123884932233;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2024";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 0 41 1.8604813831040206 75 0;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA2025";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 19.731371864588905 41 19.646943693603202 
		75 19.731371864588905;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTL -n "animCurveTL1462";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.033589776264348614 75 6.6666919674332821;
createNode animCurveTL -n "animCurveTL1463";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.22511613872864178 23 0.19717523045612451 
		41 0.23168478320881417 55 0.25534441896436189 75 0.22511613872864178;
	setAttr -s 5 ".kit[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kot[0:4]"  1 10 9 10 1;
	setAttr -s 5 ".kix[0:4]"  0.98911768198013306 0.59999996423721313 
		0.60000002384185791 0.46666666865348816 0.31155911087989807;
	setAttr -s 5 ".kiy[0:4]"  -0.0046392073854804039 0 0.032720170915126801 
		0 -0.018584476783871651;
	setAttr -s 5 ".kox[0:4]"  0.46309903264045715 0.59999996423721313 
		0.46666663885116577 0.66666668653488159 0.30061891674995422;
	setAttr -s 5 ".koy[0:4]"  -0.030420366674661636 0 0.025449018925428391 
		0 -0.018762772902846336;
createNode animCurveTL -n "animCurveTL1464";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -0.045973721978279453 41 0.10326288413627595 
		75 -0.045977437096470224;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2026";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 11.304516356559901 36 -8.8456346807767314 
		50 -5.6209126337946751 65 1.6917427520810511 75 0;
createNode animCurveTA -n "animCurveTA2027";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 -1.028868059103947 36 -7.4617016376831664 
		50 9.4864996334119187 65 -18.713452535816977 75 0;
createNode animCurveTA -n "animCurveTA2028";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 -48.318156406426453 36 12.896028850330135 
		50 11.899109175982543 65 -16.875933278649946 75 0;
createNode animCurveTA -n "animCurveTA2029";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2030";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -14.146488181616009 75 -14.146488181616009;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2031";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -4.1265910676803861 75 -4.1265910676803861;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2032";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 1.2729905952095404 26 6.898687793898282 
		52 3.6460436329356569 75 1.2729905952095404;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2033";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -2.2534544610437899 26 -1.9112608971772156 
		52 -2.0203955061020564 75 -2.2534544610437899;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2034";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -4.7698089761009097 26 -3.310801039778168 
		52 -6.7807936655566996 75 -4.7698089761009097;
createNode animCurveTA -n "animCurveTA2035";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -12.413101593828291 23 -11.606747540792208 
		50 -13.974304630643847 75 -12.413101593828291;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.59999996423721313 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.088257491588592529 0 0 0.088257491588592529;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.83333331346511841 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.088257491588592529 0 0 0.088257491588592529;
createNode animCurveTA -n "animCurveTA2036";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 33.121384411263357 23 33.770955366964209 
		50 29.133947195987126 75 33.121384411263357;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.59999996423721313 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.091562904417514801 0 -0.0058865980245172977 
		0.091562904417514801;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.83333337306976318 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.091562904417514801 0 -0.0054505537264049053 
		0.091562904417514801;
createNode animCurveTA -n "animCurveTA2037";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -12.398975986759352 23 -10.8530044021546 
		50 -14.643991235891573 75 -12.398975986759352;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.59999996423721313 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.084205880761146545 0 0 0.084205880761146545;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.83333331346511841 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.084205880761146545 0 0 0.084205880761146545;
createNode animCurveTA -n "animCurveTA2038";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -26.587256193064295 23 -25.334595872182202 
		50 -29.526498729615422 75 -26.587256193064295;
	setAttr -s 4 ".kit[0:3]"  9 10 10 1;
	setAttr -s 4 ".kot[0:3]"  9 10 10 1;
	setAttr -s 4 ".kix[3]"  0.93333333730697632;
	setAttr -s 4 ".kiy[3]"  0.08205791562795639;
	setAttr -s 4 ".kox[3]"  0.93333333730697632;
	setAttr -s 4 ".koy[3]"  0.08205791562795639;
createNode animCurveTA -n "animCurveTA2039";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -39.54220593632963 23 -38.591041486793813 
		50 -43.111460891501331 75 -39.54220593632963;
	setAttr -s 4 ".kit[0:3]"  1 10 10 9;
	setAttr -s 4 ".kot[0:3]"  1 10 10 9;
	setAttr -s 4 ".kix[0:3]"  0.34041520953178406 0.59999996423721313 
		0.89999997615814209 0.83333331346511841;
	setAttr -s 4 ".kiy[0:3]"  0.039732713252305984 0 -0.0086197247728705406 
		0.062295250594615936;
	setAttr -s 4 ".kox[0:3]"  0.34041532874107361 0.89999997615814209 
		0.83333337306976318 0.83333331346511841;
	setAttr -s 4 ".koy[0:3]"  0.039732716977596283 0 -0.0079812267795205116 
		0.062295250594615936;
createNode animCurveTA -n "animCurveTA2040";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  5 -9.9677264474011107 23 -8.9791780360974371 
		50 -9.4870331247652473 75 -9.9677264474011107;
	setAttr -s 4 ".kit[1:3]"  10 9 1;
	setAttr -s 4 ".kot[1:3]"  10 9 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.59999996423721313 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0 0 -0.0089585082605481148 0;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.83333337306976318 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0 0 -0.0082949157804250717 0;
createNode animCurveTA -n "animCurveTA2041";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 24.936495762060865 25 14.685664245749622 
		52 12.131465045141796 75 24.936495762060865;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2042";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -8.2409184517441272 25 -7.5612475070503544 
		52 -10.613745300070011 75 -8.2409184517441272;
	setAttr -s 4 ".kit[0:3]"  1 10 10 9;
	setAttr -s 4 ".kot[0:3]"  1 10 10 9;
	setAttr -s 4 ".kix[0:3]"  0.47596976161003113 0.66666668653488159 
		0.89999997615814209 0.76666665077209473;
	setAttr -s 4 ".kiy[0:3]"  0.026582252234220505 0 0 0.041413642466068268;
	setAttr -s 4 ".kox[0:3]"  0.47596976161003113 0.89999997615814209 
		0.76666665077209473 0.76666665077209473;
	setAttr -s 4 ".koy[0:3]"  0.026582248508930206 0 0 0.041413642466068268;
createNode animCurveTA -n "animCurveTA2043";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -12.596440170924348 25 -11.395238191005065 
		52 -14.932112043872596 75 -12.596440170924348;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.66666668653488159 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.052456144243478775 0 0 0.052456144243478775;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.76666665077209473 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.052456144243478775 0 0 0.052456144243478775;
createNode animCurveTA -n "animCurveTA2044";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 7.0128824805326051 25 6.2339456457251741 
		52 4.197437834433364 75 7.0128824805326051;
	setAttr -s 4 ".kit[1:3]"  1 10 3;
	setAttr -s 4 ".kot[1:3]"  1 10 3;
	setAttr -s 4 ".kix[1:3]"  0.38698247075080872 0.89999997615814209 
		0.76666665077209473;
	setAttr -s 4 ".kiy[1:3]"  -0.021306592971086502 0 0;
	setAttr -s 4 ".kox[1:3]"  0.62027645111083984 0.76666665077209473 
		0.76666665077209473;
	setAttr -s 4 ".koy[1:3]"  -0.034151352941989899 0 0;
createNode animCurveTA -n "animCurveTA2045";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -2.1233188747602703 25 -1.5822148739491209 
		52 -3.1250036228162918 75 -2.1233188747602703;
	setAttr -s 4 ".kit[0:3]"  9 10 10 9;
	setAttr -s 4 ".kot[0:3]"  9 10 10 9;
createNode animCurveTA -n "animCurveTA2046";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  5 -5.2146023219918298 25 -3.9909972288639324 
		52 -8.2843126661416289 75 -5.2146023219918298;
	setAttr -s 4 ".kit[1:3]"  3 10 1;
	setAttr -s 4 ".kot[1:3]"  3 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.66666668653488159 
		0.90000003576278687 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.055239703506231308 0 -0.011532207019627094 
		0.055239703506231308;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.76666665077209473 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.055239703506231308 0 -0.0098237311467528343 
		0.055239703506231308;
createNode animCurveTA -n "animCurveTA2047";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  5 7.0128824805326051 25 7.0777762260723769 
		52 4.197437834433364 75 7.0128824805326051;
	setAttr -s 4 ".kit[1:3]"  9 10 1;
	setAttr -s 4 ".kot[1:3]"  9 10 1;
	setAttr -s 4 ".kix[0:3]"  0.62555128335952759 0.66666662693023682 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.012124280445277691 -0.020910117775201797 
		0 0.053647719323635101;
	setAttr -s 4 ".kox[0:3]"  0.62555128335952759 0.89999997615814209 
		0.76666665077209473 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.012124277651309967 -0.028228661045432091 
		0 0.053647719323635101;
createNode animCurveTA -n "animCurveTA2048";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  5 -2.1233188747602703 25 -1.5822148739491209 
		52 -3.1250036228162918 75 -2.1233188747602703;
	setAttr -s 4 ".kit[1:3]"  9 3 1;
	setAttr -s 4 ".kot[1:3]"  9 3 1;
	setAttr -s 4 ".kix[0:3]"  0.57856929302215576 0.66666662693023682 
		0.89999997615814209 0.69780367612838745;
	setAttr -s 4 ".kiy[0:3]"  0.01380858663469553 -0.0074394452385604382 
		0 0.019973497837781906;
	setAttr -s 4 ".kox[0:3]"  0.57856929302215576 0.89999997615814209 
		0.76666665077209473 0.69780367612838745;
	setAttr -s 4 ".koy[0:3]"  0.013808584772050381 -0.0100432513281703 
		0 0.019973497837781906;
createNode animCurveTA -n "animCurveTA2049";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -5.2146023219918298 25 -3.9909972288639324 
		52 -8.2843126661416289 75 -5.2146023219918298;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.66666668653488159 
		0.90000003576278687 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.055239703506231308 0 -0.011532207019627094 
		0.055239703506231308;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.76666665077209473 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.055239703506231308 0 -0.0098237311467528343 
		0.055239703506231308;
createNode animCurveTA -n "animCurveTA2050";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -32.846554028611834 27 -33.238156418664083 
		54 -34.3641507034475 75 -32.846554028611834;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.73333334922790527 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.69999998807907104 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA2051";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -19.812246879199968 27 -18.71171269344028 
		54 -21.83653077231747 75 -19.812246879199968;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.73333334922790527 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0.072957433760166168 0 0 0.072957433760166168;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.69999998807907104 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0.072957433760166168 0 0 0.072957433760166168;
createNode animCurveTA -n "animCurveTA2052";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 16.73936320730547 27 17.427400824092818 
		54 13.888660128471185 75 16.73936320730547;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.73333334922790527 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0 0 0 0;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.69999998807907104 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0 0 0 0;
createNode animCurveTA -n "animCurveTA2053";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  5 8.3608152540575276 27 7.7629551001195338 
		54 7.9114197605655541 75 8.3608152540575276;
	setAttr -s 4 ".kit[1:3]"  3 9 1;
	setAttr -s 4 ".kot[1:3]"  3 9 1;
	setAttr -s 4 ".kix[0:3]"  0.93333333730697632 0.73333334922790527 
		0.89999997615814209 0.93333333730697632;
	setAttr -s 4 ".kiy[0:3]"  0 0 0.0058694779872894287 0;
	setAttr -s 4 ".kox[0:3]"  0.93333333730697632 0.89999997615814209 
		0.70000004768371582 0.93333333730697632;
	setAttr -s 4 ".koy[0:3]"  0 0 0.004565150011330843 0;
createNode animCurveTA -n "animCurveTA2054";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -2.5615724804630862 27 -1.6862337608731486 
		54 -4.0002143557411136 75 -2.5615724804630862;
	setAttr -s 4 ".kit[0:3]"  9 10 10 9;
	setAttr -s 4 ".kot[0:3]"  9 10 10 9;
createNode animCurveTA -n "animCurveTA2055";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -0.56940138961664799 27 0.89350841549640492 
		54 -4.4851992309726878 75 -0.56940138961664799;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.77298605442047119 0.73333334922790527 
		0.89999997615814209 0.61379349231719971;
	setAttr -s 4 ".kiy[0:3]"  0.033172871917486191 0 -0.014362082816660404 
		0.044591035693883896;
	setAttr -s 4 ".kox[0:3]"  0.77298605442047119 0.89999997615814209 
		0.70000004768371582 0.61379349231719971;
	setAttr -s 4 ".koy[0:3]"  0.033172883093357086 0 -0.011170510202646255 
		0.044591028243303299;
createNode animCurveTA -n "animCurveTA2056";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 33.76371226531262 28 33.371200294370475 
		54 34.187154559570018 75 33.76371226531262;
createNode animCurveTA -n "animCurveTA2057";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 4.3967631668876557 28 3.4616683630085348 
		54 5.4902587237815181 75 4.3967631668876557;
createNode animCurveTA -n "animCurveTA2058";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -2.1687082303991652 28 -0.790873728526022 
		54 -3.7556111874578151 75 -2.1687082303991652;
createNode animCurveTA -n "animCurveTA2059";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -48.842436584271979 30 -49.412003493442782 
		56 -48.166028548223302 75 -48.842436584271979;
createNode animCurveTA -n "animCurveTA2060";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -5.6607833041266336 30 -5.2036728596786395 
		56 -6.1670719936698486 75 -5.6607833041266336;
createNode animCurveTA -n "animCurveTA2061";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -12.375511559516685 30 -10.749793214214215 
		56 -14.263040924281775 75 -12.375511559516685;
createNode animCurveTA -n "animCurveTA2062";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 1.7308726403046661 32 1.1205044653872638 
		58 2.4565958301874504 75 1.7308726403046661;
createNode animCurveTA -n "animCurveTA2063";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -5.5385240879916626 32 -5.0162730091779251 
		58 -6.118884320553267 75 -5.5385240879916626;
createNode animCurveTA -n "animCurveTA2064";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -12.482812446025616 32 -10.89081330580709 
		58 -14.332993975272426 75 -12.482812446025616;
createNode animCurveTA -n "animCurveTA2065";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 1.3435362968557969 34 0.71802998336830814 
		60 2.0894842106625116 75 1.3435362968557969;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.71570092439651489 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  -0.017746424302458763 0.0068646939471364021 
		0.0069230673834681511 -0.013019246980547905;
	setAttr -s 4 ".kox[0:3]"  0.71570092439651489 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  -0.017746424302458763 0.0061545530334115028 
		0.0039940769784152508 -0.013019246980547905;
createNode animCurveTA -n "animCurveTA2066";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -5.3294197765631237 34 -4.7225636657629648 
		60 -6.0074163523658717 75 -5.3294197765631237;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.58692634105682373 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  0.018758704885840416 -0.0062393620610237122 
		-0.0067166481167078018 0.011833272874355316;
	setAttr -s 4 ".kox[0:3]"  0.58692634105682373 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  0.018758701160550117 -0.005593910813331604 
		-0.0038749889936298132 0.011833272874355316;
createNode animCurveTA -n "animCurveTA2067";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -8.8757356238731475 34 -7.3227766844718536 
		60 -10.682521713059204 75 -8.8757356238731475;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.63074409961700439 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  0.047189395874738693 -0.01662721112370491 
		-0.017188059166073799 0.031534366309642792;
	setAttr -s 4 ".kox[0:3]"  0.63074404001235962 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  0.047189392149448395 -0.014907155185937881 
		-0.0099161872640252113 0.031534366309642792;
createNode animCurveTA -n "animCurveTA2068";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 1.3413828738810762 34 0.68749247825351412 
		60 2.1216066523722903 75 1.3413828738810762;
createNode animCurveTA -n "animCurveTA2069";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -4.9664773383890592 34 -4.3044675779190182 
		60 -5.7076170668580923 75 -4.9664773383890592;
createNode animCurveTA -n "animCurveTA2070";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -12.758322585066164 34 -45.254781443149618 
		60 -14.522613408372411 75 -12.758322585066164;
createNode animCurveTA -n "animCurveTA2071";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 59.838197427393666 34 45.382112001111068 
		60 46.513715731710548 75 59.838197427393666;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2072";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 0.22385135043335772 34 -0.43316309672169329 
		60 0.85842118759823061 75 0.22385135043335772;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.83172208070755005 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  -0.015191926620900631 0.0058397208340466022 
		0.0072717978619039059 -0.011075332760810852;
	setAttr -s 4 ".kox[0:3]"  0.83172214031219482 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  -0.015191925689578056 0.0052356119267642498 
		0.0041952678002417088 -0.011075332760810852;
createNode animCurveTA -n "animCurveTA2073";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -0.2514286778866805 34 1.2417583469744313 
		60 -2.0705805830795052 75 -0.2514286778866805;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.63379937410354614 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  0.046050623059272766 -0.016741009429097176 
		-0.016526507213711739 0.031750191003084183;
	setAttr -s 4 ".kox[0:3]"  0.63379937410354614 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  0.046050619333982468 -0.015009180642664433 
		-0.0095345228910446167 0.031750191003084183;
createNode animCurveTA -n "animCurveTA2074";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 33.273550806451993 34 0.44127860236147004 
		60 16.502838498745181 75 33.273550806451993;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2075";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 3.0865145463569812 34 -5.4556211609331653 
		60 -42.483271391872208 75 3.0865145463569812;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2076";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -13.348824958423826 34 -11.940896562203926 
		60 -22.853801468608808 75 -13.348824958423826;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.73258179426193237 0.96666663885116577 
		0.86666667461395264 0.5;
	setAttr -s 4 ".kiy[0:3]"  0.11242870986461639 -0.087470926344394684 
		-0.01558286976069212 0.16589313745498657;
	setAttr -s 4 ".kox[0:3]"  0.7325817346572876 0.86666667461395264 
		0.49999997019767761 0.5;
	setAttr -s 4 ".koy[0:3]"  0.1124287024140358 -0.078422211110591888 
		-0.0089901164174079895 0.16589313745498657;
createNode animCurveTA -n "animCurveTA2077";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -1.045313912639122 20 -0.59068549485525568 
		48 6.0785314622157278 75 -1.045313912639122;
createNode animCurveTA -n "animCurveTA2078";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 10.492056474866592 20 9.7099202560336959 
		48 12.626981295520025 75 10.492056474866592;
createNode animCurveTA -n "animCurveTA2079";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -25.456010887158065 20 -24.511288267745392 
		48 -29.799478115159381 75 -25.456010887158065;
createNode animCurveTA -n "animCurveTA2080";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 8.6289720552899869 20 8.4665715965191843 
		48 9.1715075428585564 75 8.6289720552899869;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.33758899569511414 0.5 0.93333333730697632 
		0.89999997615814209;
	setAttr -s 4 ".kiy[0:3]"  -0.004899859894067049 0.0033031504135578871 
		0.0014429788570851088 -0.009469030424952507;
	setAttr -s 4 ".kox[0:3]"  0.33758902549743652 0.93333327770233154 
		0.89999997615814209 0.89999997615814209;
	setAttr -s 4 ".koy[0:3]"  -0.004899859894067049 0.0061658802442252636 
		0.0013914437731727958 -0.009469030424952507;
createNode animCurveTA -n "animCurveTA2081";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -17.984841714556691 20 -19.000571056882077 
		48 -17.282605996897342 75 -17.984841714556691;
createNode animCurveTA -n "animCurveTA2082";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -14.412335675324389 20 -13.650304675154191 
		48 -18.461803415161047 75 -14.412335675324389;
createNode animCurveTA -n "animCurveTA2083";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 11.278441944068955 22 10.952988064173974 
		50 11.428940198078408 75 11.278441944068955;
	setAttr -s 4 ".kit[0:3]"  1 9 9 1;
	setAttr -s 4 ".kot[0:3]"  1 9 9 1;
	setAttr -s 4 ".kix[0:3]"  0.32374903559684753 0.56666666269302368 
		0.93333327770233154 0.53643083572387695;
	setAttr -s 4 ".kiy[0:3]"  -0.006652934942394495 0.00099230522755533457 
		0.0030008824542164803 -0.0054272743873298168;
	setAttr -s 4 ".kox[0:3]"  0.32374903559684753 0.93333327770233154 
		0.83333337306976318 0.5364309549331665;
	setAttr -s 4 ".koy[0:3]"  -0.0066529340110719204 0.001634384854696691 
		0.0026793594006448984 -0.0054272753186523914;
createNode animCurveTA -n "animCurveTA2084";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 7.8881598233602421 22 6.8205142699155878 
		50 9.166797298825216 75 7.8881598233602421;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.31475764513015747 0.56666666269302368 
		0.93333327770233154 0.83333331346511841;
	setAttr -s 4 ".kiy[0:3]"  -0.025352856144309044 0.0084306532517075539 
		0.0098443403840065002 -0.022316433489322662;
	setAttr -s 4 ".kox[0:3]"  0.31475773453712463 0.93333327770233154 
		0.83333337306976318 0.83333331346511841;
	setAttr -s 4 ".koy[0:3]"  -0.025352863594889641 0.013885781168937683 
		0.0087895896285772324 -0.022316433489322662;
createNode animCurveTA -n "animCurveTA2085";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -12.704863046123954 22 -12.184227001558487 
		50 -16.450231207114417 75 -12.704863046123954;
	setAttr -s 4 ".kit[0:3]"  1 9 9 9;
	setAttr -s 4 ".kot[0:3]"  1 9 9 9;
	setAttr -s 4 ".kix[0:3]"  0.34304147958755493 0.56666666269302368 
		0.93333327770233154 0.83333331346511841;
	setAttr -s 4 ".kiy[0:3]"  0.031006960198283195 -0.024694958701729774 
		-0.0048005804419517517 0.065369002521038055;
	setAttr -s 4 ".kox[0:3]"  0.34304144978523254 0.93333327770233154 
		0.83333337306976318 0.83333331346511841;
	setAttr -s 4 ".koy[0:3]"  0.031006958335638046 -0.04067404568195343 
		-0.0042862328700721264 0.065369002521038055;
createNode animCurveTA -n "animCurveTA2086";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -16.065664968603347 24 -0.71405260930945547 
		52 0.13894687099906003 75 -16.065664968603347;
createNode animCurveTA -n "animCurveTA2087";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -2.3423934645184641 24 0.74560028024701863 
		52 2.9087633780425777 75 -2.3423934645184641;
createNode animCurveTA -n "animCurveTA2088";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -12.773111331363362 24 -17.706828005930372 
		52 -22.049493528514347 75 -12.773111331363362;
createNode animCurveTA -n "animCurveTA2089";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -45.377298494609192 26 -27.886023444924199 
		54 -30.043097250085165 75 -45.377298494609192;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2090";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -7.306394499759004 26 -20.754563268093214 
		54 -10.772644960892769 75 -7.306394499759004;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2091";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 11.454064087401083 26 -15.236237603710228 
		54 -3.1882299478973404 75 11.454064087401083;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2092";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -25.895473945723587 28 -1.6958409014547726 
		56 0.53241792657809406 75 -25.895473945723587;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2093";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -3.5035810068855007 28 0.18575345819325309 
		56 -0.55427914370880293 75 -3.5035810068855007;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2094";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 3.1875370472451463 28 -6.2725969072564816 
		56 -11.175815846999063 75 3.1875370472451463;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2095";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -5.7432504495651573 32 -0.51227202934948712 
		57 -7.9909655953666947 75 -5.7432504495651573;
createNode animCurveTA -n "animCurveTA2096";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -41.212197054826376 32 -42.298320142795504 
		57 -42.948978191482524 75 -41.212197054826376;
createNode animCurveTA -n "animCurveTA2097";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 0.50039255068051769 32 -2.8925232688370746 
		57 2.7822054324130101 75 0.50039255068051769;
createNode animCurveTA -n "animCurveTA2098";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -3.6807180612268477 32 0.19411076870817565 
		57 -5.185799359609697 75 -3.6807180612268477;
createNode animCurveTA -n "animCurveTA2099";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 10.386402038538378 32 9.4789783521729838 
		57 8.6396543826885601 75 10.386402038538378;
createNode animCurveTA -n "animCurveTA2100";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 9.373754111564919 32 9.7058521075377264 
		57 10.340799307500824 75 9.373754111564919;
createNode animCurveTA -n "animCurveTA2101";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -2.6532077848244637 36 -12.057223739755038 
		60 -4.9264745828363612 75 -2.6532077848244637;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2102";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 31.398320748885013 36 -1.7928776792171692 
		60 23.842284861535354 75 31.398320748885013;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2103";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 -27.632666087165095 36 -12.495826421949115 
		60 -26.046869292161826 75 -27.632666087165095;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2104";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -37.277067809523452 46 -8.5614891977186094 
		75 -37.277067809523452;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2105";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 19.585054233722889 46 9.0603366556262852 
		75 19.585054233722889;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2106";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -10.955175918624663 46 -0.32840086412850056 
		75 -10.955175918624663;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA2107";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2108";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2109";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2110";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 24.592391995351925 36 5.5488425982398946 
		60 4.8084016895810828 75 24.592391995351925;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2111";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 23.257939359619229 36 20.930363121421333 
		60 19.722748227580659 75 23.257939359619229;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTA -n "animCurveTA2112";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  5 17.14441316873247 36 2.7194251213980918 
		60 7.7471932885672778 75 17.14441316873247;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTL -n "animCurveTL1465";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL1466";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL1467";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL1468";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -0.018959770353138054 40 -0.21786087952439531 
		75 -0.018959770353138054;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1469";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 0.051797593738875436 40 -0.0959371314672543 
		75 0.051797593738875436;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTL -n "animCurveTL1470";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0.096290742289606199 75 0.096290742289606199;
createNode animCurveTU -n "animCurveTU308";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.013576770094999802 
		75 0.013576770094999802;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1471";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.57719404540719277 
		21 -0.52719387965077913 36 -0.65091399018991858 62 -0.48143712545212364 75 -0.57719404540719277;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.53333330154418945;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1472";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.25086364718380999 
		21 0.23627156946100378 36 0.44217641098543226 62 0.16011954134115491 75 0.25086364718380999;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.53333330154418945;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1473";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.028286589051344055 
		75 -0.028286589051344055;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1474";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.0062586747904909146 
		75 0.0062586747904909146;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1475";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.096066305391612872 
		75 0.096066305391612872;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1476";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.10433513263538075 
		75 0.10433513263538075;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1477";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.089510743724077801 
		27 -0.11540930951766998 55 -0.05807577617460348 75 -0.089510743724077801;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.13821899890899658 0.73333334922790527 
		0.93333333730697632 0.77300041913986206;
	setAttr -s 5 ".kiy[1:4]"  -0.0087902965024113655 0 0 -0.036989681422710419;
	setAttr -s 5 ".kox[1:4]"  0.46994444727897644 0.93333333730697632 
		0.66666668653488159 0.76071321964263916;
	setAttr -s 5 ".koy[1:4]"  -0.029886998236179352 0 0 -0.039193436503410339;
createNode animCurveTL -n "animCurveTL1478";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.084668858550071613 
		27 0.12777131022265192 55 0.032352287029126396 75 0.084668858550071613;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.10486189275979996 0.73333334922790527 
		0.93333339691162109 0.68802469968795776;
	setAttr -s 5 ".kiy[1:4]"  0.010825106874108315 0 -0.025143098086118698 
		0.068383984267711639;
	setAttr -s 5 ".kox[1:4]"  0.35653060674667358 0.93333333730697632 
		0.66666662693023682 0.67378181219100952;
	setAttr -s 5 ".koy[1:4]"  0.036805383861064911 0 -0.0179593525826931 
		0.069367170333862305;
createNode animCurveTL -n "animCurveTL1479";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.059499436532721717 
		75 0.059499436532721717;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1480";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.28075707428023533 
		32 -0.32940191846253353 58 -0.26045702514696417 75 -0.28075707428023533;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.1557835191488266 0.89999997615814209 
		0.86666667461395264 0.74886167049407959;
	setAttr -s 5 ".kiy[1:4]"  -0.014867658726871014 0 0 -0.041227582842111588;
	setAttr -s 5 ".kox[1:4]"  0.68544775247573853 0.86666667461395264 
		0.56666666269302368 0.74886167049407959;
	setAttr -s 5 ".koy[1:4]"  -0.06541772186756134 0 0 -0.041227582842111588;
createNode animCurveTL -n "animCurveTL1481";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.040550004911271337 
		32 0.12150862100600851 58 0.017288235397352806 75 0.040550004911271337;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.11587218195199966 0.89999991655349731 
		0.86666667461395264 0.56718146800994873;
	setAttr -s 5 ".kiy[1:4]"  0.009779779240489006 -0.011850334703922272 
		0 0.04211052879691124;
	setAttr -s 5 ".kox[1:4]"  0.50983798503875732 0.86666673421859741 
		0.56666666269302368 0.54877603054046631;
	setAttr -s 5 ".koy[1:4]"  0.043031051754951477 -0.011411434970796108 
		0 0.043705634772777557;
createNode animCurveTL -n "animCurveTL1482";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.039020992523884947 
		75 0.039020992523884947;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1483";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.039475641515128501 
		75 -0.039475641515128501;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1484";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.064868640662410826 
		75 0.064868640662410826;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1485";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.037827303279129865 
		75 -0.037827303279129865;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1486";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.010947784034289754 
		25 -0.036536626907890953 53 0.0201112503451071 75 -0.010947784034289754;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.071108750998973846 0.66666668653488159 
		0.93333333730697632 0.40367889404296875;
	setAttr -s 5 ".kiy[1:4]"  -0.0062483958899974823 0 0 -0.031790532171726227;
	setAttr -s 5 ".kox[1:4]"  0.241769939661026 0.93333333730697632 0.73333334922790527 
		0.3801475465297699;
	setAttr -s 5 ".koy[1:4]"  -0.021244557574391365 0 0 -0.032285157591104507;
createNode animCurveTL -n "animCurveTL1487";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.0101250460657063 
		25 0.033161997847481965 53 -0.062665670576289814 75 -0.0101250460657063;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.095438368618488312 0.66666668653488159 
		0.93333333730697632 0.66494107246398926;
	setAttr -s 5 ".kiy[1:4]"  0.010288997553288937 0 -0.024240745231509209 
		0.067175067961215973;
	setAttr -s 5 ".kox[1:4]"  0.32449054718017578 0.93333333730697632 
		0.73333334922790527 0.64299803972244263;
	setAttr -s 5 ".koy[1:4]"  0.034982603043317795 0 -0.019046299159526825 
		0.068375676870346069;
createNode animCurveTL -n "animCurveTL1488";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.081775722384072935 
		75 -0.081775722384072935;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU309";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.013576770094999802 
		75 0.013576770094999802;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1489";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.51544148570482229 
		19 -0.46554723474915088 34 -0.58778776706750435 60 -0.42033768915190467 75 -0.51544148570482229;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1490";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.11691341268187419 
		19 0.10196319430521782 34 0.30874985193462678 60 0.025485035193299491 75 0.11691341268187419;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1491";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.17220951542591578 
		75 -0.17220951542591578;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1492";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.25562282673960107 
		23 -0.32827104860214706 38 -0.25133497404405952 62 -0.24684943105932669 75 -0.25562282673960107;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.74996691942214966 0.59999996423721313 
		0.5 0.80000001192092896 0.74996691942214966;
	setAttr -s 6 ".kiy[1:5]"  -0.035431984812021255 0.0023388287518173456 
		0 0 -0.035431984812021255;
	setAttr -s 6 ".kox[1:5]"  0.74996691942214966 0.5 0.80000001192092896 
		0.43333333730697632 0.74996691942214966;
	setAttr -s 6 ".koy[1:5]"  -0.035431984812021255 0.0019490240374580026 
		0 0 -0.035431984812021255;
createNode animCurveTL -n "animCurveTL1493";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.056525164343554833 
		23 0.17943268331816228 38 0.049271672310248572 62 0.035660362821097059 75 0.056525164343554833;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.75234115123748779 0.59999996423721313 
		0.5 0.80000001192092896 0.75234115123748779;
	setAttr -s 6 ".kiy[1:5]"  0.032842542976140976 -0.0039564501494169235 
		0 0 0.032842542976140976;
	setAttr -s 6 ".kox[1:5]"  0.74969083070755005 0.5 0.80000001192092896 
		0.43333333730697632 0.74969083070755005;
	setAttr -s 6 ".koy[1:5]"  0.035720400512218475 -0.0032970418687909842 
		0 0 0.035720400512218475;
createNode animCurveTL -n "animCurveTL1494";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.059530928353148098 
		75 -0.059530928353148098;
	setAttr -s 3 ".kit[1:2]"  1 10;
	setAttr -s 3 ".kot[1:2]"  1 10;
	setAttr -s 3 ".kix[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTA -n "animCurveTA2113";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -2.1598275546723902 18 -14.589898269433867 
		35 -12.970467101053829 47 -18.158266567678275 60 -7.0722197977897112 75 -2.1598275546723902;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2114";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -10.942393419079574 18 -4.696278977182831 
		35 1.8597440103984311 47 -3.3256010342494289 60 -4.3048869122981399 75 -10.942393419079574;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2115";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -16.243524585053528 18 -26.717199958776451 
		35 -9.386977722744124 47 -16.912445198640807 60 -11.417998620146145 75 -16.243524585053528;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2116";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -4.1510006667317709 12 -12.312931664926912 
		28 -1.9144009277332741 42 -8.3050077949308925 56 -0.47036121858365082 75 -4.1510006667317709;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2117";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -5.5593925792374863 12 -4.7158637781673791 
		28 -9.1191368968929805 42 -8.2210853105048134 56 -8.0349271435439515 75 -5.5593925792374863;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2118";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -8.863841196016077 12 -9.6332892285770502 
		28 0.26523850028949875 42 -6.5413092450166603 56 -0.58097340150962928 75 -8.863841196016077;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2119";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -7.6887152411938313 12 -7.5808824972558124 
		23 -22.304648399725792 38 -16.447140816690151 50 -16.347996923882793 59 -12.129497170139025 
		75 -7.6887152411938313;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2120";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -38.711641678598497 12 -37.364776776014772 
		23 -35.981731958401859 38 -30.908669417516411 50 -23.234780352042073 59 -35.201943587517952 
		75 -38.711641678598497;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2121";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -3.5102215139587138 12 -10.406400188643115 
		23 -1.3743038953654227 38 -17.044577961577762 50 -4.1848472268916996 59 -19.372929892708431 
		75 -3.5102215139587138;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2122";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 20.893674516403365 13 18.782647456585707 
		26 17.977215292784564 40 26.390937534064143 51 29.283557379953578 60 30.13241020223731 
		75 20.893674516403365;
	setAttr -s 7 ".kit[0:6]"  3 1 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 1 9 9 9 9 3;
	setAttr -s 7 ".kix[1:6]"  0.24946986138820648 0.43333333730697632 
		0.46666672825813293 0.36666661500930786 0.30000001192092896 0.5;
	setAttr -s 7 ".kiy[1:6]"  -0.035083282738924026 0.063935786485671997 
		0.11050643771886826 0.035915553569793701 -0.05491165816783905 0;
	setAttr -s 7 ".kox[1:6]"  0.41613426804542542 0.46666663885116577 
		0.36666661500930786 0.30000004172325134 0.49999997019767761 0.5;
	setAttr -s 7 ".koy[1:6]"  -0.058521531522274017 0.068853922188282013 
		0.08682645857334137 0.029385462403297424 -0.091519422829151154 0;
createNode animCurveTA -n "animCurveTA2123";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -42.477103375140359 13 -43.914898370136015 
		26 -40.548108443043589 40 -48.421053618696568 51 -38.15993845526841 60 -45.394106040033599 
		75 -42.477103375140359;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2124";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 20.425932929328599 13 19.321634284398822 
		26 25.355991995204981 40 17.174373142295309 51 13.040836337939345 60 10.642865076309647 
		75 20.425932929328599;
	setAttr -s 7 ".kit[0:6]"  3 1 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 1 9 9 9 9 3;
	setAttr -s 7 ".kix[1:6]"  0.27186238765716553 0.43333333730697632 
		0.46666672825813293 0.36666661500930786 0.30000001192092896 0.5;
	setAttr -s 7 ".kiy[1:6]"  -0.028295401483774185 -0.018044374883174896 
		-0.1203664243221283 -0.062697969377040863 0.048335347324609756 0;
	setAttr -s 7 ".kox[1:6]"  0.43852964043617249 0.46666663885116577 
		0.36666661500930786 0.30000004172325134 0.49999997019767761 0.5;
	setAttr -s 7 ".koy[1:6]"  -0.04564211517572403 -0.019432401284575462 
		-0.094573594629764557 -0.0512983538210392 0.080558903515338898 0;
createNode animCurveTA -n "animCurveTA2125";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 2.2238180235519738 33 0.13511794497795937 
		43 5.4863014269908792 56 1.5337958581061637 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2126";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 -3.6969301659572591 33 1.070603233197079 
		43 -6.9642206585629838 56 6.2021703472301768 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2127";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 0.80714630453019254 33 -0.78477540667849177 
		43 0.098550556352914861 56 -2.3072247086126474 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2128";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 23 -4.530027155745092 50 3.1207277379437053 
		75 0;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.33322101831436157 0.59999996423721313 
		0.89999997615814209 0.69669061899185181;
	setAttr -s 4 ".kiy[0:3]"  -0.041507929563522339 0.02178678847849369 
		0.041052404791116714 -0.066433869302272797;
	setAttr -s 4 ".kox[0:3]"  0.33322107791900635 0.89999997615814209 
		0.83333337306976318 0.69192445278167725;
	setAttr -s 4 ".koy[0:3]"  -0.041507944464683533 0.03268018364906311 
		0.038011487573385239 -0.066657967865467072;
createNode animCurveTA -n "animCurveTA2129";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2130";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2131";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 24 6.2643895333489752 51 -2.8338896383503345 
		75 0;
	setAttr -s 4 ".kit[0:3]"  1 10 10 1;
	setAttr -s 4 ".kot[0:3]"  1 10 10 1;
	setAttr -s 4 ".kix[0:3]"  0.36568629741668701 0.63333332538604736 
		0.89999997615814209 0.51351636648178101;
	setAttr -s 4 ".kiy[0:3]"  0.042646467685699463 -0.020429423078894615 
		0 0.058961696922779083;
	setAttr -s 4 ".kox[0:3]"  0.3656863272190094 0.89999997615814209 
		0.80000001192092896 0.51109576225280762;
	setAttr -s 4 ".koy[0:3]"  0.042646463960409164 -0.029031282290816307 
		0 0.062174972146749496;
createNode animCurveTA -n "animCurveTA2132";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2133";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU310";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -31.758416714015105 
		27 -54.55841671401511 52 10.158948049320733 75 -31.758416714015105;
	setAttr -s 5 ".kit[1:4]"  1 3 10 1;
	setAttr -s 5 ".kot[1:4]"  1 3 10 1;
	setAttr -s 5 ".kix[1:4]"  0.11102013289928436 0.73333334922790527 
		0.83333337306976318 0.41366103291511536;
	setAttr -s 5 ".kiy[1:4]"  -6.1853985786437988 0 11.875000953674316 
		-23.863388061523437;
	setAttr -s 5 ".kox[1:4]"  0.57730549573898315 0.83333331346511841 
		0.76666665077209473 0.41366103291511536;
	setAttr -s 5 ".koy[1:4]"  -32.16412353515625 0 10.924999237060547 
		-23.863384246826172;
createNode animCurveTL -n "animCurveTL1495";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.59734991426452611 
		28 -0.52951852463458915 40 -0.63493169539925431 58 -0.56008927908609474 75 -0.59734991426452611;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1496";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.27110309185958181 
		28 0.12051635172661283 40 0.22370980373537938 58 0.16513818024881785 75 0.27110309185958181;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1497";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.048772735016498973 
		28 0.033778962188112369 40 0.050358916019737777 58 0.040505761747113324 75 0.048772735016498973;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1498";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.35115786616779016 
		25 -0.33999465899514347 37 -0.41574943345874965 53 -0.35259507260137757 75 -0.35115786616779016;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1499";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.11406604383450146 
		25 0.091964969585900933 37 0.11952019133351319 53 0.071414088053919161 75 0.11406604383450146;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1500";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.05363806138935244 
		25 0.050477606757408519 37 0.058985368738632825 53 0.049238370094723788 75 0.05363806138935244;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1501";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.19996587385929848 
		22 -0.24319997837153789 31 -0.30235137455484112 47 -0.21455075647917357 75 -0.19996587385929848;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1502";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.12974765050309967 
		22 0.1769640253426262 31 0.20211571836651099 47 0.16144898924649981 75 0.12974765050309967;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1503";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.04623521438182978 
		22 0.054168640902139485 31 0.062800031696036429 47 0.047602428731852948 75 0.04623521438182978;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1504";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.11005367680981593 
		19 -0.14226839498968402 44 -0.09641007039044229 75 -0.11005367680981593;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1505";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.078121863592283347 
		19 0.11212507336828076 44 0.081879590676509184 75 0.078121863592283347;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1506";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.014057059883711531 
		19 0.019836158667690285 44 0.013345853292522636 75 0.014057059883711531;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1507";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.065458998535778079 
		75 -0.065458998535778079;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1508";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.043410449465909551 
		75 0.043410449465909551;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1509";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.013532404204323001 
		75 -0.013532404204323001;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU311";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 14.677573762761186 
		30 -32.722426237238821 50 1.9393052206891541 75 14.677573762761186;
	setAttr -s 5 ".kit[0:4]"  10 3 3 10 3;
	setAttr -s 5 ".kot[0:4]"  10 3 3 10 3;
createNode animCurveTL -n "animCurveTL1510";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.71422526197326242 
		32 -0.67637343062328692 44 -0.7622848545534272 62 -0.7020768757143353 75 -0.71422526197326242;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1511";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.46175531702906814 
		32 0.30099244013749316 44 0.4224037189782951 62 0.33039686943543006 75 0.46175531702906814;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1512";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.048566732713168193 
		32 -0.063560505541554776 44 -0.046980551709929375 62 -0.056833705982553849 75 -0.048566732713168193;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1513";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.439670094418874 
		29 -0.43292907057786378 41 -0.50203423228824673 57 -0.44887642783324261 75 -0.439670094418874;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1514";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.27232558316700456 
		29 0.24850052755539015 41 0.29000417467915202 57 0.22882918314614298 75 0.27232558316700456;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1515";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.0089961231324273191 
		29 -0.01215657776437124 41 -0.0036488157831469359 57 -0.013395814427055968 75 -0.0089961231324273191;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1516";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.31016085678722577 
		38 -0.40866425160678183 54 -0.33609372235194646 75 -0.31016085678722577;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1517";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.17426690456730554 
		38 0.23205250178650183 54 0.17691236046746539 75 0.17426690456730554;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1518";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.010200819450622596 
		38 0.022033604495509531 54 0.0099772093251364498 75 0.010200819450622596;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1519";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.20950137605528596 
		26 -0.24293183924806502 35 -0.29619728840257109 51 -0.2184754282858824 75 -0.20950137605528596;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1520";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.025072542899550854 
		26 0.07967087599386935 35 0.11715069329525532 51 0.060366645253083981 75 0.025072542899550854;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1521";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.013576770094999802 
		26 0.021510196615309528 35 0.030141587409206475 51 0.014943984445022977 75 0.013576770094999802;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1522";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.12340943748539601 
		23 -0.14854416226092418 48 -0.10929949441403741 75 -0.12340943748539601;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1523";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.030537591029027311 
		23 0.070062924081858879 48 0.031622955248687273 75 0.030537591029027311;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1524";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.013576770094999802 
		23 0.019355868878978569 48 0.012865563503810911 75 0.013576770094999802;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1525";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.094490204038635284 
		21 -0.11962492881416352 46 -0.080380260967276712 75 -0.094490204038635284;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1526";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.06390811474556557 
		21 0.10343344779839714 46 0.064993478965225532 75 0.06390811474556557;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1527";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.013576770094999802 
		21 0.019355868878978569 46 0.012865563503810911 75 0.013576770094999802;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1528";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.12816845960777101 
		24 -0.16159892280055008 33 -0.21486437195505628 49 -0.13714251183836751 75 -0.12816845960777101;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1529";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.056180887556120496 
		24 0.11077922065043899 33 0.14825903795182496 49 0.091474989909653623 75 0.056180887556120496;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1530";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.0048820376787510611 
		24 0.012815464199060789 33 0.021446854992957735 49 0.0062492520287742393 75 0.0048820376787510611;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1531";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.27061890804008826 
		36 -0.36912230285964431 52 -0.29655177360480894 75 -0.27061890804008826;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1532";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.1003543561607507 
		36 0.15813995337994699 52 0.10299981206091052 75 0.1003543561607507;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1533";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.0044359769245985708 
		36 0.0073968081202883578 52 -0.00465958705008472 75 -0.0044359769245985708;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1534";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.44452153333611805 
		27 -0.43778050949510783 39 -0.50688567120549066 55 -0.45372786675048665 75 -0.44452153333611805;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1535";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.19311770864331976 
		27 0.16929265303170535 39 0.21079630015546724 55 0.1496213086224582 75 0.19311770864331976;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1536";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.040449485675541179 
		27 0.037289031043597258 39 0.045796793024821564 55 0.036049794380912534 75 0.040449485675541179;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTU -n "animCurveTU312";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 6.5634954268192143 
		28 42.563495426819216 48 13.175617729751012 75 6.5634954268192143;
	setAttr -s 5 ".kit[0:4]"  10 3 3 10 3;
	setAttr -s 5 ".kot[0:4]"  10 3 3 10 3;
createNode animCurveTL -n "animCurveTL1537";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.72098342290092432 
		30 -0.68313159155094882 42 -0.76904301548108911 60 -0.70883503664199721 75 -0.72098342290092432;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1538";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.41754806497788971 
		30 0.25678518808631473 42 0.37819646692711667 60 0.28618961738425164 75 0.41754806497788971;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1539";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.014923547541217131 
		30 -7.0225287169449583e-005 42 0.01650972854445594 60 0.0066565742718314742 75 0.014923547541217131;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTU -n "animCurveTU313";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 36.966849191613797 
		29 49.366849191613795 54 14.460191839760423 75 36.966849191613797;
	setAttr -s 5 ".kit[1:4]"  1 3 10 1;
	setAttr -s 5 ".kot[1:4]"  1 3 10 1;
	setAttr -s 5 ".kix[1:4]"  0.12343022972345352 0.80000001192092896 
		0.83333331346511841 0.48747694492340088;
	setAttr -s 5 ".kiy[1:4]"  4.0973620414733887 0 -6.7391300201416016 
		18.379096984863281;
	setAttr -s 5 ".kox[1:4]"  0.59246551990509033 0.83333331346511841 
		0.70000004768371582 0.48747691512107849;
	setAttr -s 5 ".koy[1:4]"  19.667348861694336 0 -5.6608695983886719 
		18.379095077514648;
createNode animCurveTL -n "animCurveTL1540";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.58609077608402937 
		32 -0.517930726827877 44 -0.62356897957354362 62 -0.54855384195839196 75 -0.58609077608402937;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1541";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.18309874871368673 
		32 0.032660484271419342 44 0.1356235099378113 62 0.093348620700642107 75 0.18309874871368673;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 1 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 1 3;
	setAttr -s 6 ".kix[4:5]"  0.66413861513137817 0.43333333730697632;
	setAttr -s 6 ".kiy[4:5]"  0.046213522553443909 0;
	setAttr -s 6 ".kox[4:5]"  0.36527636647224426 0.43333333730697632;
	setAttr -s 6 ".koy[4:5]"  0.025417445227503777 0;
createNode animCurveTL -n "animCurveTL1542";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.013598240306418482 
		32 -0.028592013134805069 44 -0.012012059303179664 62 -0.021865213575804138 75 -0.013598240306418482;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1543";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.34429717159734152 
		29 -0.33308573111297096 41 -0.40890049457952715 57 -0.34564516339815776 75 -0.34429717159734152;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1544";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.044079877896513076 
		29 0.022003232327337453 41 0.049392970188479809 57 0.0014466554102057737 75 0.044079877896513076;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1545";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.025752577883867103 
		29 0.022592123251923193 41 0.031099885233147495 57 0.021352886589238469 75 0.025752577883867103;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1546";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.13624453307664597 
		26 -0.17958163623449411 35 -0.238787812656717 51 -0.150890524554294 75 -0.13624453307664597;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1547";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.066229430187978805 
		26 0.11335128643163651 35 0.13837375645085048 51 0.097891447535783424 75 0.066229430187978805;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1548";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.031892271984597029 
		26 0.039825698504906755 35 0.048457089298803706 51 0.033259486334620211 75 0.031892271984597029;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 3;
createNode animCurveTL -n "animCurveTL1549";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.07339459878784993 
		23 -0.10568348960516129 48 -0.059759230271860468 75 -0.07339459878784993;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1550";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.11818364147922367 
		23 0.15211642610215967 48 0.12197115179597019 75 0.11818364147922367;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1551";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.096090279174731563 
		23 0.10186937795871032 48 0.095379072583542654 75 0.096090279174731563;
	setAttr -s 5 ".kit[0:4]"  10 3 9 9 3;
	setAttr -s 5 ".kot[0:4]"  10 3 9 9 3;
createNode animCurveTL -n "animCurveTL1552";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.0098265708771627658 
		75 0.0098265708771627658;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1553";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.0326474496810647 
		75 0.0326474496810647;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1554";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.036688039951190632 
		75 0.036688039951190632;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU314";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -47.791053425996765 
		75 -47.791053425996765;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1555";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.20627760032049108 
		21 -0.15427721320087298 38 -0.32109956930352795 63 -0.17446194956051991 75 -0.20627760032049108;
	setAttr -s 6 ".kit[0:5]"  10 1 9 9 9 9;
	setAttr -s 6 ".kot[0:5]"  10 1 9 9 9 9;
	setAttr -s 6 ".kix[1:5]"  0.18537324666976929 0.53333330154418945 
		0.56666666269302368 0.83333325386047363 0.40000000596046448;
	setAttr -s 6 ".kiy[1:5]"  -0.01964089646935463 -0.05567125603556633 
		-0.0081700123846530914 0.077582404017448425 -0.031815651804208755;
	setAttr -s 6 ".kox[1:5]"  0.59319430589675903 0.56666666269302368 
		0.83333331346511841 0.40000006556510925 0.40000000596046448;
	setAttr -s 6 ".koy[1:5]"  -0.062850892543792725 -0.059150710701942444 
		-0.012014724314212799 0.037239562720060349 -0.031815651804208755;
createNode animCurveTL -n "animCurveTL1556";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.087017743098008207 
		21 0.084033610502583275 38 0.25687391546463723 63 0.10494649094407063 75 0.087017743098008207;
	setAttr -s 6 ".kit[0:5]"  10 1 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  10 1 9 9 9 1;
	setAttr -s 6 ".kix[1:5]"  0.16827003657817841 0.53333330154418945 
		0.56666666269302368 0.83333325386047363 0.40150287747383118;
	setAttr -s 6 ".kiy[1:5]"  -0.013514122925698757 0.082354508340358734 
		0.0084647368639707565 -0.11476767063140869 -0.0099923070520162582;
	setAttr -s 6 ".kox[1:5]"  0.53846371173858643 0.56666666269302368 
		0.83333331346511841 0.40000006556510925 0.40150290727615356;
	setAttr -s 6 ".koy[1:5]"  -0.043245155364274979 0.087501667439937592 
		0.01244814321398735 -0.055088497698307037 -0.0099923070520162582;
createNode animCurveTL -n "animCurveTL1557";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.018828421952376006 
		75 0.018828421952376006;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1558";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.10435420481898076 
		31 -0.16994618888183274 60 -0.085507716012235807 75 -0.10435420481898076;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 9;
createNode animCurveTL -n "animCurveTL1559";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.05057173249078354 
		31 0.11852988146641172 60 0.031045375271638347 75 0.05057173249078354;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 9;
createNode animCurveTL -n "animCurveTL1560";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.0062247204158246486 
		75 0.0062247204158246486;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1561";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.077826664138872292 
		23 -0.11274790488574238 57 -0.035440221645718792 75 -0.077826664138872292;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 9;
createNode animCurveTL -n "animCurveTL1562";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.060141527829868847 
		23 0.096322517244909436 57 0.016226037017203727 75 0.060141527829868847;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 9;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 9;
createNode animCurveTL -n "animCurveTL1563";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.033604018316857776 
		75 -0.033604018316857776;
	setAttr -s 3 ".kit[0:2]"  10 9 9;
	setAttr -s 3 ".kot[0:2]"  10 9 9;
createNode animCurveTL -n "animCurveTL1564";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.0010491139546289219 
		75 -0.0010491139546289219;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1565";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.028730268214406607 
		75 0.028730268214406607;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1566";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.038784834719113093 
		75 -0.038784834719113093;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU315";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -19.831699159979927 
		75 -19.831699159979927;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1567";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.58811974824966218 
		15 -0.53838186463185744 30 -0.65848959701722132 56 -0.49396111493402883 75 -0.58811974824966218;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.3333333432674408;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1568";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.25951405723353821 
		15 0.24405157874013481 30 0.45208427361347125 56 0.16711258365108 75 0.25951405723353821;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.3333333432674408;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1569";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.0035475614378103902 
		75 0.0035475614378103902;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1570";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.20824152503012491 
		19 -0.28062364675811385 34 -0.20402848493371295 58 -0.17544419209951254 75 -0.20824152503012491;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.74809134006500244 0.46666666865348816 
		0.5 0.80000001192092896 0.74809134006500244;
	setAttr -s 6 ".kiy[1:5]"  -0.046107657253742218 0.0020338813774287701 
		0 0 -0.046107657253742218;
	setAttr -s 6 ".kox[1:5]"  0.74809139966964722 0.5 0.80000001192092896 
		0.56666666269302368 0.74809139966964722;
	setAttr -s 6 ".koy[1:5]"  -0.046107660979032516 0.0021791586186736822 
		0 0 -0.046107660979032516;
createNode animCurveTL -n "animCurveTL1571";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.1752358009711773 
		19 0.30226494618810729 34 0.16793860146986689 58 0.12242855467985612 75 0.1752358009711773;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.71337383985519409 0.46666666865348816 
		0.5 0.80000001192092896 0.71337383985519409;
	setAttr -s 6 ".kiy[1:5]"  0.077197760343551636 -0.003522785846143961 
		0 0 0.077197760343551636;
	setAttr -s 6 ".kox[1:5]"  0.71337378025054932 0.5 0.80000001192092896 
		0.56666666269302368 0.71337378025054932;
	setAttr -s 6 ".koy[1:5]"  0.077197752892971039 -0.0037744136061519384 
		0 0 0.077197752892971039;
createNode animCurveTL -n "animCurveTL1572";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.023449024182201329 
		75 0.023449024182201329;
	setAttr -s 3 ".kit[1:2]"  1 10;
	setAttr -s 3 ".kot[1:2]"  1 10;
	setAttr -s 3 ".kix[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1573";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.086328852712288295 
		21 -0.11147123252383438 49 -0.05581172293021916 75 -0.086328852712288295;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.15795469284057617 0.53333330154418945 
		0.93333333730697632 0.82969564199447632;
	setAttr -s 5 ".kiy[1:4]"  -0.0094760190695524216 0 0 -0.044624235481023788;
	setAttr -s 5 ".kox[1:4]"  0.53704613447189331 0.93333333730697632 
		0.86666667461395264 0.82168811559677124;
	setAttr -s 5 ".koy[1:4]"  -0.032218474894762039 0 0 -0.049103781580924988;
createNode animCurveTL -n "animCurveTL1574";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.088488360622548612 
		21 0.13203623987934024 49 0.035631141338830767 75 0.088488360622548612;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.14368362724781036 0.53333330154418945 
		0.93333333730697632 0.82918858528137207;
	setAttr -s 5 ".kiy[1:4]"  0.01504904218018055 0 -0.022580381482839584 
		0.069367997348308563;
	setAttr -s 5 ".kox[1:4]"  0.48852473497390747 0.93333333730697632 
		0.86666667461395264 0.82383131980895996;
	setAttr -s 5 ".koy[1:4]"  0.05116678774356842 0 -0.020967496559023857 
		0.07136593759059906;
createNode animCurveTL -n "animCurveTL1575";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.010529025794578144 
		75 -0.010529025794578144;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1576";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.005823654817696422 
		75 -0.005823654817696422;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1577";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.014644721646906333 
		75 -0.014644721646906333;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1578";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.013576770094999802 
		75 0.013576770094999802;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU316";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -46.324653726730091 
		75 -46.324653726730091;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1579";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.57064561357996657 
		21 -0.52100949013208575 37 -0.63975978302811276 56 -0.47709077732306426 75 -0.57064561357996657;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1580";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.15080888743424148 
		21 0.13502279998345307 37 0.34383333001516536 56 0.05779612928127191 75 0.15080888743424148;
	setAttr -s 6 ".kit[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  3 10 10 10 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1581";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.059702696751835142 
		75 0.059702696751835142;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1582";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.14494110819200023 
		25 -0.2162198759405474 41 -0.14077568323978787 58 -0.11315889906433847 75 -0.14494110819200023;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.74219566583633423 0.66666662693023682 
		0.53333330154418945 0.56666666269302368 0.74219566583633423;
	setAttr -s 6 ".kiy[1:5]"  -0.040034454315900803 0.0023141249548643827 
		0 0 -0.040034454315900803;
	setAttr -s 6 ".kox[1:5]"  0.742195725440979 0.53333336114883423 0.56666666269302368 
		0.56666666269302368 0.742195725440979;
	setAttr -s 6 ".koy[1:5]"  -0.040034454315900803 0.0018513000104576349 
		0 0 -0.040034454315900803;
createNode animCurveTL -n "animCurveTL1583";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.14758619382949767 
		25 0.27200676847942412 41 0.14026171006725288 58 0.10157602714933193 75 0.14758619382949767;
	setAttr -s 6 ".kit[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kot[1:5]"  1 10 10 10 1;
	setAttr -s 6 ".kix[1:5]"  0.7476685643196106 0.66666662693023682 
		0.53333330154418945 0.56666666269302368 0.7476685643196106;
	setAttr -s 6 ".kiy[1:5]"  0.035338524729013443 -0.0040691574104130268 
		0 0 0.035338524729013443;
	setAttr -s 6 ".kox[1:5]"  0.74463886022567749 0.53333336114883423 
		0.56666666269302368 0.56666666269302368 0.74463886022567749;
	setAttr -s 6 ".koy[1:5]"  0.03801419585943222 -0.0032553260680288076 
		0 0 0.03801419585943222;
createNode animCurveTL -n "animCurveTL1584";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.020144614464553082 
		75 0.020144614464553082;
	setAttr -s 3 ".kit[1:2]"  1 10;
	setAttr -s 3 ".kot[1:2]"  1 10;
	setAttr -s 3 ".kix[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".kiy[1:2]"  0 0;
	setAttr -s 3 ".kox[1:2]"  2.3333332538604736 2.3333332538604736;
	setAttr -s 3 ".koy[1:2]"  0 0;
createNode animCurveTL -n "animCurveTL1585";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.013576770094999815 
		25 -0.011281454329259545 56 0.043748999875672809 75 0.013576770094999815;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.094559080898761749 0.66666668653488159 
		1.0333333015441895 0.51385498046875;
	setAttr -s 5 ".kiy[1:4]"  -0.0055267522111535072 0 0 -0.028103776276111603;
	setAttr -s 5 ".kox[1:4]"  0.32150089740753174 1.0333333015441895 
		0.63333332538604736 0.50333112478256226;
	setAttr -s 5 ".koy[1:4]"  -0.018790958449244499 0 0 -0.028410937637090683;
createNode animCurveTL -n "animCurveTL1586";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.013576770094999554 
		25 0.05728747506329418 56 -0.039478082563404397 75 0.013576770094999554;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.10687332600355148 0.66666668653488159 
		1.0333333015441895 0.68392932415008545;
	setAttr -s 5 ".kiy[1:4]"  0.0097247082740068436 0 -0.027100637555122375 
		0.066732004284858704;
	setAttr -s 5 ".kox[1:4]"  0.36336901783943176 1.0333333015441895 
		0.63333332538604736 0.67585295438766479;
	setAttr -s 5 ".koy[1:4]"  0.033063985407352448 0 -0.016610067337751389 
		0.067206099629402161;
createNode animCurveTL -n "animCurveTL1587";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.055788857664020947 
		75 0.055788857664020947;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1588";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.0058610271982182383 
		75 -0.0058610271982182383;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1589";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.10170477615444184 
		75 -0.10170477615444184;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1590";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.013576770094999802 
		75 0.013576770094999802;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTU -n "animCurveTU317";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 27.093091216551862 
		75 27.093091216551862;
	setAttr -s 3 ".kit[1:2]"  3 1;
	setAttr -s 3 ".kot[1:2]"  3 1;
	setAttr -s 3 ".kix[2]"  0.1666666716337204;
	setAttr -s 3 ".kiy[2]"  0;
	setAttr -s 3 ".kox[2]"  2.3333332538604736;
	setAttr -s 3 ".koy[2]"  0;
createNode animCurveTL -n "animCurveTL1591";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.33408683261697342 
		18 -0.28207213777878692 36 -0.44975895071940686 55 -0.22005469940529462 75 -0.33408683261697342;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1592";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 -0.020842048615490053 
		18 -0.023565366774611504 36 0.14843212811092307 55 -0.087177071739726705 75 -0.020842048615490053;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1593";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  0 0.013576770094999802 5 0.057512075304308283 
		18 0.057531233377676301 36 0.056321260677605491 55 0.058078246021937445 75 0.057512075304308283;
	setAttr -s 6 ".kit[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  10 3 9 9 9 1;
	setAttr -s 6 ".kix[5]"  0.1666666716337204;
	setAttr -s 6 ".kiy[5]"  0;
	setAttr -s 6 ".kox[5]"  0.46666666865348816;
	setAttr -s 6 ".koy[5]"  0;
createNode animCurveTL -n "animCurveTL1594";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.018510340429774126 
		27 -0.22773186907196202 48 -0.059395104494579791 75 0.018510340429774126;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.10004256665706635 0.7333332896232605 
		0.70000004768371582 0.62424367666244507;
	setAttr -s 5 ".kiy[1:4]"  -0.010298918932676315 -0.039858598262071609 
		0.10773096978664398 -0.046448275446891785;
	setAttr -s 5 ".kox[1:4]"  0.34014460444450378 0.69999998807907104 
		0.89999997615814209 0.62424379587173462;
	setAttr -s 5 ".koy[1:4]"  -0.035016324371099472 -0.038046844303607941 
		0.13851124048233032 -0.046448271721601486;
createNode animCurveTL -n "animCurveTL1595";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.052985225929652643 
		27 0.099405158523836912 48 -0.038517035662705916 75 0.052985225929652643;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.11504138261079788 0.73333334922790527 
		0.70000004768371582 0.61676084995269775;
	setAttr -s 5 ".kiy[1:4]"  0.0093172378838062286 0 -0.0203087218105793 
		0.047041140496730804;
	setAttr -s 5 ".kox[1:4]"  0.39114096760749817 0.69999998807907104 
		0.89999997615814209 0.61676108837127686;
	setAttr -s 5 ".koy[1:4]"  0.031678631901741028 0 -0.026111211627721786 
		0.047041174024343491;
createNode animCurveTL -n "animCurveTL1596";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.01206023611272608 
		27 0.011733679896221346 48 0.012703938735227453 75 0.01206023611272608;
	setAttr -s 5 ".kit[1:4]"  3 10 10 10;
	setAttr -s 5 ".kot[1:4]"  3 10 10 10;
createNode animCurveTL -n "animCurveTL1597";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 -0.080491817485025013 
		27 -0.11559401662415804 48 -0.037885732667507853 75 -0.080491817485025013;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.14225687086582184 0.73333334922790527 
		0.69999998807907104 0.75069952011108398;
	setAttr -s 5 ".kiy[1:4]"  -0.01282070204615593 0 0 -0.063940577208995819;
	setAttr -s 5 ".kox[1:4]"  0.48367351293563843 0.69999998807907104 
		0.89999997615814209 0.75069969892501831;
	setAttr -s 5 ".koy[1:4]"  -0.043590400367975235 0 0 -0.063940577208995819;
createNode animCurveTL -n "animCurveTL1598";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.050162053747418479 
		27 0.086166616127895973 48 0.0064607052216483583 75 0.050162053747418479;
	setAttr -s 5 ".kit[1:4]"  1 10 10 1;
	setAttr -s 5 ".kot[1:4]"  1 10 10 1;
	setAttr -s 5 ".kix[1:4]"  0.1416056901216507 0.73333334922790527 
		0.69999998807907104 0.746623694896698;
	setAttr -s 5 ".kiy[1:4]"  0.01297687366604805 0 0 0.064972460269927979;
	setAttr -s 5 ".kox[1:4]"  0.48145967721939087 0.69999998807907104 
		0.89999997615814209 0.74662381410598755;
	setAttr -s 5 ".koy[1:4]"  0.044121392071247101 0 0 0.064972460269927979;
createNode animCurveTL -n "animCurveTL1599";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.013576770094999802 5 0.029105211490964945 
		27 0.028851925606845734 48 0.029412642937612754 75 0.029105211490964945;
	setAttr -s 5 ".kit[1:4]"  3 10 10 3;
	setAttr -s 5 ".kot[1:4]"  3 10 10 3;
createNode animCurveTL -n "animCurveTL1600";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 -0.01925644952848642 
		75 -0.01925644952848642;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1601";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.062543420447158785 
		75 0.062543420447158785;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTL -n "animCurveTL1602";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.013576770094999802 5 0.068464475962444954 
		75 0.068464475962444954;
	setAttr -s 3 ".kit[1:2]"  3 10;
	setAttr -s 3 ".kot[1:2]"  3 10;
createNode animCurveTA -n "animCurveTA2134";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -30.164742809703778 16 -29.21260580023403 
		27 -40.074349423995322 42 -35.735527948767938 54 -28.273815732703167 63 -34.943136460856891 
		75 -30.164742809703778;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2135";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -14.521278207252417 16 -21.271475652700971 
		27 -22.425825308724171 42 -34.932550004477633 54 -27.292539845542493 63 -31.82240374591629 
		75 -14.521278207252417;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2136";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 44.87161589080538 16 46.021383857095387 
		27 43.804685317460468 42 47.137565337550477 54 31.797480085005724 63 49.579296017952018 
		75 44.87161589080538;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2137";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -66.042678305735649 16 -74.618347444256798 
		32 -55.397996782876795 46 -67.439137431311337 60 -53.743660579621817 75 -66.042678305735649;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kix[0:5]"  0.16442614793777466 0.36666664481163025 
		0.53333330154418945 0.46666663885116577 0.46666666865348816 0.22653079032897949;
	setAttr -s 6 ".kiy[0:5]"  -0.10117824375629425 0.075690075755119324 
		0.066827118396759033 0.014436806552112103 0.011766184121370316 -0.13760975003242493;
	setAttr -s 6 ".kox[0:5]"  0.16442617774009705 0.53333336114883423 
		0.46666672825813293 0.46666666865348816 0.49999997019767761 0.22653086483478546;
	setAttr -s 6 ".koy[0:5]"  -0.10117827355861664 0.11009466648101807 
		0.058473736047744751 0.014436807483434677 0.012606625445187092 -0.13760977983474731;
createNode animCurveTA -n "animCurveTA2138";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -49.873736051942593 16 -52.262430668059693 
		32 -43.4965196163621 46 -47.75415777929836 60 -43.847582672305037 75 -49.873736051942593;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kix[0:5]"  0.22228723764419556 0.36666664481163025 
		0.53333330154418945 0.46666663885116577 0.46666666865348816 0.33208602666854858;
	setAttr -s 6 ".kiy[0:5]"  -0.041232418268918991 0.045345835387706757 
		0.041964907199144363 -0.0030636030714958906 -0.017858989536762238 -0.05285341665148735;
	setAttr -s 6 ".kox[0:5]"  0.22228726744651794 0.53333336114883423 
		0.46666672825813293 0.46666666865348816 0.49999997019767761 0.33208602666854858;
	setAttr -s 6 ".koy[0:5]"  -0.04123242199420929 0.065957590937614441 
		0.036719299852848053 -0.0030636033043265343 -0.019134629517793655 -0.052853412926197052;
createNode animCurveTA -n "animCurveTA2139";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 12.976305997172423 16 13.244649104566335 
		32 2.2351297643136689 46 11.268275349393763 60 3.4431765776179235 75 12.976305997172423;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kix[0:5]"  0.28764417767524719 0.36666664481163025 
		0.53333330154418945 0.46666663885116577 0.46666666865348816 0.38134199380874634;
	setAttr -s 6 ".kiy[0:5]"  0.039751976728439331 -0.076376207172870636 
		-0.018396919593214989 0.010542197152972221 0.014391401782631874 0.056534316390752792;
	setAttr -s 6 ".kox[0:5]"  0.28764417767524719 0.53333336114883423 
		0.46666672825813293 0.46666666865348816 0.49999997019767761 0.38134202361106873;
	setAttr -s 6 ".koy[0:5]"  0.039751973003149033 -0.11109267920255661 
		-0.016097309067845345 0.010542197152972221 0.01541935745626688 0.056534308940172195;
createNode animCurveTA -n "animCurveTA2140";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -38.477777703166133 22 -48.42820802629695 
		39 -37.152372267782042 51 -47.166188388443111 64 -37.531031582498159 75 -38.477777703166133;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kix[0:5]"  0.3953595757484436 0.56666666269302368 
		0.56666660308837891 0.3999999463558197 0.43333321809768677 0.24980145692825317;
	setAttr -s 6 ".kiy[0:5]"  -0.069135546684265137 0.011566344648599625 
		0.012912025675177574 -0.0031722483690828085 0.082139059901237488 -0.045710761100053787;
	setAttr -s 6 ".kox[0:5]"  0.39535966515541077 0.56666666269302368 
		0.40000003576278687 0.43333339691162109 0.3666667640209198 0.24980141222476959;
	setAttr -s 6 ".koy[0:5]"  -0.069135554134845734 0.01156634371727705 
		0.009114372543990612 -0.0034366033505648375 0.069502316415309906 -0.045710761100053787;
createNode animCurveTA -n "animCurveTA2141";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -14.228737501636873 22 -29.900270228025018 
		39 -20.934999007033653 51 -23.135502654727855 64 -16.845440091007688 75 -14.228737501636873;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2142";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 -0.8334547948398221 22 0.078488242113804549 
		39 -17.614036772963399 51 -8.7939837523471152 64 -9.6720563927375789 75 -0.8334547948398221;
	setAttr -s 6 ".kit[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kot[0:5]"  1 9 9 9 9 1;
	setAttr -s 6 ".kix[0:5]"  0.49176332354545593 0.56666666269302368 
		0.56666660308837891 0.3999999463558197 0.43333321809768677 0.31627532839775085;
	setAttr -s 6 ".kiy[0:5]"  0.083658955991268158 -0.14643821120262146 
		-0.090776391327381134 0.066534571349620819 0.075257763266563416 0.055118896067142487;
	setAttr -s 6 ".kox[0:5]"  0.49176326394081116 0.56666666269302368 
		0.40000003576278687 0.43333339691162109 0.3666667640209198 0.31627532839775085;
	setAttr -s 6 ".koy[0:5]"  0.083658948540687561 -0.14643819630146027 
		-0.064077459275722504 0.072079136967658997 0.063679680228233337 0.055118899792432785;
createNode animCurveTA -n "animCurveTA2143";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 15.323045069792654 16 18.116609823834811 
		31 12.689024352752126 45 21.784140681376041 56 20.822850518079399 65 23.475072389361603 
		75 15.323045069792654;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2144";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 0.28055051621514404 16 -4.9572072220448371 
		31 3.2816519454592235 45 1.3981011811028934 56 3.0560894912237417 65 -2.1383368659147388 
		75 0.28055051621514404;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2145";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 24.992666599224822 16 34.474085460477212 
		31 24.705961746343231 45 28.844954020962962 56 18.445425410277387 65 24.435727555789175 
		75 24.992666599224822;
	setAttr -s 7 ".kit[0:6]"  3 9 9 9 9 9 3;
	setAttr -s 7 ".kot[0:6]"  3 9 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2146";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 0 27 14.444237644034366 54 4.5960422995015353 
		75 0;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.78169083595275879 0.69999998807907104;
	setAttr -s 4 ".kiy[2:3]"  -0.14893516898155212 0;
	setAttr -s 4 ".kox[2:3]"  0.71503150463104248 0.69999998807907104;
	setAttr -s 4 ".koy[2:3]"  -0.1362345963716507 0;
createNode animCurveTA -n "animCurveTA2147";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2148";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2149";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 0 26 -11.101372218639389 53 -2.1516005337984749 
		75 0;
	setAttr -s 4 ".kit[1:3]"  10 1 3;
	setAttr -s 4 ".kot[1:3]"  10 1 3;
	setAttr -s 4 ".kix[2:3]"  0.68839520215988159 0.73333334922790527;
	setAttr -s 4 ".kiy[2:3]"  0.067027933895587921 0;
	setAttr -s 4 ".kox[2:3]"  0.62173676490783691 0.73333334922790527;
	setAttr -s 4 ".koy[2:3]"  0.060537498444318771 0;
createNode animCurveTA -n "animCurveTA2150";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2151";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2152";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 9.1161768348442394 36 -3.7242807581592716 
		48 15.454868067231155 60 -2.1351031028026077 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2153";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 4.6484884577755956 36 3.4569246980572159 
		48 3.9504927721941914 60 -0.15937559902642134 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2154";
	setAttr ".tan" 9;
	setAttr -s 6 ".ktv[0:5]"  5 0 19 -7.1919152223577747 36 3.702730876190707 
		48 -14.122357930801913 60 3.470190763848306 75 0;
	setAttr -s 6 ".kit[0:5]"  3 9 9 9 9 3;
	setAttr -s 6 ".kot[0:5]"  3 9 9 9 9 3;
createNode animCurveTA -n "animCurveTA2155";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0 31 -1.6110042271906411 42 4.330246594095355 
		52 3.4237714025027 64 2.8896621079781615 75 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA2156";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0 31 -3.1431780090303731 42 -1.3326648261373377 
		52 0.32238901567071898 64 0.56897490393608174 75 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA2157";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0 31 -29.596750832936589 42 -23.1260622225535 
		52 1.9847552338789385 64 -18.887067903720045 75 0;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU318";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 25 17 25 21 25 36 25 54 -0.5 69 24.527405247813412 
		75 25;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kix[5:6]"  0.48637977242469788 0.20000000298023224;
	setAttr -s 7 ".kiy[5:6]"  2.9233603477478027 0;
	setAttr -s 7 ".kox[5:6]"  0.19455190002918243 0.20000000298023224;
	setAttr -s 7 ".koy[5:6]"  1.1693439483642578 0;
createNode animCurveTU -n "animCurveTU319";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 22.5 17 22.5 21 22.5 31 22.5 45 7.2999999999999989 
		60 29.900000023841859 75 22.5;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 3 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 3 3;
createNode animCurveTA -n "animCurveTA2158";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  5 0 17 12.878941089279156 25 -3.4011240037133836 
		36 -22.700778088468756 75 0;
	setAttr -s 5 ".kit[1:4]"  10 1 3 1;
	setAttr -s 5 ".kot[1:4]"  10 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.15170289576053619 0.40000000596046448 
		0.098429188132286072 0.36666667461395264 0.59054857492446899;
	setAttr -s 5 ".kiy[0:4]"  0.10998626053333282 -0.035616487264633179 
		-0.15977996587753296 0 0.52456694841384888;
	setAttr -s 5 ".kox[0:4]"  0.15170283615589142 0.26666665077209473 
		0.19809551537036896 1.2999999523162842 0.54602593183517456;
	setAttr -s 5 ".koy[0:4]"  0.10998624563217163 -0.023744324222207069 
		-0.32156816124916077 0 0.49640035629272461;
createNode animCurveTA -n "animCurveTA2159";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2160";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU320";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 10.8 17 10.8 21 10.8 36 10.8 54 -14.7 
		69 10.327405247813413 75 10.8;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kix[5:6]"  0.48637977242469788 0.20000000298023224;
	setAttr -s 7 ".kiy[5:6]"  2.9233603477478027 0;
	setAttr -s 7 ".kox[5:6]"  0.19455190002918243 0.20000000298023224;
	setAttr -s 7 ".koy[5:6]"  1.1693439483642578 0;
createNode animCurveTU -n "animCurveTU321";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 10.8 17 10.8 21 10.8 31 10.8 45 -4.4 
		60 18.200000023841859 75 10.8;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 3 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 3 3;
createNode animCurveTA -n "animCurveTA2161";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  5 0 17 12.878941089279156 25 -3.4011240037133836 
		36 -22.700778088468756 75 0;
	setAttr -s 5 ".kit[1:4]"  10 1 3 1;
	setAttr -s 5 ".kot[1:4]"  10 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.15170289576053619 0.40000000596046448 
		0.098429188132286072 0.36666667461395264 0.59054857492446899;
	setAttr -s 5 ".kiy[0:4]"  0.10998626053333282 -0.035616487264633179 
		-0.15977996587753296 0 0.52456694841384888;
	setAttr -s 5 ".kox[0:4]"  0.15170283615589142 0.26666665077209473 
		0.19809551537036896 1.2999999523162842 0.54602593183517456;
	setAttr -s 5 ".koy[0:4]"  0.10998624563217163 -0.023744324222207069 
		-0.32156816124916077 0 0.49640035629272461;
createNode animCurveTA -n "animCurveTA2162";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2163";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU322";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 16 75 16;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU323";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 27.200000000000003 75 27.200000000000003;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2164";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  5 17.789214279319701 20 22.079306624146149 
		43 0.11177097995472449 62 17.011809003346212 75 17.789214279319701;
	setAttr -s 5 ".kit[2:4]"  10 1 3;
	setAttr -s 5 ".kot[2:4]"  10 1 3;
	setAttr -s 5 ".kix[3:4]"  0.60584664344787598 0.43333333730697632;
	setAttr -s 5 ".kiy[3:4]"  0.053743723779916763 0;
	setAttr -s 5 ".kox[3:4]"  0.40585091710090637 0.43333333730697632;
	setAttr -s 5 ".koy[3:4]"  0.036002408713102341 0;
createNode animCurveTA -n "animCurveTA2165";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  5 10.130109474165437 20 14.641960458211846 
		43 12.804640489207651 62 18.384290337370441 75 10.130109474165437;
	setAttr -s 5 ".kit[1:4]"  1 10 3 3;
	setAttr -s 5 ".kot[1:4]"  1 10 3 3;
	setAttr -s 5 ".kix[1:4]"  0.48887354135513306 0.76666665077209473 
		0.63333332538604736 0.43333333730697632;
	setAttr -s 5 ".kiy[1:4]"  0.006998143158853054 0 0 0;
	setAttr -s 5 ".kox[1:4]"  0.75553900003433228 0.63333332538604736 
		0.43333333730697632 0.43333333730697632;
	setAttr -s 5 ".koy[1:4]"  0.010815414600074291 0 0 0;
createNode animCurveTA -n "animCurveTA2166";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 13.246789911944141 75 13.246789911944141;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU324";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 29.8 17 29.8 21 29.8 36 29.8 54 4.3000000000000007 
		69 29.327405247813413 75 29.8;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 1 3;
	setAttr -s 7 ".kix[5:6]"  0.48637977242469788 0.20000000298023224;
	setAttr -s 7 ".kiy[5:6]"  2.9233603477478027 0;
	setAttr -s 7 ".kox[5:6]"  0.19455190002918243 0.20000000298023224;
	setAttr -s 7 ".koy[5:6]"  1.1693439483642578 0;
createNode animCurveTU -n "animCurveTU325";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 21.5 17 21.5 21 21.5 31 21.5 45 6.2999999999999989 
		60 28.900000023841859 75 21.5;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 3 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 3 3;
createNode animCurveTA -n "animCurveTA2167";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  5 0 17 12.878941089279156 25 -3.4011240037133836 
		36 -22.700778088468756 75 0;
	setAttr -s 5 ".kit[1:4]"  10 1 3 1;
	setAttr -s 5 ".kot[1:4]"  10 1 3 1;
	setAttr -s 5 ".kix[0:4]"  0.15170289576053619 0.40000000596046448 
		0.098429188132286072 0.36666667461395264 0.59054857492446899;
	setAttr -s 5 ".kiy[0:4]"  0.10998626053333282 -0.035616487264633179 
		-0.15977996587753296 0 0.52456694841384888;
	setAttr -s 5 ".kox[0:4]"  0.15170283615589142 0.26666665077209473 
		0.19809551537036896 1.2999999523162842 0.54602593183517456;
	setAttr -s 5 ".koy[0:4]"  0.10998624563217163 -0.023744324222207069 
		-0.32156816124916077 0 0.49640035629272461;
createNode animCurveTA -n "animCurveTA2168";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2169";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2170";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 20 -3.2766059880659721 38 0.9399501788155773 
		55 2.8976017782268917 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2171";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 20 1.7442643323515752 38 12.281786809398657 
		55 0.03087009857328046 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2172";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 20 -6.1959171026168942 38 -3.7113401936827839 
		55 8.7787946975736197 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTU -n "animCurveTU326";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 20.1 37 20.1 57 14.531083086053412 75 
		20.1;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTU -n "animCurveTU327";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 40.000000000000007 34 40.000000000000007 
		50 20.704005934718115 75 40.000000000000007;
	setAttr -s 4 ".kit[1:3]"  10 3 3;
	setAttr -s 4 ".kot[1:3]"  10 3 3;
createNode animCurveTA -n "animCurveTA2173";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -17.938181840568774 23 -24.497423477883853 
		47 4.7680833400546563 75 -17.938181840568774;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTA -n "animCurveTA2174";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2175";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU328";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 11.800000000000002 37 11.800000000000002 
		57 6.035608308605342 75 11.800000000000002;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTU -n "animCurveTU329";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 11.400000000000004 34 11.400000000000004 
		50 3 75 11.400000000000004;
	setAttr -s 4 ".kit[1:3]"  10 3 3;
	setAttr -s 4 ".kot[1:3]"  10 3 3;
createNode animCurveTA -n "animCurveTA2176";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -17.938181840568774 23 -24.497423477883853 
		47 4.7680833400546563 75 -17.938181840568774;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTA -n "animCurveTA2177";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2178";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU330";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 44.7 37 44.7 57 31.02685459940653 75 
		44.7;
	setAttr -s 4 ".kit[0:3]"  3 10 10 3;
	setAttr -s 4 ".kot[0:3]"  3 10 10 3;
createNode animCurveTU -n "animCurveTU331";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 35.1 34 35.1 50 16.57344213649851 75 
		35.1;
	setAttr -s 4 ".kit[1:3]"  10 3 3;
	setAttr -s 4 ".kot[1:3]"  10 3 3;
createNode animCurveTA -n "animCurveTA2179";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -17.938181840568774 23 -24.497423477883853 
		47 4.7680833400546563 75 -17.938181840568774;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTA -n "animCurveTA2180";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2181";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU332";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 24.1 75 24.1;
createNode animCurveTU -n "animCurveTU333";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 21.6 75 21.6;
createNode animCurveTA -n "animCurveTA2182";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 -2.3059144880021574 38 4.9742007443143077 
		63 -10.198617260849437 75 -2.3059144880021574;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.44395384192466736 1.1000000238418579 
		0.83333331346511841 0.13639159500598907;
	setAttr -s 4 ".kiy[0:3]"  0.16621984541416168 0 0 0.062103919684886932;
	setAttr -s 4 ".kox[0:3]"  0.44395384192466736 0.83333331346511841 
		0.40000000596046448 0.13639160990715027;
	setAttr -s 4 ".koy[0:3]"  0.1662198007106781 0 0 0.062103927135467529;
createNode animCurveTA -n "animCurveTA2183";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 -9.1916713300485959 18 -6.1091654186371214 
		63 -15.982568295357087 75 -9.1916713300485959;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.12077292799949646 0.43333333730697632 
		1.5 0.12839232385158539;
	setAttr -s 4 ".kiy[0:3]"  0.041723936796188354 0 0 0.037981379777193069;
	setAttr -s 4 ".kox[0:3]"  0.12077297270298004 1.5 0.40000000596046448 
		0.12839232385158539;
	setAttr -s 4 ".koy[0:3]"  0.041723910719156265 0 0 0.037981390953063965;
createNode animCurveTA -n "animCurveTA2184";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -8.7462661409704392 75 -8.7462661409704392;
createNode animCurveTA -n "animCurveTA2185";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -21.149833133508892 75 -21.149833133508892;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2186";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  -3 1.9381528662420378 67 1.9381528662420378;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2187";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2188";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  5 29.569979583084404 39 32.0853920839848 
		75 29.569979583084404;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTA -n "animCurveTA2189";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  -8 -19.795127588534079 62 -19.795127588534079;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2190";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -1.0564521039725223 75 -1.0564521039725223;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA2191";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 0.15593118024036831 44 10.427145716163604 
		61 -15.989502031396567 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2192";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 0.00048960529148431883 44 -16.035520515586686 
		61 -1.2199669501126016 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2193";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 8.1446839584627693 44 -20.206057004474001 
		61 13.044241508400066 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2194";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 -6.6049498729397209 43 26.607864197864405 
		62 3.2913411024761654 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2195";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 9.0910623530106847 43 -20.592979898799197 
		62 28.064690502780888 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTA -n "animCurveTA2196";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0 24 -6.9500307247337947 43 20.638759240723871 
		62 4.2275205882769278 75 0;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "Global_translateY1";
	setAttr ".tan" 2;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  5 0 75 6.6331021911689332;
createNode lightLinker -n "lightLinker1";
	setAttr -s 6 ".lnk";
	setAttr -s 10 ".slnk";
select -ne :time1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -l on ".o" 6;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 6 ".st";
select -ne :renderGlobalsList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultShaderList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 6 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr -k on ".esr";
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr -l on ".bfs";
	setAttr -l on ".mb";
	setAttr -k on ".mbf";
	setAttr -l on ".afp";
	setAttr -k on ".frts";
select -ne :defaultLightSet;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	addAttr -ci true -sn "ani" -ln "animation" -bt "ANIM" -min 0 -max 1 -at "bool";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
	setAttr ".enpt" no;
	setAttr ".hgcd" no;
	setAttr ".hgci" no;
	setAttr -k on ".ani";
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
	setAttr -s 5 ".sol";
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA1951.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA1952.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA1953.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA1954.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA1955.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA1956.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA1957.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA1958.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA1959.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA1960.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA1961.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA1962.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA1963.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA1964.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA1965.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA1966.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA1967.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA1968.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA1969.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA1970.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA1971.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA1972.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA1973.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA1974.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA1975.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA1976.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA1977.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA1978.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA1979.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA1980.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA1981.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA1982.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA1983.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA1984.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA1985.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA1986.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA1987.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA1988.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA1989.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA1990.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA1991.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA1992.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA1993.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA1994.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA1995.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTU297.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTU298.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA1996.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA1997.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA1998.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTL1423.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTL1424.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL1425.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTU299.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTU300.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA1999.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA2000.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA2001.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL1426.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTL1427.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL1428.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTU301.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTU302.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTA2002.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA2003.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA2004.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTL1429.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTL1430.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTL1431.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA2005.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA2006.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA2007.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA2008.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA2009.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA2010.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTU303.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL1432.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL1433.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTL1434.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTU304.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTU305.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL1435.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL1436.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL1437.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTL1438.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTL1439.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTL1440.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL1441.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL1442.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTL1443.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTL1444.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTL1445.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTL1446.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTL1447.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTL1448.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL1449.a" "clipLibrary1.cel[0].cev[95].cevr";
connectAttr "animCurveTU306.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTA2011.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTA2012.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTA2013.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL1450.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL1451.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTL1452.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTU307.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA2014.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA2015.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA2016.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTL1453.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTL1454.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTL1455.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA2017.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA2018.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTA2019.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTL1456.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTL1457.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr "animCurveTL1458.a" "clipLibrary1.cel[0].cev[115].cevr";
connectAttr "animCurveTA2020.a" "clipLibrary1.cel[0].cev[116].cevr";
connectAttr "animCurveTA2021.a" "clipLibrary1.cel[0].cev[117].cevr";
connectAttr "animCurveTA2022.a" "clipLibrary1.cel[0].cev[118].cevr";
connectAttr "animCurveTL1459.a" "clipLibrary1.cel[0].cev[119].cevr";
connectAttr "animCurveTL1460.a" "clipLibrary1.cel[0].cev[120].cevr";
connectAttr "animCurveTL1461.a" "clipLibrary1.cel[0].cev[121].cevr";
connectAttr "animCurveTA2023.a" "clipLibrary1.cel[0].cev[122].cevr";
connectAttr "animCurveTA2024.a" "clipLibrary1.cel[0].cev[123].cevr";
connectAttr "animCurveTA2025.a" "clipLibrary1.cel[0].cev[124].cevr";
connectAttr "animCurveTL1462.a" "clipLibrary1.cel[0].cev[125].cevr";
connectAttr "animCurveTL1463.a" "clipLibrary1.cel[0].cev[126].cevr";
connectAttr "animCurveTL1464.a" "clipLibrary1.cel[0].cev[127].cevr";
connectAttr "animCurveTA2026.a" "clipLibrary1.cel[0].cev[128].cevr";
connectAttr "animCurveTA2027.a" "clipLibrary1.cel[0].cev[129].cevr";
connectAttr "animCurveTA2028.a" "clipLibrary1.cel[0].cev[130].cevr";
connectAttr "animCurveTA2029.a" "clipLibrary1.cel[0].cev[131].cevr";
connectAttr "animCurveTA2030.a" "clipLibrary1.cel[0].cev[132].cevr";
connectAttr "animCurveTA2031.a" "clipLibrary1.cel[0].cev[133].cevr";
connectAttr "animCurveTA2032.a" "clipLibrary1.cel[0].cev[134].cevr";
connectAttr "animCurveTA2033.a" "clipLibrary1.cel[0].cev[135].cevr";
connectAttr "animCurveTA2034.a" "clipLibrary1.cel[0].cev[136].cevr";
connectAttr "animCurveTA2035.a" "clipLibrary1.cel[0].cev[137].cevr";
connectAttr "animCurveTA2036.a" "clipLibrary1.cel[0].cev[138].cevr";
connectAttr "animCurveTA2037.a" "clipLibrary1.cel[0].cev[139].cevr";
connectAttr "animCurveTA2038.a" "clipLibrary1.cel[0].cev[140].cevr";
connectAttr "animCurveTA2039.a" "clipLibrary1.cel[0].cev[141].cevr";
connectAttr "animCurveTA2040.a" "clipLibrary1.cel[0].cev[142].cevr";
connectAttr "animCurveTA2041.a" "clipLibrary1.cel[0].cev[143].cevr";
connectAttr "animCurveTA2042.a" "clipLibrary1.cel[0].cev[144].cevr";
connectAttr "animCurveTA2043.a" "clipLibrary1.cel[0].cev[145].cevr";
connectAttr "animCurveTA2044.a" "clipLibrary1.cel[0].cev[146].cevr";
connectAttr "animCurveTA2045.a" "clipLibrary1.cel[0].cev[147].cevr";
connectAttr "animCurveTA2046.a" "clipLibrary1.cel[0].cev[148].cevr";
connectAttr "animCurveTA2047.a" "clipLibrary1.cel[0].cev[149].cevr";
connectAttr "animCurveTA2048.a" "clipLibrary1.cel[0].cev[150].cevr";
connectAttr "animCurveTA2049.a" "clipLibrary1.cel[0].cev[151].cevr";
connectAttr "animCurveTA2050.a" "clipLibrary1.cel[0].cev[152].cevr";
connectAttr "animCurveTA2051.a" "clipLibrary1.cel[0].cev[153].cevr";
connectAttr "animCurveTA2052.a" "clipLibrary1.cel[0].cev[154].cevr";
connectAttr "animCurveTA2053.a" "clipLibrary1.cel[0].cev[155].cevr";
connectAttr "animCurveTA2054.a" "clipLibrary1.cel[0].cev[156].cevr";
connectAttr "animCurveTA2055.a" "clipLibrary1.cel[0].cev[157].cevr";
connectAttr "animCurveTA2056.a" "clipLibrary1.cel[0].cev[158].cevr";
connectAttr "animCurveTA2057.a" "clipLibrary1.cel[0].cev[159].cevr";
connectAttr "animCurveTA2058.a" "clipLibrary1.cel[0].cev[160].cevr";
connectAttr "animCurveTA2059.a" "clipLibrary1.cel[0].cev[161].cevr";
connectAttr "animCurveTA2060.a" "clipLibrary1.cel[0].cev[162].cevr";
connectAttr "animCurveTA2061.a" "clipLibrary1.cel[0].cev[163].cevr";
connectAttr "animCurveTA2062.a" "clipLibrary1.cel[0].cev[164].cevr";
connectAttr "animCurveTA2063.a" "clipLibrary1.cel[0].cev[165].cevr";
connectAttr "animCurveTA2064.a" "clipLibrary1.cel[0].cev[166].cevr";
connectAttr "animCurveTA2065.a" "clipLibrary1.cel[0].cev[167].cevr";
connectAttr "animCurveTA2066.a" "clipLibrary1.cel[0].cev[168].cevr";
connectAttr "animCurveTA2067.a" "clipLibrary1.cel[0].cev[169].cevr";
connectAttr "animCurveTA2068.a" "clipLibrary1.cel[0].cev[170].cevr";
connectAttr "animCurveTA2069.a" "clipLibrary1.cel[0].cev[171].cevr";
connectAttr "animCurveTA2070.a" "clipLibrary1.cel[0].cev[172].cevr";
connectAttr "animCurveTA2071.a" "clipLibrary1.cel[0].cev[173].cevr";
connectAttr "animCurveTA2072.a" "clipLibrary1.cel[0].cev[174].cevr";
connectAttr "animCurveTA2073.a" "clipLibrary1.cel[0].cev[175].cevr";
connectAttr "animCurveTA2074.a" "clipLibrary1.cel[0].cev[176].cevr";
connectAttr "animCurveTA2075.a" "clipLibrary1.cel[0].cev[177].cevr";
connectAttr "animCurveTA2076.a" "clipLibrary1.cel[0].cev[178].cevr";
connectAttr "animCurveTA2077.a" "clipLibrary1.cel[0].cev[179].cevr";
connectAttr "animCurveTA2078.a" "clipLibrary1.cel[0].cev[180].cevr";
connectAttr "animCurveTA2079.a" "clipLibrary1.cel[0].cev[181].cevr";
connectAttr "animCurveTA2080.a" "clipLibrary1.cel[0].cev[182].cevr";
connectAttr "animCurveTA2081.a" "clipLibrary1.cel[0].cev[183].cevr";
connectAttr "animCurveTA2082.a" "clipLibrary1.cel[0].cev[184].cevr";
connectAttr "animCurveTA2083.a" "clipLibrary1.cel[0].cev[185].cevr";
connectAttr "animCurveTA2084.a" "clipLibrary1.cel[0].cev[186].cevr";
connectAttr "animCurveTA2085.a" "clipLibrary1.cel[0].cev[187].cevr";
connectAttr "animCurveTA2086.a" "clipLibrary1.cel[0].cev[188].cevr";
connectAttr "animCurveTA2087.a" "clipLibrary1.cel[0].cev[189].cevr";
connectAttr "animCurveTA2088.a" "clipLibrary1.cel[0].cev[190].cevr";
connectAttr "animCurveTA2089.a" "clipLibrary1.cel[0].cev[191].cevr";
connectAttr "animCurveTA2090.a" "clipLibrary1.cel[0].cev[192].cevr";
connectAttr "animCurveTA2091.a" "clipLibrary1.cel[0].cev[193].cevr";
connectAttr "animCurveTA2092.a" "clipLibrary1.cel[0].cev[194].cevr";
connectAttr "animCurveTA2093.a" "clipLibrary1.cel[0].cev[195].cevr";
connectAttr "animCurveTA2094.a" "clipLibrary1.cel[0].cev[196].cevr";
connectAttr "animCurveTA2095.a" "clipLibrary1.cel[0].cev[197].cevr";
connectAttr "animCurveTA2096.a" "clipLibrary1.cel[0].cev[198].cevr";
connectAttr "animCurveTA2097.a" "clipLibrary1.cel[0].cev[199].cevr";
connectAttr "animCurveTA2098.a" "clipLibrary1.cel[0].cev[200].cevr";
connectAttr "animCurveTA2099.a" "clipLibrary1.cel[0].cev[201].cevr";
connectAttr "animCurveTA2100.a" "clipLibrary1.cel[0].cev[202].cevr";
connectAttr "animCurveTA2101.a" "clipLibrary1.cel[0].cev[203].cevr";
connectAttr "animCurveTA2102.a" "clipLibrary1.cel[0].cev[204].cevr";
connectAttr "animCurveTA2103.a" "clipLibrary1.cel[0].cev[205].cevr";
connectAttr "animCurveTA2104.a" "clipLibrary1.cel[0].cev[206].cevr";
connectAttr "animCurveTA2105.a" "clipLibrary1.cel[0].cev[207].cevr";
connectAttr "animCurveTA2106.a" "clipLibrary1.cel[0].cev[208].cevr";
connectAttr "animCurveTA2107.a" "clipLibrary1.cel[0].cev[209].cevr";
connectAttr "animCurveTA2108.a" "clipLibrary1.cel[0].cev[210].cevr";
connectAttr "animCurveTA2109.a" "clipLibrary1.cel[0].cev[211].cevr";
connectAttr "animCurveTA2110.a" "clipLibrary1.cel[0].cev[212].cevr";
connectAttr "animCurveTA2111.a" "clipLibrary1.cel[0].cev[213].cevr";
connectAttr "animCurveTA2112.a" "clipLibrary1.cel[0].cev[214].cevr";
connectAttr "animCurveTL1465.a" "clipLibrary1.cel[0].cev[215].cevr";
connectAttr "animCurveTL1466.a" "clipLibrary1.cel[0].cev[216].cevr";
connectAttr "animCurveTL1467.a" "clipLibrary1.cel[0].cev[217].cevr";
connectAttr "animCurveTL1468.a" "clipLibrary1.cel[0].cev[218].cevr";
connectAttr "animCurveTL1469.a" "clipLibrary1.cel[0].cev[219].cevr";
connectAttr "animCurveTL1470.a" "clipLibrary1.cel[0].cev[220].cevr";
connectAttr "animCurveTU308.a" "clipLibrary1.cel[0].cev[221].cevr";
connectAttr "animCurveTL1471.a" "clipLibrary1.cel[0].cev[222].cevr";
connectAttr "animCurveTL1472.a" "clipLibrary1.cel[0].cev[223].cevr";
connectAttr "animCurveTL1473.a" "clipLibrary1.cel[0].cev[224].cevr";
connectAttr "animCurveTL1474.a" "clipLibrary1.cel[0].cev[225].cevr";
connectAttr "animCurveTL1475.a" "clipLibrary1.cel[0].cev[226].cevr";
connectAttr "animCurveTL1476.a" "clipLibrary1.cel[0].cev[227].cevr";
connectAttr "animCurveTL1477.a" "clipLibrary1.cel[0].cev[228].cevr";
connectAttr "animCurveTL1478.a" "clipLibrary1.cel[0].cev[229].cevr";
connectAttr "animCurveTL1479.a" "clipLibrary1.cel[0].cev[230].cevr";
connectAttr "animCurveTL1480.a" "clipLibrary1.cel[0].cev[231].cevr";
connectAttr "animCurveTL1481.a" "clipLibrary1.cel[0].cev[232].cevr";
connectAttr "animCurveTL1482.a" "clipLibrary1.cel[0].cev[233].cevr";
connectAttr "animCurveTL1483.a" "clipLibrary1.cel[0].cev[234].cevr";
connectAttr "animCurveTL1484.a" "clipLibrary1.cel[0].cev[235].cevr";
connectAttr "animCurveTL1485.a" "clipLibrary1.cel[0].cev[236].cevr";
connectAttr "animCurveTL1486.a" "clipLibrary1.cel[0].cev[237].cevr";
connectAttr "animCurveTL1487.a" "clipLibrary1.cel[0].cev[238].cevr";
connectAttr "animCurveTL1488.a" "clipLibrary1.cel[0].cev[239].cevr";
connectAttr "animCurveTU309.a" "clipLibrary1.cel[0].cev[240].cevr";
connectAttr "animCurveTL1489.a" "clipLibrary1.cel[0].cev[241].cevr";
connectAttr "animCurveTL1490.a" "clipLibrary1.cel[0].cev[242].cevr";
connectAttr "animCurveTL1491.a" "clipLibrary1.cel[0].cev[243].cevr";
connectAttr "animCurveTL1492.a" "clipLibrary1.cel[0].cev[244].cevr";
connectAttr "animCurveTL1493.a" "clipLibrary1.cel[0].cev[245].cevr";
connectAttr "animCurveTL1494.a" "clipLibrary1.cel[0].cev[246].cevr";
connectAttr "animCurveTA2113.a" "clipLibrary1.cel[0].cev[247].cevr";
connectAttr "animCurveTA2114.a" "clipLibrary1.cel[0].cev[248].cevr";
connectAttr "animCurveTA2115.a" "clipLibrary1.cel[0].cev[249].cevr";
connectAttr "animCurveTA2116.a" "clipLibrary1.cel[0].cev[250].cevr";
connectAttr "animCurveTA2117.a" "clipLibrary1.cel[0].cev[251].cevr";
connectAttr "animCurveTA2118.a" "clipLibrary1.cel[0].cev[252].cevr";
connectAttr "animCurveTA2119.a" "clipLibrary1.cel[0].cev[253].cevr";
connectAttr "animCurveTA2120.a" "clipLibrary1.cel[0].cev[254].cevr";
connectAttr "animCurveTA2121.a" "clipLibrary1.cel[0].cev[255].cevr";
connectAttr "animCurveTA2122.a" "clipLibrary1.cel[0].cev[256].cevr";
connectAttr "animCurveTA2123.a" "clipLibrary1.cel[0].cev[257].cevr";
connectAttr "animCurveTA2124.a" "clipLibrary1.cel[0].cev[258].cevr";
connectAttr "animCurveTA2125.a" "clipLibrary1.cel[0].cev[259].cevr";
connectAttr "animCurveTA2126.a" "clipLibrary1.cel[0].cev[260].cevr";
connectAttr "animCurveTA2127.a" "clipLibrary1.cel[0].cev[261].cevr";
connectAttr "animCurveTA2128.a" "clipLibrary1.cel[0].cev[262].cevr";
connectAttr "animCurveTA2129.a" "clipLibrary1.cel[0].cev[263].cevr";
connectAttr "animCurveTA2130.a" "clipLibrary1.cel[0].cev[264].cevr";
connectAttr "animCurveTA2131.a" "clipLibrary1.cel[0].cev[265].cevr";
connectAttr "animCurveTA2132.a" "clipLibrary1.cel[0].cev[266].cevr";
connectAttr "animCurveTA2133.a" "clipLibrary1.cel[0].cev[267].cevr";
connectAttr "animCurveTU310.a" "clipLibrary1.cel[0].cev[268].cevr";
connectAttr "animCurveTL1495.a" "clipLibrary1.cel[0].cev[269].cevr";
connectAttr "animCurveTL1496.a" "clipLibrary1.cel[0].cev[270].cevr";
connectAttr "animCurveTL1497.a" "clipLibrary1.cel[0].cev[271].cevr";
connectAttr "animCurveTL1498.a" "clipLibrary1.cel[0].cev[272].cevr";
connectAttr "animCurveTL1499.a" "clipLibrary1.cel[0].cev[273].cevr";
connectAttr "animCurveTL1500.a" "clipLibrary1.cel[0].cev[274].cevr";
connectAttr "animCurveTL1501.a" "clipLibrary1.cel[0].cev[275].cevr";
connectAttr "animCurveTL1502.a" "clipLibrary1.cel[0].cev[276].cevr";
connectAttr "animCurveTL1503.a" "clipLibrary1.cel[0].cev[277].cevr";
connectAttr "animCurveTL1504.a" "clipLibrary1.cel[0].cev[278].cevr";
connectAttr "animCurveTL1505.a" "clipLibrary1.cel[0].cev[279].cevr";
connectAttr "animCurveTL1506.a" "clipLibrary1.cel[0].cev[280].cevr";
connectAttr "animCurveTL1507.a" "clipLibrary1.cel[0].cev[281].cevr";
connectAttr "animCurveTL1508.a" "clipLibrary1.cel[0].cev[282].cevr";
connectAttr "animCurveTL1509.a" "clipLibrary1.cel[0].cev[283].cevr";
connectAttr "animCurveTU311.a" "clipLibrary1.cel[0].cev[284].cevr";
connectAttr "animCurveTL1510.a" "clipLibrary1.cel[0].cev[285].cevr";
connectAttr "animCurveTL1511.a" "clipLibrary1.cel[0].cev[286].cevr";
connectAttr "animCurveTL1512.a" "clipLibrary1.cel[0].cev[287].cevr";
connectAttr "animCurveTL1513.a" "clipLibrary1.cel[0].cev[288].cevr";
connectAttr "animCurveTL1514.a" "clipLibrary1.cel[0].cev[289].cevr";
connectAttr "animCurveTL1515.a" "clipLibrary1.cel[0].cev[290].cevr";
connectAttr "animCurveTL1516.a" "clipLibrary1.cel[0].cev[291].cevr";
connectAttr "animCurveTL1517.a" "clipLibrary1.cel[0].cev[292].cevr";
connectAttr "animCurveTL1518.a" "clipLibrary1.cel[0].cev[293].cevr";
connectAttr "animCurveTL1519.a" "clipLibrary1.cel[0].cev[294].cevr";
connectAttr "animCurveTL1520.a" "clipLibrary1.cel[0].cev[295].cevr";
connectAttr "animCurveTL1521.a" "clipLibrary1.cel[0].cev[296].cevr";
connectAttr "animCurveTL1522.a" "clipLibrary1.cel[0].cev[297].cevr";
connectAttr "animCurveTL1523.a" "clipLibrary1.cel[0].cev[298].cevr";
connectAttr "animCurveTL1524.a" "clipLibrary1.cel[0].cev[299].cevr";
connectAttr "animCurveTL1525.a" "clipLibrary1.cel[0].cev[300].cevr";
connectAttr "animCurveTL1526.a" "clipLibrary1.cel[0].cev[301].cevr";
connectAttr "animCurveTL1527.a" "clipLibrary1.cel[0].cev[302].cevr";
connectAttr "animCurveTL1528.a" "clipLibrary1.cel[0].cev[303].cevr";
connectAttr "animCurveTL1529.a" "clipLibrary1.cel[0].cev[304].cevr";
connectAttr "animCurveTL1530.a" "clipLibrary1.cel[0].cev[305].cevr";
connectAttr "animCurveTL1531.a" "clipLibrary1.cel[0].cev[306].cevr";
connectAttr "animCurveTL1532.a" "clipLibrary1.cel[0].cev[307].cevr";
connectAttr "animCurveTL1533.a" "clipLibrary1.cel[0].cev[308].cevr";
connectAttr "animCurveTL1534.a" "clipLibrary1.cel[0].cev[309].cevr";
connectAttr "animCurveTL1535.a" "clipLibrary1.cel[0].cev[310].cevr";
connectAttr "animCurveTL1536.a" "clipLibrary1.cel[0].cev[311].cevr";
connectAttr "animCurveTU312.a" "clipLibrary1.cel[0].cev[312].cevr";
connectAttr "animCurveTL1537.a" "clipLibrary1.cel[0].cev[313].cevr";
connectAttr "animCurveTL1538.a" "clipLibrary1.cel[0].cev[314].cevr";
connectAttr "animCurveTL1539.a" "clipLibrary1.cel[0].cev[315].cevr";
connectAttr "animCurveTU313.a" "clipLibrary1.cel[0].cev[316].cevr";
connectAttr "animCurveTL1540.a" "clipLibrary1.cel[0].cev[317].cevr";
connectAttr "animCurveTL1541.a" "clipLibrary1.cel[0].cev[318].cevr";
connectAttr "animCurveTL1542.a" "clipLibrary1.cel[0].cev[319].cevr";
connectAttr "animCurveTL1543.a" "clipLibrary1.cel[0].cev[320].cevr";
connectAttr "animCurveTL1544.a" "clipLibrary1.cel[0].cev[321].cevr";
connectAttr "animCurveTL1545.a" "clipLibrary1.cel[0].cev[322].cevr";
connectAttr "animCurveTL1546.a" "clipLibrary1.cel[0].cev[323].cevr";
connectAttr "animCurveTL1547.a" "clipLibrary1.cel[0].cev[324].cevr";
connectAttr "animCurveTL1548.a" "clipLibrary1.cel[0].cev[325].cevr";
connectAttr "animCurveTL1549.a" "clipLibrary1.cel[0].cev[326].cevr";
connectAttr "animCurveTL1550.a" "clipLibrary1.cel[0].cev[327].cevr";
connectAttr "animCurveTL1551.a" "clipLibrary1.cel[0].cev[328].cevr";
connectAttr "animCurveTL1552.a" "clipLibrary1.cel[0].cev[329].cevr";
connectAttr "animCurveTL1553.a" "clipLibrary1.cel[0].cev[330].cevr";
connectAttr "animCurveTL1554.a" "clipLibrary1.cel[0].cev[331].cevr";
connectAttr "animCurveTU314.a" "clipLibrary1.cel[0].cev[332].cevr";
connectAttr "animCurveTL1555.a" "clipLibrary1.cel[0].cev[333].cevr";
connectAttr "animCurveTL1556.a" "clipLibrary1.cel[0].cev[334].cevr";
connectAttr "animCurveTL1557.a" "clipLibrary1.cel[0].cev[335].cevr";
connectAttr "animCurveTL1558.a" "clipLibrary1.cel[0].cev[336].cevr";
connectAttr "animCurveTL1559.a" "clipLibrary1.cel[0].cev[337].cevr";
connectAttr "animCurveTL1560.a" "clipLibrary1.cel[0].cev[338].cevr";
connectAttr "animCurveTL1561.a" "clipLibrary1.cel[0].cev[339].cevr";
connectAttr "animCurveTL1562.a" "clipLibrary1.cel[0].cev[340].cevr";
connectAttr "animCurveTL1563.a" "clipLibrary1.cel[0].cev[341].cevr";
connectAttr "animCurveTL1564.a" "clipLibrary1.cel[0].cev[342].cevr";
connectAttr "animCurveTL1565.a" "clipLibrary1.cel[0].cev[343].cevr";
connectAttr "animCurveTL1566.a" "clipLibrary1.cel[0].cev[344].cevr";
connectAttr "animCurveTU315.a" "clipLibrary1.cel[0].cev[345].cevr";
connectAttr "animCurveTL1567.a" "clipLibrary1.cel[0].cev[346].cevr";
connectAttr "animCurveTL1568.a" "clipLibrary1.cel[0].cev[347].cevr";
connectAttr "animCurveTL1569.a" "clipLibrary1.cel[0].cev[348].cevr";
connectAttr "animCurveTL1570.a" "clipLibrary1.cel[0].cev[349].cevr";
connectAttr "animCurveTL1571.a" "clipLibrary1.cel[0].cev[350].cevr";
connectAttr "animCurveTL1572.a" "clipLibrary1.cel[0].cev[351].cevr";
connectAttr "animCurveTL1573.a" "clipLibrary1.cel[0].cev[352].cevr";
connectAttr "animCurveTL1574.a" "clipLibrary1.cel[0].cev[353].cevr";
connectAttr "animCurveTL1575.a" "clipLibrary1.cel[0].cev[354].cevr";
connectAttr "animCurveTL1576.a" "clipLibrary1.cel[0].cev[355].cevr";
connectAttr "animCurveTL1577.a" "clipLibrary1.cel[0].cev[356].cevr";
connectAttr "animCurveTL1578.a" "clipLibrary1.cel[0].cev[357].cevr";
connectAttr "animCurveTU316.a" "clipLibrary1.cel[0].cev[358].cevr";
connectAttr "animCurveTL1579.a" "clipLibrary1.cel[0].cev[359].cevr";
connectAttr "animCurveTL1580.a" "clipLibrary1.cel[0].cev[360].cevr";
connectAttr "animCurveTL1581.a" "clipLibrary1.cel[0].cev[361].cevr";
connectAttr "animCurveTL1582.a" "clipLibrary1.cel[0].cev[362].cevr";
connectAttr "animCurveTL1583.a" "clipLibrary1.cel[0].cev[363].cevr";
connectAttr "animCurveTL1584.a" "clipLibrary1.cel[0].cev[364].cevr";
connectAttr "animCurveTL1585.a" "clipLibrary1.cel[0].cev[365].cevr";
connectAttr "animCurveTL1586.a" "clipLibrary1.cel[0].cev[366].cevr";
connectAttr "animCurveTL1587.a" "clipLibrary1.cel[0].cev[367].cevr";
connectAttr "animCurveTL1588.a" "clipLibrary1.cel[0].cev[368].cevr";
connectAttr "animCurveTL1589.a" "clipLibrary1.cel[0].cev[369].cevr";
connectAttr "animCurveTL1590.a" "clipLibrary1.cel[0].cev[370].cevr";
connectAttr "animCurveTU317.a" "clipLibrary1.cel[0].cev[371].cevr";
connectAttr "animCurveTL1591.a" "clipLibrary1.cel[0].cev[372].cevr";
connectAttr "animCurveTL1592.a" "clipLibrary1.cel[0].cev[373].cevr";
connectAttr "animCurveTL1593.a" "clipLibrary1.cel[0].cev[374].cevr";
connectAttr "animCurveTL1594.a" "clipLibrary1.cel[0].cev[375].cevr";
connectAttr "animCurveTL1595.a" "clipLibrary1.cel[0].cev[376].cevr";
connectAttr "animCurveTL1596.a" "clipLibrary1.cel[0].cev[377].cevr";
connectAttr "animCurveTL1597.a" "clipLibrary1.cel[0].cev[378].cevr";
connectAttr "animCurveTL1598.a" "clipLibrary1.cel[0].cev[379].cevr";
connectAttr "animCurveTL1599.a" "clipLibrary1.cel[0].cev[380].cevr";
connectAttr "animCurveTL1600.a" "clipLibrary1.cel[0].cev[381].cevr";
connectAttr "animCurveTL1601.a" "clipLibrary1.cel[0].cev[382].cevr";
connectAttr "animCurveTL1602.a" "clipLibrary1.cel[0].cev[383].cevr";
connectAttr "animCurveTA2134.a" "clipLibrary1.cel[0].cev[384].cevr";
connectAttr "animCurveTA2135.a" "clipLibrary1.cel[0].cev[385].cevr";
connectAttr "animCurveTA2136.a" "clipLibrary1.cel[0].cev[386].cevr";
connectAttr "animCurveTA2137.a" "clipLibrary1.cel[0].cev[387].cevr";
connectAttr "animCurveTA2138.a" "clipLibrary1.cel[0].cev[388].cevr";
connectAttr "animCurveTA2139.a" "clipLibrary1.cel[0].cev[389].cevr";
connectAttr "animCurveTA2140.a" "clipLibrary1.cel[0].cev[390].cevr";
connectAttr "animCurveTA2141.a" "clipLibrary1.cel[0].cev[391].cevr";
connectAttr "animCurveTA2142.a" "clipLibrary1.cel[0].cev[392].cevr";
connectAttr "animCurveTA2143.a" "clipLibrary1.cel[0].cev[393].cevr";
connectAttr "animCurveTA2144.a" "clipLibrary1.cel[0].cev[394].cevr";
connectAttr "animCurveTA2145.a" "clipLibrary1.cel[0].cev[395].cevr";
connectAttr "animCurveTA2146.a" "clipLibrary1.cel[0].cev[396].cevr";
connectAttr "animCurveTA2147.a" "clipLibrary1.cel[0].cev[397].cevr";
connectAttr "animCurveTA2148.a" "clipLibrary1.cel[0].cev[398].cevr";
connectAttr "animCurveTA2149.a" "clipLibrary1.cel[0].cev[399].cevr";
connectAttr "animCurveTA2150.a" "clipLibrary1.cel[0].cev[400].cevr";
connectAttr "animCurveTA2151.a" "clipLibrary1.cel[0].cev[401].cevr";
connectAttr "animCurveTA2152.a" "clipLibrary1.cel[0].cev[402].cevr";
connectAttr "animCurveTA2153.a" "clipLibrary1.cel[0].cev[403].cevr";
connectAttr "animCurveTA2154.a" "clipLibrary1.cel[0].cev[404].cevr";
connectAttr "animCurveTA2155.a" "clipLibrary1.cel[0].cev[405].cevr";
connectAttr "animCurveTA2156.a" "clipLibrary1.cel[0].cev[406].cevr";
connectAttr "animCurveTA2157.a" "clipLibrary1.cel[0].cev[407].cevr";
connectAttr "animCurveTU318.a" "clipLibrary1.cel[0].cev[408].cevr";
connectAttr "animCurveTU319.a" "clipLibrary1.cel[0].cev[409].cevr";
connectAttr "animCurveTA2158.a" "clipLibrary1.cel[0].cev[410].cevr";
connectAttr "animCurveTA2159.a" "clipLibrary1.cel[0].cev[411].cevr";
connectAttr "animCurveTA2160.a" "clipLibrary1.cel[0].cev[412].cevr";
connectAttr "animCurveTU320.a" "clipLibrary1.cel[0].cev[413].cevr";
connectAttr "animCurveTU321.a" "clipLibrary1.cel[0].cev[414].cevr";
connectAttr "animCurveTA2161.a" "clipLibrary1.cel[0].cev[415].cevr";
connectAttr "animCurveTA2162.a" "clipLibrary1.cel[0].cev[416].cevr";
connectAttr "animCurveTA2163.a" "clipLibrary1.cel[0].cev[417].cevr";
connectAttr "animCurveTU322.a" "clipLibrary1.cel[0].cev[418].cevr";
connectAttr "animCurveTU323.a" "clipLibrary1.cel[0].cev[419].cevr";
connectAttr "animCurveTA2164.a" "clipLibrary1.cel[0].cev[420].cevr";
connectAttr "animCurveTA2165.a" "clipLibrary1.cel[0].cev[421].cevr";
connectAttr "animCurveTA2166.a" "clipLibrary1.cel[0].cev[422].cevr";
connectAttr "animCurveTU324.a" "clipLibrary1.cel[0].cev[423].cevr";
connectAttr "animCurveTU325.a" "clipLibrary1.cel[0].cev[424].cevr";
connectAttr "animCurveTA2167.a" "clipLibrary1.cel[0].cev[425].cevr";
connectAttr "animCurveTA2168.a" "clipLibrary1.cel[0].cev[426].cevr";
connectAttr "animCurveTA2169.a" "clipLibrary1.cel[0].cev[427].cevr";
connectAttr "animCurveTA2170.a" "clipLibrary1.cel[0].cev[428].cevr";
connectAttr "animCurveTA2171.a" "clipLibrary1.cel[0].cev[429].cevr";
connectAttr "animCurveTA2172.a" "clipLibrary1.cel[0].cev[430].cevr";
connectAttr "animCurveTU326.a" "clipLibrary1.cel[0].cev[431].cevr";
connectAttr "animCurveTU327.a" "clipLibrary1.cel[0].cev[432].cevr";
connectAttr "animCurveTA2173.a" "clipLibrary1.cel[0].cev[433].cevr";
connectAttr "animCurveTA2174.a" "clipLibrary1.cel[0].cev[434].cevr";
connectAttr "animCurveTA2175.a" "clipLibrary1.cel[0].cev[435].cevr";
connectAttr "animCurveTU328.a" "clipLibrary1.cel[0].cev[436].cevr";
connectAttr "animCurveTU329.a" "clipLibrary1.cel[0].cev[437].cevr";
connectAttr "animCurveTA2176.a" "clipLibrary1.cel[0].cev[438].cevr";
connectAttr "animCurveTA2177.a" "clipLibrary1.cel[0].cev[439].cevr";
connectAttr "animCurveTA2178.a" "clipLibrary1.cel[0].cev[440].cevr";
connectAttr "animCurveTU330.a" "clipLibrary1.cel[0].cev[441].cevr";
connectAttr "animCurveTU331.a" "clipLibrary1.cel[0].cev[442].cevr";
connectAttr "animCurveTA2179.a" "clipLibrary1.cel[0].cev[443].cevr";
connectAttr "animCurveTA2180.a" "clipLibrary1.cel[0].cev[444].cevr";
connectAttr "animCurveTA2181.a" "clipLibrary1.cel[0].cev[445].cevr";
connectAttr "animCurveTU332.a" "clipLibrary1.cel[0].cev[446].cevr";
connectAttr "animCurveTU333.a" "clipLibrary1.cel[0].cev[447].cevr";
connectAttr "animCurveTA2182.a" "clipLibrary1.cel[0].cev[448].cevr";
connectAttr "animCurveTA2183.a" "clipLibrary1.cel[0].cev[449].cevr";
connectAttr "animCurveTA2184.a" "clipLibrary1.cel[0].cev[450].cevr";
connectAttr "animCurveTA2185.a" "clipLibrary1.cel[0].cev[451].cevr";
connectAttr "animCurveTA2186.a" "clipLibrary1.cel[0].cev[452].cevr";
connectAttr "animCurveTA2187.a" "clipLibrary1.cel[0].cev[453].cevr";
connectAttr "animCurveTA2188.a" "clipLibrary1.cel[0].cev[454].cevr";
connectAttr "animCurveTA2189.a" "clipLibrary1.cel[0].cev[455].cevr";
connectAttr "animCurveTA2190.a" "clipLibrary1.cel[0].cev[456].cevr";
connectAttr "animCurveTA2191.a" "clipLibrary1.cel[0].cev[457].cevr";
connectAttr "animCurveTA2192.a" "clipLibrary1.cel[0].cev[458].cevr";
connectAttr "animCurveTA2193.a" "clipLibrary1.cel[0].cev[459].cevr";
connectAttr "animCurveTA2194.a" "clipLibrary1.cel[0].cev[460].cevr";
connectAttr "animCurveTA2195.a" "clipLibrary1.cel[0].cev[461].cevr";
connectAttr "animCurveTA2196.a" "clipLibrary1.cel[0].cev[462].cevr";
connectAttr "Global_translateY1.a" "clipLibrary1.cel[0].cev[464].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[3].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[5].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[5].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of move.ma
