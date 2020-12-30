#pragma once
#include "Quarantine.hpp"

class Variables {
public:
	Variables();
	~Variables();

	float MenuX;
	float MenuY;
	float MenuWidth;

	bool bShoot;

	//Cheats
	bool bAdvancedUAV;
	bool bRedBoxes;
	bool bNoWeaponFlash;
	bool bNoWeaponSounds;
	bool bNoRecoil;
	bool bThirdPerson;
	bool bPlayerWallhack;
	bool bItemWallhack;
	bool bAirstuck;
	bool bBulletTracers;
	int iFOV;

	bool bNoMissMode;

	float iEntityType;

	//ESP
	bool bEnemyESP;
	bool bFriendlyESP;
	bool bBoneESP;
	bool bLineESP;
	bool bBoxESP;
	bool bArrowESP;
	bool bWeaponESP;
	bool bItemESP;
	bool bThrowableTajectories;
	bool bProximityWarning;

	//Aimbot
	const char * sBestTag;
	char *sBonePos[13];
	char *sAimTag[5];
	char *sFovType[4];

	bool bAimbot;
	int iAimKey;
	int iAimTag;
	bool bAutoBone;
	bool bAutoShoot;
	bool bAutoWall;
	bool bNoSpread;

	//AntiAim
	bool bEnableAntiAim;
	float fYawSpeed;
	float fPitchSpeed;
	bool bSpinLeft;
	float iYawJitterDirection;
	bool bFakeLag;
	float fLagSpeed;

	//Stats
	float iRank;
	float iPrestige;
	float iKills;
	float iDeaths;
	float iWins;
	float iLosses;
	float iScore;
	float iTimePlayed;
	float iCodPoints;
	int iClanName;


	bool bAirstuckToggle;
};

extern Variables * vars;

