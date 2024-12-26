//Maya ASCII 2008 scene
//Name: skinPose.ma
//Last modified: Fri, Nov 13, 2009 11:42:40 AM
//Codeset: 1251
requires maya "2008";
requires "Mayatomr" "9.0.1.4m - 3.6.51.0 ";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 89 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 89 "left_thumb_c_CTRL.rotateZ" 
		2 1 "left_thumb_c_CTRL.rotateY" 2 2 "left_thumb_c_CTRL.rotateX" 
		2 3 "left_thumb_a_CTRL.rotateZ" 2 4 "left_thumb_a_CTRL.rotateY" 
		2 5 "left_thumb_a_CTRL.rotateX" 2 6 "left_middle_c_CTRL.rotateZ" 
		2 7 "left_middle_c_CTRL.rotateY" 2 8 "left_middle_c_CTRL.rotateX" 
		2 9 "left_middle_a_CTRL.rotateZ" 2 10 "left_middle_a_CTRL.rotateY" 
		2 11 "left_middle_a_CTRL.rotateX" 2 12 "left_hand_CTRL.rotateZ" 
		2 13 "left_wrist_CTRL.rotateZ" 2 14 "left_wrist_CTRL.rotateY" 2 
		15 "left_wrist_CTRL.rotateX" 2 16 "left_shoulder_plumage_in_c_CTRL.rotateZ" 
		2 17 "left_shoulder_plumage_in_c_CTRL.rotateY" 2 18 "left_shoulder_plumage_in_c_CTRL.rotateX" 
		2 19 "left_shoulder_plumage_in_b_CTRL.rotateZ" 2 20 "left_shoulder_plumage_in_b_CTRL.rotateY" 
		2 21 "left_shoulder_plumage_in_b_CTRL.rotateX" 2 22 "left_shoulder_plumage_in_a_CTRL.rotateZ" 
		2 23 "left_shoulder_plumage_in_a_CTRL.rotateY" 2 24 "left_shoulder_plumage_in_a_CTRL.rotateX" 
		2 25 "left_ancle_CTRL.rotateZ" 2 26 "left_ancle_CTRL.rotateY" 2 
		27 "left_ancle_CTRL.rotateX" 2 28 "left_clavicle_CTRL.rotateZ" 2 
		29 "left_clavicle_CTRL.rotateY" 2 30 "left_clavicle_CTRL.rotateX" 2 
		31 "tail_d_CTRL.rotateZ" 2 32 "tail_d_CTRL.rotateY" 2 33 "tail_d_CTRL.rotateX" 
		2 34 "tail_c_CTRL.rotateZ" 2 35 "tail_c_CTRL.rotateY" 2 36 "tail_c_CTRL.rotateX" 
		2 37 "tail_b_CTRL.rotateZ" 2 38 "tail_b_CTRL.rotateY" 2 39 "tail_b_CTRL.rotateX" 
		2 40 "tail_a_CTRL.rotateZ" 2 41 "tail_a_CTRL.rotateY" 2 42 "tail_a_CTRL.rotateX" 
		2 43 "neckplum_CTRL.rotateZ" 2 44 "neckplum_CTRL.rotateY" 2 
		45 "neckplum_CTRL.rotateX" 2 46 "head_CTRL.rotateZ" 2 47 "head_CTRL.rotateY" 
		2 48 "head_CTRL.rotateX" 2 49 "spine_CTRL.rotateZ" 2 50 "spine_CTRL.rotateY" 
		2 51 "spine_CTRL.rotateX" 2 52 "right_shoulder_plumage_in_c_CTRL.rotateZ" 
		2 53 "right_shoulder_plumage_in_c_CTRL.rotateY" 2 54 "right_shoulder_plumage_in_c_CTRL.rotateX" 
		2 55 "right_shoulder_plumage_in_b_CTRL.rotateZ" 2 56 "right_shoulder_plumage_in_b_CTRL.rotateY" 
		2 57 "right_shoulder_plumage_in_b_CTRL.rotateX" 2 58 "right_shoulder_plumage_in_a_CTRL.rotateZ" 
		2 59 "right_shoulder_plumage_in_a_CTRL.rotateY" 2 60 "right_shoulder_plumage_in_a_CTRL.rotateX" 
		2 61 "right_middle_c_CTRL.rotateZ" 2 62 "right_middle_c_CTRL.rotateY" 
		2 63 "right_middle_c_CTRL.rotateX" 2 64 "right_middle_a_CTRL.rotateZ" 
		2 65 "right_middle_a_CTRL.rotateY" 2 66 "right_middle_a_CTRL.rotateX" 
		2 67 "right_thumb_c_CTRL.rotateZ" 2 68 "right_thumb_c_CTRL.rotateY" 
		2 69 "right_thumb_c_CTRL.rotateX" 2 70 "right_thumb_a_CTRL.rotateZ" 
		2 71 "right_thumb_a_CTRL.rotateY" 2 72 "right_thumb_a_CTRL.rotateX" 
		2 73 "right_hand_CTRL.rotateZ" 2 74 "right_wrist_CTRL.rotateZ" 
		2 75 "right_wrist_CTRL.rotateY" 2 76 "right_wrist_CTRL.rotateX" 
		2 77 "right_ancle_CTRL.rotateZ" 2 78 "right_ancle_CTRL.rotateY" 
		2 79 "right_ancle_CTRL.rotateX" 2 80 "right_clavicle_CTRL.rotateZ" 
		2 81 "right_clavicle_CTRL.rotateY" 2 82 "right_clavicle_CTRL.rotateX" 
		2 83 "ROOT_CTRL.rotateZ" 2 84 "ROOT_CTRL.rotateY" 2 85 "ROOT_CTRL.rotateX" 
		2 86 "ROOT_CTRL.translateZ" 1 1 "ROOT_CTRL.translateY" 1 
		2 "ROOT_CTRL.translateX" 1 3  ;
	setAttr ".cd[0].cim" -type "Int32Array" 89 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88 ;
