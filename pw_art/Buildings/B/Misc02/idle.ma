//Maya ASCII 2008 scene
//Name: idle_2.ma
//Last modified: Thu, Sep 17, 2009 12:36:54 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary2";
	setAttr -s 36 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 36 "CTRL_root.rotateZ" 2 1 "CTRL_root.rotateY" 
		2 2 "CTRL_root.rotateX" 2 3 "CTRL_root.translateZ" 1 1 "CTRL_root.translateY" 
		1 2 "CTRL_root.translateX" 1 3 "CTRL_plant_10.rotateZ" 2 
		4 "CTRL_plant_10.rotateY" 2 5 "CTRL_plant_10.rotateX" 2 6 "CTRL_plant_09.rotateZ" 
		2 7 "CTRL_plant_09.rotateY" 2 8 "CTRL_plant_09.rotateX" 2 
		9 "CTRL_plant_08.rotateZ" 2 10 "CTRL_plant_08.rotateY" 2 11 "CTRL_plant_08.rotateX" 
		2 12 "CTRL_plant_07.rotateZ" 2 13 "CTRL_plant_07.rotateY" 2 
		14 "CTRL_plant_07.rotateX" 2 15 "CTRL_plant_06.rotateZ" 2 16 "CTRL_plant_06.rotateY" 
		2 17 "CTRL_plant_06.rotateX" 2 18 "CTRL_plant_05.rotateZ" 2 
		19 "CTRL_plant_05.rotateY" 2 20 "CTRL_plant_05.rotateX" 2 21 "CTRL_plant_04.rotateZ" 
		2 22 "CTRL_plant_04.rotateY" 2 23 "CTRL_plant_04.rotateX" 2 
		24 "CTRL_plant_03.rotateZ" 2 25 "CTRL_plant_03.rotateY" 2 26 "CTRL_plant_03.rotateX" 
		2 27 "CTRL_plant_02.rotateZ" 2 28 "CTRL_plant_02.rotateY" 2 
		29 "CTRL_plant_02.rotateX" 2 30 "CTRL_plant_01.rotateZ" 2 31 "CTRL_plant_01.rotateY" 
		2 32 "CTRL_plant_01.rotateX" 2 33  ;
	setAttr ".cd[0].cim" -type "Int32Array" 36 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 ;
createNode animClip -n "idleSource1";
	setAttr ".ihi" 0;
	setAttr -s 36 ".ac[0:35]" yes yes yes no no no yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes;
	setAttr ".se" 110;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA1";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 1.1582023243882917 56 -1.1058442291868444 
		110 1.1582023243882917;
createNode animCurveTA -n "animCurveTA2";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 1.0991599852562401 12 0.1193845660030716 
		20 -0.027238075538902038 26 0.080410101534866524 40 1.1038137652573694 46 1.2282174122462517 
		54 1.1106271620132093 68 0.11428963801881803 76 -0.0071305163741912222 81 0.064346550147001996 
		98 1.1048395858828468 104 1.1793572935697321 110 1.0991059602575082;
	setAttr -s 13 ".kit[2:12]"  3 1 1 1 1 1 3 1 
		1 3 1;
	setAttr -s 13 ".kot[2:12]"  3 1 1 1 1 1 3 1 
		1 3 1;
	setAttr -s 13 ".kix[0:12]"  0.38317590951919556 0.34300634264945984 
		0.26666668057441711 0.21099501848220825 0.54253089427947998 0.19885478913784027 0.27605444192886353 
		0.41285181045532227 0.26666665077209473 0.18351234495639801 0.65153366327285767 0.20000004768371582 
		0.17436935007572174;
	setAttr -s 13 ".kiy[0:12]"  -0.016736702993512154 -0.008603694848716259 
		0 0.0043185180984437466 0.011906424537301064 0.0002547444892115891 -0.0056291059590876102 
		-0.0068795690312981606 0 0.0030040675774216652 0.0096826367080211639 0 -0.0025406889617443085;
	setAttr -s 13 ".kox[0:12]"  0.38317590951919556 0.27633902430534363 
		0.19999998807907104 0.5443306565284729 0.2091955840587616 0.26552140712738037 0.40938887000083923 
		0.27951702475547791 0.16666674613952637 0.65018284320831299 0.21819652616977692 0.20000004768371582 
		0.17436935007572174;
	setAttr -s 13 ".koy[0:12]"  -0.016736702993512154 -0.0069314637221395969 
		0 0.011141032911837101 0.0045910230837762356 0.00034014822449535131 -0.0083479676395654678 
		-0.0046577430330216885 0 0.010643384419381618 0.003242681035771966 0 -0.0025406889617443085;
