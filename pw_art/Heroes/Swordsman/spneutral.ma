//Maya ASCII 6.0 scene
//Name: Footman.spneutral.ma
//Last modified: Mon, Jul 17, 2006 05:47:51 PM
requires maya "6.0";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 6.0";
fileInfo "version" "6.0.1";
fileInfo "cutIdentifier" "200407132209-624907";
fileInfo "osv" "Microsoft Windows 2000  (Build 2195)\n";
createNode animClip -n "spneutralSource";
	setAttr ".ihi" 0;
	setAttr ".o" 1;
	setAttr ".se" 75;
	setAttr ".ci" no;
createNode animCurveTA -n "animCurveTA54";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 1.3279995858904801 35 1.3279995858904778 
		75 1.3279995858904801;
createNode animCurveTA -n "animCurveTA55";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -18.025691155969195 35 -20.145954973733389 
		75 -18.025691155969195;
createNode animCurveTA -n "animCurveTA56";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 9.0484514413106716 35 15.855571892737114 
		75 9.0484514413106716;
	setAttr -s 3 ".kit[0:2]"  1 10 10;
	setAttr -s 3 ".kot[0:2]"  1 10 10;
	setAttr -s 3 ".kix[0:2]"  0.064797878265380859 1.1666666269302368 
		1.3333333730697632;
	setAttr -s 3 ".kiy[0:2]"  -0.0032695140689611435 0 -0.11880666762590408;
	setAttr -s 3 ".kox[0:2]"  1.1314543485641479 1.3333333730697632 
		1.3333333730697632;
	setAttr -s 3 ".koy[0:2]"  -0.057089917361736298 0 -0.11880666762590408;
createNode animCurveTA -n "animCurveTA57";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA58";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA59";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL52";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL53";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL54";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA60";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA61";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA62";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL55";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL56";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL57";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL58";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.24819552039891896 35 0.20613901760230141 
		75 0.24819552039891896;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  9 10;
createNode animCurveTL -n "animCurveTL59";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.27469944966509141 35 -0.27777862849816959 
		75 -0.27469944966509141;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  9 10;
createNode animCurveTL -n "animCurveTL60";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.26769795222050691 35 0.23072032604471765 
		75 0.26769795222050691;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  9 10;
createNode animCurveTL -n "animCurveTL61";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.2613544330215532 35 -0.30341093581817075 
		75 -0.2613544330215532;
createNode animCurveTL -n "animCurveTL62";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.24709570664594427 35 -0.25017488547902245 
		75 -0.24709570664594427;
createNode animCurveTL -n "animCurveTL63";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.23566418246003235 35 0.19868655628424309 
		75 0.23566418246003235;
createNode animCurveTL -n "animCurveTL64";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0070963888536680897 15 -0.028082490497991552 
		35 -0.049152891650285635 55 -0.028082490497991552 75 -0.0070963888536680897;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 10;
createNode animCurveTL -n "animCurveTL65";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0034360675845639399 15 0.0098786113595392688 
		35 -0.0065152464176421176 55 0.0098786113595392688 75 -0.0034360675845639399;
	setAttr -s 5 ".kit[0:4]"  10 9 9 9 10;
	setAttr -s 5 ".kot[0:4]"  10 9 9 9 10;
createNode animCurveTL -n "animCurveTL66";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 0.028873232947846241 15 -0.0080403052435430878 
		35 0.050404382004710667 55 -0.015014479465370927 75 0.028873232947846241;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "animCurveTL67";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.0070963888536680897 37 -0.0070963888536680897 
		75 -0.0070963888536680897;
createNode animCurveTL -n "animCurveTL68";
	setAttr ".tan" 10;
	setAttr -s 8 ".ktv[0:7]"  0 -0.045463711799524242 7 0.010472084038153941 
		25 -0.15369543015099668 37 0.0035242980015393662 52 -0.070907274236586965 
		60 -0.0325340793948884 67 -0.062765914602867096 75 -0.045463711799524242;
	setAttr -s 8 ".kit[1:7]"  9 10 10 10 10 1 1;
	setAttr -s 8 ".kot[1:7]"  9 10 10 10 10 1 1;
	setAttr -s 8 ".kix[6:7]"  0.19876919686794281 0.19974522292613983;
	setAttr -s 8 ".kiy[6:7]"  -0.018860014155507088 0.027264850214123726;
	setAttr -s 8 ".kox[6:7]"  0.22716474533081055 0.18350985646247864;
	setAttr -s 8 ".koy[6:7]"  -0.021554291248321533 0.029858997091650963;
createNode animCurveTL -n "animCurveTL69";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  0 0.027087692813105652 15 0.048626152966571697 
		37 -0.058244659834462573 75 0.027087692813105652;
createNode animCurveTA -n "animCurveTA63";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 35 0 55 0 75 0;
createNode animCurveTA -n "animCurveTA64";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0 15 0 35 0 55 0 75 0;
createNode animCurveTA -n "animCurveTA65";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 13.657893158781347 15 13.657893158781347 
		35 13.657893158781347 55 13.657893158781347 75 13.657893158781347;
createNode animCurveTL -n "animCurveTL70";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0070963888536680897 15 -0.028082490497991552 
		35 -0.049152891650285635 55 -0.028082490497991552 75 -0.0070963888536680897;
createNode animCurveTL -n "animCurveTL71";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0034360675845639399 15 0.0098786113595392688 
		35 -0.0065152464176421176 55 0.0098786113595392688 75 -0.0034360675845639399;
createNode animCurveTL -n "animCurveTL72";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.049818208219252202 15 0.036820665743400149 
		35 0.012840582043462945 55 0.026359607924048012 75 0.049818208219252202;
createNode animCurveTU -n "animCurveTU9";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 1 75 1;
	setAttr -s 2 ".kit[0:1]"  9 10;
	setAttr -s 2 ".kot[0:1]"  5 10;
