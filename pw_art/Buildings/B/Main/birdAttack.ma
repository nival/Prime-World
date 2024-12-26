//Maya ASCII 2008 scene
//Name: birdAttack.ma
//Last modified: Wed, Jan 20, 2010 03:28:59 PM
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
createNode animClip -n "attackSource1";
	setAttr ".ihi" 0;
	setAttr -s 89 ".ac[0:88]" yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes no no no;
	setAttr ".se" 40;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA4";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA5";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA6";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA7";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 15 0 22 4.6011204078612238 
		29 0 40 0;
createNode animCurveTA -n "animCurveTA8";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 15 0 22 -61.764523031915438 
		29 0 40 0;
createNode animCurveTA -n "animCurveTA9";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 0 6 0 15 0 22 -1.5766246502429704 
		29 0 40 0;
createNode animCurveTA -n "animCurveTA10";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA11";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA12";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA13";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA14";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -34.537441864839487 3 -34.537441864839487 
		5 -23.619252821547658 6 26.151891036974583 9 26.880026566747944 11 14.111062466187539 
		15 4.2411561488610756 25 4.2411561488610756 27 7.0199887826247505 28 -1.0158908922789818 
		30 -7.9541780174311638 31 7.7378647953148816 34 4.2411561488610756 40 4.2411561488610756;
createNode animCurveTA -n "animCurveTA15";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 79.699607651032963 3 79.699607651032963 
		5 44.215924110019998 6 -15.799294385839008 9 -31.097700934680415 11 23.786169904063804 
		15 -14.837642460155786 25 -14.837642460155786 27 -30.582480322407729 28 20.868873819424369 
		30 47.852308774220511 31 -34.753062192562808 34 -14.837642460155786 40 -14.837642460155786;
createNode animCurveTA -n "animCurveTA16";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -46.719951300332205 3 -46.719951300332205 
		5 -44.281241307773797 6 -3.2935699122801405 9 -2.9463763432061616 11 -1.7544779577486507 
		15 -8.3594302701183576 25 -8.3594302701183576 27 -9.7118848049523461 28 -8.6501887800975066 
		30 -13.543870955071649 31 -9.8486818390322082 34 -8.3594302701183576 40 -8.3594302701183576;
createNode animCurveTA -n "animCurveTA17";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 1.9703009966386413 
		29 0 35 4.8749871905549753 40 0;
	setAttr -s 8 ".kit[7]"  3;
	setAttr -s 8 ".kot[7]"  3;
createNode animCurveTA -n "animCurveTA18";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -19.467534862088982 
		29 0 35 -23.65177256329611 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA19";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -8.0651587690197211 
		29 0 35 -9.7113947262771223 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 3 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 3 10 3;
createNode animCurveTA -n "animCurveTA20";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 3.1466557550827878 
		29 0 35 0.87663851017177807 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 3 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 3 10 3;
createNode animCurveTA -n "animCurveTA21";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -16.432166192052669 
		29 0 35 -13.032054940765216 40 0;
	setAttr -s 8 ".kit[0:7]"  10 10 10 3 3 3 3 3;
	setAttr -s 8 ".kot[0:7]"  10 10 10 3 3 3 3 3;
createNode animCurveTA -n "animCurveTA22";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -4.1015693415507055 
		29 0 35 -2.5509144819861524 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 10;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA23";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA24";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA25";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA26";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -18.867798537549554 3 -18.867798537549554 
		6 10.820018226006317 9 7.250659008937637 11 19.800574432207313 15 0 25 0 31 0 34 
		0 40 0;
createNode animCurveTA -n "animCurveTA27";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -41.837997054261116 3 -41.837997054261116 
		6 38.0927952724509 9 36.600155938535657 11 -20.599840995317788 15 0 25 0 27 0.22321834895183237 
		28 -25.535244956014054 31 24.221304060495122 34 0 40 0;
createNode animCurveTA -n "animCurveTA28";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 25.083206998135285 3 25.083206998135285 
		6 8.1624719784956739 9 -26.252596160633043 11 -42.248144861417906 15 0 25 0 31 0 
		34 0 40 0;
createNode animCurveTA -n "animCurveTA29";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 25 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA30";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 25 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA31";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10.039840078321413 3 10.039840078321413 
		6 24.31255607614457 11 -54.248881019105319 15 10.039840078321413 25 10.039840078321413 
		28 -54.602146633559329 31 36.441045904633555 34 10.039840078321413 40 10.039840078321413;
