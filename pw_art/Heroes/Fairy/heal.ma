//Maya ASCII 2008 scene
//Name: heal.ma
//Last modified: Wed, Jan 27, 2010 10:36:01 AM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 89 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 89 "nurbsCircle11.rotateZ" 2 
		1 "nurbsCircle11.rotateY" 2 2 "nurbsCircle11.rotateX" 2 3 "nurbsCircle11.translateZ" 
		1 1 "nurbsCircle11.translateY" 1 2 "nurbsCircle11.translateX" 
		1 3 "nurbsCircle11.visibility" 0 1 "nurbsCircle46.lockInfluenceWeights" 
		0 2 "nurbsCircle46.rotateZ" 2 4 "nurbsCircle46.rotateY" 2 
		5 "nurbsCircle46.rotateX" 2 6 "nurbsCircle46.visibility" 0 3 "nurbsCircle30.lockInfluenceWeights" 
		0 4 "nurbsCircle30.rotateZ" 2 7 "nurbsCircle30.rotateY" 2 
		8 "nurbsCircle30.rotateX" 2 9 "nurbsCircle30.visibility" 0 5 "nurbsCircle12.rotateZ" 
		2 10 "nurbsCircle12.rotateY" 2 11 "nurbsCircle12.rotateX" 2 
		12 "nurbsCircle12.translateZ" 1 4 "nurbsCircle12.translateY" 1 
		5 "nurbsCircle12.translateX" 1 6 "nurbsCircle12.visibility" 0 
		6 "nurbsCircle48.lockInfluenceWeights" 0 7 "nurbsCircle48.rotateZ" 
		2 13 "nurbsCircle48.rotateY" 2 14 "nurbsCircle48.rotateX" 2 
		15 "nurbsCircle48.visibility" 0 8 "nurbsCircle29.lockInfluenceWeights" 
		0 9 "nurbsCircle29.rotateZ" 2 16 "nurbsCircle29.rotateY" 2 
		17 "nurbsCircle29.rotateX" 2 18 "nurbsCircle29.visibility" 0 10 "nurbsCircle17.lockInfluenceWeights" 
		0 11 "nurbsCircle17.rotateZ" 2 19 "nurbsCircle17.rotateY" 2 
		20 "nurbsCircle17.rotateX" 2 21 "nurbsCircle17.visibility" 0 12 "nurbsCircle20.lockInfluenceWeights" 
		0 13 "nurbsCircle20.rotateZ" 2 22 "nurbsCircle20.rotateY" 2 
		23 "nurbsCircle20.rotateX" 2 24 "nurbsCircle20.visibility" 0 14 "nurbsCircle31.lockInfluenceWeights" 
		0 15 "nurbsCircle31.rotateZ" 2 25 "nurbsCircle31.rotateY" 2 
		26 "nurbsCircle31.rotateX" 2 27 "nurbsCircle31.visibility" 0 16 "nurbsCircle47.lockInfluenceWeights" 
		0 17 "nurbsCircle47.rotateZ" 2 28 "nurbsCircle47.rotateY" 2 
		29 "nurbsCircle47.rotateX" 2 30 "nurbsCircle47.visibility" 0 18 "nurbsCircle32.lockInfluenceWeights" 
		0 19 "nurbsCircle32.rotateZ" 2 31 "nurbsCircle32.rotateY" 2 
		32 "nurbsCircle32.rotateX" 2 33 "nurbsCircle32.visibility" 0 20 "nurbsCircle45.lockInfluenceWeights" 
		0 21 "nurbsCircle45.rotateZ" 2 34 "nurbsCircle45.rotateY" 2 
		35 "nurbsCircle45.rotateX" 2 36 "nurbsCircle45.visibility" 0 22 "nurbsCircle14.lockInfluenceWeights" 
		0 23 "nurbsCircle14.rotateZ" 2 37 "nurbsCircle14.rotateY" 2 
		38 "nurbsCircle14.rotateX" 2 39 "nurbsCircle14.translateZ" 1 7 "nurbsCircle14.translateY" 
		1 8 "nurbsCircle14.translateX" 1 9 "nurbsCircle14.visibility" 
		0 24 "nurbsCircle9.rotateZ" 2 40 "nurbsCircle9.rotateY" 2 
		41 "nurbsCircle9.rotateX" 2 42 "nurbsCircle9.translateZ" 1 10 "nurbsCircle9.translateY" 
		1 11 "nurbsCircle9.translateX" 1 12 "nurbsCircle9.visibility" 0 
		25 "nurbsCircle10.rotateZ" 2 43 "nurbsCircle10.rotateY" 2 44 "nurbsCircle10.rotateX" 
		2 45 "nurbsCircle10.translateZ" 1 13 "nurbsCircle10.translateY" 
		1 14 "nurbsCircle10.translateX" 1 15 "nurbsCircle10.visibility" 
		0 26 "nurbsCircle14.scaleZ" 0 27 "nurbsCircle14.scaleY" 0 
		28 "nurbsCircle14.scaleX" 0 29  ;
	setAttr ".cd[0].cim" -type "Int32Array" 89 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88 ;
