//Maya ASCII 2008 scene
//Name: crash.ma
//Last modified: Thu, Jul 23, 2009 03:53:35 PM
//Codeset: 1251
requires maya "2008";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Complete 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 90 ".cel[0].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 90 "joint14.rotateZ" 2 1 "joint14.rotateY" 
		2 2 "joint14.rotateX" 2 3 "joint14.translateZ" 1 1 "joint14.translateY" 
		1 2 "joint14.translateX" 1 3 "joint12.rotateZ" 2 4 "joint12.rotateY" 
		2 5 "joint12.rotateX" 2 6 "joint12.translateZ" 1 4 "joint12.translateY" 
		1 5 "joint12.translateX" 1 6 "joint13.rotateZ" 2 7 "joint13.rotateY" 
		2 8 "joint13.rotateX" 2 9 "joint13.translateZ" 1 7 "joint13.translateY" 
		1 8 "joint13.translateX" 1 9 "joint11.rotateZ" 2 10 "joint11.rotateY" 
		2 11 "joint11.rotateX" 2 12 "joint11.translateZ" 1 10 "joint11.translateY" 
		1 11 "joint11.translateX" 1 12 "joint10.rotateZ" 2 13 "joint10.rotateY" 
		2 14 "joint10.rotateX" 2 15 "joint10.translateZ" 1 13 "joint10.translateY" 
		1 14 "joint10.translateX" 1 15 "joint7.rotateZ" 2 16 "joint7.rotateY" 
		2 17 "joint7.rotateX" 2 18 "joint7.translateZ" 1 16 "joint7.translateY" 
		1 17 "joint7.translateX" 1 18 "joint8.rotateZ" 2 19 "joint8.rotateY" 
		2 20 "joint8.rotateX" 2 21 "joint8.translateZ" 1 19 "joint8.translateY" 
		1 20 "joint8.translateX" 1 21 "joint9.rotateZ" 2 22 "joint9.rotateY" 
		2 23 "joint9.rotateX" 2 24 "joint9.translateZ" 1 22 "joint9.translateY" 
		1 23 "joint9.translateX" 1 24 "joint6.rotateZ" 2 25 "joint6.rotateY" 
		2 26 "joint6.rotateX" 2 27 "joint6.translateZ" 1 25 "joint6.translateY" 
		1 26 "joint6.translateX" 1 27 "joint3.rotateZ" 2 28 "joint3.rotateY" 
		2 29 "joint3.rotateX" 2 30 "joint3.translateZ" 1 28 "joint3.translateY" 
		1 29 "joint3.translateX" 1 30 "joint4.rotateZ" 2 31 "joint4.rotateY" 
		2 32 "joint4.rotateX" 2 33 "joint4.translateZ" 1 31 "joint4.translateY" 
		1 32 "joint4.translateX" 1 33 "joint5.rotateZ" 2 34 "joint5.rotateY" 
		2 35 "joint5.rotateX" 2 36 "joint5.translateZ" 1 34 "joint5.translateY" 
		1 35 "joint5.translateX" 1 36 "joint2.rotateZ" 2 37 "joint2.rotateY" 
		2 38 "joint2.rotateX" 2 39 "joint2.translateZ" 1 37 "joint2.translateY" 
		1 38 "joint2.translateX" 1 39 "root.rotateZ" 2 40 "root.rotateY" 
		2 41 "root.rotateX" 2 42 "root.translateZ" 1 40 "root.translateY" 
		1 41 "root.translateX" 1 42 "joint15.rotateZ" 2 43 "joint15.rotateY" 
		2 44 "joint15.rotateX" 2 45 "joint15.translateZ" 1 43 "joint15.translateY" 
		1 44 "joint15.translateX" 1 45  ;
	setAttr ".cd[0].cim" -type "Int32Array" 90 0 1 2 3 4
		 5 6 7 8 9 10 11 12 13 14 15 16
		 17 18 19 20 21 22 23 24 25 26 27 28
		 29 30 31 32 33 34 35 36 37 38 39 40
		 41 42 43 44 45 46 47 48 49 50 51 52
		 53 54 55 56 57 58 59 60 61 62 63 64
		 65 66 67 68 69 70 71 72 73 74 75 76
		 77 78 79 80 81 82 83 84 85 86 87 88
		 89 ;
createNode animClip -n "clip1Source";
	setAttr ".ihi" 0;
	setAttr -s 90 ".ac[0:89]" yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes yes 
		yes yes yes yes yes yes yes no no no yes yes yes yes yes yes;
	setAttr ".se" 100;
	setAttr ".ci" no;
createNode animCurveTA -n "joint14_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 -0.07042757134107526 6 -0.27264961514744585 
		9 -0.62246194248826858 12 -1.3071515518473489 15 -1.8645771489745824 18 -1.9140841160181532 
		100 -1.9140841160181532;
createNode animCurveTA -n "joint14_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 4.285691380240543 6 8.4501774413380666 
		9 11.416077137824502 12 12.914045264175209 15 13.927191814557958 18 14.345711061027021 
		100 14.345711061027021;