createNode animCurveTA -n "animCurveTA32";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 6 9.0173812602989916 9 6.8003752646451563 
		13 2.4735078332493083 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA33";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -40.036331532764301 3 12.034807447893325 
		6 10.257244297757193 9 20.961177567999115 13 -56.2414244097737 15 -40.036331532764301 
		18 -39.151684237709041 21 3.9065374158026129 28 -40.036331532764301 31 -39.151684237709041 
		34 3.9065374158026129 40 -40.036331532764301;
	setAttr -s 12 ".kit[5:11]"  1 9 10 9 9 10 10;
	setAttr -s 12 ".kot[5:11]"  1 9 10 9 9 10 10;
	setAttr -s 12 ".kix[5:11]"  0.38822174072265625 0.25233525037765503 
		0.99892896413803101 0.40545767545700073 0.25233525037765503 0.99867814779281616 0.25233533978462219;
	setAttr -s 12 ".kiy[5:11]"  -0.92156606912612915 0.96763986349105835 
		-0.046270418912172318 -0.91411375999450684 0.96763986349105835 -0.05139864981174469 
		-0.96763986349105835;
	setAttr -s 12 ".kox[5:11]"  0.38822174072265625 0.25233525037765503 
		0.99892896413803101 0.40545767545700073 0.25233525037765503 0.99867814779281616 0.25233533978462219;
	setAttr -s 12 ".koy[5:11]"  -0.92156600952148438 0.96763986349105835 
		-0.046270418912172318 -0.91411375999450684 0.96763986349105835 -0.05139864981174469 
		-0.96763986349105835;
createNode animCurveTA -n "animCurveTA34";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 3 0 6 -3.0807557882497951 9 -2.7766115934250886 
		13 -1.1926228659202964 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA35";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 2.3239955881394598 9 0.25224979308316026 
		11 1.6695095775190751 13 1.2209660710031947 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA36";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -19.416335164826403 3 19.744831144337773 
		6 7.2614890459487071 9 14.813596061240654 11 -19.698567704993934 13 -32.684321204436479 
		15 -19.416335164826403 18 8.4128480614280878 21 7.0057223064829586 28 -19.416335164826403 
		31 8.4128480614280878 34 7.0057223064829586 40 -19.416335164826403;
	setAttr -s 13 ".kit[6:12]"  3 9 9 3 9 9 3;
	setAttr -s 13 ".kot[6:12]"  3 9 9 3 9 9 3;
createNode animCurveTA -n "animCurveTA37";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 -5.465757215865314 9 -4.2536882349066314 
		11 -2.8618874904321139 13 -1.6021019388034137 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA38";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 -3.2160285214863329 9 -1.6713375429301891 
		11 -2.5204805000786927 13 -1.8786881070583383 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA39";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -12.552883748630155 3 7.8161487752727439 
		6 -25.460474847139913 9 -21.619742771850056 11 -28.397754124863223 13 -29.735720934892065 
		15 0 18 6.7708540275091185 21 -21.01850466100662 28 0 31 6.7708540275091185 34 -21.01850466100662 
		40 0;
	setAttr -s 13 ".kit[6:12]"  9 10 10 10 10 10 10;
	setAttr -s 13 ".kot[6:12]"  9 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA40";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 0 3 0 6 7.6911931186042919 9 6.1900943745636807 
		11 4.1950084261335112 13 2.3343846551813483 15 0 21 0 28 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA41";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 21 0 28 0 31 0 34 0 40 
		0;
createNode animCurveTA -n "animCurveTA42";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 12.11538331107635 3 7.4604300549082438 
		6 -24.226064980914998 11 -28.833569454175166 15 0 18 -7.7287447479087357 21 2.4830749674410115 
		28 0 31 -7.7287447479087357 34 2.4830749674410115 40 0;
	setAttr -s 11 ".kit[6:10]"  9 9 10 9 1;
	setAttr -s 11 ".kot[6:10]"  9 9 10 9 1;
	setAttr -s 11 ".kix[10]"  0.8057364821434021;
	setAttr -s 11 ".kiy[10]"  -0.59227418899536133;
	setAttr -s 11 ".kox[10]"  0.80573660135269165;
	setAttr -s 11 ".koy[10]"  -0.59227412939071655;
createNode animCurveTA -n "animCurveTA43";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 15 0 21 0 28 0 31 0 34 0 40 
		0;
createNode animCurveTA -n "animCurveTA44";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -1.7246092802463264 
		29 0 35 -0.90165092286515613 40 0;
createNode animCurveTA -n "animCurveTA45";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 4.8159986216921036 3 4.8159986216921036 
		6 2.0091632523829359 15 0 22 -7.2106511431797431 29 0 35 -1.2711635476079859 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 10;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA46";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 6.6214915972778634 
		29 0 35 -9.0888163699971205 40 0;
