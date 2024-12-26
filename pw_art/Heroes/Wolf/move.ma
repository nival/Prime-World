//Maya ASCII 2008 scene
//Name: move.ma
//Last modified: Fri, Dec 12, 2008 04:26:42 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008";
fileInfo "cutIdentifier" "200708022245-704165";
fileInfo "osv" "Microsoft Windows XP Service Pack 2 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 114 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 115 "R_Knee_locator.translateZ" 
		1 4 "R_Knee_locator.translateY" 1 5 "R_Knee_locator.translateX" 
		1 6 "L_Knee_locator.translateZ" 1 7 "L_Knee_locator.translateY" 
		1 8 "L_Knee_locator.translateX" 1 9 "R_Elbow_locator.translateZ" 
		1 13 "R_Elbow_locator.translateY" 1 14 "R_Elbow_locator.translateX" 
		1 15 "L_Elbow_locator.translateZ" 1 22 "L_Elbow_locator.translateY" 
		1 23 "L_Elbow_locator.translateX" 1 24 "Tongue_locator3.rotateZ" 
		2 1 "Tongue_locator3.rotateY" 2 2 "Tongue_locator3.rotateX" 2 
		3 "Tongue_locator2.rotateZ" 2 4 "Tongue_locator2.rotateY" 2 5 "Tongue_locator2.rotateX" 
		2 6 "Tongue_locator1.rotateZ" 2 7 "Tongue_locator1.rotateY" 2 
		8 "Tongue_locator1.rotateX" 2 9 "Neck_locator.rotateZ" 2 10 "Neck_locator.rotateY" 
		2 11 "Neck_locator.rotateX" 2 12 "Tail_locator.rotateZ" 2 
		13 "Tail_locator.rotateY" 2 14 "Tail_locator.rotateX" 2 15 "R_Hand_locator.Toe" 
		0 5 "R_Hand_locator.rotateZ" 2 16 "R_Hand_locator.rotateY" 2 
		17 "R_Hand_locator.rotateX" 2 18 "R_Hand_locator.translateZ" 1 
		25 "R_Hand_locator.translateY" 1 26 "R_Hand_locator.translateX" 1 
		27 "L_Hand_locator.Toe" 0 6 "L_Hand_locator.rotateZ" 2 19 "L_Hand_locator.rotateY" 
		2 20 "L_Hand_locator.rotateX" 2 21 "L_Hand_locator.translateZ" 
		1 28 "L_Hand_locator.translateY" 1 29 "L_Hand_locator.translateX" 
		1 30 "R_Leg_locator.Toe" 0 7 "R_Leg_locator.rotateZ" 2 22 "R_Leg_locator.rotateY" 
		2 23 "R_Leg_locator.rotateX" 2 24 "R_Leg_locator.translateZ" 1 
		31 "R_Leg_locator.translateY" 1 32 "R_Leg_locator.translateX" 1 
		33 "L_Leg_locator.Toe" 0 8 "L_Leg_locator.rotateZ" 2 25 "L_Leg_locator.rotateY" 
		2 26 "L_Leg_locator.rotateX" 2 27 "L_Leg_locator.translateZ" 1 
		34 "L_Leg_locator.translateY" 1 35 "L_Leg_locator.translateX" 1 
		36 "Head_locator.Jaw" 0 9 "Head_locator.translateZ" 1 37 "Head_locator.translateY" 
		1 38 "Head_locator.translateX" 1 39 "Head_Top_locator.Hair" 0 
		10 "Head_Top_locator.translateZ" 1 40 "Head_Top_locator.translateY" 
		1 41 "Head_Top_locator.translateX" 1 42 "Chest_locator.Breath" 
		0 11 "Chest_locator.rotateZ" 2 28 "Chest_locator.rotateY" 2 
		29 "Chest_locator.rotateX" 2 30 "Hip_locator.rotateZ" 2 31 "Hip_locator.rotateY" 
		2 32 "Hip_locator.rotateX" 2 33 "Hip_locator.translateZ" 1 
		43 "Hip_locator.translateY" 1 44 "Hip_locator.translateX" 1 45 "cluster5Handle.Twist" 
		0 12 "cluster5Handle.translateZ" 1 46 "cluster5Handle.translateY" 
		1 47 "cluster5Handle.translateX" 1 48 "cluster4Handle.translateZ" 
		1 49 "cluster4Handle.translateY" 1 50 "cluster4Handle.translateX" 
		1 51 "cluster3Handle.translateZ" 1 52 "cluster3Handle.translateY" 
		1 53 "cluster3Handle.translateX" 1 54 "cluster2Handle.translateZ" 
		1 55 "cluster2Handle.translateY" 1 56 "cluster2Handle.translateX" 
		1 57 "cluster1Handle.translateZ" 1 58 "cluster1Handle.translateY" 
		1 59 "cluster1Handle.translateX" 1 60 "R_Ear_locator.rotateZ" 2 
		34 "R_Ear_locator.rotateY" 2 35 "R_Ear_locator.rotateX" 2 36 "R_Ear_locator1.rotateZ" 
		2 37 "R_Ear_locator1.rotateY" 2 38 "R_Ear_locator1.rotateX" 2 
		39 "Global.Mark" 0 13 "Tongue_locator2.translateZ" 1 61 "Tongue_locator2.translateY" 
		1 62 "Tongue_locator2.translateX" 1 63 "Tongue_locator1.translateZ" 
		1 64 "Tongue_locator1.translateY" 1 65 "Tongue_locator1.translateX" 
		1 66 "F_RL_locator.rotateZ" 2 40 "F_RL_locator.rotateY" 2 
		41 "F_RL_locator.rotateX" 2 42 "R_BL_locator.rotateZ" 2 43 "R_BL_locator.rotateY" 
		2 44 "R_BL_locator.rotateX" 2 45 "L_BL_locator.rotateZ" 2 
		46 "L_BL_locator.rotateY" 2 47 "L_BL_locator.rotateX" 2 48 "F_LL_locator.rotateZ" 
		2 49 "F_LL_locator.rotateY" 2 50 "F_LL_locator.rotateX" 2 
		51 "Global.translateY" 1 67  ;
	setAttr ".cd[0].cim" -type "Int32Array" 115 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88
		 89 90 91 92 93 94 95 96 97 98 99 100
		 101 102 103 104 105 106 107 108 109 110 111 112
		 113 114 ;
