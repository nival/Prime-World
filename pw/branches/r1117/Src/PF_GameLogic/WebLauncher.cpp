#include "stdafx.h"
#include "WebLauncher.h"
#include <iostream>
#include <map>
#include <set>
#include <json/json.h>

#pragma comment(lib, "wininet.lib")

static std::set<std::string> allResourcesIDs;
//#pragma optimize("", off)

WebLauncherPostRequest::WebLauncherPostRequest()
{
	//const std::string apiUrl = "https://playpw.fun";
	//const std::string apiEndpoint = "/api/launcher/";

	hInternet = InternetOpenW(L"HTTP Post Request", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL) {
		std::cerr << "InternetOpen failed with error: " << GetLastError() << std::endl;
		return;
	}

	// Connect to the server
	hConnect = InternetConnectW(hInternet, L"playpw.fun", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (hConnect == NULL) {
		std::cerr << "InternetConnect failed with error: " << GetLastError() << std::endl;
		InternetCloseHandle(hInternet);
		return;
	}

	// Open the HTTP request
	hRequest = HttpOpenRequestW(hConnect, L"POST", L"/api/launcher/", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
	if (hRequest == NULL) {
		std::cerr << "HttpOpenRequest failed with error: " << GetLastError() << std::endl;
		InternetCloseHandle(hConnect);
		InternetCloseHandle(hInternet);
		return;
	}

	//fill characters
	 characterMap.insert(std::make_pair("prince", 1));
    characterMap.insert(std::make_pair("snowqueen", 2));
    characterMap.insert(std::make_pair("faceless", 3));
    characterMap.insert(std::make_pair("warlord", 4));
    characterMap.insert(std::make_pair("thundergod", 5));
    characterMap.insert(std::make_pair("invisible", 6));
    characterMap.insert(std::make_pair("mowgly", 7));
    characterMap.insert(std::make_pair("inventor", 8));
    characterMap.insert(std::make_pair("artist", 9));
    characterMap.insert(std::make_pair("highlander", 10));
    characterMap.insert(std::make_pair("marine", 11));
    characterMap.insert(std::make_pair("firefox", 12));
    characterMap.insert(std::make_pair("healer", 13));
    characterMap.insert(std::make_pair("night", 14));
    characterMap.insert(std::make_pair("rockman", 15));
    characterMap.insert(std::make_pair("assassin", 16));
    characterMap.insert(std::make_pair("unicorn", 17));
    characterMap.insert(std::make_pair("hunter", 18));
    characterMap.insert(std::make_pair("ghostlord", 19));
    characterMap.insert(std::make_pair("ratcatcher", 20));
    characterMap.insert(std::make_pair("archeress", 21));
    characterMap.insert(std::make_pair("werewolf", 22));
    characterMap.insert(std::make_pair("frogenglut", 23));
    characterMap.insert(std::make_pair("witchdoctor", 24));
    characterMap.insert(std::make_pair("manawyrm", 25));
    characterMap.insert(std::make_pair("bard", 26));
    characterMap.insert(std::make_pair("naga", 27));
    characterMap.insert(std::make_pair("mage", 28));
    characterMap.insert(std::make_pair("fairy", 29));
    characterMap.insert(std::make_pair("witcher", 30));
    characterMap.insert(std::make_pair("alchemist", 31));
    characterMap.insert(std::make_pair("demonolog", 32));
    characterMap.insert(std::make_pair("vampire", 33));
    characterMap.insert(std::make_pair("witch", 34));
    characterMap.insert(std::make_pair("crusader_A", 35));
    characterMap.insert(std::make_pair("crusader_B", 36));
    characterMap.insert(std::make_pair("monster", 37));
    characterMap.insert(std::make_pair("angel", 38));
    characterMap.insert(std::make_pair("freeze", 39));
    characterMap.insert(std::make_pair("gunslinger", 40));
    characterMap.insert(std::make_pair("reaper", 41));
    characterMap.insert(std::make_pair("fluffy", 42));
    characterMap.insert(std::make_pair("rifleman", 43));
    characterMap.insert(std::make_pair("magicgirl", 44));
    characterMap.insert(std::make_pair("pinkgirl", 45));
    characterMap.insert(std::make_pair("ironknight", 46));
    characterMap.insert(std::make_pair("fallenangel", 47));
    characterMap.insert(std::make_pair("bladedancer", 48));
    characterMap.insert(std::make_pair("ent", 49));
    characterMap.insert(std::make_pair("plaguedoctor", 50));
    characterMap.insert(std::make_pair("katana", 51));
    characterMap.insert(std::make_pair("plane", 52));
    characterMap.insert(std::make_pair("zealot", 53));
    characterMap.insert(std::make_pair("wraithking", 54));
    characterMap.insert(std::make_pair("dryad", 55));
    characterMap.insert(std::make_pair("stalker", 56));
    characterMap.insert(std::make_pair("gunner", 57));
    characterMap.insert(std::make_pair("chronicle", 58));
    characterMap.insert(std::make_pair("brewer", 59));
    characterMap.insert(std::make_pair("shadow", 60));
    characterMap.insert(std::make_pair("wendigo", 61));
    characterMap.insert(std::make_pair("trickster", 62));
    characterMap.insert(std::make_pair("banshee", 63));
    characterMap.insert(std::make_pair("shaman", 64));
    characterMap.insert(std::make_pair("bomber", 65));

	//fill class talents
	// Insert the key-value pairs
	classTalentMap[1] = "Prince_A0";
	classTalentMap[2] = "SnowQueen_A0";
	classTalentMap[3] = "Faceless_A2";
	classTalentMap[4] = "Warlord_A0";
	classTalentMap[5] = "Thunder_A0";
	classTalentMap[6] = "Invisible_A0";
  classTalentMap[7] = "Mowgli_A0";
  classTalentMap[8] = "Inventor_A0";
	classTalentMap[9] = "Artist_A0";
	classTalentMap[10] = "Highlander_A0";
	classTalentMap[11] = "Marine_A0";
	classTalentMap[12] = "Firefox_A0";
	classTalentMap[13] = "Healer_A0";
	classTalentMap[14] = "Night_A0";
	classTalentMap[15] = "Rockman_A0";
	classTalentMap[16] = "Assassin_A0";
	classTalentMap[17] = "Unicorn_A0";
	classTalentMap[18] = "Hunter_A0";
	classTalentMap[19] = "GhostLord_A0";
	classTalentMap[20] = "Ratcatcher_A0";
	classTalentMap[21] = "Archeress_A0";
	classTalentMap[22] = "Werewolf_A0";
	classTalentMap[23] = "Frogenglut_A0";
	classTalentMap[24] = "Vedun_A0";
	classTalentMap[25] = "ManaWyrm_A0";
	classTalentMap[26] = "Bard_A0";
	classTalentMap[27] = "Naga_A0";
	classTalentMap[28] = "Mage_A0";
	classTalentMap[29] = "Fairy_A0";
	classTalentMap[30] = "Witcher_A0";
	classTalentMap[31] = "Alchemist_A0";
	classTalentMap[32] = "Demonolog_A0";
	classTalentMap[33] = "Vampire_A0";
	classTalentMap[34] = "Witch_A0";
	classTalentMap[35] = "Crusader_A0";
	classTalentMap[36] = "Monster_A0";
	classTalentMap[37] = "Prince_A1";
	classTalentMap[38] = "Prince_A2";
	classTalentMap[39] = "Prince_A1u1";
	classTalentMap[40] = "Prince_A2u";
	classTalentMap[41] = "Prince_A3";
	classTalentMap[42] = "Prince_A4";
	classTalentMap[43] = "Prince_A3u";
	classTalentMap[44] = "Prince_A5";
	classTalentMap[45] = "SnowQueen_A1";
	classTalentMap[46] = "SnowQueen_A2";
	classTalentMap[47] = "SnowQueen_A1u";
	classTalentMap[48] = "SnowQueen_A3";
	classTalentMap[49] = "SnowQueen_A5";
	classTalentMap[50] = "SnowQueen_A4";
	classTalentMap[51] = "SnowQueen_A3u";
	classTalentMap[52] = "SnowQueen_A4u";
	classTalentMap[53] = "Faceless_A1";
	classTalentMap[54] = "Faceless_A3";
	classTalentMap[55] = "Faceless_A1u1";
	classTalentMap[56] = "Faceless_A3u1";
	classTalentMap[57] = "Faceless_A0";
	classTalentMap[58] = "Faceless_A4";
	classTalentMap[59] = "Faceless_A3u2";
	classTalentMap[60] = "Faceless_A4u1";
	classTalentMap[61] = "Warlord_A1";
	classTalentMap[62] = "Warlord_A2";
	classTalentMap[63] = "Warlord_A1u";
	classTalentMap[64] = "Warlord_A2u";
	classTalentMap[65] = "Warlord_A3";
	classTalentMap[66] = "Warlord_A4";
	classTalentMap[67] = "Warlord_A3u";
	classTalentMap[68] = "Warlord_A4u";
	classTalentMap[69] = "Thunder_A1";
	classTalentMap[70] = "Thunder_A2";
	classTalentMap[71] = "Thunder_A1_Upg";
	classTalentMap[72] = "Thunder_A3";
	classTalentMap[73] = "Thunder_A4";
	classTalentMap[74] = "Thunder_A1_Upg2";
	classTalentMap[75] = "Thunder_A3_Upg";
	classTalentMap[76] = "Thunder_A4_Upg";
	classTalentMap[77] = "Invisible_A1";
	classTalentMap[78] = "Invisible_A1u";
	classTalentMap[79] = "Invisible_A2";
	classTalentMap[80] = "Invisible_A2u1"; //wtf
	classTalentMap[81] = "Invisible_A3";
	classTalentMap[82] = "Invisible_A4";
	classTalentMap[83] = "Invisible_A2u2"; //wtf
	classTalentMap[84] = "Invisible_A3u";
	classTalentMap[85] = "Mowgli_A1";
	classTalentMap[86] = "Mowgli_A3";
	classTalentMap[87] = "Mowgli_A1_Upg2";
	classTalentMap[88] = "Mowgli_A3_Upg";
	classTalentMap[89] = "Mowgli_A2";
	classTalentMap[90] = "Mowgli_A1_Upg1";
	classTalentMap[91] = "Mowgli_A4";
	classTalentMap[92] = "Mowgli_A4_Upg";
  classTalentMap[93] = "Inventor_A1";
  classTalentMap[94] = "Inventor_A3";
  classTalentMap[95] = "Inventor_A1u";
  classTalentMap[96] = "Inventor_A5";
  classTalentMap[97] = "Inventor_A2";
	classTalentMap[98] = "Inventor_A4";
  classTalentMap[99] = "Inventor_A3u";
  classTalentMap[100] = "Inventor_A2u";
	classTalentMap[101] = "Artist_A1";
	classTalentMap[102] = "Artist_A3";
	classTalentMap[103] = "Artist_A1u";
	classTalentMap[104] = "Artist_A0u";
	classTalentMap[105] = "Artist_A2";
	classTalentMap[106] = "Artist_A2u";
	classTalentMap[107] = "Artist_A4";
	classTalentMap[108] = "Artist_A4u";
	classTalentMap[109] = "Highlander_A1";
	classTalentMap[110] = "Highlander_A3";
	classTalentMap[111] = "Highlander_A1u1";
	classTalentMap[112] = "Highlander_A3u";
	classTalentMap[113] = "Highlander_A2";
	classTalentMap[114] = "Highlander_A1u2";
	classTalentMap[115] = "Highlander_A4";
	classTalentMap[116] = "Highlander_A2u";
	classTalentMap[117] = "Marine_A2";
	classTalentMap[118] = "Marine_A3";
	classTalentMap[119] = "Marine_A1";
	classTalentMap[120] = "Marine_A2u";
	classTalentMap[121] = "Marine_A3u";
	classTalentMap[122] = "Marine_A4";
	classTalentMap[123] = "Marine_A1u";
	classTalentMap[124] = "Marine_A4u";
	classTalentMap[125] = "Firefox_A1";
	classTalentMap[126] = "Firefox_A3";
	classTalentMap[127] = "Firefox_A1_Upg1";
	classTalentMap[128] = "Firefox_A3_Upg1";
	classTalentMap[129] = "Firefox_A4";
	classTalentMap[130] = "Firefox_A1_Upg2";
	classTalentMap[131] = "Firefox_A4_Upg1";
	classTalentMap[132] = "Firefox_A2";
	classTalentMap[133] = "Healer_A1";
	classTalentMap[134] = "Healer_A5";
	classTalentMap[135] = "Healer_A1_Upg2";
	classTalentMap[136] = "Healer_A2";
	classTalentMap[137] = "Healer_A4";
	classTalentMap[138] = "Healer_A1_Upg1";
	classTalentMap[139] = "Healer_A3";
	classTalentMap[140] = "Healer_A4_Upg";
	classTalentMap[141] = "Night_A2";
	classTalentMap[142] = "Night_A1";
	classTalentMap[143] = "Night_A2u";
	classTalentMap[144] = "Night_A1u";
	classTalentMap[145] = "Night_A3";
	classTalentMap[146] = "Night_A4";
	classTalentMap[147] = "Night_A3u";
	classTalentMap[148] = "Night_A4u";
	classTalentMap[149] = "Rockman_A1";
	classTalentMap[150] = "Rockman_A3";
	classTalentMap[151] = "Rockman_A1_Upg";
	classTalentMap[152] = "Rockman_A2";
  classTalentMap[153] = "Rockman_A4";
  classTalentMap[154] = "Rockman_A3_Upg";
	classTalentMap[155] = "Rockman_A4_Upg";
	classTalentMap[156] = "Rockman_A2_Upg";
	classTalentMap[157] = "Assassin_A1";
	classTalentMap[158] = "Assassin_A2";
	classTalentMap[159] = "Assassin_A1u";
	classTalentMap[160] = "Assassin_A2u1";
	classTalentMap[161] = "Assassin_A3";
	classTalentMap[162] = "Assassin_A2u2";
	classTalentMap[163] = "Assassin_A4";
	classTalentMap[164] = "Assassin_A3u";
	classTalentMap[165] = "Unicorn_A1";
	classTalentMap[166] = "Unicorn_A3";
	classTalentMap[167] = "Unicorn_A1u";
	classTalentMap[168] = "Unicorn_A3u";
	classTalentMap[169] = "Unicorn_A2";
	classTalentMap[170] = "Unicorn_A2u";
	classTalentMap[171] = "Unicorn_A4";
	classTalentMap[172] = "Unicorn_A4u";
	classTalentMap[173] = "Hunter_A1";
	classTalentMap[174] = "Hunter_A2";
	classTalentMap[175] = "Hunter_A1u";
	classTalentMap[176] = "Hunter_A3";
	classTalentMap[177] = "Hunter_A4";
	classTalentMap[178] = "Hunter_A3u1";
	classTalentMap[179] = "Hunter_A4u";
	classTalentMap[180] = "Hunter_A3u2";
	classTalentMap[181] = "GhostLord_A2";
	classTalentMap[182] = "GhostLord_A1";
	classTalentMap[183] = "GhostLord_A2u";
	classTalentMap[184] = "GhostLord_A3";
	classTalentMap[185] = "GhostLord_A5";
	classTalentMap[186] = "GhostLord_A4";
	classTalentMap[187] = "GhostLord_A1u";
	classTalentMap[188] = "GhostLord_A4u";
	classTalentMap[189] = "Ratcatcher_A1";
	classTalentMap[190] = "Ratcatcher_A2";
	classTalentMap[191] = "Ratcatcher_A1_3_Upg";
	classTalentMap[192] = "Ratcatcher_A2_Upg1";
	classTalentMap[193] = "Ratcatcher_A3";
	classTalentMap[194] = "Ratcatcher_A4";
	classTalentMap[195] = "Ratcatcher_A2_Upg2";
	classTalentMap[196] = "Ratcatcher_A4_Upg";
	classTalentMap[197] = "Archeress_A1";
	classTalentMap[198] = "Archeress_A2";
	classTalentMap[199] = "Archeress_A1u";
	classTalentMap[200] = "Archeress_A2u2";
	classTalentMap[201] = "Archeress_A3";
	classTalentMap[202] = "Archeress_A2u1";
	classTalentMap[203] = "Archeress_A4";
	classTalentMap[204] = "Archeress_A4u";
	classTalentMap[205] = "Werewolf_A2";
	classTalentMap[206] = "Werewolf_A1";
	classTalentMap[207] = "Werewolf_A2u";
	classTalentMap[208] = "Werewolf_A1u1";
	classTalentMap[209] = "Werewolf_A3";
	classTalentMap[210] = "Werewolf_A4";
	classTalentMap[211] = "Werewolf_A3u";
	classTalentMap[212] = "Werewolf_A1u2";
	classTalentMap[213] = "Frogenglut_A1";
	classTalentMap[214] = "Frogenglut_A3";
	classTalentMap[215] = "Frogenglut_A1u";
	classTalentMap[216] = "Frogenglut_A3u";
	classTalentMap[217] = "Frogenglut_A2";
	classTalentMap[218] = "Frogenglut_A4";
	classTalentMap[219] = "Frogenglut_A2u";
	classTalentMap[220] = "Frogenglut_A4u";
	classTalentMap[221] = "Vedun_A1";
	classTalentMap[222] = "Vedun_A2";
	classTalentMap[223] = "Vedun_A1u";
	classTalentMap[224] = "Vedun_A2u";
	classTalentMap[225] = "Vedun_A3";
	classTalentMap[226] = "Vedun_A4";
	classTalentMap[227] = "Vedun_A3u";
	classTalentMap[228] = "Vedun_A4u";
	classTalentMap[229] = "ManaWyrm_A1";
	classTalentMap[230] = "ManaWyrm_A2";
	classTalentMap[231] = "ManaWyrm_A1_Upg";
	classTalentMap[232] = "ManaWyrm_A2u1";
	classTalentMap[233] = "ManaWyrm_A3";
  classTalentMap[234] = "ManaWyrm_A4";
  classTalentMap[235] = "ManaWyrm_A2u2";
	classTalentMap[236] = "ManaWyrm_A4u";
	classTalentMap[237] = "Bard_A1";
	classTalentMap[238] = "Bard_A2";
	classTalentMap[239] = "Bard_A3";
	classTalentMap[240] = "Bard_A1u";
	classTalentMap[241] = "Bard_A2u";
	classTalentMap[242] = "Bard_A3u";
	classTalentMap[243] = "Bard_A4";
	classTalentMap[244] = "Bard_A4u";
	classTalentMap[245] = "Naga_A1";
	classTalentMap[246] = "Naga_A5";
	classTalentMap[247] = "Naga_A4";
	classTalentMap[248] = "Naga_A2";
	classTalentMap[249] = "Naga_A3";
	classTalentMap[250] = "Naga_A4u1";
	classTalentMap[251] = "Naga_A2u1";
	classTalentMap[252] = "Naga_A3u1";
	classTalentMap[253] = "Mage_A1";
	classTalentMap[254] = "Mage_A2";
	classTalentMap[255] = "Mage_A1u";
	classTalentMap[256] = "Mage_A2u";
	classTalentMap[257] = "Mage_A3";
	classTalentMap[258] = "Mage_A4";
	classTalentMap[259] = "Mage_A3u";
	classTalentMap[260] = "Mage_A4u";
	classTalentMap[261] = "Fairy_A1";
	classTalentMap[262] = "Fairy_A2";
	classTalentMap[263] = "Fairy_A1u";
	classTalentMap[264] = "Fairy_A2u";
	classTalentMap[265] = "Fairy_A3";
	classTalentMap[266] = "Fairy_A4";
	classTalentMap[267] = "Fairy_A3u1";
	classTalentMap[268] = "Fairy_A3u2";
	classTalentMap[269] = "Witcher_A1";
	classTalentMap[270] = "Witcher_A3";
	classTalentMap[271] = "Witcher_A1u1";
	classTalentMap[272] = "Witcher_A2";
	classTalentMap[273] = "Witcher_A1u2";
	classTalentMap[274] = "Witcher_A4";
	classTalentMap[275] = "Witcher_A2u";
	classTalentMap[276] = "Witcher_A4u";
	classTalentMap[277] = "Alchemist_A1";
	classTalentMap[278] = "Alchemist_A3";
	classTalentMap[279] = "Alchemist_A1u";
	classTalentMap[280] = "Alchemist_A3u";
	classTalentMap[281] = "Alchemist_A2";
	classTalentMap[282] = "Alchemist_A2u";
	classTalentMap[283] = "Alchemist_A4";
	classTalentMap[284] = "Alchemist_A4u";
	classTalentMap[285] = "Demonolog_A1";
	classTalentMap[286] = "Demonolog_A2";
	classTalentMap[287] = "Demonolog_A1u1";
	classTalentMap[288] = "Demonolog_A2u";
	classTalentMap[289] = "Demonolog_A3";
	classTalentMap[290] = "Demonolog_A1u2";
	classTalentMap[291] = "Demonolog_A4";
	classTalentMap[292] = "Demonolog_A4u";
	classTalentMap[293] = "Vampire_A1";
	classTalentMap[294] = "Vampire_A2";
	classTalentMap[295] = "Vampire_A1u";
	classTalentMap[296] = "Vampire_A3";
	classTalentMap[297] = "Vampire_A2u";
	classTalentMap[298] = "Vampire_A4";
	classTalentMap[299] = "Vampire_A3u";
	classTalentMap[300] = "Vampire_A4u";
	classTalentMap[301] = "Witch_A1";
	classTalentMap[302] = "Witch_A2";
	classTalentMap[303] = "Witch_A1u";
	classTalentMap[304] = "Witch_A2u";
	classTalentMap[305] = "Witch_A3";
	classTalentMap[306] = "Witch_A4";
	classTalentMap[307] = "Witch_A3u";
	classTalentMap[308] = "Witch_A4u";
	classTalentMap[309] = "Crusader_A1_A";
	classTalentMap[310] = "Crusader_A2";
	classTalentMap[311] = "Crusader_A1u_A";
	classTalentMap[312] = "Crusader_A2u";
	classTalentMap[313] = "Crusader_A3";
	classTalentMap[314] = "Crusader_A4";
	classTalentMap[315] = "Crusader_A3u";
	classTalentMap[316] = "Crusader_A4u";
  classTalentMap[317] = "Crusader_A1_B";
  classTalentMap[318] = "Crusader_A1u_B";
	classTalentMap[319] = "Monster_A3";
	classTalentMap[320] = "Monster_A1";
	classTalentMap[321] = "Monster_A3u";	
	classTalentMap[322] = "Monster_A1u";
	classTalentMap[323] = "Monster_A2";
	classTalentMap[324] = "Monster_A4";
	classTalentMap[325] = "Monster_A2u";
	classTalentMap[326] = "Monster_A4u";
	classTalentMap[327] = "Angel_A0";
	classTalentMap[328] = "Angel_A1";
	classTalentMap[329] = "Angel_A2";
	classTalentMap[330] = "Angel_A5";
	classTalentMap[331] = "Angel_A2u";
	classTalentMap[332] = "Angel_A3";
	classTalentMap[333] = "Angel_A1u";
	classTalentMap[334] = "Angel_A4";
	classTalentMap[335] = "Angel_A5u";
	classTalentMap[336] = "Freeze_A0";
	classTalentMap[337] = "Freeze_A1";
	classTalentMap[338] = "Freeze_A2";
	classTalentMap[339] = "Freeze_A1u";
	classTalentMap[340] = "Freeze_A2u";
	classTalentMap[341] = "Freeze_A3";
	classTalentMap[342] = "Freeze_A4";
	classTalentMap[343] = "Freeze_A3u";
	classTalentMap[344] = "Freeze_A4u";
	classTalentMap[345] = "Gunslinger_A0";
	classTalentMap[346] = "Gunslinger_A1";
	classTalentMap[347] = "Gunslinger_A2";
	classTalentMap[348] = "Gunslinger_A1u";
	classTalentMap[349] = "Gunslinger_A2u";
  classTalentMap[350] = "Gunslinger_A3";
  classTalentMap[351] = "Gunslinger_A4";
	classTalentMap[352] = "Gunslinger_A3u";
	classTalentMap[353] = "Gunslinger_A4u";
	classTalentMap[354] = "Reaper_A0";
	classTalentMap[355] = "Reaper_A1";
	classTalentMap[356] = "Reaper_A2";
	classTalentMap[357] = "Reaper_A1u";
	classTalentMap[358] = "Reaper_A2u";
	classTalentMap[359] = "Reaper_A3";
	classTalentMap[360] = "Reaper_A4";
	classTalentMap[361] = "Reaper_A3u";
	classTalentMap[362] = "Reaper_A4u";
	classTalentMap[363] = "Fluffy_A0";
	classTalentMap[364] = "Fluffy_A1";
	classTalentMap[365] = "Fluffy_A3";
	classTalentMap[366] = "Fluffy_A1u";
	classTalentMap[367] = "Fluffy_A3u";
	classTalentMap[368] = "Fluffy_A2";
	classTalentMap[369] = "Fluffy_A4";
	classTalentMap[370] = "Fluffy_A2u";
	classTalentMap[371] = "Fluffy_A4u";
	classTalentMap[372] = "Rifleman_A0";
	classTalentMap[373] = "Rifleman_A1";
	classTalentMap[374] = "Rifleman_A2";
	classTalentMap[375] = "Rifleman_A1u";
	classTalentMap[376] = "Rifleman_A2u";
	classTalentMap[377] = "Rifleman_A3";
	classTalentMap[378] = "Rifleman_A4";
	classTalentMap[379] = "Rifleman_A3u";
	classTalentMap[380] = "Rifleman_A4u";
	classTalentMap[381] = "MagicGirl_A0";
	classTalentMap[382] = "MagicGirl_A1";
	classTalentMap[383] = "MagicGirl_A2";
	classTalentMap[384] = "MagicGirl_A1u";
	classTalentMap[385] = "MagicGirl_A2u";
	classTalentMap[386] = "MagicGirl_A3";
	classTalentMap[387] = "MagicGirl_A4";
	classTalentMap[388] = "MagicGirl_A3u";
	classTalentMap[389] = "MagicGirl_A4u";
	classTalentMap[390] = "PinkGirl_A0";
	classTalentMap[391] = "PinkGirl_A1";
	classTalentMap[392] = "PinkGirl_A2";
	classTalentMap[393] = "PinkGirl_A1u";
	classTalentMap[394] = "PinkGirl_A2u";
	classTalentMap[395] = "PinkGirl_A3";
	classTalentMap[396] = "PinkGirl_A4";
	classTalentMap[397] = "PinkGirl_A3u";
	classTalentMap[398] = "PinkGirl_A4u";
	classTalentMap[399] = "IronKnight_A0";
	classTalentMap[400] = "IronKnight_A1";
	classTalentMap[401] = "IronKnight_A2";
	classTalentMap[402] = "IronKnight_A1u";
	classTalentMap[403] = "IronKnight_A2u";
	classTalentMap[404] = "IronKnight_A3";
	classTalentMap[405] = "IronKnight_A4";
	classTalentMap[406] = "IronKnight_A3u";
	classTalentMap[407] = "IronKnight_A4u";
	classTalentMap[408] = "FallenAngel_A0";
	classTalentMap[409] = "FallenAngel_A2";
	classTalentMap[410] = "FallenAngel_A1";
	classTalentMap[411] = "FallenAngel_A4";
	classTalentMap[412] = "FallenAngel_A1u";
	classTalentMap[413] = "FallenAngel_A3";
	classTalentMap[414] = "FallenAngel_A4u";
	classTalentMap[415] = "FallenAngel_A3u";
	classTalentMap[416] = "FallenAngel_A2u";
	classTalentMap[417] = "BladeDancer_A0";
	classTalentMap[418] = "BladeDancer_A1";
	classTalentMap[419] = "BladeDancer_A2";
	classTalentMap[420] = "BladeDancer_A1u";
	classTalentMap[421] = "BladeDancer_A2u";
	classTalentMap[422] = "BladeDancer_A3";
	classTalentMap[423] = "BladeDancer_A4";
	classTalentMap[424] = "BladeDancer_A3u";
	classTalentMap[425] = "BladeDancer_A4u";
	classTalentMap[426] = "Ent_A0";
	classTalentMap[427] = "Ent_A1";
	classTalentMap[428] = "Ent_A2";
	classTalentMap[429] = "Ent_A5";
	classTalentMap[430] = "Ent_A1u";
	classTalentMap[431] = "Ent_A2u";
	classTalentMap[432] = "Ent_A3";
	classTalentMap[433] = "Ent_A4";
	classTalentMap[434] = "Ent_A4u";
	classTalentMap[435] = "Firefox_A4_2";
	classTalentMap[436] = "Firefox_A4_2U";
	classTalentMap[437] = "Werewolf_A4_2";
	classTalentMap[438] = "Archeress_A4_2";
	classTalentMap[439] = "Archeress_A4_2u";
	classTalentMap[440] = "GhostLord_A4_2";
	classTalentMap[441] = "GhostLord_A4_2u";
	classTalentMap[442] = "Inventor_A4_2";
	classTalentMap[443] = "Highlander_A4a";
	classTalentMap[444] = "Faceless_A4_2";
	classTalentMap[445] = "Faceless_A4_2U";
	classTalentMap[446] = "Alchemist_A4u_2";
	classTalentMap[447] = "Alchemist_A4_2";
	classTalentMap[448] = "Vampire_A4_2";
	classTalentMap[449] = "Vampire_A4_2u";
	classTalentMap[450] = "Monster_A4_2";
	classTalentMap[451] = "Monster_A4_2u";
	classTalentMap[452] = "Angel_A5_2";
	classTalentMap[453] = "Angel_A5_2u";
	classTalentMap[454] = "SnowQueen_A4_2";
	classTalentMap[455] = "SnowQueen_A4_2u";
	classTalentMap[456] = "Warlord_A4_2";
	classTalentMap[457] = "Warlord_A4_2u";
	classTalentMap[458] = "Artist_A4_2";
	classTalentMap[459] = "Artist_A4_2u";
	classTalentMap[460] = "Marine_A4_2";
	classTalentMap[461] = "Marine_A4u_2";
	classTalentMap[462] = "Unicorn_A4_2";
	classTalentMap[463] = "Unicorn_A4_2u";
	classTalentMap[464] = "Ratcatcher_A4_2";
  classTalentMap[465] = "Ratcatcher_A4_2u";
  classTalentMap[466] = "Frogenglut_A4_2";
	classTalentMap[467] = "Frogenglut_A4_2u";
	classTalentMap[468] = "Witcher_A4_2";
	classTalentMap[469] = "Witcher_A4_2u";
	classTalentMap[470] = "Prince_A4_2u";
	classTalentMap[471] = "PlagueDoctor_A0";
	classTalentMap[472] = "PlagueDoctor_A1";
	classTalentMap[473] = "PlagueDoctor_A2";
	classTalentMap[474] = "PlagueDoctor_A5";
	classTalentMap[475] = "PlagueDoctor_A1u";
	classTalentMap[476] = "PlagueDoctor_A2u";
	classTalentMap[477] = "PlagueDoctor_A3";
	classTalentMap[478] = "PlagueDoctor_A4";
	classTalentMap[479] = "PlagueDoctor_A4u";
	classTalentMap[480] = "Vedun_A4_2";
	classTalentMap[481] = "Vedun_A4_2u";
	classTalentMap[482] = "Witch_A4_2";
	classTalentMap[483] = "Witch_A4_2u";
	classTalentMap[484] = "Bard_A4_2";
	classTalentMap[485] = "Bard_A4_2u";
	classTalentMap[486] = "BladeDancer_A4_2";
	classTalentMap[487] = "BladeDancer_A4_2u";
	classTalentMap[488] = "Hunter_A4_2";
	classTalentMap[489] = "Hunter_A4_2u";
	classTalentMap[490] = "Healer_A4_2";
	classTalentMap[491] = "Healer_A4_2u";
	classTalentMap[492] = "IronKnight_A4_2";
	classTalentMap[493] = "IronKnight_A4_2u";
	classTalentMap[494] = "Gunslinger_A4_2";
	classTalentMap[495] = "Gunslinger_A4_2u";
	classTalentMap[496] = "Rifleman_A4_2";
	classTalentMap[497] = "Rifleman_A4_2u";
	classTalentMap[498] = "ManaWyrm_A4_2";
	classTalentMap[499] = "ManaWyrm_A4_2u";
	classTalentMap[500] = "Mowgli_A4_2";
	classTalentMap[501] = "Mowgli_A4_2Upg";
	classTalentMap[502] = "MagicGirl_A4_2";
	classTalentMap[503] = "MagicGirl_A4_2u";
	classTalentMap[504] = "Reaper_A4_2";
	classTalentMap[505] = "Reaper_A4_2u";
	classTalentMap[506] = "Katana_A0";
	classTalentMap[507] = "Katana_A1";
	classTalentMap[508] = "Katana_A2";
	classTalentMap[509] = "Katana_A1u";
	classTalentMap[510] = "Katana_A2u";
	classTalentMap[511] = "Katana_A3";
	classTalentMap[512] = "Katana_A4_2";
	classTalentMap[513] = "Katana_A3u";
	classTalentMap[514] = "Katana_A4_2u";
	classTalentMap[515] = "Katana_A4";
	classTalentMap[516] = "Katana_A4u";
	classTalentMap[517] = "Rockman_A4_2";
	classTalentMap[518] = "Rockman_A4_2u";
	classTalentMap[519] = "Ent_A4_2";
	classTalentMap[520] = "Ent_A4_2u";
  classTalentMap[521] = "Crusader_A4_2";
  classTalentMap[522] = "Crusader_A4_2u";
	classTalentMap[523] = "Assassin_A3_2";
	classTalentMap[524] = "Assassin_A3_2u";
	classTalentMap[525] = "Freeze_A4_2";
	classTalentMap[526] = "Freeze_A4_2u";
	classTalentMap[527] = "Plane_A0";
	classTalentMap[528] = "Plane_A1";
	classTalentMap[529] = "Plane_A2";
	classTalentMap[530] = "Plane_A1u";
	classTalentMap[531] = "Plane_A2u";
	classTalentMap[532] = "Plane_A3";
	classTalentMap[533] = "Plane_A4";
	classTalentMap[534] = "Plane_A3u";
	classTalentMap[535] = "Plane_A4u";
	classTalentMap[536] = "Plane_A4_2";
	classTalentMap[537] = "Plane_A4_2u";
	classTalentMap[538] = "Mage_A4_2";
	classTalentMap[539] = "Mage_A4_2u";
	classTalentMap[540] = "PlagueDoctor_A4_2";
	classTalentMap[541] = "PlagueDoctor_A4_2u";
	classTalentMap[542] = "Fairy_A3_2";
	classTalentMap[543] = "Fairy_A3_2u1";
	classTalentMap[544] = "Fairy_A3_2u2";
	classTalentMap[545] = "Thunder_A4_2";
	classTalentMap[546] = "Thunder_A4_2u";
	classTalentMap[547] = "FallenAngel_A4_2";
	classTalentMap[548] = "FallenAngel_A4_2u";
	classTalentMap[549] = "Invisible_A4_2";
	classTalentMap[550] = "Invisible_A4_2u";
	classTalentMap[551] = "Zealot_A0";
	classTalentMap[552] = "Zealot_A1";
	classTalentMap[553] = "Zealot_A2";
	classTalentMap[554] = "Zealot_A1u";
	classTalentMap[555] = "Zealot_A2u";
	classTalentMap[556] = "Zealot_A3";
	classTalentMap[557] = "Zealot_A4";
	classTalentMap[558] = "Zealot_A3u";
	classTalentMap[559] = "Zealot_A4u";
	classTalentMap[560] = "Zealot_A4_2";
	classTalentMap[561] = "Zealot_A4_2u";
	classTalentMap[562] = "Fluffy_A4_2";
	classTalentMap[563] = "Fluffy_A4_2u";
	classTalentMap[564] = "PinkGirl_A4_2";
	classTalentMap[565] = "PinkGirl_A4_2u";
	classTalentMap[566] = "WraithKing_A0";
	classTalentMap[567] = "WraithKing_A1";
	classTalentMap[568] = "WraithKing_A3";
	classTalentMap[569] = "WraithKing_A1u";
	classTalentMap[570] = "WraithKing_A3u";
  classTalentMap[571] = "WraithKing_A2";
  classTalentMap[572] = "WraithKing_A4";
	classTalentMap[573] = "WraithKing_A2u";
	classTalentMap[574] = "WraithKing_A4u";
	classTalentMap[575] = "WraithKing_A4_2";
	classTalentMap[576] = "WraithKing_A4_2u";
	classTalentMap[577] = "Demonolog_A4_2";
	classTalentMap[578] = "Demonolog_A4_2u";
	classTalentMap[579] = "Naga_A4_2";
	classTalentMap[580] = "Naga_A4_2u";
	classTalentMap[581] = "Night_A4_2";
	classTalentMap[582] = "Night_A4_2u";
	classTalentMap[583] = "Dryad_A0";
	classTalentMap[584] = "Dryad_A1";
	classTalentMap[585] = "Dryad_A2";
	classTalentMap[586] = "Dryad_A1u";
	classTalentMap[587] = "Dryad_A2u";
	classTalentMap[588] = "Dryad_A3";
	classTalentMap[589] = "Dryad_A4";
	classTalentMap[590] = "Dryad_A3u";
	classTalentMap[591] = "Dryad_A4u";
	classTalentMap[592] = "Dryad_A4_2";
	classTalentMap[593] = "Dryad_A4_2u";
	classTalentMap[594] = "Firefox_A1_SUP";
	classTalentMap[595] = "Firefox_A3_SUP";
	classTalentMap[596] = "SnowQueen_A1_SUP";
	classTalentMap[597] = "SnowQueen_A2_SUP";
	classTalentMap[598] = "Archeress_A1_SUP";
	classTalentMap[599] = "Archeress_A2_SUP";
	classTalentMap[600] = "Rockman_A0_SUP";
	classTalentMap[601] = "Rockman_A3_SUP";
	classTalentMap[602] = "Gunslinger_A2_SUP";
	classTalentMap[603] = "Gunslinger_A3_SUP";
	classTalentMap[604] = "Mage_A1_SUP";
	classTalentMap[605] = "Mage_A2_SUP";
	classTalentMap[606] = "PlagueDoctor_A1_SUP";
	classTalentMap[607] = "PlagueDoctor_A5_SUP";
	classTalentMap[608] = "Prince_A1_SUP";
	classTalentMap[609] = "Prince_A2_SUP";
	classTalentMap[610] = "Werewolf_A2_SUP";
	classTalentMap[611] = "Werewolf_A4_A4_2_SUP";
	classTalentMap[612] = "Dryad_A1_SUP";
	classTalentMap[613] = "Dryad_A2_SUP";
	classTalentMap[614] = "Stalker_A0";
	classTalentMap[615] = "Stalker_A1";
	classTalentMap[616] = "Stalker_A2";
	classTalentMap[617] = "Stalker_A1u";
	classTalentMap[618] = "Stalker_A2u";
	classTalentMap[619] = "Stalker_A3";
	classTalentMap[620] = "Stalker_A4";
	classTalentMap[621] = "Stalker_A3u";
	classTalentMap[622] = "Stalker_A4u";
	classTalentMap[623] = "Stalker_A4_2";
	classTalentMap[624] = "Stalker_A4_2u";
	classTalentMap[625] = "Monster_A1_SUP";
	classTalentMap[626] = "Monster_A2_SUP";
	classTalentMap[627] = "Mowgli_A0_SUP";
	classTalentMap[628] = "Mowgli_A2_SUP";
	classTalentMap[629] = "Bard_A5_SUP";
	classTalentMap[630] = "Bard_A0_SUP";
	classTalentMap[631] = "Vampire_A0_SUP";
	classTalentMap[632] = "Vampire_A1_SUP";
	classTalentMap[633] = "Plane_A0_SUP";
	classTalentMap[634] = "Plane_A3_SUP";
	classTalentMap[635] = "Angel_A1_SUP";
	classTalentMap[636] = "Angel_A3_SUP";
	classTalentMap[637] = "Ratcatcher_A1_SUP";
	classTalentMap[638] = "Ratcatcher_A2_SUP";
	classTalentMap[639] = "Thunder_A0_SUP";
	classTalentMap[640] = "Thunder_A3_SUP";
	classTalentMap[641] = "Alchemist_A1_SUP";
	classTalentMap[642] = "Alchemist_A3_SUP";
	classTalentMap[643] = "Inventor_A4_SUP";
	classTalentMap[644] = "Inventor_A4_2_SUP";
	classTalentMap[645] = "Artist_A1_SUP";
	classTalentMap[646] = "Artist_A2_SUP";
	classTalentMap[647] = "Highlander_A1_SUP";
	classTalentMap[648] = "Highlander_A2_SUP";
	classTalentMap[649] = "ManaWyrm_A0_SUP";
	classTalentMap[650] = "ManaWyrm_A3_SUP";
	classTalentMap[651] = "Stalker_A0_SUP";
	classTalentMap[652] = "Stalker_A2_SUP";
	classTalentMap[653] = "Gunner_A0";
	classTalentMap[654] = "Gunner_A1";
	classTalentMap[655] = "Gunner_A2";
	classTalentMap[656] = "Gunner_A1u";
	classTalentMap[657] = "Gunner_A2u";
	classTalentMap[658] = "Gunner_A3";
	classTalentMap[659] = "Gunner_A4";
	classTalentMap[660] = "Gunner_A3u";
	classTalentMap[661] = "Gunner_A4u";
	classTalentMap[662] = "Gunner_A4_2";
	classTalentMap[663] = "Gunner_A4_2u";
	classTalentMap[664] = "Gunner_A0_SUP";
	classTalentMap[665] = "Gunner_A1_SUP";
	classTalentMap[666] = "IronKnight_A2_SUP";
	classTalentMap[667] = "IronKnight_A3_SUP";
	classTalentMap[668] = "Ent_A1_SUP";
	classTalentMap[669] = "Ent_A3_SUP";
	classTalentMap[670] = "Marine_A2_SUP";
	classTalentMap[671] = "Marine_A3_SUP";
	classTalentMap[672] = "Frogenglut_A0_SUP";
	classTalentMap[673] = "Frogenglut_A2_SUP";
	classTalentMap[674] = "Rifleman_A1_SUP";
	classTalentMap[675] = "Rifleman_A3_SUP";
	classTalentMap[676] = "Chronicle_A0";
	classTalentMap[677] = "Chronicle_A1";
	classTalentMap[678] = "Chronicle_A2";
	classTalentMap[679] = "Chronicle_A1u";
	classTalentMap[680] = "Chronicle_A5";
	classTalentMap[681] = "Chroniclel_A3";
	classTalentMap[682] = "Chronicle_A4_2";
	classTalentMap[683] = "Chronicle_A3u";
	classTalentMap[684] = "Chronicle_A4_2u";
	classTalentMap[685] = "Chronicle_A5_SUP";
	classTalentMap[686] = "Chronicle_A3_SUP";
	classTalentMap[687] = "Vedun_A1_SUP";
	classTalentMap[688] = "Vedun_A3_SUP";
	classTalentMap[689] = "Chronicle_A4";
	classTalentMap[690] = "Chronicle_A4u";
	classTalentMap[691] = "GhostLord_A0_SUP";
	classTalentMap[692] = "GhostLord_A2_SUP";
	classTalentMap[693] = "Hunter_A0_SUP";
	classTalentMap[694] = "Hunter_A1_SUP";
	classTalentMap[695] = "Fairy_A2_SUP";
	classTalentMap[696] = "Fairy_A4_SUP";
	classTalentMap[697] = "Unicorn_A0_SUP";
	classTalentMap[698] = "Unicorn_A1_SUP";
	classTalentMap[699] = "Invisible_A1_SUP";
	classTalentMap[700] = "Invisible_A2_SUP";
	classTalentMap[701] = "Naga_A1_SUP";
	classTalentMap[702] = "Naga_A3_SUP";
	classTalentMap[703] = "Freeze_A0_SUP";
	classTalentMap[704] = "Freeze_A1_SUP";
	classTalentMap[705] = "PinkGirl_A0_SUP";
	classTalentMap[706] = "PinkGirl_A3_SUP";
	classTalentMap[707] = "Witch_A1_SUP";
	classTalentMap[708] = "Witch_A2_SUP";
	classTalentMap[709] = "Assassin_A0_SUP";
	classTalentMap[710] = "Assassin_A0_SUP_2";
	classTalentMap[711] = "Brewer_A0";
	classTalentMap[712] = "Brewer_A1";
	classTalentMap[713] = "Brewer_A2";
	classTalentMap[714] = "Brewer_A4";
	classTalentMap[715] = "Brewer_A2u";
	classTalentMap[716] = "Brewer_A3";
	classTalentMap[717] = "Brewer_A1u";
	classTalentMap[718] = "Brewer_A3u";
	classTalentMap[719] = "Brewer_A4u";
	classTalentMap[720] = "Brewer_A4_2";
	classTalentMap[721] = "Brewer_A4_2u";
	classTalentMap[722] = "Katana_A0_SUP";
	classTalentMap[723] = "Katana_A4_A4_2_SUP";
	classTalentMap[724] = "Zealot_A1_SUP";
	classTalentMap[725] = "Zealot_A2_SUP";
	classTalentMap[726] = "Warlord_A1_SUP";
	classTalentMap[727] = "Warlord_A3_SUP";
	classTalentMap[728] = "Brewer_A0_SUP";
	classTalentMap[729] = "Brewer_A1_SUP";
	classTalentMap[730] = "WraithKing_A1_SUP";
	classTalentMap[731] = "WraithKing_A2_SUP";
	classTalentMap[732] = "Witcher_A3_SUP";
	classTalentMap[733] = "Witcher_A2_SUP";
	classTalentMap[734] = "Demonolog_A0_SUP";
	classTalentMap[735] = "Demonolog_A3_SUP";
	classTalentMap[736] = "Crusader_A2_SUP";
	classTalentMap[737] = "Crusader_A3_SUP";
	classTalentMap[738] = "BladeDancer_A0_SUP";
	classTalentMap[739] = "BladeDancer_A0_SUP_2";
	classTalentMap[740] = "Fluffy_A0_SUP";
	classTalentMap[741] = "Fluffy_A4_A4_2_SUP";
	classTalentMap[742] = "Reaper_A1_SUP";
	classTalentMap[743] = "Reaper_A2_SUP";
	classTalentMap[744] = "MagicGirl_A1_SUP";
	classTalentMap[745] = "MagicGirl_A2_SUP";
	classTalentMap[746] = "Night_A0_SUP";
	classTalentMap[747] = "Night_A3_SUP";
	classTalentMap[748] = "Healer_A1_SUP";
  classTalentMap[749] = "Healer_A5_SUP";
  classTalentMap[750] = "Shadow_A0";
  classTalentMap[751] = "Shadow_A1";
  classTalentMap[752] = "Shadow_A2";
  classTalentMap[753] = "Shadow_A1u";
  classTalentMap[754] = "Shadow_A2u";
  classTalentMap[755] = "Shadow_A3";
  classTalentMap[756] = "Shadow_A4";
  classTalentMap[757] = "Shadow_A3u";
  classTalentMap[758] = "Shadow_A4u";
  classTalentMap[759] = "Shadow_A4_2";
  classTalentMap[760] = "Shadow_A4_2u";
  classTalentMap[761] = "Shadow_A0_SUP";
  classTalentMap[762] = "Shadow_A1_SUP";
	classTalentMap[763] = "Faceless_A2_SUP";
	classTalentMap[764] = "Faceless_A1_SUP";
	classTalentMap[765] = "FallenAngel_A3_SUP";
	classTalentMap[766] = "FallenAngel_A4_2_SUP";
	classTalentMap[767] = "Wendigo_A2";
	classTalentMap[768] = "Wendigo_A1";
	classTalentMap[769] = "Wendigo_A3";
	classTalentMap[770] = "Wendigo_A2u";
	classTalentMap[771] = "Wendigo_A3u";
	classTalentMap[772] = "Wendigo_A4";
	classTalentMap[773] = "Wendigo_A5";
	classTalentMap[774] = "Wendigo_A0";
	classTalentMap[775] = "Wendigo_A4u";
	classTalentMap[776] = "Wendigo_A4_2";
	classTalentMap[777] = "Wendigo_A4_2u";
	classTalentMap[778] = "Wendigo_A5_SUP";
	classTalentMap[779] = "Wendigo_A0_SUP";
	classTalentMap[780] = "Trickster_A0";
	classTalentMap[781] = "Trickster_A1";
	classTalentMap[782] = "Trickster_A2";
	classTalentMap[783] = "Trickster_A1u";
	classTalentMap[784] = "Trickster_A2u";
	classTalentMap[785] = "Trickster_A3";
	classTalentMap[786] = "Trickster_A4";
	classTalentMap[787] = "Trickster_A3u";
	classTalentMap[788] = "Trickster_A4u";
	classTalentMap[789] = "Trickster_A4_2";
	classTalentMap[790] = "Trickster_A4_2u";
	classTalentMap[791] = "Trickster_A2_SUP";
	classTalentMap[792] = "Trickster_A3_SUP";
	classTalentMap[793] = "Banshee_A0";
	classTalentMap[794] = "Banshee_A1";
	classTalentMap[795] = "Banshee_A2";
	classTalentMap[796] = "Banshee_A1u";
	classTalentMap[797] = "Banshee_A2u";
	classTalentMap[798] = "Banshee_A3";
	classTalentMap[799] = "Banshee_A4_2";
	classTalentMap[800] = "Banshee_A5";
	classTalentMap[801] = "Banshee_A4_2u";
	classTalentMap[802] = "Banshee_A4";
	classTalentMap[803] = "Banshee_A4u";
	classTalentMap[804] = "Banshee_A0_SUP";
	classTalentMap[805] = "Banshee_A3_SUP";
  classTalentMap[806] = "Shaman_A0";
	classTalentMap[807] = "Shaman_A1";
	classTalentMap[808] = "Shaman_A2";
	classTalentMap[809] = "Shaman_A1u";
  classTalentMap[810] = "Shaman_A2u";
	classTalentMap[811] = "Shaman_A3";
	classTalentMap[812] = "Shaman_A4";
	classTalentMap[813] = "Shaman_A3u";
	classTalentMap[814] = "Shaman_A4u";
	classTalentMap[815] = "Shaman_A4_2";
	classTalentMap[816] = "Shaman_A4_2u";
	classTalentMap[817] = "Shaman_A2_SUP";
	classTalentMap[818] = "Shaman_A0_SUP";
	classTalentMap[819] = "Bomber_A0";
	classTalentMap[820] = "Bomber_A1";
	classTalentMap[821] = "Bomber_A2";
	classTalentMap[822] = "Bomber_A1u";
	classTalentMap[823] = "Bomber_A2u";
	classTalentMap[824] = "Bomber_A3";
	classTalentMap[825] = "Bomber_A4";
	classTalentMap[826] = "Bomber_A3u";
	classTalentMap[827] = "Bomber_A4u";
	classTalentMap[828] = "Bomber_A4_2";
	classTalentMap[829] = "Bomber_A4_2u";
	classTalentMap[830] = "Bomber_A1_SUP";
	classTalentMap[831] = "Bomber_A3_SUP";

	keysClassTalent.clear();
	std::map<int, std::string>::iterator it;

    for (it = classTalentMap.begin(); it != classTalentMap.end(); ++it) {
		keysClassTalent.push_back(it->first);

		//if(allResourcesIDs.find(it->second) == allResourcesIDs.end())
		//{
		//	OutputDebugStringA(it->second.c_str());
		//	OutputDebugStringA("\n");
		//}
	}
}
WebLauncherPostRequest::~WebLauncherPostRequest()
{
	// Close handles
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
}

std::string WideCharToMultiByteString(const wchar_t* wideCharString) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wideCharString, -1, NULL, 0, NULL, NULL);
    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideCharString, -1, &result[0], size_needed, NULL, NULL);
    return result;
}