createNode animCurveTA -n "animCurveTA3";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 0.43378333458208251 20 1.7057582625621892 
		78 -1.3839537525044801 110 0.43396056776278052;
	setAttr -s 4 ".kit[0:3]"  1 3 3 1;
	setAttr -s 4 ".kot[0:3]"  1 3 3 1;
	setAttr -s 4 ".kix[0:3]"  0.54985451698303223 0.66666668653488159 
		1.933333158493042 0.11610320955514908;
	setAttr -s 4 ".kiy[0:3]"  0.023981822654604912 0 0 0.0080813784152269363;
	setAttr -s 4 ".kox[0:3]"  0.54985451698303223 1.933333158493042 1.066666841506958 
		0.11610321700572968;
	setAttr -s 4 ".koy[0:3]"  0.023981822654604912 0 0 0.0080813812091946602;
createNode animCurveTL -n "animCurveTL1";
	setAttr ".tan" 1;
	setAttr -s 9 ".ktv[0:8]"  0 -0.045191478331340289 21 0.044890640782354753 
		28 0.044890640782354753 48 -0.047858001805748493 55 -0.047858001805748493 77 0.044890640782354753 
		84 0.044890640782354753 104 -0.045191478331340289 110 -0.045191478331340289;
	setAttr -s 9 ".kix[0:8]"  0.68728196620941162 0.68670666217803955 
		0.24109014868736267 0.64304941892623901 0.24425676465034485 0.70996338129043579 0.32719609141349792 
		0.64531880617141724 0.20133869349956512;
	setAttr -s 9 ".kiy[0:8]"  0.029832575470209122 0.021649954840540886 
		-0.011770732700824738 -0.02840372733771801 0.0089694177731871605 0.019478181377053261 
		-0.01049469318240881 -0.024277612566947937 0.0086815999820828438;
	setAttr -s 9 ".kox[0:8]"  0.68728184700012207 0.24236729741096497 
		0.68882924318313599 0.24114356935024261 0.7327696681022644 0.23665468394756317 0.93484598398208618 
		0.2016623318195343 0.20133864879608154;
	setAttr -s 9 ".koy[0:8]"  0.029832556843757629 0.0076411701738834381 
		-0.033630687743425369 -0.010651401244103909 0.026908213272690773 0.0064927381463348866 
		-0.029984856024384499 -0.0075867623090744019 0.0086815999820828438;
createNode animCurveTL -n "animCurveTL2";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 0.047414790354509587 8 0.043911433932225408 
		44 -0.0435199573988648 59 -0.0435199573988648 102 0.046781146426865233 110 0.047434956944800911;
	setAttr -s 6 ".kit[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kot[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kix[1:5]"  0.185877725481987 1.2219072580337524 0.47002917528152466 
		1.204564094543457 0.26666665077209473;
	setAttr -s 6 ".kiy[1:5]"  -0.0065023507922887802 -0.02444743737578392 
		0.010343401692807674 0.014611248858273029 0;
	setAttr -s 6 ".kox[1:5]"  1.1524392366409302 0.47299644351005554 
		1.4492578506469727 0.16277897357940674 0.26666665077209473;
	setAttr -s 6 ".koy[1:5]"  -0.040314491838216782 -0.0094635253772139549 
		0.031892184168100357 0.0019744934979826212 0;