createNode animClip -n "clip00Source";
	setAttr ".ihi" 0;
	setAttr -s 114 ".ac";
	setAttr ".ac[0:94]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes;
	setAttr ".ac[96:114]" yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes no;
	setAttr ".ss" 5;
	setAttr ".se" 21;
	setAttr ".ci" no;
createNode animCurveTL -n "animCurveTL272";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 0.63447475485147664 13 2.09426466946358 
		17 3.6040869746436357 21 4.907152130536887;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTL -n "animCurveTL273";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.24980296460239734 9 0.25444066348215016 
		13 0.54003127393854566 17 0.34895501720411576 21 -0.24980296460239734;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL274";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.045640681084394771 9 0.045694074398130238 
		13 0 17 -0.045245296093720577 21 -0.045640681084394799;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL275";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 1.0331416671746179 13 1.7119860305709411 
		17 3.7462912979267484 21 4.907152130536887;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTL -n "animCurveTL276";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.095750067577279704 9 0.52549020386311163 
		13 0.11569181346015524 17 0.1835317788166502 21 -0.095750067577279704;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL277";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.029599382846540404 9 0.016094691551589824 
		13 -0.029599382846540404 17 0.10132425112880665 21 -0.029599382846540432;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL278";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -0.21037008270526603 9 1.1068966977454828 
		11 1.5618467432170846 13 2.2409522945400835 17 3.1849804355473221 19 3.7209437079294476 
		21 4.6967820478316211;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL279";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0.0010044686737233439 9 0.47677045639628618 
		11 0.06093402746657145 13 -0.39099325229322124 17 -0.20395404543190124 19 -0.12103686006153075 
		21 0.0010044686737233439;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL280";
	setAttr ".tan" 9;
	setAttr -s 7 ".ktv[0:6]"  5 -0.066684099026529831 9 -0.13864449653841487 
		11 -0.10221333241674366 13 -0.091138486413099129 17 -0.0017773124885811014 19 0.012050907156674078 
		21 -0.066684099026529858;
	setAttr -s 7 ".kit[0:6]"  2 10 9 9 9 10 2;
	setAttr -s 7 ".kot[0:6]"  2 10 9 9 9 10 2;
createNode animCurveTL -n "animCurveTL281";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 1.4608197692436273e-017 9 0.71348275748959389 
		13 2.2991140610433249 17 3.5942108051003574 19 3.763312642911667 21 4.907152130536887;
	setAttr -s 6 ".kit[0:5]"  9 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  9 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL282";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0.23989478107063858 9 0.033862317226882641 
		13 -0.15038928848792663 17 -0.36340840808042812 19 -0.072323281006404991 21 0.23989478107063858;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL283";
	setAttr ".tan" 10;
	setAttr -s 6 ".ktv[0:5]"  5 0.040264042142889957 9 -0.06892762519564867 
		13 0.15105481728394241 17 0.11703722556098993 19 0.13509349349103109 21 0.040264042142889929;
	setAttr -s 6 ".kit[0:5]"  3 10 10 10 10 10;
	setAttr -s 6 ".kot[0:5]"  3 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA256";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -15.173504444656048 9 -15.173504444656096 
		13 -15.173504444656068 17 -15.173504444656064 21 -15.173504444656048;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA257";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 1.9878466759146985e-016 13 0 17 -7.9513867036587939e-016 
		21 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA258";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 6.1208339390336901 9 26.811853834611128 
		13 3.0216997773825707 17 -16.464722262932597 21 6.1208339390336901;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
