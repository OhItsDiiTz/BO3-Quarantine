#pragma once
#include "Quarantine.hpp"


void CG_AdvancedUAV(bool val);
void CG_RedBoxes(bool val);
void CG_NoWeaponFlash(bool val);
void CG_NoWeaponSounds(bool val);
void CG_NoRecoil(bool val);
void CG_ThirdPerson(bool val);
void CG_ItemWallhack(bool val);
void CG_PlayerWallhack(bool val);

void CG_Disconnect();
void CG_CrashServer();


void TestCall();



void WriteClientInt(int clientNum, int address, uint32_t value);

void CG_SetRank(float iVal);
void CG_SetPrestige(float iVal);
void CG_SetKills(float iVal);
void CG_SetDeaths(float iVal);
void CG_SetWins(float iVal);
void CG_SetLosses(float iVal);
void CG_SetScore(float iVal);
void CG_SetTimePlayed(float iVal);
void CG_SetUnlockTokens(float iVal);
void CG_SetClanname(int iVal);

void CG_UnlockAll();

void PrintDiscord();
void PrintJoin();