createNode animClip -n "healSource";
	setAttr ".ihi" 0;
	setAttr -s 89 ".ac[0:88]" yes yes yes no no no no no yes yes yes no 
		no yes yes yes no yes yes yes no no no no no yes yes yes no no yes yes yes no no 
		yes yes yes no no yes yes yes no no yes yes yes no no yes yes yes no no yes yes yes 
		no no yes yes yes no no yes yes yes no no no no yes yes yes no no no no yes yes yes 
		no no no no no no no;
	setAttr ".se" 40;
	setAttr ".ci" no;
createNode animCurveTA -n "character1_nurbsCircle11_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle11_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle11_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.068606529095617916 20 -0.049699384615965632 
		40 -0.068606529095617916;
createNode animCurveTL -n "character1_nurbsCircle11_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.044316350862610668 20 -0.044689634022474597 
		40 -0.044316350862610668;
createNode animCurveTL -n "character1_nurbsCircle11_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.049568755973435789 20 -0.047000219275084666 
		40 -0.049568755973435789;
createNode animCurveTU -n "character1_nurbsCircle11_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTU -n "character1_nurbsCircle46_lockInfluenceWeights";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 0 8 0 12 0 16 0 20 0 24 0 28 0 32 
		0 36 0 40 0;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 1 9 9 9 
		1 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle46_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 4.0587917333862071 2 -3.7924693815486705 
		4 -4.1191410841423624 6 5.8899044735393087 8 4.0587917333862071 10 -3.7924693815486705 
		12 -4.1191410841423624 14 5.8899044735393087 16 4.0587917333862071 18 -3.7924693815486705 
		20 -4.1191410841423624 22 5.8899044735393087 24 4.0587917333862071 26 -3.7924693815486705 
		28 -4.1191410841423624 30 5.8899044735393087 32 4.0587917333862071 34 -3.7924693815486705 
		36 -4.1191410841423624 38 5.8899044735393087 40 4.0587917333862071;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle46_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 6.6310237553774272 2 -9.4160772938212762 
		4 -8.9235653388411329 6 11.185537482677312 8 6.6310237553774272 10 -9.4160772938212762 
		12 -8.9235653388411329 14 11.185537482677312 16 6.6310237553774272 18 -9.4160772938212762 
		20 -8.9235653388411329 22 11.185537482677312 24 6.6310237553774272 26 -9.4160772938212762 
		28 -8.9235653388411329 30 11.185537482677312 32 6.6310237553774272 34 -9.4160772938212762 
		36 -8.9235653388411329 38 11.185537482677312 40 6.6310237553774272;
createNode animCurveTA -n "character1_nurbsCircle46_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -163.77927842242835 2 -163.18292549786256 
		4 -163.50094225380047 6 -162.8165919715413 8 -163.77927842242835 10 -163.18292549786256 
		12 -163.50094225380047 14 -162.8165919715413 16 -163.77927842242835 18 -163.18292549786256 
		20 -163.50094225380047 22 -162.8165919715413 24 -163.77927842242835 26 -163.18292549786256 
		28 -163.50094225380047 30 -162.8165919715413 32 -163.77927842242835 34 -163.18292549786256 
		36 -163.50094225380047 38 -162.8165919715413 40 -163.77927842242835;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle46_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 4 1 8 1 12 1 16 1 20 1 24 1 28 1 32 
		1 36 1 40 1;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 1 9 9 9 
		1 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle30_lockInfluenceWeights";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 0 8 0 12 0 16 0 20 0 24 0 28 0 32 
		0 36 0 40 0;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 9 9 9 9 
		9 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
createNode animCurveTA -n "character1_nurbsCircle30_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -134.24462471570493 4 -175.17782437495234 
		8 -134.24462471570493 12 -175.17782437495234 16 -134.24462471570493 20 -175.17782437495234 
		24 -134.24462471570493 28 -175.17782437495234 32 -134.24462471570493 36 -175.17782437495234 
		40 -134.24462471570493;
createNode animCurveTA -n "character1_nurbsCircle30_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 22.332695586533116 4 -8.3577464261525289 
		8 22.332695586533116 12 -8.3577464261525289 16 22.332695586533116 20 -8.3577464261525289 
		24 22.332695586533116 28 -8.3577464261525289 32 22.332695586533116 36 -8.3577464261525289 
		40 22.332695586533116;
createNode animCurveTA -n "character1_nurbsCircle30_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -17.979999460928827 4 -58.458517851858169 
		8 -17.979999460928827 12 -58.458517851858169 16 -17.979999460928827 20 -58.458517851858169 
		24 -17.979999460928827 28 -58.458517851858169 32 -17.979999460928827 36 -58.458517851858169 
		40 -17.979999460928827;
createNode animCurveTU -n "character1_nurbsCircle30_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 4 1 8 1 12 1 16 1 20 1 24 1 28 1 32 
		1 36 1 40 1;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 9 9 9 9 
		9 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
createNode animCurveTA -n "character1_nurbsCircle12_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle12_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle12_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle12_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.052248552049646353 20 -0.043041577885270389 
		40 -0.052248552049646353;
createNode animCurveTL -n "character1_nurbsCircle12_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.051031120018675699 20 -0.051299397026937185 
		40 -0.051031120018675699;
createNode animCurveTL -n "character1_nurbsCircle12_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.060727839701660395 20 0.048992851096485948 
		40 0.060727839701660395;