createNode animCurveTA -n "animCurveTA66";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -140.09137328137615 15 -132.32586059228359 
		35 -138.30378020034746 55 -146.37254744557782 75 -140.09137328137615;
	setAttr -s 5 ".kit[1:4]"  9 10 9 10;
	setAttr -s 5 ".kot[1:4]"  9 10 9 10;
createNode animCurveTA -n "animCurveTA67";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -41.32214986621824 15 -37.120277098386453 
		35 -42.77778893149415 55 -46.351381508037434 75 -41.32214986621824;
	setAttr -s 5 ".kit[1:4]"  9 10 9 10;
	setAttr -s 5 ".kot[1:4]"  9 10 9 10;
createNode animCurveTA -n "animCurveTA68";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 48.2339608204746 15 43.236186926041583 
		35 47.036519303467784 55 52.644325018874355 75 48.2339608204746;
	setAttr -s 5 ".kit[1:4]"  9 10 9 10;
	setAttr -s 5 ".kot[1:4]"  9 10 9 10;
createNode animCurveTL -n "animCurveTL73";
	setAttr ".tan" 3;
	setAttr -s 2 ".ktv[0:1]"  0 0.22829510939120629 75 0.22829510939120629;
	setAttr -s 2 ".kit[1]"  10;
	setAttr -s 2 ".kot[1]"  10;
createNode animCurveTL -n "animCurveTL74";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.3818372728130861 15 -0.39929142901791942 
		35 -0.35272939787498453 55 -0.32863486425211874 75 -0.3818372728130861;
	setAttr -s 5 ".kit[2:4]"  1 9 1;
	setAttr -s 5 ".kot[2:4]"  1 9 1;
	setAttr -s 5 ".kix[2:4]"  0.55495595932006836 0.66666674613952637 
		0.88517212867736816;
	setAttr -s 5 ".kiy[2:4]"  0.05780458077788353 -0.014553938992321491 
		-0.065836846828460693;
	setAttr -s 5 ".kox[2:4]"  0.69369524717330933 0.66666662693023682 
		0.88517218828201294;
	setAttr -s 5 ".koy[2:4]"  0.072255760431289673 -0.014553936198353767 
		-0.065836824476718903;
createNode animCurveTL -n "animCurveTL75";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.26678912622464734 15 -0.28543030781126139 
		35 -0.29974750397367012 55 -0.28326831509915873 75 -0.26678912622464734;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTU -n "animCurveTU10";
	setAttr ".tan" 9;
	setAttr -s 3 ".ktv[0:2]"  0 1 50 1 75 1;
	setAttr -s 3 ".kot[0:2]"  5 5 5;
createNode animCurveTA -n "animCurveTA69";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  0 115.39853119105926 31 113.71702337560286 
		61 106.88867086730436 75 115.39853119105926;
	setAttr -s 4 ".kit[2:3]"  9 9;
	setAttr -s 4 ".kot[2:3]"  9 9;
	setAttr -s 4 ".kix[0:3]"  1.0140419006347656 1.0112788677215576 
		1 0.46666666865348816;
	setAttr -s 4 ".kiy[0:3]"  0.089912556111812592 -0.11931514739990234 
		0.020009895786643028 0.14852507412433624;
	setAttr -s 4 ".kox[0:3]"  1.0140422582626343 0.97794586420059204 
		0.46666666865348816 0.46666666865348816;
	setAttr -s 4 ".koy[0:3]"  0.089912578463554382 -0.1153823658823967 
		0.0093379514291882515 0.14852507412433624;
createNode animCurveTA -n "animCurveTA70";
	setAttr ".tan" 3;
	setAttr -s 4 ".ktv[0:3]"  0 -29.952315954069405 20 -29.115434085357169 
		50 -28.036334764123694 75 -29.952315954069405;
	setAttr -s 4 ".kit[1:3]"  9 10 3;
	setAttr -s 4 ".kot[1:3]"  9 10 3;
createNode animCurveTA -n "animCurveTA71";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  0 -65.818388294309344 20 -59.816948146692731 
		50 -60.452131007330067 75 -65.818388294309344;
	setAttr -s 4 ".kit[0:3]"  3 1 1 3;
	setAttr -s 4 ".kot[0:3]"  3 1 1 3;
	setAttr -s 4 ".kix[1:3]"  0.90938341617584229 0.77397054433822632 
		0.83333331346511841;
	setAttr -s 4 ".kiy[1:3]"  0.06413162499666214 -0.023562479764223099 
		0;
	setAttr -s 4 ".kox[1:3]"  1.0760338306427002 0.77397060394287109 
		0.83333331346511841;
	setAttr -s 4 ".koy[1:3]"  0.075884155929088593 -0.023562479764223099 
		0;
createNode animCurveTL -n "animCurveTL76";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  0 -0.28472365344926526 20 -0.31074424438002085 
		50 -0.29599583102703891 75 -0.28472365344926526;
	setAttr -s 4 ".kit[0:3]"  10 1 1 10;
	setAttr -s 4 ".kot[0:3]"  10 1 1 10;
	setAttr -s 4 ".kix[1:3]"  1.1345860958099365 0.72677475214004517 
		0.83333331346511841;
	setAttr -s 4 ".kiy[1:3]"  0.0053008836694061756 0.014739801175892353 
		0;
	setAttr -s 4 ".kox[1:3]"  1.2966690063476562 0.72677463293075562 
		0.83333331346511841;
	setAttr -s 4 ".koy[1:3]"  0.0060581550933420658 0.014739800244569778 
		0;