createNode animCurveTA -n "joint14_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 0 3 0.22992340988151211 6 0.44921462814670304 
		9 -0.28454693250314245 12 -4.5627275260975022 15 -10.314477034714889 18 -11.986132881285412 
		100 -11.986132881285412;
createNode animCurveTL -n "joint14_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 7.7697551478709901 27 5.8676315968700639 
		36 5.7308261864818348 42 4.9697565465002977 45 4.1392550673484907 48 2.953187316107746 
		51 1.4459106698061011 54 -0.34598145564289218 60 -4.6372384803287137 66 -9.6278364306413078 
		84 -25.868202562255572 90 -30.728690941991108 100 -30.728690941991108;
createNode animCurveTL -n "joint14_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 2.2785475567443649 12 2.2785475567443645 
		15 2.2785475567443645 18 2.278547556744364 100 2.278547556744364;
createNode animCurveTL -n "joint14_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 -1.6718924220379574 3 -1.6718924220379576 
		6 -1.6718924220379578 9 -1.6718924220379581 12 -1.6718924220379583 100 -1.6718924220379583;
createNode animCurveTA -n "joint12_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "joint12_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "joint12_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 12 -5.9930844018127054 100 -5.9930844018127054;
createNode animCurveTL -n "joint12_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 8 ".ktv[0:7]"  0 7.787426491775558 9 7.4901584208897978 
		24 6.0637925478036374 30 5.1437559487122133 33 4.4955985249151222 51 -0.62172816152485044 
		90 -13.109659778025344 100 -13.109659778025344;
createNode animCurveTL -n "joint12_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.0310572987263578 100 -1.0310572987263578;
createNode animCurveTL -n "joint12_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.9637141351894833 100 -1.9637141351894833;
createNode animCurveTA -n "joint13_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.17688091490585073 6 -0.598673865835187 
		9 -1.1021041621056851 12 -1.5238971130350221 15 -1.7007780279408728 100 -1.7007780279408728;
createNode animCurveTA -n "joint13_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 0 3 -0.81968998676240379 6 -2.8746594998782542 
		9 -5.635503042245583 12 -8.5728151167624205 15 -11.157190226326799 100 -11.157190226326799;
createNode animCurveTA -n "joint13_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 0 15 -6.4574474076144588 100 -6.4574474076144588;
createNode animCurveTL -n "joint13_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 19 ".ktv[0:18]"  0 7.6016166768447349 12 7.1714615010736873 
		15 6.6459769292708257 21 5.0343019855859543 24 5.1269128301630493 33 5.8311463658744511 
		36 5.6595956347799765 39 5.0376374253469587 45 3.2706003484901305 51 1.1629545185362431 
		72 -7.0773398318737808 78 -9.1587879207062119 84 -10.88798381594316 87 -11.581120091719429 
		90 -12.138952800004153 93 -12.28188057807983 96 -11.846032017613306 99 -10.98925521048354 
		100 -10.637407107840582;
createNode animCurveTL -n "joint13_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -1.3366057593044516 3 -1.3440958390121052 
		6 -1.3545819500313725 9 -1.361368099663314 12 -1.3807135649222233 15 -1.3923208437085834 
		100 -1.3923208437085834;
createNode animCurveTL -n "joint13_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 1.9328227402157536 3 1.9458735585870262 
		6 1.9641447033111092 9 1.9720974203633115 12 1.996015094724457 15 2.0218986051891359 
		100 2.0218986051891359;
createNode animCurveTA -n "joint11_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 21 -0.077341470563338927 24 -1.0851836930374639 
		27 -2.0811909438249212 30 -1.9536235338300438 33 -1.257541391694776 39 0.60886282424538962 
		42 1.2491992351683472 84 4.6951080924091224 90 5.1012246208707408 100 5.1012246208707408;
createNode animCurveTA -n "joint11_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 21 -1.7603138287400633 24 -7.9029156615919485 
		27 -12.388431075516719 30 -12.987207036201722 39 -13.381552507659826 42 -13.755881177133205 
		87 -24.527891606828529 90 -25.127165696954606 100 -25.127165696954606;
createNode animCurveTA -n "joint11_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 21 3.0917798016485714 24 7.8106169587509582 
		30 10.764961844841411 33 11.874726065121139 36 12.616832488394857 42 13.9679317846023 
		45 14.586351694597056 90 22.84123430770968 100 22.84123430770968;
createNode animCurveTL -n "joint11_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 6.2023272794565214 36 6.0571570295580628 
		39 5.5342545478666256 42 4.6128800872055109 45 3.3299853672452686 48 1.7225276943902503 
		51 -0.17252876248448087 57 -4.6775419197156491 63 -9.8891775547454728 81 -26.803159573415655 
		87 -31.880150589565442 90 -34.146799221425809 100 -34.146799221425809;
createNode animCurveTL -n "joint11_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -2.7675641056509757 21 -2.7685620850211494 
		24 -2.7714718921933743 30 -2.7825262300089393 36 -2.7997267211374091 42 -2.822058306487552 
		51 -2.8628724632322173 78 -3.0029685726623883 87 -3.0433143746535571 90 -3.0550115334000196 
		100 -3.0550115334000196;