createNode animCurveTL -n "animCurveTL3";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 0.0021867855454055047 18 -0.0016613801478439563 
		45 0.0040023354811478257 72 -0.0013000910077720904 101 0.0036836465433987514 110 
		0.0021896148581055323;
	setAttr -s 6 ".kit[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kot[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kix[0:5]"  0.41893067955970764 0.60000002384185791 
		0.89999997615814209 0.90000009536743164 0.96666646003723145 0.28168880939483643;
	setAttr -s 6 ".kiy[0:5]"  -0.0043192976154386997 0 0 0 0 -0.0026021390222012997;
	setAttr -s 6 ".kox[0:5]"  0.41893067955970764 0.89999997615814209 
		0.90000009536743164 0.96666646003723145 0.30000019073486328 0.28168883919715881;
	setAttr -s 6 ".koy[0:5]"  -0.0043192976154386997 0 0 0 0 -0.0026021401863545179;
createNode animCurveTA -n "animCurveTA4";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 -0.89581955153052106 17 -1.4548012644253951 
		44 -4.9974163497605479 67 -5.2911173649130596 95 -1.4791889810928314 110 -0.89600362086144181;
	setAttr -s 6 ".kit[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kot[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kix[1:5]"  0.58171099424362183 0.89401924610137939 
		0.73788607120513916 0.95293480157852173 0.5;
	setAttr -s 6 ".kiy[1:5]"  -0.022503064945340157 -0.037998788058757782 
		0.027375893667340279 0.037378419190645218 0;
	setAttr -s 6 ".kox[1:5]"  0.9150460958480835 0.76068633794784546 
		0.90455108880996704 0.51959842443466187 0.5;
	setAttr -s 6 ".koy[1:5]"  -0.035397883504629135 -0.032331697642803192 
		0.033559244126081467 0.020381001755595207 0;
createNode animCurveTA -n "animCurveTA5";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 0.99345006014194726 9 2.8818294764051853 
		34 -2.1033477680260941 61 2.8519902654124323 91 -2.1033477680260941 110 0.99345032786620613;
	setAttr -s 6 ".kit[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kot[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kix[0:5]"  0.23770706355571747 0.30000001192092896 
		0.83333331346511841 0.89999997615814209 1 0.49287641048431396;
	setAttr -s 6 ".kiy[0:5]"  0.035585623234510422 0 0 0 0 0.061414647847414017;
	setAttr -s 6 ".kox[0:5]"  0.23770706355571747 0.83333331346511841 
		0.89999997615814209 1 0.63333344459533691 0.49287641048431396;
	setAttr -s 6 ".koy[0:5]"  0.035585623234510422 0 0 0 0 0.061414647847414017;
createNode animCurveTA -n "animCurveTA6";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA7";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 -1.624334625602609 17 -1.0385566478146553 
		44 2.6738829859586182 67 2.9816633298196162 95 -1.0129998419657196 110 -1.6241417224713526;
	setAttr -s 6 ".kit[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kot[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kix[1:5]"  0.58171099424362183 0.89401924610137939 
		0.73788607120513916 0.95293480157852173 0.5;
	setAttr -s 6 ".kiy[1:5]"  0.023581819608807564 0.039820361882448196 
		-0.028688233345746994 -0.039170254021883011 0;
	setAttr -s 6 ".kox[1:5]"  0.9150460958480835 0.76068633794784546 
		0.90455108880996704 0.51959842443466187 0.5;
	setAttr -s 6 ".koy[1:5]"  0.037094760686159134 0.033881593495607376 
		-0.035168003290891647 -0.021358026191592216 0;
createNode animCurveTA -n "animCurveTA8";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 0.090824537949312167 13 2.4638877797192582 
		38 -1.8732159888494659 65 2.4379276687538218 95 -1.8732159888494659 110 0.091007719903452827;
	setAttr -s 6 ".kit[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kot[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kix[0:5]"  0.41007521748542786 0.43333333730697632 
		0.83333331346511841 0.90000009536743164 1 0.47433879971504211;
	setAttr -s 6 ".kiy[0:5]"  0.046160362660884857 0 0 0 0 0.041287653148174286;
	setAttr -s 6 ".kox[0:5]"  0.41007521748542786 0.83333331346511841 
		0.90000009536743164 1 0.5 0.4743388295173645;
	setAttr -s 6 ".koy[0:5]"  0.046160370111465454 0 0 0 0 0.041287653148174286;