static Json::Value ParseJson(const char* json) {
  Json::Reader jsonReader;
  Json::Value root;
  bool isOk = jsonReader.parse(json, root, false);
  return isOk ? root : Json::Value();
}


std::string WebLauncherPostRequest::SendPostRequest(const std::string& jsonData) {
  // Set headers and data for the POST request
  const char* headers = "Content-Type: application/json\r\n";
  const char* postData = jsonData.c_str();
  DWORD postDataLen = jsonData.length();
  DWORD headersDataLen = strlen(headers);

  // Send the HTTP request
  BOOL bRequestSent = HttpSendRequestA(hRequest, headers, headersDataLen, (LPVOID)postData, postDataLen);
  if (!bRequestSent) {
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return "";
  }

  // Read the response
  char buffer[4096];
  DWORD bytesRead = 0;
  std::string responseStream;

  while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    responseStream += buffer;
  }

  OutputDebugStringA(responseStream.c_str());

  return responseStream;
}


std::vector<WebLauncherPostRequest::TalentWebData> WebLauncherPostRequest::GetTallentSet(const wchar_t* nickName, const char* heroName)
{
	std::vector<TalentWebData> result;

	int heroID = characterMap[heroName];
	std::string nickNameU8 = WideCharToMultiByteString(nickName);

  // Talent build json request
	char jsonBuff[1024];
	ZeroMemory(jsonBuff,1024);
  sprintf(jsonBuff,"{\"method\": \"getUserBuildByNickname\", \"data\": {\"nickname\": \"%s\", \"hero\": %d}}",nickNameU8.c_str(), heroID);
	std::string jsonData = jsonBuff;
  std::string responseStream = SendPostRequest(jsonData);

  Json::Value parsedJsonSet = ParseJson(responseStream.c_str());
  int buildFetchRetryCount = 0;
  while (parsedJsonSet.empty() && buildFetchRetryCount < 10) {
    CriticalTrace( "Build fetch failed!" );
    parsedJsonSet = ParseJson(responseStream.c_str());
    Sleep(1000);
    buildFetchRetryCount++; // Failed json
  }
  if (parsedJsonSet.empty()) {
    ErrorTrace( "Build fetch failed! Player may be kicked from server" );
    ErrorTrace( responseStream.c_str() );
    return result;
  }

  Json::Value errorSet = parsedJsonSet.get("error", "ERROR");
  if (!errorSet.asString().empty()) {
    return result; // no talent set will be loaded
  }

  Json::Value dataSet = parsedJsonSet.get("data", "");
  bool isArrayTalents = dataSet.isArray();
  if (!isArrayTalents) {
    return result; // json parsing error
  }

  // Talent active slots json request
  ZeroMemory(jsonBuff,1024);
  sprintf(jsonBuff,"{\"method\": \"getUserActiveBarByNickname\", \"data\": {\"nickname\": \"%s\", \"hero\": %d}}",nickNameU8.c_str(), heroID);
  jsonData = jsonBuff;
  //responseStream = SendPostRequest(jsonData);
  //responseStream = "{\"error\":\"\",\"data\":[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-3,-9,0,8,0,0,0,0,7,0,0,2,0,0,0,0,0,0]}";
  responseStream = "{\"error\":\"invalid\",\"data\":[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]}";

  result.resize(36); // resize by max talent number

  bool useUserSlots = false;
  Json::Value parsedJsonBar = ParseJson(responseStream.c_str());
  if (!parsedJsonBar.empty()) {
    Json::Value errorBar = parsedJsonBar.get("error", "ERROR_BAR");
    if (errorBar.asString().empty()){
      Json::Value dataBar = parsedJsonBar.get("data" , "");
      bool isArrayBar = dataBar.isArray();
      if (isArrayBar) {
        useUserSlots = true;

        for (int i = 0; i < 36; ++i) {
          int activeSlot = dataBar[i].asInt();
          result[i].activeSlot = abs(activeSlot) - 1; // fill active slots
          result[i].isSmartCast = activeSlot < 0;
        }
      }
    }
  }

  for (int i = 0; i < 36; ++i) {
    result[i].webTalentId = dataSet[i].asInt();;
    if (!useUserSlots) {
      result[i].activeSlot = -1;
    }
    if (result[i].webTalentId == 0) {
      result.clear();
      break; // empty slot in build
    }
	}

	return result;
}