createNode animCurveTL -n "animCurveTL77";
	setAttr ".tan" 1;
	setAttr -s 4 ".ktv[0:3]"  0 -0.43669291079980133 20 -0.43669291079980133 
		50 -0.36614167288818711 75 -0.43669291079980133;
	setAttr -s 4 ".kit[1:3]"  9 10 1;
	setAttr -s 4 ".kot[1:3]"  9 10 1;
	setAttr -s 4 ".kix[0:3]"  0.67409521341323853 0.66666668653488159 
		0.99999994039535522 0.70396530628204346;
	setAttr -s 4 ".kiy[0:3]"  -0.024658393114805222 0.028220497071743011 
		0 -0.022444784641265869;
	setAttr -s 4 ".kox[0:3]"  0.67409533262252808 0.99999994039535522 
		0.83333337306976318 0.70396548509597778;
	setAttr -s 4 ".koy[0:3]"  -0.02465839684009552 0.042330741882324219 
		0 -0.022444786503911018;
createNode animCurveTL -n "animCurveTL78";
	setAttr ".tan" 9;
	setAttr -s 4 ".ktv[0:3]"  0 0.29198697373812826 20 0.27315043279985113 
		50 0.21363274640951976 75 0.29198697373812826;
	setAttr -s 4 ".kit[0:3]"  3 9 9 3;
	setAttr -s 4 ".kot[0:3]"  3 9 9 3;
createNode animCurveTL -n "animCurveTL79";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.15728441520586695 35 -0.19934091800248449 
		75 -0.15728441520586695;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  9 10;
createNode animCurveTL -n "animCurveTL80";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.063144408114785111 35 0.060065229281706933 
		75 0.063144408114785111;
createNode animCurveTL -n "animCurveTL81";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.50898231702401886 35 -0.54595994319980812 
		75 -0.50898231702401886;
	setAttr -s 3 ".kit[1:2]"  9 10;
	setAttr -s 3 ".kot[1:2]"  9 10;
createNode animCurveTL -n "animCurveTL82";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.00069708472453872128 35 -0.041359418072078824 
		75 0.00069708472453872128;
	setAttr -s 3 ".kit[0:2]"  3 10 10;
	setAttr -s 3 ".kot[0:2]"  3 10 10;
createNode animCurveTL -n "animCurveTL83";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.027296557722927772 35 0.024217378889849595 
		75 0.027296557722927772;
createNode animCurveTL -n "animCurveTL84";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.30320886908454558 35 0.26623124290875633 
		75 0.30320886908454558;
createNode animCurveTU -n "animCurveTU11";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA72";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 2.4545668869252451 75 2.4545668869252451;
createNode animCurveTA -n "animCurveTA73";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -59.222044573256952 75 -59.222044573256952;
createNode animCurveTA -n "animCurveTA74";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -2.434202033955327 75 -2.434202033955327;
createNode animCurveTL -n "animCurveTL85";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -0.3296746241193716 75 -0.3296746241193716;
createNode animCurveTL -n "animCurveTL86";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL87";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -0.045436156506848263 75 -0.045436156506848263;
createNode animCurveTU -n "animCurveTU12";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA75";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA76";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 15.642077920431827 75 15.642077920431827;
createNode animCurveTA -n "animCurveTA77";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL88";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0.093590416298333118 75 0.093590416298333118;
createNode animCurveTL -n "animCurveTL89";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL90";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0.22004454697835768 75 0.22004454697835768;
createNode animCurveTA -n "animCurveTA78";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.91153173449061375 15 0.91153173449060998 
		35 0.91153173449060998 55 0.91153173449060998 75 0.91153173449061375;
createNode animCurveTA -n "animCurveTA79";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 -15.302297995125491 15 -15.302297995125516 
		35 -15.302297995125516 55 -15.302297995125516 75 -15.302297995125491;
createNode animCurveTA -n "animCurveTA80";
	setAttr ".tan" 10;
	setAttr -s 5 ".ktv[0:4]"  0 0.10953910533628934 15 0.051103812633386064 
		35 0.030389132625500238 55 0.051103812633386064 75 0.10953910533628934;
	setAttr -s 5 ".kit[1:4]"  9 10 1 10;
	setAttr -s 5 ".kot[1:4]"  9 10 1 10;
	setAttr -s 5 ".kix[3:4]"  0.63707560300827026 0.66666668653488159;
	setAttr -s 5 ".kiy[3:4]"  0.00089398719137534499 0;
	setAttr -s 5 ".kox[3:4]"  0.63707560300827026 0.66666668653488159;
	setAttr -s 5 ".koy[3:4]"  0.00089398707496002316 0;
createNode animCurveTL -n "animCurveTL91";
	setAttr ".tan" 3;
	setAttr -s 5 ".ktv[0:4]"  0 -0.15726637602639884 15 -0.1614430168543026 
		35 -0.16398438044662969 55 -0.15964445882280967 75 -0.15726637602639884;
	setAttr -s 5 ".kit[1:4]"  1 3 1 3;
	setAttr -s 5 ".kot[1:4]"  1 3 1 3;
	setAttr -s 5 ".kix[1:4]"  0.44905674457550049 0.66666668653488159 
		0.45922741293907166 0.66666668653488159;
	setAttr -s 5 ".kiy[1:4]"  -0.0044492022134363651 0 0.0027106788475066423 
		0;
	setAttr -s 5 ".kox[1:4]"  0.59874230623245239 0.66666668653488159 
		0.91845369338989258 0.66666668653488159;
	setAttr -s 5 ".koy[1:4]"  -0.0059322686865925789 0 0.0054213455878198147 
		0;
createNode animCurveTL -n "animCurveTL92";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  0 -0.051637082257696622 15 -0.05802423962250032 
		35 -0.057193333522879364 55 -0.05954251358478202 75 -0.051637082257696622;
	setAttr -s 5 ".kix[0:4]"  0.1468593031167984 0.48721268773078918 
		0.7035897970199585 0.60976290702819824 1.0024493932723999;
	setAttr -s 5 ".kiy[0:4]"  -0.00057487166486680508 -0.0097969751805067062 
		-0.0064097251743078232 0.0036544795148074627 -0.002341125626116991;
	setAttr -s 5 ".kox[0:4]"  0.73429751396179199 0.64961689710617065 
		0.3517947793006897 0.60976302623748779 1.0024497509002686;
	setAttr -s 5 ".koy[0:4]"  -0.0028743634466081858 -0.013062631711363792 
		-0.0032048642169684172 0.0036544797476381063 -0.0023411272559314966;