createNode animCurveTL -n "joint11_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 23 ".ktv[0:22]"  0 -2.8921500211591717 18 -2.8921500211591717 
		21 -2.8926162199285415 24 -2.8939611267422953 27 -2.8960865872847434 30 -2.8988753741241577 
		33 -2.9021963498455148 36 -2.9059092457421252 48 -2.9217951872688963 51 -2.9253379419444459 
		54 -2.9284668471481985 57 -2.9310851943151719 60 -2.9331140982056985 63 -2.9344943118338436 
		66 -2.9351876081633361 69 -2.9351777019567469 72 -2.9344706903154196 75 -2.9330949969614788 
		78 -2.9311008126275868 81 -2.9285590314313588 84 -2.9255596902075545 90 -2.9186314544312637 
		100 -2.9186314544312637;
createNode animCurveTA -n "joint10_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0 21 -0.081211848923077534 24 -0.95662761053547563 
		27 -1.2089994916026914 30 -0.78208993073295074 33 -0.12023832486687092 36 0.58743046639524299 
		39 1.1582327001802335 45 1.7589576965061695 48 2.1758329741918745 54 3.0700117157508049 
		81 6.0842238249418745 90 6.9408169249018057 100 6.9408169249018057;
createNode animCurveTA -n "joint10_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 21 -1.03093209337849 24 -4.2388359669256781 
		27 -6.5816002289128548 33 -10.807954486037648 36 -12.641933911635014 39 -13.936124449137637 
		42 -14.379024570251778 45 -13.458892640765505 48 -11.64250117754743 51 -9.629620925409732 
		54 -8.7684468964596096 81 -15.664077326297454 90 -17.625719099855608 100 -17.625719099855608;
createNode animCurveTA -n "joint10_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 0 24 0.013878484770466649 27 0.15529434405823045 
		30 0.59346376541795554 33 1.2290773848526697 39 2.5675280508413487 42 3.0339147692474566 
		54 4.8315139949840642 81 9.6888362921765321 90 11.087409100801725 100 11.087409100801725;
createNode animCurveTL -n "joint10_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 5.9008226677411457 36 5.7429193970179124 
		39 5.2159033888830173 42 4.2900100859729786 45 3.0022525564491969 48 1.38964846546405 
		51 -0.51077905044362448 57 -5.0269813790147015 63 -10.250045904888401 81 -27.196032261873786 
		87 -32.281894739693861 90 -34.552495228764968 100 -34.552495228764968;
createNode animCurveTL -n "joint10_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 -2.5422185653779161 21 -2.5432955264234374 
		24 -2.5464350516756729 30 -2.5583544046512543 36 -2.5768769100217042 42 -2.6008820665989956 
		51 -2.6446328383339148 78 -2.7936669532606619 87 -2.8362721498119132 90 -2.8485986579940037 
		100 -2.8485986579940037;
createNode animCurveTL -n "joint10_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 22 ".ktv[0:21]"  0 -3.5299657845189123 21 -3.530270296808049 
		24 -3.5311428588289293 27 -3.5325031024434064 30 -3.534250265371091 42 -3.5426836288535495 
		45 -3.5445126793310577 48 -3.5459842403499628 51 -3.5469912216885247 54 -3.5474407324698389 
		57 -3.5472567269154558 60 -3.5463822251893715 63 -3.5447810847443915 66 -3.5424392996648386 
		69 -3.5393658094649361 72 -3.5355928042547928 75 -3.531175519645311 78 -3.5261915216898325 
		81 -3.5207394889843782 87 -3.5089208802737923 90 -3.5028395217261652 100 -3.5028395217261652;
createNode animCurveTA -n "joint7_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 30 0 63 -399.03167110060741 100 -399.03167110060741;
createNode animCurveTA -n "joint7_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 30 0 60 -14.081182610977054 100 -14.081182610977059;
createNode animCurveTA -n "joint7_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 30 0 72 888.67539313488101 100 888.67539313488101;
createNode animCurveTL -n "joint7_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 5.5202200782152548 30 5.5202200782152548 
		60 -8.4896383147418497 100 -8.4896383147418462;
createNode animCurveTL -n "joint7_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 -5.7649417681673834 30 -5.7649417681673834 
		33 -5.7649417681673834 36 -5.7649417681673851 39 -5.7649417681673842 42 -5.7649417681673834 
		48 -5.7649417681673869 51 -5.764941768167386 54 -5.764941768167386 57 -5.7649417681673869 
		60 -5.764941768167386 63 -5.7649417681673834 69 -5.7649417681673851 72 -5.764941768167386 
		100 -5.764941768167386;
createNode animCurveTL -n "joint7_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 17 ".ktv[0:16]"  0 0 30 0 33 1.4003794986045772e-015 36 
		3.9560780615127163e-017 39 -2.0771250973801006e-015 42 -1.0907947783859039e-015 45 
		-3.8673886420605001e-016 48 -1.7758376709716669e-015 51 -1.1310382216423761e-015 
		54 1.1667301893258019e-015 57 1.0908800136589547e-015 60 4.9596012779470123e-016 
		63 1.5944154751490713e-015 66 1.0279407990500864e-015 69 -7.795947583429137e-016 
		72 -1.2723175907843589e-015 100 -1.2723175907843589e-015;