static int firstID = 360;

std::string WebLauncherPostRequest::ConvertFromClassID(int id)
{
	return classTalentMap[id-1];
}


// TODO: Remove duplicate code
WebLauncherPostRequest::WebLoginResponse WebLauncherPostRequest::GetNickName(const char* token)
{
  WebLoginResponse res;
  res.response = std::string();
  res.retCode = LoginResponse_FAIL;

  char jsonBuff[1024];
  ZeroMemory(jsonBuff,1024);

  sprintf(jsonBuff,"{\"method\": \"getUserByToken\", \"data\": {\"token\": \"%s\"}}", token);
  const std::string jsonData = jsonBuff;

  std::string responseStream = SendPostRequest(jsonData);

  OutputDebugStringA(responseStream.c_str());

  std::string curNumber = "";
  
  Json::Value parsedJson = ParseJson(responseStream.c_str());
  if (parsedJson.empty()) {
    return res; // Failed json
  }
  
  Json::Value data = parsedJson.get("data", "");
  Json::Value nickname = data.get("nickname", "");
  std::string utf8String = nickname.asString();
  
  // Fix 1251 encoding
	int utf8Length = static_cast<int>(utf8String.length());
  int wideCharLength = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), utf8Length, NULL, 0);

  wchar_t* wideCharString = new wchar_t[wideCharLength + 1];
  MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), utf8Length, wideCharString, wideCharLength);
  wideCharString[wideCharLength] = L'\0';

  int win1251Length = WideCharToMultiByte(1251, 0, wideCharString, -1, NULL, 0, NULL, NULL);
  char* win1251String = new char[win1251Length];
  WideCharToMultiByte(1251, 0, wideCharString, -1, win1251String, win1251Length, NULL, NULL);


  res.response = win1251String;
  res.retCode = res.response.empty() ?  WebLauncherPostRequest::LoginResponse_FAIL : WebLauncherPostRequest::LoginResponse_OK;

  return res;
}

void AddResourcePersistanceID(const char* data)
{
	allResourcesIDs.insert(data);
}