createNode animCurveTA -n "animCurveTA9";
	setAttr ".tan" 2;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA10";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -2.1211232422302024 27 1.3526960872451397 
		54 -1.9705512701357439 81 1.1921632375348445 110 -2.121;
createNode animCurveTA -n "animCurveTA11";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -4.3069563841631942 26 -10.634296716545666 
		52 -4.3448292287870878 82 -10.634296716545666 110 -4.307;
createNode animCurveTA -n "animCurveTA12";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 8.0202658884852482 18 8.0202658884852482 
		45 8.0202658884852482 72 8.0202658884852482 101 8.0202658884852482 110 8.0202658884852482;
	setAttr -s 6 ".kit[0:5]"  9 2 2 2 2 2;
	setAttr -s 6 ".kot[0:5]"  9 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA13";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 6.2322252869796984 6 5.5958391990720013 
		33 8.8215287662919106 60 5.735656038531574 87 8.6724625399303967 110 6.2323568313195485;
	setAttr -s 6 ".kit[0:5]"  9 1 1 1 1 9;
	setAttr -s 6 ".kot[0:5]"  9 1 1 1 1 9;
	setAttr -s 6 ".kwl[0:5]" no no no no no no;
	setAttr -s 6 ".kix[1:5]"  0.37466931343078613 1.2992440462112427 
		1.1495280265808105 1.199433445930481 0.76666665077209473;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 -0.042587880045175552;
	setAttr -s 6 ".kox[1:5]"  1.074669361114502 1.2992440462112427 1.1495281457901001 
		1.0660998821258545 0.76666665077209473;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 -0.042587880045175552;
createNode animCurveTA -n "animCurveTA14";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 2.4193229090721271 8 3.9482063437563761 
		33 0.088714515580611664 60 3.9251050205056588 90 0.088714515580611664 110 2.4192724023595291;
	setAttr -s 6 ".kit[0:5]"  9 1 1 1 1 1;
	setAttr -s 6 ".kot[0:5]"  9 1 1 1 1 1;
	setAttr -s 6 ".kwl[0:5]" no no no no no no;
	setAttr -s 6 ".kix[1:5]"  0.54114699363708496 1.2824828624725342 
		1.2246824502944946 1.3493384122848511 0.5303381085395813;
	setAttr -s 6 ".kiy[1:5]"  0 0 0 0 0.051966607570648193;
	setAttr -s 6 ".kox[1:5]"  1.1078137159347534 1.3491494655609131 1.3246824741363525 
		1.0160051584243774 0.53033816814422607;
	setAttr -s 6 ".koy[1:5]"  0 0 0 0 0.051966607570648193;
createNode animCurveTA -n "animCurveTA15";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 8.0202658884852482 18 8.0202658884852482 
		45 8.0202658884852482 72 8.0202658884852482 101 8.0202658884852482 110 8.0202658884852482;
	setAttr -s 6 ".kit[0:5]"  9 2 2 2 2 2;
	setAttr -s 6 ".kot[0:5]"  9 2 2 2 2 2;
createNode animCurveTA -n "animCurveTA16";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 8.5069803012506053 27 7.1577734241375719 
		54 8.4484992114234707 81 7.2201232484343532 110 8.506993304899181;