createNode animCurveTA -n "animCurveTA259";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA260";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA261";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -22.538673498619961 21 -22.538673498619961;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA262";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA263";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA264";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -16.766075537198322 21 -16.766075537198322;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA265";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 0 13 0 17 0 21 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA266";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 5.8039332042122043 9 5.8039332042122016 
		13 5.8039332042122025 17 5.8039332042122043 21 5.8039332042122043;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA267";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 16.838050032386644 9 -6.6945360109146055 
		13 -12.00352115789976 17 -30.420386839301464 21 16.838050032386644;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTA -n "animCurveTA268";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA269";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -14.507496363273809 21 -14.507496363273809;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA270";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 26.095200660532537 21 26.095200660532537;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTU -n "animCurveTU42";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 28.3 9 18.700000000000003 11 43.64509964050162 
		13 46.678963185574773 17 53.489076249676522 18 -18.011185080928037 19 33.789076249676519 
		21 28.3;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 9 10;
createNode animCurveTA -n "animCurveTA271";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  5 24.3046495715944 9 -2.8003586932526998 
		11 -7.8386687222121703 13 -8.2825335448691302 17 1.3680148610647271 18 1.3535887949192584 
		19 1.6376007199245883 21 24.3046495715944;
	setAttr -s 8 ".kit[1:7]"  10 10 10 3 3 3 10;
	setAttr -s 8 ".kot[1:7]"  10 10 10 3 3 3 10;
createNode animCurveTA -n "animCurveTA272";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  5 -17.099891319761511 9 -15.095872305540395 
		11 -6.2171468855456746 13 2.8670084265682152 17 6.51446677248956 18 6.514 19 -14.424754596429144 
		21 -17.099891319761511;
	setAttr -s 8 ".kit[1:7]"  9 10 9 3 3 9 10;
	setAttr -s 8 ".kot[1:7]"  9 10 9 3 3 9 10;
createNode animCurveTA -n "animCurveTA273";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 69.778408550894497 9 100.23308349299266 
		11 -5.5444177889735684 13 -72.894232015293184 17 -50.891180274355889 18 19.014109256277436 
		19 79.207304156571411 21 69.778408550894497;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 1 10 3 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 1 10 3 10;
	setAttr -s 8 ".kix[4:7]"  0.12861119210720062 0.033333305269479752 
		0.033333331346511841 0.066666662693023682;
	setAttr -s 8 ".kiy[4:7]"  2.5343227386474609 1.1353224515914917 0 
		-0.16456528007984161;
	setAttr -s 8 ".kox[4:7]"  0.028612403199076653 0.033333361148834229 
		0.066666662693023682 0.066666662693023682;
	setAttr -s 8 ".koy[4:7]"  0.56381607055664063 1.1353244781494141 
		0 -0.16456528007984161;
createNode animCurveTL -n "animCurveTL284";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 -0.27233192039142912 9 0.97188867809675039 
		11 1.9392763563096043 13 2.817343659355275 17 3.4749360842921155 18 3.6143850768726082 
		19 3.8128863508516084 21 4.6348202101454588;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 9 10 9 10;
createNode animCurveTL -n "animCurveTL285";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 0.11460671677351671 9 0.26304864645897075 
		11 0.097866816747603655 13 0.1436062335544562 17 -0.097254176466394476 18 -0.00071302148000667144 
		19 0.0070456902533442139 21 0.11460671677351671;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 9 10 9 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 9 10 9 10;
createNode animCurveTL -n "animCurveTL286";
	setAttr ".tan" 3;
	setAttr -s 8 ".ktv[0:7]"  5 -0.012090429051572702 9 -0.048339857487240921 
		11 -0.023345298054847877 13 0.032838174127403141 17 0.112 18 0.12350207516606115 
		19 0.112 21 -0.012090429051572732;
	setAttr -s 8 ".kit[1:7]"  9 9 1 3 3 3 10;
	setAttr -s 8 ".kot[1:7]"  9 9 1 3 3 3 10;
	setAttr -s 8 ".kix[3:7]"  0.064838849008083344 0.13333332538604736 
		0.033333331346511841 0.033333331346511841 0.066666662693023682;
	setAttr -s 8 ".kiy[3:7]"  0.067245505750179291 0 0 0 -0.12409042567014694;
	setAttr -s 8 ".kox[3:7]"  0.12967769801616669 0.033333331346511841 
		0.033333331346511841 0.066666662693023682 0.066666662693023682;
	setAttr -s 8 ".koy[3:7]"  0.13449101150035858 0 0 0 -0.12409042567014694;