createNode animClip -n "skinPoseSource";
	setAttr ".ihi" 0;
	setAttr -s 89 ".ac[0:88]" yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no;
	setAttr ".se" 1;
	setAttr ".ci" no;
createNode animCurveTA -n "bird_left_thumb_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_thumb_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_thumb_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_thumb_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_thumb_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_thumb_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_middle_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_hand_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_wrist_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_wrist_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_wrist_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_b_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_b_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_b_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_shoulder_plumage_in_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_ancle_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_ancle_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_ancle_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_clavicle_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_clavicle_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_left_clavicle_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_d_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_d_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_d_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_b_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_b_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_b_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_tail_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_neckplum_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_neckplum_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_neckplum_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_head_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_head_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_head_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_spine_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_spine_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_spine_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_b_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_b_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_b_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_shoulder_plumage_in_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_middle_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_c_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_c_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_c_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_a_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_a_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_thumb_a_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_hand_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_wrist_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_wrist_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_wrist_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_ancle_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_ancle_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_ancle_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_clavicle_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_clavicle_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_right_clavicle_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_ROOT_CTRL_rotateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_ROOT_CTRL_rotateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTA -n "bird_ROOT_CTRL_rotateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTL -n "bird_ROOT_CTRL_translateZ1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTL -n "bird_ROOT_CTRL_translateY1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode animCurveTL -n "bird_ROOT_CTRL_translateX1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 1 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
createNode lightLinker -n "_:lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
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
	setAttr -s 7 ".st";
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
	setAttr -s 7 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 3 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".ln";
select -ne :defaultTextureList1;
	setAttr -s 4 ".tx";
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
	setAttr ".hwfr" 30;
select -ne :characterPartition;
	setAttr -s 2 ".st";
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
connectAttr "skinPoseSource.cl" "clipLibrary1.sc[0]";
connectAttr "bird_left_thumb_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "bird_left_thumb_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[1].cevr"
		;
connectAttr "bird_left_thumb_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[2].cevr"
		;
connectAttr "bird_left_thumb_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[3].cevr"
		;
connectAttr "bird_left_thumb_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "bird_left_thumb_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "bird_left_middle_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "bird_left_middle_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "bird_left_middle_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "bird_left_middle_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "bird_left_middle_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "bird_left_middle_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "bird_left_hand_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "bird_left_wrist_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[13].cevr"
		;
connectAttr "bird_left_wrist_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[14].cevr"
		;
connectAttr "bird_left_wrist_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[15].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_b_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_b_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[20].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_b_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[21].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[22].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[23].cevr"
		;
connectAttr "bird_left_shoulder_plumage_in_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[24].cevr"
		;
connectAttr "bird_left_ancle_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[25].cevr"
		;
connectAttr "bird_left_ancle_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[26].cevr"
		;
connectAttr "bird_left_ancle_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[27].cevr"
		;
connectAttr "bird_left_clavicle_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[28].cevr"
		;
connectAttr "bird_left_clavicle_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[29].cevr"
		;
connectAttr "bird_left_clavicle_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[30].cevr"
		;
connectAttr "bird_tail_d_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "bird_tail_d_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "bird_tail_d_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "bird_tail_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "bird_tail_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "bird_tail_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "bird_tail_b_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "bird_tail_b_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "bird_tail_b_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "bird_tail_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "bird_tail_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "bird_tail_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "bird_neckplum_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "bird_neckplum_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "bird_neckplum_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "bird_head_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "bird_head_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "bird_head_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "bird_spine_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "bird_spine_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "bird_spine_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "bird_right_shoulder_plumage_in_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[52].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[53].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[54].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_b_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[55].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_b_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_b_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[57].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[58].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[59].cevr"
		;
connectAttr "bird_right_shoulder_plumage_in_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[60].cevr"
		;
connectAttr "bird_right_middle_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "bird_right_middle_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "bird_right_middle_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "bird_right_middle_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "bird_right_middle_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "bird_right_middle_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "bird_right_thumb_c_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "bird_right_thumb_c_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "bird_right_thumb_c_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "bird_right_thumb_a_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "bird_right_thumb_a_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "bird_right_thumb_a_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "bird_right_hand_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "bird_right_wrist_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[74].cevr"
		;
connectAttr "bird_right_wrist_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[75].cevr"
		;
connectAttr "bird_right_wrist_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "bird_right_ancle_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "bird_right_ancle_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "bird_right_ancle_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "bird_right_clavicle_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "bird_right_clavicle_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "bird_right_clavicle_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "bird_ROOT_CTRL_rotateZ1.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "bird_ROOT_CTRL_rotateY1.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "bird_ROOT_CTRL_rotateX1.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "bird_ROOT_CTRL_translateZ1.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "bird_ROOT_CTRL_translateY1.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "bird_ROOT_CTRL_translateX1.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "_:lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "_:lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "_:lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "_:lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "_:lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "_:lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "_:lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "_:lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "_:lightLinker1.msg" ":lightList1.ln" -na;
// End of skinPose.ma