createNode animCurveTL -n "animCurveTL93";
	setAttr ".tan" 1;
	setAttr -s 5 ".ktv[0:4]"  0 0.066874042172448467 15 0.058108132905130006 
		35 0.049901935270701386 55 0.055934225474650087 75 0.066874042172448467;
	setAttr -s 5 ".kit[0:4]"  10 1 1 1 10;
	setAttr -s 5 ".kot[0:4]"  10 1 1 1 10;
	setAttr -s 5 ".kix[1:4]"  0.35217803716659546 0.66962820291519165 
		0.36188429594039917 0.66666668653488159;
	setAttr -s 5 ".kiy[1:4]"  -0.0093158306553959846 -0.00089011213276535273 
		0.0072302063927054405 0;
	setAttr -s 5 ".kox[1:4]"  0.70435595512390137 0.3348143994808197 
		0.72376817464828491 0.66666668653488159;
	setAttr -s 5 ".koy[1:4]"  -0.018631676211953163 -0.00044505769619718194 
		0.014460415579378605 0;
createNode animCurveTA -n "animCurveTA81";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -6.7097270679247689 35 -10.385882924913318 
		75 -6.7097270679247689;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA82";
	setAttr ".tan" 3;
	setAttr -s 3 ".ktv[0:2]"  0 -24.005486609752403 35 -19.816277318619484 
		75 -24.005486609752403;
	setAttr -s 3 ".kit[1:2]"  10 3;
	setAttr -s 3 ".kot[1:2]"  10 3;
createNode animCurveTA -n "animCurveTA83";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0 35 1.2477515994946331 75 0;
createNode animCurveTA -n "animCurveTA84";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 9.6921754187547098 35 13.14373187969033 
		75 9.6921754187547098;
createNode animCurveTA -n "animCurveTA85";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 8.810063617344392 35 7.7438573530905837 
		75 8.810063617344392;
createNode animCurveTA -n "animCurveTA86";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 23.265079145375779 35 17.579502194203698 
		75 23.265079145375779;
createNode animCurveTL -n "animCurveTL94";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.040210713659284476 35 -0.040210713659284476 
		75 -0.040210713659284476;
createNode animCurveTL -n "animCurveTL95";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -0.92172394262998947 35 -0.92172394262998947 
		75 -0.92172394262998947;
createNode animCurveTL -n "animCurveTL96";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 0.020592262861709541 35 0.020592262861709541 
		75 0.020592262861709541;
createNode animCurveTA -n "animCurveTA87";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -10.814320486728878 35 -13.252130839073335 
		75 -10.814320486728878;
createNode animCurveTA -n "animCurveTA88";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -3.7464163230089 35 0.62273784498000273 
		75 -3.7464163230089;
createNode animCurveTA -n "animCurveTA89";
	setAttr ".tan" 10;
	setAttr -s 3 ".ktv[0:2]"  0 -10.897220128485484 35 -16.413212079771739 
		75 -10.897220128485484;
createNode animCurveTA -n "animCurveTA90";
	setAttr ".tan" 1;
	setAttr -s 3 ".ktv[0:2]"  0 0.72504957116732272 35 9.0052724458255753 
		75 0.72504957116732272;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  0.026390543207526207 1.1666666269302368 
		1.2691526412963867;
	setAttr -s 3 ".kiy[0:2]"  -0.0051881764084100723 0 -0.21529695391654968;
	setAttr -s 3 ".kox[0:2]"  1.0930348634719849 1.3333333730697632 
		1.2691529989242554;
	setAttr -s 3 ".koy[0:2]"  -0.21488223969936371 0 -0.21529701352119446;
createNode animCurveTA -n "animCurveTA91";
	setAttr ".tan" 1;
	setAttr -s 3 ".ktv[0:2]"  0 -16.065060266995822 35 -12.07642108610667 
		75 -16.065060266995822;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  0.0049999016337096691 1.1666666269302368 
		1.2074915170669556;
	setAttr -s 3 ".kiy[0:2]"  -0.00093731930246576667 0 -0.23963500559329987;
	setAttr -s 3 ".kox[0:2]"  1.0716347694396973 1.3333333730697632 
		1.2074918746948242;
	setAttr -s 3 ".koy[0:2]"  -0.2008967399597168 0 -0.23963506519794464;
createNode animCurveTA -n "animCurveTA92";
	setAttr ".tan" 1;
	setAttr -s 3 ".ktv[0:2]"  0 -1.8244965449281254 35 -1.7786265010053246 
		75 -1.8244965449281254;
	setAttr -s 3 ".kit[1:2]"  10 1;
	setAttr -s 3 ".kot[1:2]"  10 1;
	setAttr -s 3 ".kix[0:2]"  0.0064845560118556023 1.1666666269302368 
		1.2293301820755005;
	setAttr -s 3 ".kiy[0:2]"  0.00034248217707499862 0 0.063923828303813934;
	setAttr -s 3 ".kox[0:2]"  1.0731217861175537 1.3333333730697632 
		1.2293300628662109;
	setAttr -s 3 ".koy[0:2]"  0.056676976382732391 0 0.063923820853233337;
createNode animCurveTA -n "animCurveTA93";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -5.0566276381482984 15 -13.379136088787408 
		35 -8.6135945883730383 55 -1.4160724301588929 75 -5.0566276381482984;
	setAttr -s 5 ".kit[4]"  1;
	setAttr -s 5 ".kot[4]"  1;
	setAttr -s 5 ".kix[4]"  0.50688058137893677;
	setAttr -s 5 ".kiy[4]"  -0.088189415633678436;
	setAttr -s 5 ".kox[4]"  0.50688064098358154;
	setAttr -s 5 ".koy[4]"  -0.088189437985420227;