createNode animCurveTA -n "animCurveTA17";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 0.29944204090877546 11 1.5006596764406337 
		36 -2.1892029278516905 63 1.4767258717077167 92 -2.1892029278516905 110 0.29944204090877546;
	setAttr -s 6 ".kit[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kot[0:5]"  1 3 3 3 3 1;
	setAttr -s 6 ".kix[0:5]"  0.25445458292961121 0.36666667461395264 
		0.83333337306976318 0.89999985694885254 0.96666669845581055 0.47939234972000122;
	setAttr -s 6 ".kiy[0:5]"  0.024305768311023712 0 0 0 0 0.038205545395612717;
	setAttr -s 6 ".kox[0:5]"  0.25445458292961121 0.83333337306976318 
		0.89999985694885254 0.96666669845581055 0.60000014305114746 0.47939237952232361;
	setAttr -s 6 ".koy[0:5]"  0.024305768311023712 0 0 0 0 0.038205545395612717;
createNode animCurveTA -n "animCurveTA18";
	setAttr ".tan" 2;
	setAttr -s 6 ".ktv[0:5]"  0 8.0202658884852482 18 8.0202658884852482 
		45 8.0202658884852482 72 8.0202658884852482 101 8.0202658884852482 110 8.0202658884852482;
createNode animCurveTA -n "animCurveTA19";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 11.399957793431222 4 11.399957793431222 
		30 7.4023092290655352 58 11.226680552738317 84 7.5870493825711245 110 11.214715681661694;
	setAttr -s 6 ".kit[0:5]"  2 3 3 3 3 2;
	setAttr -s 6 ".kot[0:5]"  2 3 3 3 3 2;
createNode animCurveTA -n "animCurveTA20";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 -0.228 14 2.514563467090011 40 -2.2651350060715996 
		66 2.478442633481432 96 -2.2651350060715996 110 -0.22846644831517168;
	setAttr -s 6 ".kit[0:5]"  2 3 3 3 3 2;
	setAttr -s 6 ".kot[0:5]"  2 3 3 3 3 2;
createNode animCurveTA -n "animCurveTA21";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 8.0202658884852482 110 8.0202658884852482;
createNode animCurveTA -n "animCurveTA22";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 7.8412714921999296 6 7.3046511270519918 
		33 10.024651998074283 60 7.4225489957676398 87 9.8989547612218693 110 7.8413824144419495;
	setAttr -s 6 ".kit[0:5]"  9 3 3 3 3 9;
	setAttr -s 6 ".kot[0:5]"  9 3 3 3 3 9;
createNode animCurveTA -n "animCurveTA23";
	setAttr ".tan" 3;
	setAttr -s 6 ".ktv[0:5]"  0 -0.050762747416870091 14 1.5247529356149072 
		39 -1.738947222516886 66 1.5000887081490684 95 -1.738947222516886 110 -0.050760940239779256;
	setAttr -s 6 ".kit[0:5]"  9 3 3 3 3 9;
	setAttr -s 6 ".kot[0:5]"  9 3 3 3 3 9;
createNode animCurveTA -n "animCurveTA24";
	setAttr ".tan" 9;
	setAttr ".ktv[0]"  0 8.0202658884852482;
createNode animCurveTA -n "animCurveTA25";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 3.7229898027242396 4 3.8056912094989976 
		12 3.6138118677357012 26 1.7827958346783077 32 1.5919747555902923 38 1.7650270267337116 
		52 3.6454669708090512 58 3.7771616185985271 64 3.6148396439910679 80 1.8791590417559467 
		86 1.6942754733424144 92 1.8453648476337088 110 3.7232493168233223;
	setAttr -s 13 ".kit[0:12]"  2 3 1 1 3 1 1 9 
		1 1 3 1 1;
	setAttr -s 13 ".kot[0:12]"  2 3 1 1 3 1 1 9 
		1 1 3 1 1;
	setAttr -s 13 ".kix[2:12]"  0.23754681646823883 0.47432264685630798 
		0.20000004768371582 0.20659254491329193 0.50657176971435547 0.19999992847442627 0.20435361564159393 
		0.50201696157455444 0.19999980926513672 0.20539760589599609 0.75737625360488892;
	setAttr -s 13 ".kiy[2:12]"  -0.0092389388009905815 -0.0125850485637784 
		0 0.0064199292100965977 0.016343507915735245 -0.00026727368822321296 -0.0073716738261282444 
		-0.02173638716340065 0 0.0067940806038677692 0.029116224497556686;
	setAttr -s 13 ".kox[2:12]"  0.47088080644607544 0.20765464007854462 
		0.19999992847442627 0.50659370422363281 0.20657055079936981 0.20000016689300537 0.50435435771942139 
		0.20201666653156281 0.20000004768371582 0.53873193264007568 0.75737625360488892;
	setAttr -s 13 ".koy[2:12]"  -0.018314046785235405 -0.0055096368305385113 
		0 0.015742560848593712 0.0066645783372223377 -0.00026727400836534798 -0.018193639814853668 
		-0.0087469406425952911 0 0.01782001368701458 0.029116230085492134;