createNode animCurveTU -n "character1_nurbsCircle12_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTU -n "character1_nurbsCircle48_lockInfluenceWeights";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 0 8 0 12 0 16 0 20 0 24 0 28 0 32 
		0 36 0 40 0;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 1 9 9 9 
		1 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle48_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -25.345210128336447 2 -11.281756778534715 
		4 -10.992995439719449 6 -26.590846805771921 8 -25.345210128336447 10 -11.281756778534715 
		12 -10.992995439719449 14 -26.590846805771921 16 -25.345210128336447 18 -11.281756778534715 
		20 -10.992995439719449 22 -26.590846805771921 24 -25.345210128336447 26 -11.281756778534715 
		28 -10.992995439719449 30 -26.590846805771921 32 -25.345210128336447 34 -11.281756778534715 
		36 -10.992995439719449 38 -26.590846805771921 40 -25.345210128336447;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle48_rotateY";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 2.2092979617159396 2 14.74578514932486 
		4 16.465267118790958 6 -1.5063849855479363 8 2.2092979617159396 10 14.74578514932486 
		12 16.465267118790958 14 -1.5063849855479363 16 2.2092979617159396 18 14.74578514932486 
		20 16.465267118790958 22 -1.5063849855479363 24 2.2092979617159396 26 14.74578514932486 
		28 16.465267118790958 30 -1.5063849855479363 32 2.2092979617159396 34 14.74578514932486 
		36 16.465267118790958 38 -1.5063849855479363 40 2.2092979617159396;
createNode animCurveTA -n "character1_nurbsCircle48_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -155.12648812727866 2 -152.43791296534357 
		4 -152.78617619115172 6 -154.02637142235201 8 -155.12648812727866 10 -152.43791296534357 
		12 -152.78617619115172 14 -154.02637142235201 16 -155.12648812727866 18 -152.43791296534357 
		20 -152.78617619115172 22 -154.02637142235201 24 -155.12648812727866 26 -152.43791296534357 
		28 -152.78617619115172 30 -154.02637142235201 32 -155.12648812727866 34 -152.43791296534357 
		36 -152.78617619115172 38 -154.02637142235201 40 -155.12648812727866;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle48_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 4 1 8 1 12 1 16 1 20 1 24 1 28 1 32 
		1 36 1 40 1;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 1 9 9 9 
		1 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
	setAttr -s 11 ".kix[4:10]"  1 1 1 1 1 1 1;
	setAttr -s 11 ".kiy[4:10]"  0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle29_lockInfluenceWeights";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 4 0 8 0 12 0 16 0 20 0 24 0 28 0 32 
		0 36 0 40 0;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 9 9 9 9 
		9 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
createNode animCurveTA -n "character1_nurbsCircle29_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -82.390899083213384 4 -38.529988924959362 
		8 -82.390899083213384 12 -38.529988924959362 16 -82.390899083213384 20 -38.529988924959362 
		24 -82.390899083213384 28 -38.529988924959362 32 -82.390899083213384 36 -38.529988924959362 
		40 -82.390899083213384;
createNode animCurveTA -n "character1_nurbsCircle29_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 25.628954212195655 4 -13.843656408563412 
		8 25.628954212195655 12 -13.843656408563412 16 25.628954212195655 20 -13.843656408563412 
		24 25.628954212195655 28 -13.843656408563412 32 25.628954212195655 36 -13.843656408563412 
		40 25.628954212195655;
createNode animCurveTA -n "character1_nurbsCircle29_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -161.5110161569059 4 -123.98867045802191 
		8 -161.5110161569059 12 -123.98867045802191 16 -161.5110161569059 20 -123.98867045802191 
		24 -161.5110161569059 28 -123.98867045802191 32 -161.5110161569059 36 -123.98867045802191 
		40 -161.5110161569059;
createNode animCurveTU -n "character1_nurbsCircle29_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 1 4 1 8 1 12 1 16 1 20 1 24 1 28 1 32 
		1 36 1 40 1;
	setAttr -s 11 ".kit[0:10]"  10 9 9 9 9 9 9 9 
		9 9 9;
	setAttr -s 11 ".kot[0:10]"  10 5 5 5 5 5 5 5 
		5 5 5;
createNode animCurveTU -n "character1_nurbsCircle17_lockInfluenceWeights";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTA -n "character1_nurbsCircle17_rotateZ";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -98.592843766057683 20 -101.68501388940609 
		40 -98.592843766057683;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "character1_nurbsCircle17_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -43.599484460196919 20 -44.198169565587477 
		40 -43.599484460196919;
createNode animCurveTA -n "character1_nurbsCircle17_rotateX";
	setAttr ".tan" 3;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -92.875507331357198 20 -96.023259519428962 
		40 -92.875507331357198;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTU -n "character1_nurbsCircle17_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTU -n "character1_nurbsCircle20_lockInfluenceWeights";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTA -n "character1_nurbsCircle20_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 89.134004122842413 20 89.134004122842413 
		40 89.134004122842413;
createNode animCurveTA -n "character1_nurbsCircle20_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 74.328519787248823 20 74.328519787248823 
		40 74.328519787248823;