createNode animCurveTU -n "animCurveTU43";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 54.900000000000006 9 54.087384259259267 
		11 52.382290767663036 13 50.300049720715549 17 46.470253448106803 19 35.043905147124313 
		20 -9.5560948528756882 21 54.900000000000006;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA274";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 13.000307067191216 9 5.8707809591105606 
		11 0.78900023356842097 13 -2.8161707532102365 17 1.8671797363410061 19 0.23114252792105588 
		20 0.50591518804374636 21 13.000307067191216;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 1 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 1 10;
	setAttr -s 8 ".kix[6:7]"  0.017953610047698021 0.033333331346511841;
	setAttr -s 8 ".kiy[6:7]"  0.0044622709974646568 0.21806827187538147;
	setAttr -s 8 ".kox[6:7]"  0.017953606322407722 0.033333331346511841;
	setAttr -s 8 ".koy[6:7]"  0.0044622714631259441 0.21806827187538147;
createNode animCurveTA -n "animCurveTA275";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 15.613789998616479 9 5.0340680491094494 
		11 -4.7521108318534058 13 -11.188058232706318 17 -9.5743495461727672 19 0.052727133882387624 
		20 1.094585833196446 21 15.613789998616479;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA276";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 62.605778613997821 9 86.062373949623051 
		11 39.121305231458301 13 -31.534693984276391 17 -61.272855527013149 19 -34.31558973039585 
		20 11.310938999085744 21 62.605778613997821;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL287";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 -0.52588164472607368 9 1.1157302415497412 
		11 2.0675593531152261 13 2.9352990066919715 17 3.9041952794290911 19 4.0409750344519431 
		20 4.1499641993463268 21 4.3812704858108145;
	setAttr -s 8 ".kit[0:7]"  9 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  9 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL288";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 0.042317058419902812 9 0.084097093660715438 
		11 0.18408115254651911 13 0.19132145958218535 17 0.07839218993825324 19 -0.067929196970435146 
		20 -0.0019133043842991038 21 0.042317058419902812;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL289";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 -0.14144042907029683 9 0.012558021879154333 
		11 0.013224537979036877 13 0.01389105407891948 17 0.017319670231434343 19 -0.10361221766834654 
		20 -0.10995930136104404 21 -0.14144042907029686;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU44";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 33.813896554385053 7 -11.812499713897704 
		9 23.9 13 41.800000000000004 17 35.933550711055389 19 27.122887325031943 21 33.813896554385053;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA277";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0 7 0 9 -8.0536947238616116e-016 13 0 
		17 -13.948323368871018 19 -8.7177021528739544 21 0;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA278";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -9.1423050618651391 7 -9.1423050618651374 
		9 -9.1423050618651391 13 -9.1423050618651374 17 -5.3219967899780549 19 -6.7546123804063463 
		21 -9.1423050618651391;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA279";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -21.101144197349999 7 19.64603391550822 
		9 82.56080886496818 13 82.981618682738628 17 -45.441000343035249 19 -23.522578335196801 
		21 -21.101144197349999;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL290";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0.56307145309593798 7 0.76568431308904661 
		9 1.0130658296057067 13 2.2439164213339371 17 4.1067849498882998 19 4.819718638084149 
		21 5.4702235836328263;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL291";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0.11068222645335893 7 0.020688170488973142 
		9 0.19658217437667763 13 0.43215673427227003 17 0.3746269407783665 19 0.25555551723917663 
		21 0.11068222645335893;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL292";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -0.18988055603226744 7 -0.1281762379018451 
		9 -0.066471919771422777 13 -0.066471919771422805 17 -0.18630879643677672 19 -0.18809467623452208 
		21 -0.18988055603226747;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU45";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 5.8719989246544522 7 31.8 9 33.2 13 21.1 
		17 23.104252400548692 19 34.994822704118718 21 5.8719989246544522;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 3;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 3;
createNode animCurveTA -n "animCurveTA280";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 3.6032941055514156 7 1.4206156117773099 
		9 5.9737999701811047e-016 13 2.5866011350024678 17 1.7154380277935757 19 4.5755316079107455 
		21 3.6032941055514156;
	setAttr -s 7 ".kit[0:6]"  3 9 10 10 9 10 10;
	setAttr -s 7 ".kot[0:6]"  3 9 10 10 9 10 10;
createNode animCurveTA -n "animCurveTA281";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -2.0268991042684217 7 2.3279878365567757 
		9 3.3585122118666453 13 -13.179431446401823 17 -0.86327897083296368 19 10.064070364011826 
		21 -2.0268991042684217;
	setAttr -s 7 ".kit[0:6]"  3 9 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 9 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA282";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -2.44871469706914 7 76.931433804551816 
		9 108.90714334896244 13 67.908819406944062 17 -9.5682322122982804 19 -26.594994708636207 
		21 -2.44871469706914;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL293";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0.39294022980231236 7 0.52926302716449714 
		9 0.89822243666003099 13 2.5274949398066155 17 3.9954482256989694 19 4.8295769826930197 
		21 5.3000923603392014;
	setAttr -s 7 ".kit[0:6]"  9 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  9 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL294";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 -0.0052870309666185143 7 0.097885181989278591 
		9 0.41073222779540275 13 0.32784318916090671 17 0.32446967871879789 19 0.19544731245923319 
		21 -0.0052870309666185143;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTL -n "animCurveTL295";
	setAttr ".tan" 10;
	setAttr -s 7 ".ktv[0:6]"  5 0.14784053453271653 7 0.073920267266358253 
		9 0 13 -1.1686558153949018e-016 17 0.16493739216786379 19 0.27869960593549464 21 
		0.14784053453271651;
	setAttr -s 7 ".kit[0:6]"  3 10 10 10 10 10 10;
	setAttr -s 7 ".kot[0:6]"  3 10 10 10 10 10 10;