createNode animCurveTA -n "animCurveTA26";
	setAttr ".tan" 9;
	setAttr -s 14 ".ktv[0:13]"  0 2.6301798238337688 4 3.2647754784759755 
		8 3.4822458933184985 16 3.034083320484847 28 0.21802521371315811 34 -0.19368064626490583 
		40 0.14742743311059889 54 3.1469437373673426 60 3.4646144719918297 66 3.1144977727274603 
		82 0.29619550639240189 90 -0.19368064626490583 96 0.30322258173266503 110 2.6301293312673089;
	setAttr -s 14 ".kit[0:13]"  2 9 9 9 9 9 9 9 
		9 9 9 9 9 9;
	setAttr -s 14 ".kot[0:13]"  2 9 9 9 9 9 9 9 
		9 9 9 9 9 9;
createNode animCurveTA -n "animCurveTA27";
	setAttr ".tan" 9;
	setAttr -s 2 ".ktv[0:1]"  0 0 110 0;
	setAttr -s 2 ".kit[1]"  2;
	setAttr -s 2 ".kot[1]"  2;
createNode animCurveTA -n "animCurveTA28";
	setAttr ".tan" 1;
	setAttr -s 13 ".ktv[0:12]"  0 0.87822911422511685 7 0.6824251401125867 
		14 0.90197855347908718 28 2.9970754875494228 34 3.2154180091524278 40 3.0174070271835389 
		55 0.86575794797957129 61 0.71506945162791102 67 0.90080254472621901 82 2.8868141593793855 
		88 3.0983628243555148 94 2.9254823693877174 110 0.87807939958928882;
	setAttr -s 13 ".kit[1:12]"  3 1 1 3 1 1 9 1 
		1 3 1 1;
	setAttr -s 13 ".kot[1:12]"  3 1 1 3 1 1 9 1 
		1 3 1 1;
	setAttr -s 13 ".kix[0:12]"  0.21954922378063202 0.23333333432674408 
		0.23754681646823883 0.47432264685630798 0.19999998807907104 0.20659254491329193 0.50657176971435547 
		0.19999992847442627 0.20435361564159393 0.50201696157455444 0.20000004768371582 0.20539760589599609 
		0.53775638341903687;
	setAttr -s 13 ".kiy[0:12]"  -0.0063878213986754417 0 0.010571444407105446 
		0.014400141313672066 0 -0.0073458547703921795 -0.018700666725635529 0.00030582171166315675 
		0.0084348637610673904 0.0248713418841362 0 -0.0077739660628139973 -0.021749032661318779;
	setAttr -s 13 ".kox[0:12]"  0.21954917907714844 0.23333333432674408 
		0.47088080644607544 0.20765464007854462 0.20000004768371582 0.50659370422363281 0.20657055079936981 
		0.20000004768371582 0.50435435771942139 0.20201666653156281 0.20000004768371582 0.53873193264007568 
		0.23775562644004822;
	setAttr -s 13 ".koy[0:12]"  -0.0063878204673528671 0 0.020955406129360199 
		0.0063042715191841125 0 -0.018013058230280876 -0.0076257884502410889 0.00030582188628613949 
		0.020817635580897331 0.010008473880589008 0 -0.02039012685418129 -0.0096157975494861603;