createNode animCurveTA -n "character1_nurbsCircle20_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 87.338469253508094 20 87.338469253508094 
		40 87.338469253508094;
createNode animCurveTU -n "character1_nurbsCircle20_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTU -n "character1_nurbsCircle31_lockInfluenceWeights";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 8 0 12 0 16 0 20 0 24 0 28 0 32 0 36 
		0 40 0;
	setAttr -s 10 ".kit[0:9]"  10 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  10 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTA -n "character1_nurbsCircle31_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 122.72495037828011 4 120.1359429466566 
		8 122.72495037828011 12 120.1359429466566 16 122.72495037828011 20 120.1359429466566 
		24 122.72495037828011 28 120.1359429466566 32 122.72495037828011 36 120.1359429466566 
		40 122.72495037828011;
createNode animCurveTA -n "character1_nurbsCircle31_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 71.777088982526692 4 26.713150525541028 
		8 71.777088982526692 12 26.713150525541028 16 71.777088982526692 20 26.713150525541028 
		24 71.777088982526692 28 26.713150525541028 32 71.777088982526692 36 26.713150525541028 
		40 71.777088982526692;
createNode animCurveTA -n "character1_nurbsCircle31_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -96.51124310983937 4 -63.393174604695993 
		8 -96.51124310983937 12 -63.393174604695993 16 -96.51124310983937 20 -63.393174604695993 
		24 -96.51124310983937 28 -63.393174604695993 32 -96.51124310983937 36 -63.393174604695993 
		40 -96.51124310983937;
createNode animCurveTU -n "character1_nurbsCircle31_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 8 1 12 1 16 1 20 1 24 1 28 1 32 1 36 
		1 40 1;
	setAttr -s 10 ".kit[0:9]"  10 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  10 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "character1_nurbsCircle47_lockInfluenceWeights";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 2 0 4 0 6 0 8 0 10 0 12 0 14 0 16 0 
		18 0 20 0 22 0 24 0 26 0 28 0 30 0 32 0 34 0 36 0 38 0 40 0;
	setAttr -s 21 ".kit[0:20]"  10 9 9 9 9 9 9 9 
		1 9 9 9 9 9 9 9 1 9 9 9 9;
	setAttr -s 21 ".kot[0:20]"  10 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle47_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -21.79199549911726 2 -20.741784779012306 
		4 -20.531802978612927 6 -22.226103668357169 8 -21.79199549911726 10 -20.741784779012306 
		12 -20.531802978612927 14 -22.226103668357169 16 -21.79199549911726 18 -20.741784779012306 
		20 -20.531802978612927 22 -22.226103668357169 24 -21.79199549911726 26 -20.741784779012306 
		28 -20.531802978612927 30 -22.226103668357169 32 -21.79199549911726 34 -20.741784779012306 
		36 -20.531802978612927 38 -22.226103668357169 40 -21.79199549911726;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle47_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 10.424620385956821 2 -6.3306217820168058 
		4 -9.6429162296890656 6 17.007435506950646 8 10.424620385956821 10 -6.3306217820168058 
		12 -9.6429162296890656 14 17.007435506950646 16 10.424620385956821 18 -6.3306217820168058 
		20 -9.6429162296890656 22 17.007435506950646 24 10.424620385956821 26 -6.3306217820168058 
		28 -9.6429162296890656 30 17.007435506950646 32 10.424620385956821 34 -6.3306217820168058 
		36 -9.6429162296890656 38 17.007435506950646 40 10.424620385956821;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  0.96862030029296875 0.35577818751335144 
		0.31109520792961121 0.35577818751335144 0.31109520792961121 0.35577818751335144 0.31109520792961121 
		0.35577830672264099 0.96862030029296875 0.35577818751335144 0.31109520792961121 0.35577818751335144 
		0.50188416242599487;
	setAttr -s 21 ".kiy[8:20]"  -0.24854527413845062 -0.93457049131393433 
		0.95037871599197388 0.93457049131393433 -0.95037871599197388 -0.93457049131393433 
		0.95037871599197388 0.93457037210464478 -0.24854527413845062 -0.93457049131393433 
		0.95037871599197388 0.93457049131393433 -0.86493492126464844;
	setAttr -s 21 ".kox[5:20]"  0.35577821731567383 0.31109520792961121 
		0.35577824711799622 0.31109532713890076 0.35577821731567383 0.31109520792961121 0.35577818751335144 
		0.31109520792961121 0.35577821731567383 0.31109520792961121 0.35577830672264099 0.31109520792961121 
		0.35577821731567383 0.31109520792961121 0.35577818751335144 0.50188416242599487;
	setAttr -s 21 ".koy[5:20]"  -0.93457037210464478 0.95037871599197388 
		0.93457037210464478 -0.95037877559661865 -0.93457037210464478 0.95037871599197388 
		0.93457049131393433 -0.95037871599197388 -0.93457037210464478 0.95037871599197388 
		0.93457037210464478 -0.95037871599197388 -0.93457037210464478 0.95037871599197388 
		0.93457049131393433 -0.86493492126464844;