createNode animCurveTA -n "animCurveTA94";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -17.107761286541351 15 -11.351870319964018 
		35 -14.672851124216253 55 -19.594770815387243 75 -17.107761286541351;
	setAttr -s 5 ".kit[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kot[0:4]"  1 9 9 9 1;
	setAttr -s 5 ".kix[0:4]"  0.63621163368225098 0.5 0.66666662693023682 
		0.66666674613952637 0.2870171070098877;
	setAttr -s 5 ".kiy[0:4]"  0.093572653830051422 0.018213085830211639 
		-0.071932874619960785 -0.021248601377010345 0.070782370865345001;
	setAttr -s 5 ".kox[0:4]"  0.63621169328689575 0.66666662693023682 
		0.66666668653488159 0.66666662693023682 0.28701719641685486;
	setAttr -s 5 ".koy[0:4]"  0.093572638928890228 0.024284113198518753 
		-0.071932882070541382 -0.021248597651720047 0.070782393217086792;
createNode animCurveTA -n "animCurveTA95";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -55.761927886665404 15 -54.080709412597933 
		35 -55.390123601664214 55 -57.365269670749377 75 -55.761927886665404;
createNode animCurveTL -n "animCurveTL97";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.011301811406185556 15 -0.0096922747526011366 
		35 -0.0082271993039075425 55 -0.0097645053550465492 75 -0.011301811406185556;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "animCurveTL98";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0098431871193776898 15 -0.0068916567255465234 
		35 -0.0034403696451043618 55 -0.0066417783822410262 75 -0.0098431871193776898;
	setAttr -s 5 ".kit[0:4]"  3 9 9 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 9 9 3;
createNode animCurveTL -n "animCurveTL99";
	setAttr ".tan" 9;
	setAttr -s 5 ".ktv[0:4]"  0 -0.0040455390558233545 15 -0.0065701149047574245 
		35 -0.0087199311052271865 55 -0.0063827350805252701 75 -0.0040455390558233545;
	setAttr -s 5 ".kit[0:4]"  3 9 10 9 3;
	setAttr -s 5 ".kot[0:4]"  3 9 10 9 3;
createNode animCurveTU -n "animCurveTU13";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA96";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -45.000000000000007 75 -45.000000000000007;
createNode animCurveTA -n "animCurveTA97";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA98";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTU -n "animCurveTU14";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 4.6000000000000005 75 4.6000000000000005;
createNode animCurveTA -n "animCurveTA99";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -35.00000000000005 75 -35.00000000000005;
createNode animCurveTA -n "animCurveTA100";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA101";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTA -n "animCurveTA102";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL100";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL101";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTL -n "animCurveTL102";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTU -n "animCurveTU15";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 2.9000000000000004 75 2.9000000000000004;
createNode animCurveTA -n "animCurveTA103";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 8.3135312287614322 75 8.3135312287614322;
createNode animCurveTA -n "animCurveTA104";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 -19.995134732632 75 -19.995134732632;
createNode animCurveTA -n "animCurveTA105";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 1.5108588730100463 75 1.5108588730100463;
createNode animCurveTU -n "animCurveTU16";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 7.6000000000000005 75 7.6000000000000005;
createNode animCurveTA -n "animCurveTA106";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 24.999999999999996 75 24.999999999999996;
createNode animCurveTU -n "Footman_Global_Mark";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTU -n "Footman_Weapon_Transparency";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode animCurveTU -n "Footman_Body_Transparency";
	setAttr ".tan" 10;
	setAttr -s 2 ".ktv[0:1]"  0 0 75 0;