createNode animCurveTA -n "animCurveTA47";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 16.252368930439289 3 16.252368930439289 
		6 2.0797458542697713 9 1.0242365220106628 15 0.035642986213674469 40 0.035642986213674469;
createNode animCurveTA -n "animCurveTA48";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -34.954472857500399 3 -34.954472857500399 
		6 -2.8978087277321114 9 62.50371456722354 15 44.495337353090669 40 44.495337353090669;
createNode animCurveTA -n "animCurveTA49";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.0918801789065153 3 -1.0918801789065153 
		6 -0.53452748681020568 9 -0.93942881139511791 15 0.041834327553186369 40 0.041834327553186369;
createNode animCurveTA -n "animCurveTA50";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0.57898536319157257 3 0.57898536319157257 
		6 0.48656346552278412 9 0.61277476062160607 15 0.54377834360588972 40 0.54377834360588972;
createNode animCurveTA -n "animCurveTA51";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -14.421779022422633 3 -14.421779022422633 
		6 24.092277157806045 9 -23.986044981860939 15 0.00025541155772244536 40 0.00025541155772244536;
createNode animCurveTA -n "animCurveTA52";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -0.1413579818630388 3 -0.1413579818630388 
		6 -0.15180991087992202 9 -0.15190592983405604 15 -0.13690357971903194 40 -0.13690357971903194;
createNode animCurveTA -n "animCurveTA53";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 9.5870432829910328 
		29 0 35 3.78635431538844 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA54";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -26.62358905875994 
		29 0 35 -34.192262430360856 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA55";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -13.254588920463897 
		29 0 35 -3.873489071969499 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 10 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA56";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 1.9878378624717363 
		29 0 35 1.8809837388580815 40 0;
createNode animCurveTA -n "animCurveTA57";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -15.423911471952781 
		29 0 35 -15.75074604530392 40 0;
	setAttr -s 8 ".kit[3:7]"  3 10 3 10 3;
	setAttr -s 8 ".kot[3:7]"  3 10 3 10 3;
createNode animCurveTA -n "animCurveTA58";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -1.6700421114373334 
		29 0 35 -2.3796788864135414 40 0;
createNode animCurveTA -n "animCurveTA59";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA60";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA61";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA62";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA63";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA64";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA65";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -2.7282363870164983 
		29 0 35 -1.4436173701762893 40 0;
createNode animCurveTA -n "animCurveTA66";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -7.7312655795642105 
		29 0 35 -15.503486106239885 40 0;
createNode animCurveTA -n "animCurveTA67";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0 6 0 15 0 22 -0.71631292871938834 
		29 0 35 -2.8749443236170436 40 0;
createNode animCurveTA -n "animCurveTA68";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA69";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA70";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA71";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA72";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA73";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 0 3 0 6 0 15 0 40 0;
createNode animCurveTA -n "animCurveTA74";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 -18.639201237289793 3 -18.639201237289793 
		6 -14.69452682265149 15 0 40 0;
createNode animCurveTA -n "animCurveTA75";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -7.913110523478001 3 -7.913110523478001 
		5 -28.353716890544131 6 30.408248217596004 9 25.444910682582602 11 8.3151076325258337 
		15 4.4354313029508949 25 4.4354313029508949 27 7.6774320060526415 28 -3.2728222750973397 
		30 -13.189614177493654 31 8.6510551491418433 34 4.4354313029508949 40 4.4354313029508949;
createNode animCurveTA -n "animCurveTA76";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 65.994019113039769 3 65.994019113039769 
		5 50.416783274709594 6 -4.4380033208435758 9 -26.59211522720474 11 10.752996584182773 
		15 -16.033678544223676 25 -16.033678544223676 27 -31.377316461280579 28 28.509856403410481 
		30 53.865802523336427 31 -36.515293398236381 34 -16.033678544223676 40 -16.033678544223676;
createNode animCurveTA -n "animCurveTA77";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 -12.437232781742816 3 -12.437232781742816 
		5 -39.593393652992887 6 2.4728163704528439 9 -1.7764004738023562 11 -12.561179715723352 
		15 -9.5675898384059739 25 -9.5675898384059739 27 -11.388987376690114 28 -10.474042985952606 
		30 -18.352793848900685 31 -11.464621138672438 34 -9.5675898384059739 40 -9.5675898384059739;
createNode animCurveTA -n "animCurveTA78";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 -22.866626262679571 3 -22.866626262679571 
		6 3.0392779796157812 9 -7.419870094872933 11 11.382556316710728 15 0 25 0 31 0 34 
		0 40 0;