createNode animCurveTA -n "character1_nurbsCircle47_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 176.38387241400648 2 176.42179084698137 
		4 176.39260282283044 6 176.28077052385242 8 176.38387241400648 10 176.42179084698137 
		12 176.39260282283044 14 176.28077052385242 16 176.38387241400648 18 176.42179084698137 
		20 176.39260282283044 22 176.28077052385242 24 176.38387241400648 26 176.42179084698137 
		28 176.39260282283044 30 176.28077052385242 32 176.38387241400648 34 176.42179084698137 
		36 176.39260282283044 38 176.28077052385242 40 176.38387241400648;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle47_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 2 1 4 1 6 1 8 1 10 1 12 1 14 1 16 1 
		18 1 20 1 22 1 24 1 26 1 28 1 30 1 32 1 34 1 36 1 38 1 40 1;
	setAttr -s 21 ".kit[0:20]"  10 9 9 9 9 9 9 9 
		1 9 9 9 9 9 9 9 1 9 9 9 9;
	setAttr -s 21 ".kot[0:20]"  10 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle32_lockInfluenceWeights";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 8 0 12 0 16 0 20 0 24 0 28 0 32 0 36 
		0 40 0;
	setAttr -s 10 ".kit[0:9]"  10 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  10 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTA -n "character1_nurbsCircle32_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 16.965893791662619 4 22.087922018174076 
		8 16.965893791662619 12 22.087922018174076 16 16.965893791662619 20 22.087922018174076 
		24 16.965893791662619 28 22.087922018174076 32 16.965893791662619 36 22.087922018174076 
		40 16.965893791662619;
createNode animCurveTA -n "character1_nurbsCircle32_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 63.099253669342545 4 24.022192272777431 
		8 63.099253669342545 12 24.022192272777431 16 63.099253669342545 20 24.022192272777431 
		24 63.099253669342545 28 24.022192272777431 32 63.099253669342545 36 24.022192272777431 
		40 63.099253669342545;
createNode animCurveTA -n "character1_nurbsCircle32_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -60.648348538017096 4 -116.11355216193031 
		8 -60.648348538017096 12 -116.11355216193031 16 -60.648348538017096 20 -116.11355216193031 
		24 -60.648348538017096 28 -116.11355216193031 32 -60.648348538017096 36 -116.11355216193031 
		40 -60.648348538017096;
createNode animCurveTU -n "character1_nurbsCircle32_visibility";
	setAttr ".tan" 9;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 1 8 1 12 1 16 1 20 1 24 1 28 1 32 1 36 
		1 40 1;
	setAttr -s 10 ".kit[0:9]"  10 9 9 9 9 9 9 9 
		9 9;
	setAttr -s 10 ".kot[0:9]"  10 5 5 5 5 5 5 5 
		5 5;
createNode animCurveTU -n "character1_nurbsCircle45_lockInfluenceWeights";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 2 0 4 0 6 0 8 0 10 0 12 0 14 0 16 0 
		18 0 20 0 22 0 24 0 26 0 28 0 30 0 32 0 34 0 36 0 38 0 40 0;
	setAttr -s 21 ".kit[0:20]"  10 9 9 9 9 9 9 9 
		1 9 9 9 9 9 9 9 1 9 9 9 9;
	setAttr -s 21 ".kot[0:20]"  10 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle45_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 3.1695485236152807 2 10.25782185179378 
		4 9.7159323061130767 6 1.5881709774019352 8 3.1695485236152807 10 10.25782185179378 
		12 9.7159323061130767 14 1.5881709774019352 16 3.1695485236152807 18 10.25782185179378 
		20 9.7159323061130767 22 1.5881709774019352 24 3.1695485236152807 26 10.25782185179378 
		28 9.7159323061130767 30 1.5881709774019352 32 3.1695485236152807 34 10.25782185179378 
		36 9.7159323061130767 38 1.5881709774019352 40 3.1695485236152807;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTA -n "character1_nurbsCircle45_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -11.318153801278379 2 12.348311657778909 
		4 10.587468455452067 6 -16.35437973345724 8 -11.318153801278379 10 12.348311657778909 
		12 10.587468455452067 14 -16.35437973345724 16 -11.318153801278379 18 12.348311657778909 
		20 10.587468455452067 22 -16.35437973345724 24 -11.318153801278379 26 12.348311657778909 
		28 10.587468455452067 30 -16.35437973345724 32 -11.318153801278379 34 12.348311657778909 
		36 10.587468455452067 38 -16.35437973345724 40 -11.318153801278379;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  0.96508562564849854 1 1 0.32929301261901855 
		0.25720325112342834 1 1 0.32929316163063049 0.96508562564849854 1 1 0.32929301261901855 
		0.60429978370666504;
	setAttr -s 21 ".kiy[8:20]"  0.2619347870349884 0 0 -0.94422781467437744 
		0.96635735034942627 0 0 -0.94422769546508789 0.2619347870349884 0 0 -0.94422781467437744 
		0.7967570424079895;
	setAttr -s 21 ".kox[5:20]"  1 1 0.32929307222366333 0.25720331072807312 
		1 1 0.32929301261901855 0.25720325112342834 1 1 0.32929316163063049 0.25720325112342834 
		1 1 0.32929301261901855 0.60429978370666504;
	setAttr -s 21 ".koy[5:20]"  0 0 -0.94422775506973267 0.96635729074478149 
		0 0 -0.94422781467437744 0.96635735034942627 0 0 -0.94422769546508789 0.96635735034942627 
		0 0 -0.94422781467437744 0.7967570424079895;