createNode animCurveTA -n "joint8_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 24 0 60 21.729328437971706 100 21.729328437971706;
createNode animCurveTA -n "joint8_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 24 0 60 22.282109957751832 100 22.282109957751832;
createNode animCurveTA -n "joint8_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 24 0 60 -95.703886532744761 100 -95.703886532744761;
createNode animCurveTL -n "joint8_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 5.1101461023968939 24 5.1101461023968939 
		60 -9.5426368782546493 100 -9.5426368782546493;
createNode animCurveTL -n "joint8_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 -6.5395259447131782 36 -6.5395259447131791 
		45 -6.5395259447131791 48 -6.5395259447131799 54 -6.5395259447131808 60 -6.5395259447131817 
		100 -6.5395259447131817;
createNode animCurveTL -n "joint8_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 14 ".ktv[0:13]"  0 0.47941670297323813 24 0.47941670297323813 
		27 0.47941670297323802 30 0.47941670297323791 33 0.4794167029732378 36 0.47941670297323769 
		39 0.47941670297323752 42 0.47941670297323741 45 0.4794167029732373 48 0.47941670297323724 
		51 0.47941670297323719 57 0.47941670297323724 60 0.4794167029732373 100 0.4794167029732373;
createNode animCurveTA -n "joint9_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 21 1.8544861714531986 60 74.179416279757632 
		100 74.179416279757632;
createNode animCurveTA -n "joint9_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 21 0.1916116975857042 60 7.6644640217985893 
		100 7.6644640217985893;
createNode animCurveTA -n "joint9_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 21 1.5060847494213969 60 60.24336432378005 
		100 60.24336432378005;
createNode animCurveTL -n "joint9_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 4.6545083514876024 21 4.6282401195921317 
		60 -12.58970155018566 100 -12.58970155018566;
	setAttr -s 4 ".kit[1:3]"  3 10 10;
	setAttr -s 4 ".kot[1:3]"  3 10 10;
createNode animCurveTL -n "joint9_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -7.3029564692028384 45 -7.3029564692028393 
		100 -7.3029564692028393;
createNode animCurveTL -n "joint9_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0.86927204385257384 21 0.86927204385257373 
		24 0.86927204385257362 27 0.8692720438525734 30 0.86927204385257317 33 0.86927204385257306 
		36 0.86927204385257284 39 0.86927204385257273 42 0.86927204385257262 45 0.86927204385257251 
		48 0.8692720438525724 54 0.86927204385257228 57 0.86927204385257228 60 0.8692720438525724 
		100 0.8692720438525724;
createNode animCurveTA -n "joint6_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 21 ".ktv[0:20]"  0 0 3 0.16946368550839008 6 0.087842428660663899 
		9 -0.92707148131706907 12 -1.9676661375237197 15 -2.7821983324064155 18 -3.2766108384581716 
		21 -3.2564114600763072 24 -2.9988758799524935 33 -1.8621688327286541 36 -1.6679212107072912 
		39 -1.6339680279306366 42 -1.536680817029338 45 -1.3638334331362842 48 -1.1228988607864649 
		51 -0.82135008451487157 57 -0.066301858346319992 63 0.84152736908944803 84 4.3589503363025903 
		90 5.2144686004767937 100 5.2144686004767937;
createNode animCurveTA -n "joint6_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 3 -2.1706883824729997 6 -2.9859210023378062 
		9 -0.89583845567756026 12 2.279934302989596 15 5.5535379413950485 18 7.9733032695590342 
		21 8.2019240371867426 27 8.0294416784525655 30 7.7669401306157404 33 7.3068872646009435 
		36 6.589249776009555 39 5.7134164889835946 42 5.1505872242930373 45 4.9083826054334532 
		48 4.9550925015672576 51 5.2590067818568702 54 5.7884153154647082 57 6.5116079715531896 
		60 7.3968746192847368 66 9.5267893663266818 81 15.468161929054416 87 17.425432484605434 
		90 18.187381852700586 100 18.187381852700586;
createNode animCurveTA -n "joint6_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 0.071655475329308715 6 -0.70204728545275386 
		12 -7.8028718655973224 15 -7.8219031082175849 18 -6.5538100179009735 21 -4.5532598807198399 
		24 -3.1534016935151334 27 -2.267833883772985 36 -0.73284832379035936 42 0.86495818875687591 
		48 2.9002164335474143 57 6.5688621766017397 90 22.00740998790171 100 22.00740998790171;
createNode animCurveTL -n "joint6_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 9.4204662649497326 6 9.2145967705551381 
		12 8.5071599179980311 21 6.8144222336762557 33 6.9412532706346166 36 6.8450119656207757 
		39 6.5773830401659783 42 6.1269918412363724 45 5.5099717503845094 48 4.7428025489512073 
		54 2.8239359397035475 60 0.50223026421992512 84 -10.176218085543551 90 -12.534545331309006 
		100 -12.534545331309006;
createNode animCurveTL -n "joint6_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 15 ".ktv[0:14]"  0 0 3 4.8410893345021036e-018 6 -4.3246684627404662e-017 
		12 -4.7724276704987955e-016 15 -4.6640078224078613e-016 18 -3.7684785606243308e-016 
		21 -2.5287965641930157e-016 24 -1.6884175349786808e-016 27 -1.1777502411511877e-016 
		36 -3.3555793922597425e-017 42 6.2163769389204151e-017 48 1.8572705918605184e-016 
		81 1.0314313162570187e-015 90 1.232348997365969e-015 100 1.232348997365969e-015;