createNode clipLibrary -n "clipLibrary1";
	setAttr -s 115 ".cel[1].cev";
	setAttr ".cd[0].cm" -type "characterMapping" 115 "Chest_locator.rotateZ" 
		2 1 "Chest_locator.rotateY" 2 2 "Chest_locator.rotateX" 
		2 3 "Shield_locator_World.rotateZ" 2 4 "Shield_locator_World.rotateY" 
		2 5 "Shield_locator_World.rotateX" 2 6 "Shield_locator_World.translateZ" 
		1 1 "Shield_locator_World.translateY" 1 2 "Shield_locator_World.translateX" 
		1 3 "Sword_locator_World.rotateZ" 2 7 "Sword_locator_World.rotateY" 
		2 8 "Sword_locator_World.rotateX" 2 9 "Sword_locator_World.translateZ" 
		1 4 "Sword_locator_World.translateY" 1 5 "Sword_locator_World.translateX" 
		1 6 "L_Locot_locator.translateZ" 1 7 "L_Locot_locator.translateY" 
		1 8 "L_Locot_locator.translateX" 1 9 "R_Locot_locator.translateZ" 
		1 10 "R_Locot_locator.translateY" 1 11 "R_Locot_locator.translateX" 
		1 12 "HeadTop_locator.translateZ" 1 13 "HeadTop_locator.translateY" 
		1 14 "HeadTop_locator.translateX" 1 15 "Head_locator.translateZ" 
		1 16 "Head_locator.translateY" 1 17 "Head_locator.translateX" 
		1 18 "Clothe_locator.rotateZ" 2 10 "Clothe_locator.rotateY" 
		2 11 "Clothe_locator.rotateX" 2 12 "Clothe_locator.translateZ" 
		1 19 "Clothe_locator.translateY" 1 20 "Clothe_locator.translateX" 
		1 21 "L_Hand_locator.Shield" 0 1 "L_Hand_locator.rotateZ" 
		2 13 "L_Hand_locator.rotateY" 2 14 "L_Hand_locator.rotateX" 
		2 15 "L_Hand_locator.translateZ" 1 22 "L_Hand_locator.translateY" 
		1 23 "L_Hand_locator.translateX" 1 24 "R_Hand_locator.Sword" 
		0 2 "R_Hand_locator.rotateZ" 2 16 "R_Hand_locator.rotateY" 
		2 17 "R_Hand_locator.rotateX" 2 18 "R_Hand_locator.translateZ" 
		1 25 "R_Hand_locator.translateY" 1 26 "R_Hand_locator.translateX" 
		1 27 "R_Knee_locator.translateZ" 1 28 "R_Knee_locator.translateY" 
		1 29 "R_Knee_locator.translateX" 1 30 "L_Knee_locator.translateZ" 
		1 31 "L_Knee_locator.translateY" 1 32 "L_Knee_locator.translateX" 
		1 33 "R_Leg_locator.Toe" 0 3 "R_Leg_locator.rotateZ" 2 
		19 "R_Leg_locator.rotateY" 2 20 "R_Leg_locator.rotateX" 2 
		21 "R_Leg_locator.translateZ" 1 34 "R_Leg_locator.translateY" 
		1 35 "R_Leg_locator.translateX" 1 36 "L_Leg_locator.Toe" 
		0 4 "L_Leg_locator.rotateZ" 2 22 "L_Leg_locator.rotateY" 
		2 23 "L_Leg_locator.rotateX" 2 24 "L_Leg_locator.translateZ" 
		1 37 "L_Leg_locator.translateY" 1 38 "L_Leg_locator.translateX" 
		1 39 "Hip_locator.rotateZ" 2 25 "Hip_locator.rotateY" 2 
		26 "Hip_locator.rotateX" 2 27 "Hip_locator.translateZ" 1 
		40 "Hip_locator.translateY" 1 41 "Hip_locator.translateX" 1 
		42 "Bag_locator.rotateZ" 2 28 "Bag_locator.rotateY" 2 29 "Bag_locator.rotateX" 
		2 30 "SmallSword_locator.rotateZ" 2 31 "SmallSword_locator.rotateY" 
		2 32 "SmallSword_locator.rotateX" 2 33 "SmallSword_locator.translateZ" 
		1 43 "SmallSword_locator.translateY" 1 44 "SmallSword_locator.translateX" 
		1 45 "L_Clavice_locator.rotateZ" 2 34 "L_Clavice_locator.rotateY" 
		2 35 "L_Clavice_locator.rotateX" 2 36 "R_Clavice_locator.rotateZ" 
		2 37 "R_Clavice_locator.rotateY" 2 38 "R_Clavice_locator.rotateX" 
		2 39 "Shield_locator_Hand.rotateZ" 2 40 "Shield_locator_Hand.rotateY" 
		2 41 "Shield_locator_Hand.rotateX" 2 42 "Shield_locator_Hand.translateZ" 
		1 46 "Shield_locator_Hand.translateY" 1 47 "Shield_locator_Hand.translateX" 
		1 48 "L_Thumb_locator.Thumb02" 0 5 "L_Thumb_locator.rotateZ" 
		2 43 "L_Thumb_locator.rotateY" 2 44 "L_Thumb_locator.rotateX" 
		2 45 "L_Fingers_locator.Fingers02" 0 6 "L_Fingers_locator.rotateZ" 
		2 46 "Sword_locator_Hand.rotateZ" 2 47 "Sword_locator_Hand.rotateY" 
		2 48 "Sword_locator_Hand.rotateX" 2 49 "Sword_locator_Hand.translateZ" 
		1 49 "Sword_locator_Hand.translateY" 1 50 "Sword_locator_Hand.translateX" 
		1 51 "R_Thumb_locator.Thumb02" 0 7 "R_Thumb_locator.rotateZ" 
		2 50 "R_Thumb_locator.rotateY" 2 51 "R_Thumb_locator.rotateX" 
		2 52 "R_Fingers_locator.Fingers02" 0 8 "R_Fingers_locator.rotateZ" 
		2 53 "Global.Mark" 0 9 "Weapon.Transparency" 0 10 "Body.Transparency" 
		0 11  ;
	setAttr ".cd[0].cim" -type "Int32Array" 115 0 1 2 3
		 4 5 6 7 8 9 10 11 12 13 14
		 15 16 17 18 19 20 21 22 23 24 25
		 26 27 28 29 30 31 32 33 34 35 36
		 37 38 39 40 41 42 43 44 45 46 47
		 48 49 50 51 52 53 54 55 56 57 58
		 59 60 61 62 63 64 65 66 67 68 69
		 70 71 72 73 74 75 76 77 78 79 80
		 81 82 83 84 85 86 87 88 89 90 91
		 92 93 94 95 96 97 98 99 100 101 102
		 103 104 105 106 107 108 109 110 111 112 113
		 114 ;
createNode animClip -n "spneutral";
	setAttr ".o" 1;
	setAttr ".se" 75;
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
select -ne :time1;
	setAttr -l on ".o" 75;
select -ne :renderPartition;
	setAttr -s 5 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
select -ne :lightList1;
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
select -ne :lambert1;
	setAttr ".miic" -type "float3" 9.8696051 9.8696051 9.8696051 ;
select -ne :initialShadingGroup;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -k on ".mwc";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	addAttr -ci true -sn "materialIndex" -ln "materialIndex" -at "long";
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	setAttr ".mcfr" 30;
	setAttr -l on ".bfs";
	setAttr -k on ".mbf";
select -ne :defaultResolution;
	setAttr -k on ".cch";
	setAttr -k on ".nds";
	setAttr -av ".w" 320;
	setAttr -av ".h" 240;
	setAttr -k on ".off";
	setAttr -k on ".fld";
	setAttr -k on ".zsl";
select -ne :hardwareRenderGlobals;
	addAttr -ci true -sn "ani" -ln "animation" -bt "ANIM" -min 0 -max 1 -at "bool";
	setAttr ".fn" -type "string" "default-%4n.%e";
	setAttr ".hwfr" 30;
	setAttr -k on ".ani" yes;