createNode animCurveTA -n "animCurveTA79";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 12 ".ktv[0:11]"  0 -44.091079811634565 3 -44.091079811634565 
		6 36.512471965948947 9 48.594682153857718 11 -4.8458231943836871 15 0 25 0 27 0.26090174596453569 
		28 -20.421602084898517 31 17.483267832665192 34 0 40 0;
createNode animCurveTA -n "animCurveTA80";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 39.086365438141137 3 39.086365438141137 
		6 -7.7922153590574226 9 -32.638817129228812 11 -26.731631771668045 15 0 25 0 31 0 
		34 0 40 0;
createNode animCurveTA -n "animCurveTA81";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 -6.3072103433224749 15 0 
		25 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA82";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 9 ".ktv[0:8]"  0 0 3 0 6 0 11 -1.8734246492407323 15 0 
		25 0 31 0 34 0 40 0;
createNode animCurveTA -n "animCurveTA83";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 10.517920770862339 3 10.517920770862339 
		6 28.346036538535287 11 -73.874926424381258 15 10.517920770862339 25 10.517920770862339 
		28 -56.498030112935552 31 39.1483968099324 34 10.517920770862339 40 10.517920770862339;
createNode animCurveTA -n "animCurveTA84";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 -90 6 -90 15 -90 40 -90;
createNode animCurveTA -n "animCurveTA85";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 10.273084499082367 6 10.185744266156821 
		11 -17.854702667254646 15 0 40 0;
createNode animCurveTA -n "animCurveTA86";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 0 15 0 40 0;
createNode animCurveTL -n "animCurveTL1";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.25635110414733975 6 0.049370242845867579 
		15 0.29637375777867286 40 0.29637375777867286;
createNode animCurveTL -n "animCurveTL2";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.067077747789509687 6 0.085901096686456346 
		15 0 40 0;
createNode animCurveTL -n "animCurveTL3";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0.27509653853828719 6 0.27509653853828714 
		15 0.27509653853828708 40 0.27509653853828708;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".macc";
	setAttr -k on ".macd";
	setAttr -k on ".macq";
	setAttr ".mcfr" 30;
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".outf";
	setAttr -k on ".gama";
	setAttr -k on ".be";
	setAttr -k on ".fec";
	setAttr -k on ".ofc";
	setAttr -k on ".comp";
	setAttr -k on ".cth";
	setAttr -k on ".soll";
	setAttr -k on ".rd";
	setAttr -k on ".lp";
	setAttr -k on ".sp";
	setAttr -k on ".shs";
	setAttr -k on ".lpr";
	setAttr -k on ".mm";
	setAttr -k on ".npu";
	setAttr -k on ".itf";
	setAttr -k on ".shp";
	setAttr -k on ".uf";
	setAttr -k on ".oi";
	setAttr -k on ".rut";
	setAttr -av -k on ".mbf";
	setAttr -k on ".afp";
	setAttr -k on ".pfb";
	setAttr -av -k on ".bll";
	setAttr -k on ".bls";
	setAttr -k on ".smv";
	setAttr -k on ".ubc";
	setAttr -k on ".mbc";
	setAttr -k on ".udbx";
	setAttr -k on ".smc";
	setAttr -k on ".kmv";
	setAttr -k on ".rlen";
	setAttr -av -k on ".frts";
	setAttr -k on ".tlwd";
	setAttr -k on ".tlht";
	setAttr -k on ".jfc";
	setAttr -k on ".ope";
	setAttr -k on ".oppf";
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
connectAttr "attackSource1.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTA1.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTA2.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTA3.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTA4.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTA5.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTA6.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTA7.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTA8.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTA9.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTA10.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTA11.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTA12.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA13.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA14.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA15.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA16.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA17.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA18.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA19.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA20.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA21.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA22.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA23.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA24.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA25.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA26.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA27.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTA28.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA29.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA30.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA31.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTA32.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTA33.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTA34.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTA35.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA36.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA37.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA38.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTA39.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTA40.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTA41.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTA42.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA43.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA44.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA45.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTA46.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTA47.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTA48.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTA49.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA50.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA51.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA52.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTA53.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTA54.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTA55.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTA56.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTA57.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTA58.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTA59.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTA60.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTA61.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTA62.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTA63.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTA64.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA65.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA66.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA67.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA68.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA69.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA70.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTA71.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTA72.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTA73.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTA74.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTA75.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTA76.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTA77.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTA78.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTA79.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTA80.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTA81.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTA82.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTA83.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTA84.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTA85.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTA86.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTL1.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL2.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL3.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of birdAttack.ma