createNode animCurveTL -n "joint6_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 25 ".ktv[0:24]"  0 0 3 1.3455086885101788e-016 6 1.8511549687564584e-016 
		9 5.0166505689157044e-017 12 -1.5650360562974549e-016 15 -3.6368539755224285e-016 
		18 -5.1195867792710426e-016 21 -5.2044330528607718e-016 27 -5.0176810940811925e-016 
		30 -4.8362378542157779e-016 33 -4.5402741076677712e-016 36 -4.0879316100623286e-016 
		39 -3.5353480981780091e-016 42 -3.1735092997243636e-016 45 -3.0103093519000934e-016 
		48 -3.028907669431728e-016 51 -3.2118978752643477e-016 54 -3.5411670903954605e-016 
		57 -3.9977820484933184e-016 60 -4.5619422207117388e-016 66 -5.9297046385767977e-016 
		81 -9.7348944810086201e-016 87 -1.0969164229891645e-015 90 -1.1448329794463466e-015 
		100 -1.1448329794463466e-015;
createNode animCurveTA -n "joint3_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 33 -0.043666008296139085 36 -0.68043129480906528 
		39 -2.0280046278597186 42 -4.0248737770062464 45 -6.6095265118067994 48 -9.7204506018195271 
		54 -17.2750639257141 60 -26.196615905155166 81 -61.082027129593691 87 -70.065092245250696 
		90 -74.085031111839513 100 -74.085031111839513;
createNode animCurveTA -n "joint3_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 16 ".ktv[0:15]"  0 0 33 -0.0019567205482342123 36 -0.030215448892544329 
		39 -0.089190198673531063 42 -0.17519504738909658 45 -0.28454407253714287 48 -0.41355135161557283 
		54 -0.71579698155519222 69 -1.5574159250390966 75 -1.8510610773425467 78 -1.9739251581094299 
		81 -2.0759023452836187 84 -2.1533067163630166 87 -2.2024523488455392 90 -2.2196533202290505 
		100 -2.2196533202290505;
createNode animCurveTA -n "joint3_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 33 0.14825040087396216 36 2.3101312912980649 
		39 6.8852755318084338 42 13.664843031753788 45 22.43999370048283 48 33.001887447344281 
		54 58.650543812859262 60 88.940091403088417 81 207.37949589329108 87 237.87788502025674 
		90 251.52597234258667 100 251.52597234258667;
createNode animCurveTL -n "joint3_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 5.0471181240412024 33 5.0259588238486641 
		36 4.7174005572748952 39 4.0644050193702945 42 3.0967792814164898 45 1.8443304146951065 
		48 0.33686549048777009 54 -3.3238842452582582 60 -7.6470133555685855 81 -24.551486083320803 
		87 -28.904422322289513 90 -30.852369566729465 100 -30.852369566729465;
createNode animCurveTL -n "joint3_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 2.3453818186648929 33 2.3469224401783366 
		36 2.3693887552269199 39 2.416933757580733 42 2.4873871763662918 45 2.5785787407101095 
		48 2.6883381797387025 54 2.9548795983562739 60 3.2696492652311258 81 4.5004742684316792 
		87 4.8174142359892844 90 4.9592454788888078 100 4.9592454788888078;
createNode animCurveTL -n "joint3_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 1.8063629467824338 33 1.807238088749358 
		36 1.8199999611062341 39 1.8470076500993142 42 1.887028344666942 45 1.9388292337474615 
		48 2.001177506279217 54 2.1525849574498097 60 2.3313882096854717 81 3.0305518482764309 
		87 3.2105879102009514 90 3.2911543895761142 100 3.2911543895761142;
createNode animCurveTA -n "joint4_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 21 0.02312090992458941 24 0.090515902629664885 
		30 0.34632171396911754 36 0.74380458919404524 42 1.2593516834801339 51 2.2023896375957612 
		81 5.8574610402764131 90 6.8004989450531079 100 6.8004989450531079;
createNode animCurveTA -n "joint4_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 21 -0.047988912681833286 24 -0.18787148801206488 
		30 -0.71881265032611263 36 -1.5438135343589234 42 -2.6138641875272763 51 -4.5711992131331547 
		81 -12.157531705521786 90 -14.114866791767229 100 -14.114866791767229;
createNode animCurveTA -n "joint4_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 10 ".ktv[0:9]"  0 0 21 0.033893458995112133 24 0.13268928622297199 
		30 0.50768074683207565 36 1.0903597847375925 42 1.8461118028498047 51 3.2285322367719167 
		81 8.5865832016086934 90 9.9690035844223086 100 9.9690035844223086;
createNode animCurveTL -n "joint4_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 5.0471181240412024 36 4.9471519970686453 
		39 4.4393698590342838 42 3.5349043398739326 45 2.2705611150478591 48 0.6831458600163326 
		51 -1.1905357497603812 57 -5.6494753317082926 63 -10.811812227113734 81 -27.574752757253783 
		87 -32.606224869667898 90 -34.852052624247648 100 -34.852052624247648;