createNode animCurveTA -n "character1_nurbsCircle45_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 -163.22722709607808 2 -163.16203890116836 
		4 -163.26979018452172 6 -162.84865545107169 8 -163.22722709607808 10 -163.16203890116836 
		12 -163.26979018452172 14 -162.84865545107169 16 -163.22722709607808 18 -163.16203890116836 
		20 -163.26979018452172 22 -162.84865545107169 24 -163.22722709607808 26 -163.16203890116836 
		28 -163.26979018452172 30 -162.84865545107169 32 -163.22722709607808 34 -163.16203890116836 
		36 -163.26979018452172 38 -162.84865545107169 40 -163.22722709607808;
	setAttr -s 21 ".kit[8:20]"  1 10 10 10 10 10 10 10 
		1 10 10 10 10;
	setAttr -s 21 ".kot[5:20]"  1 10 10 10 1 10 10 10 
		1 10 10 10 1 10 10 10;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
	setAttr -s 21 ".kox[5:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".koy[5:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle45_visibility";
	setAttr ".tan" 5;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 1 2 1 4 1 6 1 8 1 10 1 12 1 14 1 16 1 
		18 1 20 1 22 1 24 1 26 1 28 1 30 1 32 1 34 1 36 1 38 1 40 1;
	setAttr -s 21 ".kit[0:20]"  10 9 9 9 9 9 9 9 
		1 9 9 9 9 9 9 9 1 9 9 9 9;
	setAttr -s 21 ".kot[0:20]"  10 5 5 5 5 5 5 5 
		5 5 5 5 5 5 5 5 5 5 5 5 5;
	setAttr -s 21 ".kix[8:20]"  1 1 1 1 1 1 1 1 1 1 1 1 1;
	setAttr -s 21 ".kiy[8:20]"  0 0 0 0 0 0 0 0 0 0 0 0 0;
createNode animCurveTU -n "character1_nurbsCircle14_lockInfluenceWeights";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 0;
	setAttr -s 2 ".kit[1]"  9;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "character1_nurbsCircle14_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle14_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 89.999999999999986 40 89.999999999999986;
createNode animCurveTA -n "character1_nurbsCircle14_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle14_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle14_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle14_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.8969178199768063e-005 40 1.8969178199768063e-005;
createNode animCurveTU -n "character1_nurbsCircle14_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1 40 1;
	setAttr -s 2 ".kit[1]"  9;
	setAttr -s 2 ".kot[1]"  5;
createNode animCurveTA -n "character1_nurbsCircle9_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle9_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle9_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle9_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.020703575293962495 20 0.020693187923820074 
		40 0.020703575293962495;
createNode animCurveTL -n "character1_nurbsCircle9_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.013798142295761196 20 0.013694241336963198 
		40 0.013798142295761196;
createNode animCurveTL -n "character1_nurbsCircle9_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.014195188547997072 20 -0.0014343501483895624 
		40 0.014195188547997072;
createNode animCurveTU -n "character1_nurbsCircle9_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTA -n "character1_nurbsCircle10_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle10_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTA -n "character1_nurbsCircle10_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 20 0 40 0;
createNode animCurveTL -n "character1_nurbsCircle10_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.045738539992526979 20 0.045747167416395264 
		40 0.045738539992526979;
createNode animCurveTL -n "character1_nurbsCircle10_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0.020168821435394044 20 0.020255118313197346 
		40 0.020168821435394044;
createNode animCurveTL -n "character1_nurbsCircle10_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0073150209857454594 20 0.0056663836769804314 
		40 -0.0073150209857454594;
createNode animCurveTU -n "character1_nurbsCircle10_visibility";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 1 20 1 40 1;
	setAttr -s 3 ".kit[1:2]"  9 9;
	setAttr -s 3 ".kot[1:2]"  5 5;
createNode animCurveTU -n "character1_nurbsCircle14_scaleZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.12561260640364144 40 0.12561260640364144;
createNode animCurveTU -n "character1_nurbsCircle14_scaleY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.12561260640364144 40 0.12561260640364144;
createNode animCurveTU -n "character1_nurbsCircle14_scaleX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0.12561260640364144 40 0.12561260640364144;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 40;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 5 ".st";
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
	setAttr -s 5 ".s";
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
select -ne :defaultTextureList1;
	setAttr -s 3 ".tx";
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
	setAttr -s 2 ".gn";
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
connectAttr "healSource.cl" "clipLibrary1.sc[0]";
connectAttr "character1_nurbsCircle11_rotateZ.a" "clipLibrary1.cel[0].cev[0].cevr"
		;
connectAttr "character1_nurbsCircle11_rotateY.a" "clipLibrary1.cel[0].cev[1].cevr"
		;
connectAttr "character1_nurbsCircle11_rotateX.a" "clipLibrary1.cel[0].cev[2].cevr"
		;
connectAttr "character1_nurbsCircle11_translateZ.a" "clipLibrary1.cel[0].cev[3].cevr"
		;
connectAttr "character1_nurbsCircle11_translateY.a" "clipLibrary1.cel[0].cev[4].cevr"
		;
connectAttr "character1_nurbsCircle11_translateX.a" "clipLibrary1.cel[0].cev[5].cevr"
		;
connectAttr "character1_nurbsCircle11_visibility.a" "clipLibrary1.cel[0].cev[6].cevr"
		;
connectAttr "character1_nurbsCircle46_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[7].cevr"
		;
connectAttr "character1_nurbsCircle46_rotateZ.a" "clipLibrary1.cel[0].cev[8].cevr"
		;
connectAttr "character1_nurbsCircle46_rotateY.a" "clipLibrary1.cel[0].cev[9].cevr"
		;
connectAttr "character1_nurbsCircle46_rotateX.a" "clipLibrary1.cel[0].cev[10].cevr"
		;
connectAttr "character1_nurbsCircle46_visibility.a" "clipLibrary1.cel[0].cev[11].cevr"
		;
connectAttr "character1_nurbsCircle30_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[12].cevr"
		;
connectAttr "character1_nurbsCircle30_rotateZ.a" "clipLibrary1.cel[0].cev[13].cevr"
		;
connectAttr "character1_nurbsCircle30_rotateY.a" "clipLibrary1.cel[0].cev[14].cevr"
		;
connectAttr "character1_nurbsCircle30_rotateX.a" "clipLibrary1.cel[0].cev[15].cevr"
		;
connectAttr "character1_nurbsCircle30_visibility.a" "clipLibrary1.cel[0].cev[16].cevr"
		;
connectAttr "character1_nurbsCircle12_rotateZ.a" "clipLibrary1.cel[0].cev[17].cevr"
		;
connectAttr "character1_nurbsCircle12_rotateY.a" "clipLibrary1.cel[0].cev[18].cevr"
		;
connectAttr "character1_nurbsCircle12_rotateX.a" "clipLibrary1.cel[0].cev[19].cevr"
		;
connectAttr "character1_nurbsCircle12_translateZ.a" "clipLibrary1.cel[0].cev[20].cevr"
		;
connectAttr "character1_nurbsCircle12_translateY.a" "clipLibrary1.cel[0].cev[21].cevr"
		;
connectAttr "character1_nurbsCircle12_translateX.a" "clipLibrary1.cel[0].cev[22].cevr"
		;
connectAttr "character1_nurbsCircle12_visibility.a" "clipLibrary1.cel[0].cev[23].cevr"
		;
connectAttr "character1_nurbsCircle48_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[24].cevr"
		;
connectAttr "character1_nurbsCircle48_rotateZ.a" "clipLibrary1.cel[0].cev[25].cevr"
		;
connectAttr "character1_nurbsCircle48_rotateY.a" "clipLibrary1.cel[0].cev[26].cevr"
		;
connectAttr "character1_nurbsCircle48_rotateX.a" "clipLibrary1.cel[0].cev[27].cevr"
		;
connectAttr "character1_nurbsCircle48_visibility.a" "clipLibrary1.cel[0].cev[28].cevr"
		;
connectAttr "character1_nurbsCircle29_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[29].cevr"
		;
connectAttr "character1_nurbsCircle29_rotateZ.a" "clipLibrary1.cel[0].cev[30].cevr"
		;
connectAttr "character1_nurbsCircle29_rotateY.a" "clipLibrary1.cel[0].cev[31].cevr"
		;
connectAttr "character1_nurbsCircle29_rotateX.a" "clipLibrary1.cel[0].cev[32].cevr"
		;
connectAttr "character1_nurbsCircle29_visibility.a" "clipLibrary1.cel[0].cev[33].cevr"
		;
connectAttr "character1_nurbsCircle17_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[34].cevr"
		;
connectAttr "character1_nurbsCircle17_rotateZ.a" "clipLibrary1.cel[0].cev[35].cevr"
		;
connectAttr "character1_nurbsCircle17_rotateY.a" "clipLibrary1.cel[0].cev[36].cevr"
		;
connectAttr "character1_nurbsCircle17_rotateX.a" "clipLibrary1.cel[0].cev[37].cevr"
		;
connectAttr "character1_nurbsCircle17_visibility.a" "clipLibrary1.cel[0].cev[38].cevr"
		;
connectAttr "character1_nurbsCircle20_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[39].cevr"
		;
connectAttr "character1_nurbsCircle20_rotateZ.a" "clipLibrary1.cel[0].cev[40].cevr"
		;
connectAttr "character1_nurbsCircle20_rotateY.a" "clipLibrary1.cel[0].cev[41].cevr"
		;
connectAttr "character1_nurbsCircle20_rotateX.a" "clipLibrary1.cel[0].cev[42].cevr"
		;
connectAttr "character1_nurbsCircle20_visibility.a" "clipLibrary1.cel[0].cev[43].cevr"
		;
connectAttr "character1_nurbsCircle31_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[44].cevr"
		;
connectAttr "character1_nurbsCircle31_rotateZ.a" "clipLibrary1.cel[0].cev[45].cevr"
		;
connectAttr "character1_nurbsCircle31_rotateY.a" "clipLibrary1.cel[0].cev[46].cevr"
		;
connectAttr "character1_nurbsCircle31_rotateX.a" "clipLibrary1.cel[0].cev[47].cevr"
		;
connectAttr "character1_nurbsCircle31_visibility.a" "clipLibrary1.cel[0].cev[48].cevr"
		;
connectAttr "character1_nurbsCircle47_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[49].cevr"
		;
connectAttr "character1_nurbsCircle47_rotateZ.a" "clipLibrary1.cel[0].cev[50].cevr"
		;
connectAttr "character1_nurbsCircle47_rotateY.a" "clipLibrary1.cel[0].cev[51].cevr"
		;
connectAttr "character1_nurbsCircle47_rotateX.a" "clipLibrary1.cel[0].cev[52].cevr"
		;
connectAttr "character1_nurbsCircle47_visibility.a" "clipLibrary1.cel[0].cev[53].cevr"
		;
connectAttr "character1_nurbsCircle32_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[54].cevr"
		;
connectAttr "character1_nurbsCircle32_rotateZ.a" "clipLibrary1.cel[0].cev[55].cevr"
		;
connectAttr "character1_nurbsCircle32_rotateY.a" "clipLibrary1.cel[0].cev[56].cevr"
		;
connectAttr "character1_nurbsCircle32_rotateX.a" "clipLibrary1.cel[0].cev[57].cevr"
		;
connectAttr "character1_nurbsCircle32_visibility.a" "clipLibrary1.cel[0].cev[58].cevr"
		;
connectAttr "character1_nurbsCircle45_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[59].cevr"
		;
connectAttr "character1_nurbsCircle45_rotateZ.a" "clipLibrary1.cel[0].cev[60].cevr"
		;
connectAttr "character1_nurbsCircle45_rotateY.a" "clipLibrary1.cel[0].cev[61].cevr"
		;
connectAttr "character1_nurbsCircle45_rotateX.a" "clipLibrary1.cel[0].cev[62].cevr"
		;
connectAttr "character1_nurbsCircle45_visibility.a" "clipLibrary1.cel[0].cev[63].cevr"
		;
connectAttr "character1_nurbsCircle14_lockInfluenceWeights.a" "clipLibrary1.cel[0].cev[64].cevr"
		;
connectAttr "character1_nurbsCircle14_rotateZ.a" "clipLibrary1.cel[0].cev[65].cevr"
		;
connectAttr "character1_nurbsCircle14_rotateY.a" "clipLibrary1.cel[0].cev[66].cevr"
		;
connectAttr "character1_nurbsCircle14_rotateX.a" "clipLibrary1.cel[0].cev[67].cevr"
		;
connectAttr "character1_nurbsCircle14_translateZ.a" "clipLibrary1.cel[0].cev[68].cevr"
		;
connectAttr "character1_nurbsCircle14_translateY.a" "clipLibrary1.cel[0].cev[69].cevr"
		;
connectAttr "character1_nurbsCircle14_translateX.a" "clipLibrary1.cel[0].cev[70].cevr"
		;
connectAttr "character1_nurbsCircle14_visibility.a" "clipLibrary1.cel[0].cev[71].cevr"
		;
connectAttr "character1_nurbsCircle9_rotateZ.a" "clipLibrary1.cel[0].cev[72].cevr"
		;
connectAttr "character1_nurbsCircle9_rotateY.a" "clipLibrary1.cel[0].cev[73].cevr"
		;
connectAttr "character1_nurbsCircle9_rotateX.a" "clipLibrary1.cel[0].cev[74].cevr"
		;
connectAttr "character1_nurbsCircle9_translateZ.a" "clipLibrary1.cel[0].cev[75].cevr"
		;
connectAttr "character1_nurbsCircle9_translateY.a" "clipLibrary1.cel[0].cev[76].cevr"
		;
connectAttr "character1_nurbsCircle9_translateX.a" "clipLibrary1.cel[0].cev[77].cevr"
		;
connectAttr "character1_nurbsCircle9_visibility.a" "clipLibrary1.cel[0].cev[78].cevr"
		;
connectAttr "character1_nurbsCircle10_rotateZ.a" "clipLibrary1.cel[0].cev[79].cevr"
		;
connectAttr "character1_nurbsCircle10_rotateY.a" "clipLibrary1.cel[0].cev[80].cevr"
		;
connectAttr "character1_nurbsCircle10_rotateX.a" "clipLibrary1.cel[0].cev[81].cevr"
		;
connectAttr "character1_nurbsCircle10_translateZ.a" "clipLibrary1.cel[0].cev[82].cevr"
		;
connectAttr "character1_nurbsCircle10_translateY.a" "clipLibrary1.cel[0].cev[83].cevr"
		;
connectAttr "character1_nurbsCircle10_translateX.a" "clipLibrary1.cel[0].cev[84].cevr"
		;
connectAttr "character1_nurbsCircle10_visibility.a" "clipLibrary1.cel[0].cev[85].cevr"
		;
connectAttr "character1_nurbsCircle14_scaleZ.a" "clipLibrary1.cel[0].cev[86].cevr"
		;
connectAttr "character1_nurbsCircle14_scaleY.a" "clipLibrary1.cel[0].cev[87].cevr"
		;
connectAttr "character1_nurbsCircle14_scaleX.a" "clipLibrary1.cel[0].cev[88].cevr"
		;
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of heal.ma