createNode animCurveTA -n "animCurveTA29";
	setAttr ".tan" 9;
	setAttr -s 14 ".ktv[0:13]"  0 1.9584429574387994 6 3.5021176854847562 
		11 3.8443248374884704 18 3.1391050594551335 30 -1.2921883893256321 36 -1.9400406036525983 
		42 -1.4032796633054907 56 3.3166999836349547 63 3.8165803809271166 69 3.2656436541500073 
		84 -1.1691811598207229 92 -1.9400406036525983 98 -1.1581234927773836 110 1.9584429574387994;
createNode animCurveTA -n "animCurveTA30";
	setAttr ".tan" 9;
	setAttr ".ktv[0]"  0 0;
createNode animCurveTA -n "animCurveTA31";
	setAttr ".tan" 1;
	setAttr -s 6 ".ktv[0:5]"  0 3.0673999477624889 17 2.4560137016169907 
		44 -1.4187215331809579 67 -1.7399570172780665 95 2.4293396366137805 110 3.067198621932564;
	setAttr -s 6 ".kit[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kot[0:5]"  3 1 1 1 1 3;
	setAttr -s 6 ".kix[1:5]"  0.58171099424362183 0.89401924610137939 
		0.73788607120513916 0.95293480157852173 0.5;
	setAttr -s 6 ".kiy[1:5]"  -0.024612728506326675 -0.041561178863048553 
		0.029942385852336884 0.040882643312215805 0;
	setAttr -s 6 ".kox[1:5]"  0.9150460958480835 0.76068633794784546 
		0.90455108880996704 0.51959842443466187 0.5;
	setAttr -s 6 ".koy[1:5]"  -0.03871643915772438 -0.035362794995307922 
		0.036705426871776581 0.022291721776127815 0;
createNode animCurveTA -n "animCurveTA32";
	setAttr ".tan" 1;
	setAttr -s 14 ".ktv[0:13]"  0 1.7873469146992613 3 1.85104398100405 
		9 1.6097952077095383 21 -1.3329886404974647 29 -1.776181145932973 35 -1.4525729316569658 
		49 1.6239476477282939 55 1.9979255742091739 63 1.6444298446149213 77 -1.3507254447779586 
		85 -1.7157344993512875 91 -1.5008626223964125 107 1.4843807518081871 110 1.7872153632085468;
	setAttr -s 14 ".kit[1:13]"  3 1 1 3 1 1 9 1 
		1 3 1 1 1;
	setAttr -s 14 ".kot[1:13]"  3 1 1 3 1 1 9 1 
		1 3 1 1 1;
	setAttr -s 14 ".kix[0:13]"  0.092409856617450714 0.10000000149011612 
		0.21119481325149536 0.40399795770645142 0.26666665077209473 0.21424767374992371 0.47578838467597961 
		0.20000004768371582 0.27704107761383057 0.47993725538253784 0.26666665077209473 0.21450339257717133 
		0.5366891622543335 0.10244369506835937;
	setAttr -s 14 ".kiy[0:13]"  0.0019956713076680899 0 -0.0097459033131599426 
		-0.031852394342422485 0 0.011737316846847534 0.033276453614234924 0.00015320653619710356 
		-0.016122525557875633 -0.024623239412903786 0 0.011054612696170807 0.041521597653627396 
		0.0029472291935235262;
	setAttr -s 14 ".kox[0:13]"  0.092409878969192505 0.20000001788139343 
		0.41119709610939026 0.27066421508789063 0.19999998807907104 0.48091703653335571 0.20911994576454163 
		0.26666653156280518 0.47704243659973145 0.27993535995483398 0.20000004768371582 0.54783964157104492 
		0.10335057228803635 0.10244368016719818;
	setAttr -s 14 ".koy[0:13]"  0.0019956713076680899 0 -0.018975298851728439 
		-0.021339980885386467 0 0.026346500962972641 0.014625757932662964 0.00020427523122634739 
		-0.027761716395616531 -0.014362114481627941 0 0.028233375400304794 0.0079958401620388031 
		0.0029472291935235262;