createNode animCurveTL -n "joint4_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 3 ".ktv[0:2]"  0 -1.5281790664790873 54 -1.5281790664790871 
		100 -1.5281790664790871;
createNode animCurveTL -n "joint4_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -2.1126896137386342 100 -2.1126896137386342;
createNode animCurveTA -n "joint5_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "joint5_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "joint5_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "joint5_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 7 ".ktv[0:6]"  0 5.0471181240412024 39 5.0053649565555851 
		42 4.6500509549228362 45 4.003444542215167 84 -10.096526436844368 90 -12.408220030032069 
		100 -12.408220030032069;
createNode animCurveTL -n "joint5_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 -1.6828350861494783 100 -1.6828350861494783;
createNode animCurveTL -n "joint5_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 1.9901652258174312 100 1.9901652258174312;
createNode animCurveTA -n "joint2_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 39 0.24434515745654201 42 1.4831037713404236 
		45 3.6839705000074785 48 6.7517917876949172 51 10.591414078639948 54 15.10768381707979 
		60 25.789551413392722 69 44.508369770003462 81 70.502909899444433 87 82.231465526417608 
		90 87.445527285297558 100 87.445527285297558;
createNode animCurveTA -n "joint2_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 39 0.041045691614866785 42 0.2491353652964704 
		45 0.61884229173826488 48 1.1341823463453862 51 1.7791714045229681 54 2.5378253416761489 
		60 4.3321913545298445 69 7.4766238512557619 81 11.843249771804034 87 13.813441028619355 
		90 14.689311795080286 100 14.689311795080286;
createNode animCurveTA -n "joint2_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 0 39 0.64280805495813831 42 3.9016572350957484 
		45 9.6915606630511242 48 17.7621942857234 51 27.863234050011719 54 39.744355902815222 
		60 67.84554966156432 69 117.08985463603031 81 185.47467779958777 87 216.32943493880941 
		90 230.04626571192787 100 230.04626571192787;
createNode animCurveTL -n "joint2_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 5.0471181240412024 39 4.9890525849319767 
		42 4.6946772530279555 45 4.1716690838294026 48 3.442640116754248 51 2.5302023912204206 
		54 1.4569679466458485 60 -1.0814429419538121 69 -5.5297336822106651 81 -11.70700790740054 
		87 -14.494151126835934 90 -15.733207125301004 100 -15.733207125301004;
createNode animCurveTL -n "joint2_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 2.8770868166569961 39 2.8827792474110585 
		42 2.9116382095042597 45 2.9629110958084537 48 3.0343811445121602 51 3.1238315938038976 
		54 3.2290456818721869 60 3.4778977270924942 69 3.9139840404600705 81 4.519570520537262 
		87 4.7928069317922466 90 4.914277263883652 100 4.914277263883652;
createNode animCurveTL -n "joint2_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 13 ".ktv[0:12]"  0 -1.9695094698315831 39 -1.9760714015318921 
		42 -2.009338479559589 45 -2.0684431383577002 48 -2.1508300126486728 51 -2.253943737154954 
		54 -2.3752289465989906 60 -2.6620923591901198 69 -3.1647894831711585 81 -3.8628773829981013 
		87 -4.1778497869951465 90 -4.3178743240431272 100 -4.3178743240431272;
createNode animCurveTA -n "root_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "root_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "root_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "root_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "root_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTL -n "root_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 2 ".ktv[0:1]"  0 0 100 0;
createNode animCurveTA -n "joint15_rotateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 0 6 -0.053830414842934826 9 -0.6545777166001604 
		12 -1.3715986234906079 15 -1.5696944177872072 100 -1.5696944177872072;
createNode animCurveTA -n "joint15_rotateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 -1.9835406219177281 15 -17.85186397340323 
		100 -17.85186397340323;
createNode animCurveTA -n "joint15_rotateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 4 ".ktv[0:3]"  0 0 6 -0.6619660217142922 15 -5.9576935399934303 
		100 -5.9576935399934303;
createNode animCurveTL -n "joint15_translateZ";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 11 ".ktv[0:10]"  0 7.8203054891045216 6 7.7993444173597579 
		9 7.5273679652757863 15 6.484376850140448 21 4.9030419354544881 24 4.8217547446821127 
		30 5.6294628693819062 33 5.3931307114227875 48 1.3334234668311755 90 -11.820981047999963 
		100 -11.820981047999963;
createNode animCurveTL -n "joint15_translateY";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 6 ".ktv[0:5]"  0 1.8374269333295208 6 1.8374269333295208 
		9 1.8374269333295206 12 1.8374269333295203 15 1.8374269333295201 100 1.8374269333295201;
createNode animCurveTL -n "joint15_translateX";
	setAttr ".tan" 10;
	setAttr ".wgt" no;
	setAttr -s 5 ".ktv[0:4]"  0 1.3742257752306215 6 1.3742257752306217 
		12 1.3742257752306228 15 1.3742257752306233 100 1.3742257752306233;
createNode lightLinker -n "lightLinker1";
	setAttr -s 22 ".lnk";
	setAttr -s 22 ".slnk";