createNode animCurveTU -n "animCurveTU46";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -1.3164099377710419 9 -4.1660755541276053 
		13 -1.3164099377710419 17 2.2835900622289582 21 -1.3164099377710419;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 10;
createNode animCurveTL -n "animCurveTL296";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0.3209818656346165 9 1.4791012743079763 
		17 3.7775057851863085 21 5.2281339961715059;
	setAttr -s 4 ".kit[0:3]"  9 10 10 10;
	setAttr -s 4 ".kot[0:3]"  9 10 10 10;
createNode animCurveTL -n "animCurveTL297";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.22544005256277394 9 -0.17831957620909719 
		13 0.13052099930711 17 -0.085662042777854788 21 -0.22544005256277394;
	setAttr -s 5 ".kit[0:4]"  3 9 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 10 3;
createNode animCurveTL -n "animCurveTL298";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 9 -7.3040985688048128e-018 17 -2.3535429543669801e-017 
		21 -2.9216395384872545e-017;
	setAttr -s 4 ".kit[0:3]"  2 10 10 2;
	setAttr -s 4 ".kot[0:3]"  2 10 10 2;
createNode animCurveTU -n "animCurveTU47";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 9 -19.6 17 17.3 21 0;
	setAttr -s 4 ".kit[0:3]"  2 10 10 10;
	setAttr -s 4 ".kot[0:3]"  2 10 10 10;
createNode animCurveTL -n "animCurveTL299";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 -2.3373116307898036e-016 9 1.1581194086733595 
		17 3.4565239195516915 21 4.907152130536887;
	setAttr -s 4 ".kit[0:3]"  9 10 10 10;
	setAttr -s 4 ".kot[0:3]"  9 10 10 10;
createNode animCurveTL -n "animCurveTL300";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 9 -2.4286128663675304e-016 17 -3.3997874907350528e-016 
		21 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTL -n "animCurveTL301";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 9 -6.3910864904408689e-018 17 -2.465133360598621e-017 
		21 -2.9216395384872545e-017;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTU -n "animCurveTU48";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 0 13 0 17 0 21 0;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA283";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 2.5065717908604999 9 2.5065717908604856 
		13 2.5065717908604848 17 2.5065717908604821 21 2.5065717908604999;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA284";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.12484905324867301 9 4.8665489033387868 
		13 -0.12484905324869448 17 -5.1625703708455051 21 -0.12484905324867301;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
createNode animCurveTA -n "animCurveTA285";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 20.194757143638896 9 14.201131001328701 
		13 15.684441788212762 17 56.430550846673732 21 20.194757143638896;
	setAttr -s 5 ".kit[0:4]"  2 9 9 3 2;
	setAttr -s 5 ".kot[0:4]"  2 9 9 3 2;
createNode animCurveTA -n "animCurveTA286";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  5 0.16005720141585345 9 8.0937234706949024 
		17 -5.522980563975298 21 0.16005720141585345;
	setAttr -s 4 ".kit[0:3]"  2 3 3 2;
	setAttr -s 4 ".kot[0:3]"  2 3 3 2;
createNode animCurveTA -n "animCurveTA287";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.017773173459608729 9 -4.5630225055694416 
		13 0.0050543978296511685 17 5.6332415689778488 21 0.017773173459608729;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
createNode animCurveTA -n "animCurveTA288";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -13.270638193650576 13 6.8081116374988451 
		21 -13.270638193650576;
	setAttr -s 3 ".kit[1:2]"  9 3;
	setAttr -s 3 ".kot[1:2]"  9 3;
createNode animCurveTL -n "animCurveTL302";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  5 0.072463099030683667 21 4.979615229567572;
createNode animCurveTL -n "animCurveTL303";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 -0.17375620975976919 9 -0.05952396099918382 
		13 0.043936653850159109 17 0.073441174543788776 21 -0.17375620975976919;
	setAttr -s 5 ".kit[0:4]"  3 10 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 9 3;
createNode animCurveTL -n "animCurveTL304";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0 9 0 13 0 17 0 21 -2.9216395384872545e-017;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTU -n "animCurveTU49";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -37.4 9 -37.4 13 -37.4 17 -37.4 21 -37.4;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTL -n "animCurveTL305";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.018243167863815475 9 0.029649879992748381 
		13 0.093768347652101042 17 -0.1165823764642349 21 -0.018243167863815475;
	setAttr -s 5 ".kit[0:4]"  9 9 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 9 10 10 10;