createNode animCurveTA -n "animCurveTA33";
	setAttr ".tan" 2;
	setAttr -s 2 ".ktv[0:1]"  0 0 110 0;
createNode lightLinker -n "lightLinker1";
	setAttr -s 4 ".lnk";
	setAttr -s 4 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 85;
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
	setAttr -k on ".cch";
	setAttr -k on ".nds";
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
connectAttr "idleSource1.cl" "clipLibrary2.sc[0]";
connectAttr "animCurveTA1.a" "clipLibrary2.cel[0].cev[0].cevr";
connectAttr "animCurveTA2.a" "clipLibrary2.cel[0].cev[1].cevr";
connectAttr "animCurveTA3.a" "clipLibrary2.cel[0].cev[2].cevr";
connectAttr "animCurveTL1.a" "clipLibrary2.cel[0].cev[3].cevr";
connectAttr "animCurveTL2.a" "clipLibrary2.cel[0].cev[4].cevr";
connectAttr "animCurveTL3.a" "clipLibrary2.cel[0].cev[5].cevr";
connectAttr "animCurveTA4.a" "clipLibrary2.cel[0].cev[6].cevr";
connectAttr "animCurveTA5.a" "clipLibrary2.cel[0].cev[7].cevr";
connectAttr "animCurveTA6.a" "clipLibrary2.cel[0].cev[8].cevr";
connectAttr "animCurveTA7.a" "clipLibrary2.cel[0].cev[9].cevr";
connectAttr "animCurveTA8.a" "clipLibrary2.cel[0].cev[10].cevr";
connectAttr "animCurveTA9.a" "clipLibrary2.cel[0].cev[11].cevr";
connectAttr "animCurveTA10.a" "clipLibrary2.cel[0].cev[12].cevr";
connectAttr "animCurveTA11.a" "clipLibrary2.cel[0].cev[13].cevr";
connectAttr "animCurveTA12.a" "clipLibrary2.cel[0].cev[14].cevr";
connectAttr "animCurveTA13.a" "clipLibrary2.cel[0].cev[15].cevr";
connectAttr "animCurveTA14.a" "clipLibrary2.cel[0].cev[16].cevr";
connectAttr "animCurveTA15.a" "clipLibrary2.cel[0].cev[17].cevr";
connectAttr "animCurveTA16.a" "clipLibrary2.cel[0].cev[18].cevr";
connectAttr "animCurveTA17.a" "clipLibrary2.cel[0].cev[19].cevr";
connectAttr "animCurveTA18.a" "clipLibrary2.cel[0].cev[20].cevr";
connectAttr "animCurveTA19.a" "clipLibrary2.cel[0].cev[21].cevr";
connectAttr "animCurveTA20.a" "clipLibrary2.cel[0].cev[22].cevr";
connectAttr "animCurveTA21.a" "clipLibrary2.cel[0].cev[23].cevr";
connectAttr "animCurveTA22.a" "clipLibrary2.cel[0].cev[24].cevr";
connectAttr "animCurveTA23.a" "clipLibrary2.cel[0].cev[25].cevr";
connectAttr "animCurveTA24.a" "clipLibrary2.cel[0].cev[26].cevr";
connectAttr "animCurveTA25.a" "clipLibrary2.cel[0].cev[27].cevr";
connectAttr "animCurveTA26.a" "clipLibrary2.cel[0].cev[28].cevr";
connectAttr "animCurveTA27.a" "clipLibrary2.cel[0].cev[29].cevr";
connectAttr "animCurveTA28.a" "clipLibrary2.cel[0].cev[30].cevr";
connectAttr "animCurveTA29.a" "clipLibrary2.cel[0].cev[31].cevr";
connectAttr "animCurveTA30.a" "clipLibrary2.cel[0].cev[32].cevr";
connectAttr "animCurveTA31.a" "clipLibrary2.cel[0].cev[33].cevr";
connectAttr "animCurveTA32.a" "clipLibrary2.cel[0].cev[34].cevr";
connectAttr "animCurveTA33.a" "clipLibrary2.cel[0].cev[35].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of idle_2.ma