select -ne :time1;
	setAttr -av -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr ".o" 130;
select -ne :renderPartition;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 15 ".st";
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
	setAttr -s 15 ".s";
select -ne :postProcessList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -s 13 ".u";
select -ne :lightList1;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -k on ".nds";
	setAttr -cb on ".bnm";
select -ne :defaultTextureList1;
	setAttr -s 30 ".tx";
select -ne :lambert1;
	setAttr ".c" -type "float3" 0.32749999 0.46414876 0.5 ;
select -ne :initialShadingGroup;
	setAttr -k on ".cch";
	setAttr -k on ".ihi";
	setAttr -av -k on ".nds";
	setAttr -cb on ".bnm";
	setAttr -s 3 ".dsm";
	setAttr -k on ".mwc";
	setAttr -k on ".an";
	setAttr -k on ".il";
	setAttr -k on ".vo";
	setAttr -k on ".eo";
	setAttr -k on ".fo";
	setAttr -k on ".epo";
	setAttr ".ro" yes;
	setAttr -s 120 ".gn";
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
connectAttr "clip1Source.cl" "clipLibrary1.sc[0]";
connectAttr "joint14_rotateZ.a" "clipLibrary1.cel[0].cev[0].cevr";
connectAttr "joint14_rotateY.a" "clipLibrary1.cel[0].cev[1].cevr";
connectAttr "joint14_rotateX.a" "clipLibrary1.cel[0].cev[2].cevr";
connectAttr "joint14_translateZ.a" "clipLibrary1.cel[0].cev[3].cevr";
connectAttr "joint14_translateY.a" "clipLibrary1.cel[0].cev[4].cevr";
connectAttr "joint14_translateX.a" "clipLibrary1.cel[0].cev[5].cevr";
connectAttr "joint12_rotateZ.a" "clipLibrary1.cel[0].cev[6].cevr";
connectAttr "joint12_rotateY.a" "clipLibrary1.cel[0].cev[7].cevr";
connectAttr "joint12_rotateX.a" "clipLibrary1.cel[0].cev[8].cevr";
connectAttr "joint12_translateZ.a" "clipLibrary1.cel[0].cev[9].cevr";
connectAttr "joint12_translateY.a" "clipLibrary1.cel[0].cev[10].cevr";
connectAttr "joint12_translateX.a" "clipLibrary1.cel[0].cev[11].cevr";
connectAttr "joint13_rotateZ.a" "clipLibrary1.cel[0].cev[12].cevr";
connectAttr "joint13_rotateY.a" "clipLibrary1.cel[0].cev[13].cevr";
connectAttr "joint13_rotateX.a" "clipLibrary1.cel[0].cev[14].cevr";
connectAttr "joint13_translateZ.a" "clipLibrary1.cel[0].cev[15].cevr";
connectAttr "joint13_translateY.a" "clipLibrary1.cel[0].cev[16].cevr";
connectAttr "joint13_translateX.a" "clipLibrary1.cel[0].cev[17].cevr";
connectAttr "joint11_rotateZ.a" "clipLibrary1.cel[0].cev[18].cevr";
connectAttr "joint11_rotateY.a" "clipLibrary1.cel[0].cev[19].cevr";
connectAttr "joint11_rotateX.a" "clipLibrary1.cel[0].cev[20].cevr";
connectAttr "joint11_translateZ.a" "clipLibrary1.cel[0].cev[21].cevr";
connectAttr "joint11_translateY.a" "clipLibrary1.cel[0].cev[22].cevr";
connectAttr "joint11_translateX.a" "clipLibrary1.cel[0].cev[23].cevr";
connectAttr "joint10_rotateZ.a" "clipLibrary1.cel[0].cev[24].cevr";
connectAttr "joint10_rotateY.a" "clipLibrary1.cel[0].cev[25].cevr";
connectAttr "joint10_rotateX.a" "clipLibrary1.cel[0].cev[26].cevr";
connectAttr "joint10_translateZ.a" "clipLibrary1.cel[0].cev[27].cevr";
connectAttr "joint10_translateY.a" "clipLibrary1.cel[0].cev[28].cevr";
connectAttr "joint10_translateX.a" "clipLibrary1.cel[0].cev[29].cevr";
connectAttr "joint7_rotateZ.a" "clipLibrary1.cel[0].cev[30].cevr";
connectAttr "joint7_rotateY.a" "clipLibrary1.cel[0].cev[31].cevr";
connectAttr "joint7_rotateX.a" "clipLibrary1.cel[0].cev[32].cevr";
connectAttr "joint7_translateZ.a" "clipLibrary1.cel[0].cev[33].cevr";
connectAttr "joint7_translateY.a" "clipLibrary1.cel[0].cev[34].cevr";
connectAttr "joint7_translateX.a" "clipLibrary1.cel[0].cev[35].cevr";
connectAttr "joint8_rotateZ.a" "clipLibrary1.cel[0].cev[36].cevr";
connectAttr "joint8_rotateY.a" "clipLibrary1.cel[0].cev[37].cevr";
connectAttr "joint8_rotateX.a" "clipLibrary1.cel[0].cev[38].cevr";
connectAttr "joint8_translateZ.a" "clipLibrary1.cel[0].cev[39].cevr";
connectAttr "joint8_translateY.a" "clipLibrary1.cel[0].cev[40].cevr";
connectAttr "joint8_translateX.a" "clipLibrary1.cel[0].cev[41].cevr";
connectAttr "joint9_rotateZ.a" "clipLibrary1.cel[0].cev[42].cevr";
connectAttr "joint9_rotateY.a" "clipLibrary1.cel[0].cev[43].cevr";
connectAttr "joint9_rotateX.a" "clipLibrary1.cel[0].cev[44].cevr";
connectAttr "joint9_translateZ.a" "clipLibrary1.cel[0].cev[45].cevr";
connectAttr "joint9_translateY.a" "clipLibrary1.cel[0].cev[46].cevr";
connectAttr "joint9_translateX.a" "clipLibrary1.cel[0].cev[47].cevr";
connectAttr "joint6_rotateZ.a" "clipLibrary1.cel[0].cev[48].cevr";
connectAttr "joint6_rotateY.a" "clipLibrary1.cel[0].cev[49].cevr";
connectAttr "joint6_rotateX.a" "clipLibrary1.cel[0].cev[50].cevr";
connectAttr "joint6_translateZ.a" "clipLibrary1.cel[0].cev[51].cevr";
connectAttr "joint6_translateY.a" "clipLibrary1.cel[0].cev[52].cevr";
connectAttr "joint6_translateX.a" "clipLibrary1.cel[0].cev[53].cevr";
connectAttr "joint3_rotateZ.a" "clipLibrary1.cel[0].cev[54].cevr";
connectAttr "joint3_rotateY.a" "clipLibrary1.cel[0].cev[55].cevr";
connectAttr "joint3_rotateX.a" "clipLibrary1.cel[0].cev[56].cevr";
connectAttr "joint3_translateZ.a" "clipLibrary1.cel[0].cev[57].cevr";
connectAttr "joint3_translateY.a" "clipLibrary1.cel[0].cev[58].cevr";
connectAttr "joint3_translateX.a" "clipLibrary1.cel[0].cev[59].cevr";
connectAttr "joint4_rotateZ.a" "clipLibrary1.cel[0].cev[60].cevr";
connectAttr "joint4_rotateY.a" "clipLibrary1.cel[0].cev[61].cevr";
connectAttr "joint4_rotateX.a" "clipLibrary1.cel[0].cev[62].cevr";
connectAttr "joint4_translateZ.a" "clipLibrary1.cel[0].cev[63].cevr";
connectAttr "joint4_translateY.a" "clipLibrary1.cel[0].cev[64].cevr";
connectAttr "joint4_translateX.a" "clipLibrary1.cel[0].cev[65].cevr";
connectAttr "joint5_rotateZ.a" "clipLibrary1.cel[0].cev[66].cevr";
connectAttr "joint5_rotateY.a" "clipLibrary1.cel[0].cev[67].cevr";
connectAttr "joint5_rotateX.a" "clipLibrary1.cel[0].cev[68].cevr";
connectAttr "joint5_translateZ.a" "clipLibrary1.cel[0].cev[69].cevr";
connectAttr "joint5_translateY.a" "clipLibrary1.cel[0].cev[70].cevr";
connectAttr "joint5_translateX.a" "clipLibrary1.cel[0].cev[71].cevr";
connectAttr "joint2_rotateZ.a" "clipLibrary1.cel[0].cev[72].cevr";
connectAttr "joint2_rotateY.a" "clipLibrary1.cel[0].cev[73].cevr";
connectAttr "joint2_rotateX.a" "clipLibrary1.cel[0].cev[74].cevr";
connectAttr "joint2_translateZ.a" "clipLibrary1.cel[0].cev[75].cevr";
connectAttr "joint2_translateY.a" "clipLibrary1.cel[0].cev[76].cevr";
connectAttr "joint2_translateX.a" "clipLibrary1.cel[0].cev[77].cevr";
connectAttr "root_rotateZ.a" "clipLibrary1.cel[0].cev[78].cevr";
connectAttr "root_rotateY.a" "clipLibrary1.cel[0].cev[79].cevr";
connectAttr "root_rotateX.a" "clipLibrary1.cel[0].cev[80].cevr";
connectAttr "root_translateZ.a" "clipLibrary1.cel[0].cev[81].cevr";
connectAttr "root_translateY.a" "clipLibrary1.cel[0].cev[82].cevr";
connectAttr "root_translateX.a" "clipLibrary1.cel[0].cev[83].cevr";
connectAttr "joint15_rotateZ.a" "clipLibrary1.cel[0].cev[84].cevr";
connectAttr "joint15_rotateY.a" "clipLibrary1.cel[0].cev[85].cevr";
connectAttr "joint15_rotateX.a" "clipLibrary1.cel[0].cev[86].cevr";
connectAttr "joint15_translateZ.a" "clipLibrary1.cel[0].cev[87].cevr";
connectAttr "joint15_translateY.a" "clipLibrary1.cel[0].cev[88].cevr";
connectAttr "joint15_translateX.a" "clipLibrary1.cel[0].cev[89].cevr";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of crash.ma