select -ne :characterPartition;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
select -ne :ikSystem;
connectAttr "spneutralSource.cl" "clipLibrary1.sc[1]";
connectAttr "animCurveTA54.a" "clipLibrary1.cel[1].cev[0].cevr";
connectAttr "animCurveTA55.a" "clipLibrary1.cel[1].cev[1].cevr";
connectAttr "animCurveTA56.a" "clipLibrary1.cel[1].cev[2].cevr";
connectAttr "animCurveTA57.a" "clipLibrary1.cel[1].cev[3].cevr";
connectAttr "animCurveTA58.a" "clipLibrary1.cel[1].cev[4].cevr";
connectAttr "animCurveTA59.a" "clipLibrary1.cel[1].cev[5].cevr";
connectAttr "animCurveTL52.a" "clipLibrary1.cel[1].cev[6].cevr";
connectAttr "animCurveTL53.a" "clipLibrary1.cel[1].cev[7].cevr";
connectAttr "animCurveTL54.a" "clipLibrary1.cel[1].cev[8].cevr";
connectAttr "animCurveTA60.a" "clipLibrary1.cel[1].cev[9].cevr";
connectAttr "animCurveTA61.a" "clipLibrary1.cel[1].cev[10].cevr";
connectAttr "animCurveTA62.a" "clipLibrary1.cel[1].cev[11].cevr";
connectAttr "animCurveTL55.a" "clipLibrary1.cel[1].cev[12].cevr";
connectAttr "animCurveTL56.a" "clipLibrary1.cel[1].cev[13].cevr";
connectAttr "animCurveTL57.a" "clipLibrary1.cel[1].cev[14].cevr";
connectAttr "animCurveTL58.a" "clipLibrary1.cel[1].cev[15].cevr";
connectAttr "animCurveTL59.a" "clipLibrary1.cel[1].cev[16].cevr";
connectAttr "animCurveTL60.a" "clipLibrary1.cel[1].cev[17].cevr";
connectAttr "animCurveTL61.a" "clipLibrary1.cel[1].cev[18].cevr";
connectAttr "animCurveTL62.a" "clipLibrary1.cel[1].cev[19].cevr";
connectAttr "animCurveTL63.a" "clipLibrary1.cel[1].cev[20].cevr";
connectAttr "animCurveTL64.a" "clipLibrary1.cel[1].cev[21].cevr";
connectAttr "animCurveTL65.a" "clipLibrary1.cel[1].cev[22].cevr";
connectAttr "animCurveTL66.a" "clipLibrary1.cel[1].cev[23].cevr";
connectAttr "animCurveTL67.a" "clipLibrary1.cel[1].cev[24].cevr";
connectAttr "animCurveTL68.a" "clipLibrary1.cel[1].cev[25].cevr";
connectAttr "animCurveTL69.a" "clipLibrary1.cel[1].cev[26].cevr";
connectAttr "animCurveTA63.a" "clipLibrary1.cel[1].cev[27].cevr";
connectAttr "animCurveTA64.a" "clipLibrary1.cel[1].cev[28].cevr";
connectAttr "animCurveTA65.a" "clipLibrary1.cel[1].cev[29].cevr";
connectAttr "animCurveTL70.a" "clipLibrary1.cel[1].cev[30].cevr";
connectAttr "animCurveTL71.a" "clipLibrary1.cel[1].cev[31].cevr";
connectAttr "animCurveTL72.a" "clipLibrary1.cel[1].cev[32].cevr";
connectAttr "animCurveTU9.a" "clipLibrary1.cel[1].cev[33].cevr";
connectAttr "animCurveTA66.a" "clipLibrary1.cel[1].cev[34].cevr";
connectAttr "animCurveTA67.a" "clipLibrary1.cel[1].cev[35].cevr";
connectAttr "animCurveTA68.a" "clipLibrary1.cel[1].cev[36].cevr";
connectAttr "animCurveTL73.a" "clipLibrary1.cel[1].cev[37].cevr";
connectAttr "animCurveTL74.a" "clipLibrary1.cel[1].cev[38].cevr";
connectAttr "animCurveTL75.a" "clipLibrary1.cel[1].cev[39].cevr";
connectAttr "animCurveTU10.a" "clipLibrary1.cel[1].cev[40].cevr";
connectAttr "animCurveTA69.a" "clipLibrary1.cel[1].cev[41].cevr";
connectAttr "animCurveTA70.a" "clipLibrary1.cel[1].cev[42].cevr";
connectAttr "animCurveTA71.a" "clipLibrary1.cel[1].cev[43].cevr";
connectAttr "animCurveTL76.a" "clipLibrary1.cel[1].cev[44].cevr";
connectAttr "animCurveTL77.a" "clipLibrary1.cel[1].cev[45].cevr";
connectAttr "animCurveTL78.a" "clipLibrary1.cel[1].cev[46].cevr";
connectAttr "animCurveTL79.a" "clipLibrary1.cel[1].cev[47].cevr";
connectAttr "animCurveTL80.a" "clipLibrary1.cel[1].cev[48].cevr";
connectAttr "animCurveTL81.a" "clipLibrary1.cel[1].cev[49].cevr";
connectAttr "animCurveTL82.a" "clipLibrary1.cel[1].cev[50].cevr";
connectAttr "animCurveTL83.a" "clipLibrary1.cel[1].cev[51].cevr";
connectAttr "animCurveTL84.a" "clipLibrary1.cel[1].cev[52].cevr";
connectAttr "animCurveTU11.a" "clipLibrary1.cel[1].cev[53].cevr";
connectAttr "animCurveTA72.a" "clipLibrary1.cel[1].cev[54].cevr";
connectAttr "animCurveTA73.a" "clipLibrary1.cel[1].cev[55].cevr";
connectAttr "animCurveTA74.a" "clipLibrary1.cel[1].cev[56].cevr";
connectAttr "animCurveTL85.a" "clipLibrary1.cel[1].cev[57].cevr";
connectAttr "animCurveTL86.a" "clipLibrary1.cel[1].cev[58].cevr";
connectAttr "animCurveTL87.a" "clipLibrary1.cel[1].cev[59].cevr";
connectAttr "animCurveTU12.a" "clipLibrary1.cel[1].cev[60].cevr";
connectAttr "animCurveTA75.a" "clipLibrary1.cel[1].cev[61].cevr";
connectAttr "animCurveTA76.a" "clipLibrary1.cel[1].cev[62].cevr";
connectAttr "animCurveTA77.a" "clipLibrary1.cel[1].cev[63].cevr";
connectAttr "animCurveTL88.a" "clipLibrary1.cel[1].cev[64].cevr";
connectAttr "animCurveTL89.a" "clipLibrary1.cel[1].cev[65].cevr";
connectAttr "animCurveTL90.a" "clipLibrary1.cel[1].cev[66].cevr";
connectAttr "animCurveTA78.a" "clipLibrary1.cel[1].cev[67].cevr";
connectAttr "animCurveTA79.a" "clipLibrary1.cel[1].cev[68].cevr";
connectAttr "animCurveTA80.a" "clipLibrary1.cel[1].cev[69].cevr";
connectAttr "animCurveTL91.a" "clipLibrary1.cel[1].cev[70].cevr";
connectAttr "animCurveTL92.a" "clipLibrary1.cel[1].cev[71].cevr";
connectAttr "animCurveTL93.a" "clipLibrary1.cel[1].cev[72].cevr";
connectAttr "animCurveTA81.a" "clipLibrary1.cel[1].cev[73].cevr";
connectAttr "animCurveTA82.a" "clipLibrary1.cel[1].cev[74].cevr";
connectAttr "animCurveTA83.a" "clipLibrary1.cel[1].cev[75].cevr";
connectAttr "animCurveTA84.a" "clipLibrary1.cel[1].cev[76].cevr";
connectAttr "animCurveTA85.a" "clipLibrary1.cel[1].cev[77].cevr";
connectAttr "animCurveTA86.a" "clipLibrary1.cel[1].cev[78].cevr";
connectAttr "animCurveTL94.a" "clipLibrary1.cel[1].cev[79].cevr";
connectAttr "animCurveTL95.a" "clipLibrary1.cel[1].cev[80].cevr";
connectAttr "animCurveTL96.a" "clipLibrary1.cel[1].cev[81].cevr";
connectAttr "animCurveTA87.a" "clipLibrary1.cel[1].cev[82].cevr";
connectAttr "animCurveTA88.a" "clipLibrary1.cel[1].cev[83].cevr";
connectAttr "animCurveTA89.a" "clipLibrary1.cel[1].cev[84].cevr";
connectAttr "animCurveTA90.a" "clipLibrary1.cel[1].cev[85].cevr";
connectAttr "animCurveTA91.a" "clipLibrary1.cel[1].cev[86].cevr";
connectAttr "animCurveTA92.a" "clipLibrary1.cel[1].cev[87].cevr";
connectAttr "animCurveTA93.a" "clipLibrary1.cel[1].cev[88].cevr";
connectAttr "animCurveTA94.a" "clipLibrary1.cel[1].cev[89].cevr";
connectAttr "animCurveTA95.a" "clipLibrary1.cel[1].cev[90].cevr";
connectAttr "animCurveTL97.a" "clipLibrary1.cel[1].cev[91].cevr";
connectAttr "animCurveTL98.a" "clipLibrary1.cel[1].cev[92].cevr";
connectAttr "animCurveTL99.a" "clipLibrary1.cel[1].cev[93].cevr";
connectAttr "animCurveTU13.a" "clipLibrary1.cel[1].cev[94].cevr";
connectAttr "animCurveTA96.a" "clipLibrary1.cel[1].cev[95].cevr";
connectAttr "animCurveTA97.a" "clipLibrary1.cel[1].cev[96].cevr";
connectAttr "animCurveTA98.a" "clipLibrary1.cel[1].cev[97].cevr";
connectAttr "animCurveTU14.a" "clipLibrary1.cel[1].cev[98].cevr";
connectAttr "animCurveTA99.a" "clipLibrary1.cel[1].cev[99].cevr";
connectAttr "animCurveTA100.a" "clipLibrary1.cel[1].cev[100].cevr";
connectAttr "animCurveTA101.a" "clipLibrary1.cel[1].cev[101].cevr";
connectAttr "animCurveTA102.a" "clipLibrary1.cel[1].cev[102].cevr";
connectAttr "animCurveTL100.a" "clipLibrary1.cel[1].cev[103].cevr";
connectAttr "animCurveTL101.a" "clipLibrary1.cel[1].cev[104].cevr";
connectAttr "animCurveTL102.a" "clipLibrary1.cel[1].cev[105].cevr";
connectAttr "animCurveTU15.a" "clipLibrary1.cel[1].cev[106].cevr";
connectAttr "animCurveTA103.a" "clipLibrary1.cel[1].cev[107].cevr";
connectAttr "animCurveTA104.a" "clipLibrary1.cel[1].cev[108].cevr";
connectAttr "animCurveTA105.a" "clipLibrary1.cel[1].cev[109].cevr";
connectAttr "animCurveTU16.a" "clipLibrary1.cel[1].cev[110].cevr";
connectAttr "animCurveTA106.a" "clipLibrary1.cel[1].cev[111].cevr";
connectAttr "Footman_Global_Mark.a" "clipLibrary1.cel[1].cev[112].cevr";
connectAttr "Footman_Weapon_Transparency.a" "clipLibrary1.cel[1].cev[113].cevr"
		;
connectAttr "Footman_Body_Transparency.a" "clipLibrary1.cel[1].cev[114].cevr"
		;
connectAttr "spneutralSource.cl" "spneutral.cl";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[3].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
// End of Footman.spneutral.ma