createNode animCurveTL -n "animCurveTL306";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.033305179799206136 9 -0.03634442095496225 
		13 -0.13319624752763362 17 0.21166672592123864 21 0.033305179799206136;
	setAttr -s 5 ".kit[0:4]"  9 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 10 10 10;
createNode animCurveTL -n "animCurveTL307";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.10518328701909811 9 -0.23370042001805399 
		13 -0.095897449394264575 17 -0.053124539527218864 21 -0.10518328701909811;
	setAttr -s 5 ".kit[0:4]"  9 10 9 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 9 10 10;
createNode animCurveTL -n "animCurveTL308";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.068028869385781773 9 0.092043140000783952 
		13 0.043167683571947266 17 -0.031560858808935777 21 0.068028869385781773;
	setAttr -s 5 ".kit[0:4]"  2 10 9 10 10;
	setAttr -s 5 ".kot[0:4]"  2 10 9 10 10;
createNode animCurveTL -n "animCurveTL309";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.020124225378025301 9 -0.036787869107065795 
		13 0.0069894817901431337 17 0.15325503122652434 21 0.020124225378025301;
	setAttr -s 5 ".kit[0:4]"  9 10 9 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 9 10 10;
createNode animCurveTL -n "animCurveTL310";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 -0.11505074686907299 9 -0.089442802253459033 
		13 -0.037012269871729425 17 -0.093526362006571301 21 -0.11505074686907299;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTL -n "animCurveTL311";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0.080081738938711844 9 0.085434523476856067 
		13 0.02791501140275934 17 0.034500295740482655 21 0.080081738938711844;
	setAttr -s 5 ".kit[1:4]"  10 9 9 1;
	setAttr -s 5 ".kot[1:4]"  10 9 9 1;
	setAttr -s 5 ".kix[4]"  0.13214798271656036;
	setAttr -s 5 ".kiy[4]"  0.019576733931899071;
	setAttr -s 5 ".kox[4]"  0.13214798271656036;
	setAttr -s 5 ".koy[4]"  0.01957673579454422;
createNode animCurveTL -n "animCurveTL312";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.036247446531235905 9 -0.032567903402250402 
		13 0.02701878196858995 17 0.088743546859112316 21 -0.036247446531235905;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 3;
createNode animCurveTL -n "animCurveTL313";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -0.044041692968890482 9 -0.026768589504969714 
		13 -0.049101953423645553 17 -0.098316357817079189 21 -0.044041692968890482;
	setAttr -s 5 ".kit[0:4]"  9 10 9 10 10;
	setAttr -s 5 ".kot[0:4]"  9 10 9 10 10;
createNode animCurveTL -n "animCurveTL314";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 0.029645879534958074 9 -0.0032298435416591564 
		13 0.0055019487658868535 17 0.020770856897184036 21 0.029645879534958074;
	setAttr -s 5 ".kit[0:4]"  3 10 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 9 3;
createNode animCurveTL -n "animCurveTL315";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  5 -0.021893828204953114 9 -0.015507062712383926 
		13 0.0065225275928852289 17 0.0057926768996740584 21 -0.021893828204953114;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 10;
createNode animCurveTL -n "animCurveTL316";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 0.0070995008129579968 9 0.0049088011257932222 
		13 -0.035329373598424516 17 -0.059566808064311527 21 0.0070995008129579968;
	setAttr -s 5 ".kit[0:4]"  3 10 9 10 3;
	setAttr -s 5 ".kot[0:4]"  3 10 9 10 3;
createNode animCurveTL -n "animCurveTL317";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0.0079218253907189177 21 0.0079218253907189177;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL318";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -0.02264927433814122 21 -0.02264927433814122;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL319";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 -0.00073701537917605919 21 -0.00073701537917605919;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA289";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 -8.6722583183314459 13 -18.812387067558692 
		21 -8.6722583183314459;
createNode animCurveTA -n "animCurveTA290";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 11.2936261571031 13 6.014305843621635 
		21 11.2936261571031;
createNode animCurveTA -n "animCurveTA291";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  5 -20.578244701913306 9 -46.208995759925457 
		13 -23.755884897247931 17 -5.6822184394179063 21 -20.578244701913306;
	setAttr -s 5 ".kit[0:4]"  2 3 1 3 2;
	setAttr -s 5 ".kot[0:4]"  2 3 1 3 2;
	setAttr -s 5 ".kix[2:4]"  0.1324201226234436 0.13333332538604736 
		0.13333332538604736;
	setAttr -s 5 ".kiy[2:4]"  0.5420985221862793 0 -0.25998470187187195;
	setAttr -s 5 ".kox[2:4]"  0.13242010772228241 0.13333332538604736 
		1;
	setAttr -s 5 ".koy[2:4]"  0.54209840297698975 0 0;
