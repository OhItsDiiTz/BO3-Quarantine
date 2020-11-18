#include "MenuFuncs.hpp"

void CG_AdvancedUAV(bool val) {
	if (val) {
		*(uint32_t*)(0x000C8998) = 0x408200AC;
	}
	else {
		*(uint32_t*)(0x000C8998) = 0x418200AC;
	}
}

void CG_RedBoxes(bool val) {
	if (val) {
		*(uint32_t*)(0x0058D69C) = 0x38600001;
		*(uint32_t*)(0x0058DF48) = 0x60000000;
	}
	else {
		*(uint32_t*)(0x0058D69C) = 0x38600000;
		*(uint32_t*)(0x0058DF48) = 0x418201D4;
	}
}

void CG_NoWeaponFlash(bool val) {
	if (val) {
		*(uint32_t*)(0x001909D0) = 0x60000000;
	}
	else {
		*(uint32_t*)(0x001909D0) = 0x4BFFE2B5;
	}
}

void CG_NoWeaponSounds(bool val) {
	if (val) {

	}
	else {

	}
}

void CG_NoRecoil(bool val) {
	if (val) {
		*(uint32_t*)(0x001908E8) = 0x60000000;
	}
	else {
		*(uint32_t*)(0x001908E8) = 0x485F7531;
	}
}

void CG_ThirdPerson(bool val) {
	if (val) {
		CG_SetThirdPerson(0, true);
	}
	else {
		CG_SetThirdPerson(0, false);
	}
}

//KILLS
void CG_PlayerWallhack(bool val) {

	///SetChallengeValue("mastery_hero_weapon", 1);
	///SetChallengeValue("completed_all_challenges", 1);
	///SetChallengeValue("mastery_boot_camp", 1);
	///SetChallengeValue("mastery_game_mode_victories", 1);
	///SetChallengeValue("mastery_game_mode_heroics", 1);
	///SetChallengeValue("mastery_career", 1);
	///SetChallengeValue("mastery_killer", 1);
	///SetChallengeValue("mastery_humiliation", 1);
	///SetChallengeValue("mastery_specialist_abilitites", 1);
	///SetChallengeValue("mastery_specialist_killjoy", 1);
	///SetChallengeValue("mastery_wildcards", 1);
	///SetChallengeValue("mastery_air_assault", 1);
	///SetChallengeValue("mastery_ground_assault", 1);
	///SetChallengeValue("mastery_support", 1);
	///SetChallengeValue("mastery_return_fire", 1);
	///SetChallengeValue("mastery_handling", 1);
	///SetChallengeValue("mastery_efficiency", 1);
	///SetChallengeValue("mastery_lethals", 1);
	///SetChallengeValue("mastery_tactical", 1);
	///SetChallengeValue("mastery_perk_1", 1);
	///SetChallengeValue("mastery_perk_2", 1);
	///SetChallengeValue("mastery_perk_3", 1);

	if (val) {

	}
	else {

	}
}

void CG_ItemWallhack(bool val) {
	if (val) {

	}
	else {

	}
}

void CG_Disconnect() {
	Cbuf_AddText(0, "disconnect\n");
}

void CG_CrashServer() {
	Cbuf_AddText(0, "cmd sl 1\n");
}

void TestCall() {
	Cbuf_AddText(0, "set lobbyTimerStatusVotingInterval 0; set lobbyTimerStartInterval 0;set lobbyTimerStatusStartInterval 0;set lobbyTimerStatusBeginInterval 0;set lobbySearchSkip 1;set party_minplayers 1;");
}

void WriteClientInt(int clientNum, int address, uint32_t value) {
	SV_GameSendServerCommand(clientNum, 0, va("i %i %i", (int)((address - 0x36C85AC4) / 4), value));
}

void CG_SetRank(float iVal) {
	StatSetValue("RANK", (int)(iVal - 1));
	StatSetValue("RANKXP", *(uint32_t*)(0x011FFFC4 + ((int)(iVal) * 4)));

	//*(char*)(stats_list + 0xC65D) = (int)(iVal);
	//*(uint32_t*)(stats_list + 0xC663) = ReverseInt(*(uint32_t*)(0x011FFFC0 + ((int)(iVal) * 4)));
}

void CG_SetPrestige(float iVal) {
	//*(char*)(stats_list + 0xC645) = (int)iVal;
	StatSetValue("PLEVEL", (int)iVal);
}

void CG_SetKills(float iVal) {
	StatSetValue("KILLS", (int)iVal);
}

void CG_SetDeaths(float iVal) {
	StatSetValue("DEATHS", (int)iVal);
}

void CG_SetWins(float iVal) {
	StatSetValue("WINS", (int)iVal);
}

void CG_SetLosses(float iVal) {
	StatSetValue("LOSSES", (int)iVal);
}

void CG_SetScore(float iVal) {
	StatSetValue("SCORE", (int)iVal);
}

void CG_SetTimePlayed(float iVal) {
	StatSetValue("TIME_PLAYED_TOTAL", (int)iVal);
}

void CG_SetUnlockTokens(float iVal) {
	*(char*)(stats_list + 0xB8F7) = (int)iVal;
}

void CG_SetClanname(int iVal) {
	strcpy((char*)(stats_list + 0xC7D9), va("^%i\x0", iVal));
}
#define GAMEMODE_COUNT 20
#define ATTACHMENT_COUNT 44