createNode animCurveTA -n "animCurveTA292";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 14.401823033426929 13 8.6833171924626811 
		21 14.401823033426929;
createNode animCurveTA -n "animCurveTA293";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  5 6.6031978183830029 13 -3.387631637472782 
		21 6.6031978183830029;
createNode animCurveTA -n "animCurveTA294";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -39.528069508442755 9 -59.078531114129454 
		13 -52.181676087144858 17 -24.765634722799668 21 -39.528069508442755;
	setAttr -s 5 ".kit[0:4]"  2 10 10 10 2;
	setAttr -s 5 ".kot[0:4]"  2 10 10 10 2;
createNode animCurveTL -n "animCurveTL320";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL321";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL322";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL323";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL324";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL325";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 0;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTA -n "animCurveTA295";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 0 9 0 11 0 13 0 17 -0.99007892341483994 
		18 18.66010498724734 19 0 21 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA296";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 0 9 0 11 0 13 0 17 16.191599313153574 
		18 33.709833931591149 19 0 21 0;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA297";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  5 14.739791323048834 9 4.0781963745433556 
		11 46.679729080113013 13 0 17 -3.5463925877250024 18 38.94975538901214 19 0 21 14.739791323048834;
	setAttr -s 8 ".kit[0:7]"  3 10 10 10 10 10 10 10;
	setAttr -s 8 ".kot[0:7]"  3 10 10 10 10 10 10 10;
createNode animCurveTA -n "animCurveTA298";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -10.619043112096254 9 -10.90714774724775 
		13 -10.61904311209628 17 -15.667170517720518 21 -10.619043112096254;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA299";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -22.945146757338748 9 -22.590052452695833 
		13 -22.945146757338669 17 -7.491648184525304 21 -22.945146757338748;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA300";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -73.137175139484398 9 41.33647509102726 
		13 35.407638964646871 17 -61.000213247399458 21 -73.137175139484398;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA301";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 6.9526818168273099 7 3.4763409084136723 
		9 0 17 3.3535175119251814 21 6.9526818168273099;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA302";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 8.4246778212106861 7 4.0216317046855483 
		9 0 17 24.698712109762909 21 8.4246778212106861;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA303";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  5 -50.22781443124336 7 23.113060975897174 
		9 59.449419035399877 17 -49.98789786060847 21 -50.22781443124336;
	setAttr -s 5 ".kit[0:4]"  3 10 10 10 10;
	setAttr -s 5 ".kot[0:4]"  3 10 10 10 10;
createNode animCurveTA -n "animCurveTA304";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 13 17.575265816655502 17 0 21 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTA -n "animCurveTA305";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 0 13 12.234023487305599 17 0 21 0;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTA -n "animCurveTA306";
	setAttr ".tan" 10;
	setAttr -s 4 ".ktv[0:3]"  5 60.095756229983174 13 -35.064115835120191 
		17 -36.105893088189113 21 60.095756229983174;
	setAttr -s 4 ".kit[0:3]"  3 10 10 10;
	setAttr -s 4 ".kot[0:3]"  3 10 10 10;
createNode animCurveTL -n "animCurveTL326";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  5 0 21 4.662;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -l on ".o" 21;
select -ne :renderPartition;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -s 4 ".st";
	setAttr -l on ".an";
	setAttr -l on ".pt";
select -ne :renderGlobalsList1;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
select -ne :defaultShaderList1;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :lightList1;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :initialShadingGroup;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -l on -k on ".mwc";
	setAttr -l on ".an";
	setAttr -l on ".il";
	setAttr -l on ".vo";
	setAttr -l on ".eo";
	setAttr -l on ".fo";
	setAttr -l on ".epo";
	setAttr -l on ".ro" yes;
select -ne :initialParticleSE;
	setAttr -l on -k on ".cch";
	setAttr -l on ".ihi";
	setAttr -l on -k on ".nds";
	setAttr -l on -k on ".mwc";
	setAttr -l on ".an";
	setAttr -l on ".il";
	setAttr -l on ".vo";
	setAttr -l on ".eo";
	setAttr -l on ".fo";
	setAttr -l on ".epo";
	setAttr -l on ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".clip";
	setAttr -k on ".edm";
	setAttr -k on ".edl";
	setAttr -av -k on ".esr";
	setAttr -k on ".ors";
	setAttr -k on ".gama";
	setAttr ".fs" 1;
	setAttr ".ef" 10;
	setAttr -l on ".bfs";
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
	setAttr -k on ".shp";
	setAttr -k on ".uf";
	setAttr -k on ".oi";
	setAttr -k on ".rut";
	setAttr -l on ".mb";
	setAttr -k on ".mbf";
	setAttr -l on ".afp";
	setAttr -k on ".pfb";
	setAttr -k on ".bll";
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -l on ".ef";
	setAttr -l on ".bf";
	setAttr -l on ".sf";
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
	setAttr -s 4 ".sol";
connectAttr "clip00Source.cl" "clipLibrary1.sc[0]";
connectAttr "animCurveTL272.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "animCurveTL273.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "animCurveTL274.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "animCurveTL275.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "animCurveTL276.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "animCurveTL277.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "animCurveTL278.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "animCurveTL279.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "animCurveTL280.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "animCurveTL281.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "animCurveTL282.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "animCurveTL283.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "animCurveTA256.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "animCurveTA257.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "animCurveTA258.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "animCurveTA259.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "animCurveTA260.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "animCurveTA261.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "animCurveTA262.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "animCurveTA263.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "animCurveTA264.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "animCurveTA265.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "animCurveTA266.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "animCurveTA267.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "animCurveTA268.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "animCurveTA269.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "animCurveTA270.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "animCurveTU42.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "animCurveTA271.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "animCurveTA272.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "animCurveTA273.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "animCurveTL284.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "animCurveTL285.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "animCurveTL286.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "animCurveTU43.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "animCurveTA274.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "animCurveTA275.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "animCurveTA276.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "animCurveTL287.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "animCurveTL288.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "animCurveTL289.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "animCurveTU44.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "animCurveTA277.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "animCurveTA278.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "animCurveTA279.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "animCurveTL290.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "animCurveTL291.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "animCurveTL292.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "animCurveTU45.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "animCurveTA280.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "animCurveTA281.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "animCurveTA282.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "animCurveTL293.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "animCurveTL294.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "animCurveTL295.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "animCurveTU46.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "animCurveTL296.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "animCurveTL297.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "animCurveTL298.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "animCurveTU47.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "animCurveTL299.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "animCurveTL300.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "animCurveTL301.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "animCurveTU48.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "animCurveTA283.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "animCurveTA284.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "animCurveTA285.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "animCurveTA286.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "animCurveTA287.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "animCurveTA288.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "animCurveTL302.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "animCurveTL303.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "animCurveTL304.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "animCurveTU49.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "animCurveTL305.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "animCurveTL306.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "animCurveTL307.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "animCurveTL308.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "animCurveTL309.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "animCurveTL310.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "animCurveTL311.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "animCurveTL312.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "animCurveTL313.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "animCurveTL314.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "animCurveTL315.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "animCurveTL316.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "animCurveTL317.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "animCurveTL318.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "animCurveTL319.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "animCurveTA289.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr "animCurveTA290.a" "clipLibrary1.cel[0].cev[90].cevr";
connectAttr "animCurveTA291.a" "clipLibrary1.cel[0].cev[91].cevr";
connectAttr "animCurveTA292.a" "clipLibrary1.cel[0].cev[92].cevr";
connectAttr "animCurveTA293.a" "clipLibrary1.cel[0].cev[93].cevr";
connectAttr "animCurveTA294.a" "clipLibrary1.cel[0].cev[94].cevr";
connectAttr "animCurveTL320.a" "clipLibrary1.cel[0].cev[96].cevr";
connectAttr "animCurveTL321.a" "clipLibrary1.cel[0].cev[97].cevr";
connectAttr "animCurveTL322.a" "clipLibrary1.cel[0].cev[98].cevr";
connectAttr "animCurveTL323.a" "clipLibrary1.cel[0].cev[99].cevr";
connectAttr "animCurveTL324.a" "clipLibrary1.cel[0].cev[100].cevr";
connectAttr "animCurveTL325.a" "clipLibrary1.cel[0].cev[101].cevr";
connectAttr "animCurveTA295.a" "clipLibrary1.cel[0].cev[102].cevr";
connectAttr "animCurveTA296.a" "clipLibrary1.cel[0].cev[103].cevr";
connectAttr "animCurveTA297.a" "clipLibrary1.cel[0].cev[104].cevr";
connectAttr "animCurveTA298.a" "clipLibrary1.cel[0].cev[105].cevr";
connectAttr "animCurveTA299.a" "clipLibrary1.cel[0].cev[106].cevr";
connectAttr "animCurveTA300.a" "clipLibrary1.cel[0].cev[107].cevr";
connectAttr "animCurveTA301.a" "clipLibrary1.cel[0].cev[108].cevr";
connectAttr "animCurveTA302.a" "clipLibrary1.cel[0].cev[109].cevr";
connectAttr "animCurveTA303.a" "clipLibrary1.cel[0].cev[110].cevr";
connectAttr "animCurveTA304.a" "clipLibrary1.cel[0].cev[111].cevr";
connectAttr "animCurveTA305.a" "clipLibrary1.cel[0].cev[112].cevr";
connectAttr "animCurveTA306.a" "clipLibrary1.cel[0].cev[113].cevr";
connectAttr "animCurveTL326.a" "clipLibrary1.cel[0].cev[114].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[4].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[5].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[5].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of move.ma