void CG_UnlockAll() {
	StringTable *table;
	StringTable_GetCoreAsset(CORE_TABLE_MILESTONE_1, &table);

	for (int i = 0; i < table->rowCount; i++) {
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "global")) {
			SetChallengeValue(StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "gamemode")) {
			for (int a = 0; a < GAMEMODE_COUNT; a++) {
				SetGamemodeChallengeValue(LiveStats_GetGameTypeName(a), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "attachment")) {
			for (int a = 0; a < ATTACHMENT_COUNT; a++) {
				SetAttachmentStat((char*)(*(uint32_t*)(0x00E5DE8C + (a * 4))), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "killstreak")) {
			for (int a = 0; a < 17; a++) {
				SetSpecialStat(LookupItemIndex(killstreaks[a]), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
	}
	StringTable_GetCoreAsset(CORE_TABLE_MILESTONE_2, &table);
	for (int i = 0; i < table->rowCount; i++) {
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "global")) {
			SetChallengeValue(StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "gamemode")) {
			for (int a = 0; a < GAMEMODE_COUNT; a++) {
				SetGamemodeChallengeValue(LiveStats_GetGameTypeName(a), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "attachment")) {
			for (int a = 0; a < ATTACHMENT_COUNT; a++) {
				SetAttachmentStat((char*)(*(uint32_t*)(0x00E5DE8C + (a * 4))), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "killstreak")) {
			for (int a = 0; a < 17; a++) {
				SetSpecialStat(LookupItemIndex(killstreaks[a]), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
	}
	StringTable_GetCoreAsset(CORE_TABLE_MILESTONE_3, &table);
	for (int i = 0; i < table->rowCount; i++) {
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "global")) {
			SetChallengeValue(StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "gamemode")) {
			for (int a = 0; a < GAMEMODE_COUNT; a++) {
				SetGamemodeChallengeValue(LiveStats_GetGameTypeName(a), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "attachment")) {
			for (int a = 0; a < ATTACHMENT_COUNT; a++) {
				SetAttachmentStat((char*)(*(uint32_t*)(0x00E5DE8C + (a * 4))), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "killstreak")) {
			for (int a = 0; a < 17; a++) {
				SetSpecialStat(LookupItemIndex(killstreaks[a]), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
	}
	StringTable_GetCoreAsset(CORE_TABLE_MILESTONE_4, &table);
	for (int i = 0; i < table->rowCount; i++) {
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "global")) {
			SetChallengeValue(StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "gamemode")) {
			for (int a = 0; a < GAMEMODE_COUNT; a++) {
				SetGamemodeChallengeValue(LiveStats_GetGameTypeName(a), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "attachment")) {
			for (int a = 0; a < ATTACHMENT_COUNT; a++) {
				SetAttachmentStat((char*)(*(uint32_t*)(0x00E5DE8C + (a * 4))), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 3), "killstreak")) {
			for (int a = 0; a < 17; a++) {
				SetSpecialStat(LookupItemIndex(killstreaks[a]), StringTable_GetColumnValueForRow(table, i, 4), atoi(StringTable_GetColumnValueForRow(table, i, 2)));
			}
		}
	}

	StringTable_GetCoreAsset(CORE_TABLE_GUNLEVELS, &table);
	for (int i = 0; i < table->rowCount;i++) {
		SetItemStat(LookupItemIndex(StringTable_GetColumnValueForRow(table, i, 2)), "xp", atoi(StringTable_GetColumnValueForRow(table, i, 1)));
		//SetItemStat(LookupItemIndex(StringTable_GetColumnValueForRow(table, i, 2)), "plevel", 2);
	}

	ddlValue_t tttt;
#define HERO_MAX_KILL 100
	SetSpecialStat(LookupItemIndex("hero_minigun"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_lightninggun"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_gravityspikes"), "kills", HERO_MAX_KILL);

	SetSpecialStat(LookupItemIndex("hero_armblade"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_annihilator"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_pineapplegun"), "kills", HERO_MAX_KILL);

	SetSpecialStat(LookupItemIndex("hero_bowlauncher"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_chemicalgelgun"), "kills", HERO_MAX_KILL);
	SetSpecialStat(LookupItemIndex("hero_flamethrower"), "kills", HERO_MAX_KILL);

#define LETHAL_MAX_KILLS 300
	SetSpecialStat(LookupItemIndex("frag_grenade"), "kills", LETHAL_MAX_KILLS);
	SetSpecialStat(LookupItemIndex("sticky_grenade"), "kills", LETHAL_MAX_KILLS);
	SetSpecialStat(LookupItemIndex("hatchet"), "kills", LETHAL_MAX_KILLS);

	SetSpecialStat(LookupItemIndex("satchel_charge"), "kills", LETHAL_MAX_KILLS);
	SetSpecialStat(LookupItemIndex("incendiary_grenade"), "kills", LETHAL_MAX_KILLS);
	SetSpecialStat(LookupItemIndex("bouncingbetty"), "kills", LETHAL_MAX_KILLS);

	StatSetValue("RANK", 54);
	StatSetValue("RANKXP", 0x00163C30);
	StatSetValue("PLEVEL", 11);
	StatSetValue("SCORE", 2500000);

	//Cbuf_AddText(0, "PrestigeAddCAC 1;");
	//Cbuf_AddText(0, "uploadstats;");
}

void PrintDiscord() {
	SV_GameSendServerCommand(-1, 0, "; \"discord.gg/mqW5Ys4\"");
	SV_GameSendServerCommand(-1, 0, "< \"discord.gg/mqW5Ys4\"");
}

void PrintJoin() {
	SV_GameSendServerCommand(-1, 0, "; \"Join ^6discord.gg/mqW5Ys4^7 to get a $5 Rank 55, Master Prestige Any Color Name, or $8 Unlock All with Dark Matter!\"");
	SV_GameSendServerCommand(-1, 0, "< \"Join ^6discord.gg/mqW5Ys4^7 to get a $5 Rank 55, Master Prestige Any Color Name, or $8 Unlock All with Dark Matter!\"");
}
