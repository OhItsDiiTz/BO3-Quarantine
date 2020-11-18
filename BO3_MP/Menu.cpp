#include "Menu.hpp"
uint32_t stats_list;
Menu::Menu() {
	isMenuOpen = false;
	CurrentMenu = 0;
	CurrentOption = 0;
}

Menu::~Menu() {
	memset(this, 0, sizeof(Menu));
}

bool Menu::MenuOpened() {
	return isMenuOpen;
}

void Menu::ResetMaxScroll() {
	MaxScroll = 0;
}

int Menu::GetMaxScroll() {
	return MaxScroll;
}

void SelectMenu(int menuID) {
	menu->LastOption[menu->CurrentMenu] = menu->CurrentOption;
	menu->CurrentMenu = menuID;
	menu->CurrentOption = menu->LastOption[menuID];
}

void nullsub() {}

void test() {

}



void Menu::RenderMenu() {
	if (MenuOpened()) {
		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY - 45, vars->MenuWidth, 30.5 + (MaxScroll * 17), 0, 0, 1, 1, colorBlackFaded, Material_RegisterHandle("white", 0, 0, -1));

		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY - 45, vars->MenuWidth, 1, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY - 15 + (MaxScroll * 17), vars->MenuWidth, 1, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));

		ResetMaxScroll();

		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY + (CurrentOption * 17) - 19, vars->MenuWidth, 17, 0, 0, 1, 1, colorGreyFaded, Material_RegisterHandle("white", 0, 0, -1));
		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY + (CurrentOption * 17) - 19, vars->MenuWidth, 1, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		R_AddCmdDrawStretchPicInternal(vars->MenuX - 15, vars->MenuY + (CurrentOption * 17) - 2, vars->MenuWidth, 1, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		
		//R_AddCmdDrawStretchPicInternal(vars->MenuX - 60, vars->MenuY, 50, 50, 0, 0, 1, 1, colorWhite, Material_RegisterHandle("ps3button_x", 0, 0, -1));

		switch (CurrentMenu) {
		case MenuBase:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Quarantine CE (b0.1)");
			AddOption("Cheats", SelectMenu, Cheats);
			AddOption("ESP", SelectMenu, ESP);
			//AddOption("Aimbot", SelectMenu, Aimbot);
			//AddOption("Anti-Aim", SelectMenu, AntiAim);
			//AddOption("Names", SelectMenu, Names);
			AddOption("Stats", SelectMenu, Stats);
			///AddOption("Menu Settings", SelectMenu, MenuSettings);
			//AddOption("Discord", PrintDiscord);
			//AddOption("Join Discord", PrintJoin);
			//AddBool("No Miss Mode", &vars->bNoMissMode);
			//AddOption("Force Host", TestCall);
			//AddSlider("eType Switcher", &vars->iEntityType, 0, 50, 1, true);
			//AddSlider("Set FOV", &vars->fTest1, 40, 160, 1, false, CG_SetFOV);
			break;
		case Cheats:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Cheats");
			AddBool("Unlimited V-Sat", &vars->bAdvancedUAV, CG_AdvancedUAV);
			AddBool("Red Boxes", &vars->bRedBoxes, CG_RedBoxes);
			AddBool("No Weapon Flash", &vars->bNoWeaponFlash, CG_NoWeaponFlash);
			//AddBool("No Weapon Sounds", &vars->bNoWeaponSounds, CG_NoWeaponSounds);
			AddBool("No Recoil", &vars->bNoRecoil, CG_NoRecoil);
			AddBool("Third Person", &vars->bThirdPerson, CG_ThirdPerson);
			//AddBool("Player Wallhack", &vars->bPlayerWallhack, CG_PlayerWallhack);
			//AddBool("Item Wallhack", &vars->bItemWallhack, CG_ItemWallhack);
			AddBool("Air Stuck", &vars->bAirstuck);
			AddBool("Bullet Tracers", &vars->bBulletTracers);
			//AddSlider("FOV", &vars->fFOV, 40, 160, 1, false);
			AddBool("Enable Aimbot", &vars->bAimbot);
			AddOption("Disconnect", CG_Disconnect);
			//AddOption("End Game", nullsub);
			AddOption("Crash Server", CG_CrashServer);
			break;

		case ESP:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("ESP");
			AddBool("Enemy ESP", &vars->bEnemyESP);
			AddBool("Friendly ESP", &vars->bFriendlyESP);
			AddBool("Bone ESP", &vars->bBoneESP);
			AddBool("Line ESP", &vars->bLineESP);
			AddBool("Box ESP", &vars->bBoxESP);
			//AddBool("Arrow ESP", &vars->bArrowESP);
			//AddBool("Weapon ESP", &vars->bWeaponESP);
			//AddBool("Item ESP", &vars->bItemESP);
			//AddBool("Throwable Trajectories", &vars->bThrowableTajectories);
			//AddBool("Proximity Warning", &vars->bProximityWarning);

			break;

		case Aimbot:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Aimbot");
			//AddSlider("Aimbot Key", &vars->iAimKey, 0, 5, 1, true);
			AddStringSlider("Aim Tag", &vars->iAimTag, 0, 2, vars->sAimTag);
			AddBool("Auto Shoot", &vars->bAutoShoot);
			AddBool("Auto Wall", &vars->bAutoWall);
			AddBool("No Spread", &vars->bNoSpread);
			break;
		case AntiAim:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Anti-Aim");
			AddBool("Enable Anti-Aim", &vars->bEnableAntiAim);
			AddSlider("Yaw Speed", &vars->fYawSpeed, 0, 60, 1, true);
			AddSlider("Pitch Speed", &vars->fPitchSpeed, 0, 60, 1, true);
			AddBool("Yaw Direction", &vars->bSpinLeft);
			AddSlider("Pitch Jitter Direction", &vars->iYawJitterDirection, 0, 4, 1, true);
			AddBool("Fake Lag", &vars->bFakeLag);
			AddSlider("Fake Lag Speed", &vars->fLagSpeed, 0, 300, 1, true);
			break;
		case Names:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Names");
			AddOption("Custom Name", nullsub);
			break;
		case Stats:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Stats");
			AddSlider("Rank", &vars->iRank, 0, 55, 1, false, CG_SetRank);
			AddSlider("Prestige", &vars->iPrestige, 0, 11, 1, false, CG_SetPrestige);
			AddSlider("Kills", &vars->iKills, 0, 0x7FFFFFFE, 1, false, CG_SetKills);
			AddSlider("Deaths", &vars->iDeaths, 0, 0x7FFFFFFE, 1, false, CG_SetDeaths);
			AddSlider("Wins", &vars->iWins, 0, 0x7FFFFFFE, 1, false, CG_SetWins);
			AddSlider("Losses", &vars->iLosses, 0, 0x7FFFFFFE, 1, false, CG_SetLosses);
			AddSlider("Score", &vars->iScore, 0, 0x7FFFFFFE, 1, false, CG_SetScore);
			AddSlider("Time Played", &vars->iTimePlayed, 0, 0x7FFFFFFE, 1, false, CG_SetTimePlayed);
			AddSlider("Unlock Tokens", &vars->iCodPoints, 0, 255, 1, false, CG_SetUnlockTokens);
			AddOption("Unlock All", CG_UnlockAll);
			AddStringSlider("Clan Name", &vars->iClanName, 0, 9, clanname_array, CG_SetClanname);
			///AddOption("Unlock All", nullsub);
			///AddOption("Low Weapon Stats", nullsub);
			///AddOption("Medium Weapon Stats", nullsub);
			///AddOption("High Weapon Stats", nullsub);
			break;
		case MenuSettings:
			menu->LastMenu[menu->CurrentMenu] = MenuBase;
			AddTitle("Menu Settings/Configs");
			AddOption("Save Config", nullsub);
			AddOption("Load Config", nullsub);
			AddOption("Advanced Configurations", nullsub);
			break;
		}

		//R_AddCmdDrawStretchPic(200, 200, 200, 200, 0, 0, 1, 1, colorWhite, Material_RegisterHandle("white", 0));
		//R_AddCmdDrawText("Crack Den SPRX", 0x7FFFFFFF, CL_RegisterFont("fonts/normalFont", 0), 20, 25, 0.65f, 0.65f, 0.0f, colorWhite, 0);
	}
}

void Menu::RunControls() {
	if (!MenuOpened()) {
		if (KeyPressed[BUTTON_LSHLDR] && KeyPressed[DPAD_LEFT]) {
			isMenuOpen = true;
		}
	}
	else {
		if (KeyPressed[BUTTON_B]) {
			if (menu->CurrentMenu == MenuBase) {
				isMenuOpen = false;
			}
			else {
				SelectMenu(menu->LastMenu[menu->CurrentMenu]);

			}
			KeyPressed[BUTTON_B] = false;
		}
		if (KeyPressed[DPAD_UP]) {
			CurrentOption -= 1;
			if (CurrentOption < 0) {
				CurrentOption = GetMaxScroll() - 1;
			}
			KeyPressed[DPAD_UP] = false;
		}
		if (KeyPressed[DPAD_DOWN]) {
			CurrentOption += 1;
			if (CurrentOption > GetMaxScroll() - 1) {
				CurrentOption = 0;
			}
			KeyPressed[DPAD_DOWN] = false;
		}
	}
}

void Menu::AddTitle(const char * title) {
	uint32_t font = CL_GetNormalFont();
	float textWidth = R_TextWidth(title, strlen(title) + 1, font) * 0.75f;
	R_AddCmdDrawTextInternal(title, 0x7FFFFFFF, font, vars->MenuX - 15 + ((vars->MenuWidth / 2) - (textWidth / 2)), vars->MenuY - 17, 0.75f, 0.75f, 0.0f, colorWhite, 0);
}

void Menu::AddOption(const char * opt, void(*func)()) {
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, CL_GetNormalFont(), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			func();
			KeyPressed[BUTTON_A] = false;
		}
	}
	MaxScroll += 1;
}

void Menu::AddOption(const char * opt, void(*func)(int value), int value) {
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, CL_GetNormalFont(), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			func(value);
			KeyPressed[BUTTON_A] = false;
		}
	}
	MaxScroll += 1;
}

void Menu::AddBool(const char * opt, bool * value) {
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, CL_GetNormalFont(), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 35, vars->MenuY + (MaxScroll * 17) - 18, 15, 15, 0, 0, 1, 1, colorWhite, Material_RegisterHandle(*value ? "ps3button_x" : "ps3button_circle", 0, 0, -1));

	//R_AddCmdDrawText(opt, 0x7FFFFFFF, CL_RegisterFont("fonts/normalFont", 0), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			*value = !*value;
			KeyPressed[BUTTON_A] = false;
		}
	}

	MaxScroll += 1;
}

void Menu::AddBool(const char * opt, bool * value, void(*func)(bool value)) {
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, CL_GetNormalFont(), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 35, vars->MenuY + (MaxScroll * 17) - 18, 15, 15, 0, 0, 1, 1, colorWhite, Material_RegisterHandle(*value ? "ps3button_x" : "ps3button_circle", 0, 0, -1));

	//R_AddCmdDrawText(opt, 0x7FFFFFFF, CL_RegisterFont("fonts/normalFont", 0), vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			*value = !*value;
			func(*value);
			KeyPressed[BUTTON_A] = false;
		}
	}

	MaxScroll += 1;
}



void Menu::AddSlider(const char * opt, float * value, float min, float max, float scale, bool useShader) {
	uint32_t font = CL_GetNormalFont();
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, font, vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);
	float textWidth = R_TextWidth(va("%.2f", *value), strlen(va("%.2f", *value)) + 1, font) * (useShader ? 0.35f : 0.45f);

	if(useShader) {
		R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, 70, 14, 0, 0, 1, 1, colorWhite, Material_RegisterHandle("white", 0, 0, -1));
		if (min == 0.0f) {
			R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, (70 / (max - min)) * *value, 14, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		}
		else {
			R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, ((70 / (max - min)) * (*value - min)), 14, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		}
	}
	R_AddCmdDrawTextInternal(va("%.0f", *value), 0x7FFFFFFF, font, vars->MenuX + (vars->MenuWidth - (useShader ? 48 : 5)) - (useShader ? (textWidth / 2) : (textWidth)), vars->MenuY + (17 * MaxScroll) - (useShader ? 4 : 2), useShader ? 0.35f : 0.45f, useShader ? 0.35f : 0.45f, 0.0f, useShader ? colorBlack : colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (min == 0.0f) {
			if (KeyPressed[DPAD_LEFT]) {
				if (*value > (min - min)) {
					*value -= KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_LEFT] = false;
				}
			}
			if (KeyPressed[DPAD_RIGHT]) {
				if (*value < (max - min)) {
					*value += KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_RIGHT] = false;
				}
			}
		}
		else {
			if (KeyPressed[DPAD_LEFT]) {
				if (*value > (min)) {
					*value -= KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_LEFT] = false;
				}
			}
			if (KeyPressed[DPAD_RIGHT]) {
				if (*value < (max)) {
					*value += KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_RIGHT] = false;
				}
			}
		}
	}

	MaxScroll += 1;
}

void Menu::AddSlider(const char * opt, float * value, float min, float max, float scale, bool useShader, void(*func)(float val)) {
	uint32_t font = CL_GetNormalFont();
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, font, vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);
	float textWidth = R_TextWidth(va("%.2f", *value), strlen(va("%.2f", *value)) + 1, font) * (useShader ? 0.35f : 0.45f);
	if (useShader) {
		R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, 70, 14, 0, 0, 1, 1, colorWhite, Material_RegisterHandle("white", 0, 0, -1));
		if (min == 0.0f) {
			R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, (70 / (max - min)) * *value, 14, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		}
		else {
			R_AddCmdDrawStretchPicInternal(vars->MenuX + (vars->MenuWidth) - 90, vars->MenuY + (MaxScroll * 17) - 17, ((70 / (max - min)) * (*value - min)), 14, 0, 0, 1, 1, colorRedFaded, Material_RegisterHandle("white", 0, 0, -1));
		}
	}
	R_AddCmdDrawTextInternal(va("%.0f", *value), 0x7FFFFFFF, font, vars->MenuX + (vars->MenuWidth - (useShader ? 48 : 5)) - (useShader ? (textWidth / 2) : (textWidth)), vars->MenuY + (17 * MaxScroll) - (useShader ? 4 : 2), useShader ? 0.35f : 0.45f, useShader ? 0.35f : 0.45f, 0.0f, useShader ? colorBlack : colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			func(*value);
			KeyPressed[BUTTON_A] = false;
		}
		if (min == 0.0f) {
			if (KeyPressed[DPAD_LEFT]) {
				if (*value > (min - min)) {
					*value -= KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_LEFT] = false;
				}
			}
			if (KeyPressed[DPAD_RIGHT]) {
				if (*value < (max - min)) {
					*value += KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_RIGHT] = false;
				}
			}
		}
		else {
			if (KeyPressed[DPAD_LEFT]) {
				if (*value > (min)) {
					*value -= KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_LEFT] = false;
				}
			}
			if (KeyPressed[DPAD_RIGHT]) {
				if (*value < (max)) {
					*value += KeyPressed[BUTTON_RSHLDR] ? 50 : scale;
				}
				if (KeyPressed[BUTTON_LSHLDR]) {
					KeyPressed[DPAD_RIGHT] = false;
				}
			}
		}
	}

	MaxScroll += 1;
}

void Menu::AddStringSlider(const char * opt, int * value, int min, int max, char ** options) {
	uint32_t font = CL_GetNormalFont();
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, font, vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);
	float textWidth = R_TextWidth(options[*value], strlen(options[*value]) + 1, font) * 0.55f;
	R_AddCmdDrawTextInternal(options[*value], 0x7FFFFFFF, font, vars->MenuX + vars->MenuWidth - 22 - (textWidth), vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[DPAD_LEFT]) {
			if (*value > (min)) {
				*value -= 1;
			}
			KeyPressed[DPAD_LEFT] = false;
		}
		if (KeyPressed[DPAD_RIGHT]) {
			if (*value < (max)) {
				*value += 1;
			}
			KeyPressed[DPAD_RIGHT] = false;
		}
	}
	MaxScroll += 1;
}

void Menu::AddStringSlider(const char * opt, int * value, int min, int max, char ** options, void(*func)(int iVal)) {
	uint32_t font = CL_GetNormalFont();
	R_AddCmdDrawTextInternal(opt, 0x7FFFFFFF, font, vars->MenuX, vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);
	float textWidth = R_TextWidth(options[*value], strlen(options[*value]) + 1, font) * 0.55f;
	R_AddCmdDrawTextInternal(options[*value], 0x7FFFFFFF, font, vars->MenuX + vars->MenuWidth - 22 - (textWidth), vars->MenuY + (17 * MaxScroll), 0.55f, 0.55f, 0.0f, colorWhite, 0);

	if (CurrentOption == MaxScroll) {
		if (KeyPressed[BUTTON_A]) {
			func(*value);
			KeyPressed[BUTTON_A] = false;
		}
		if (KeyPressed[DPAD_LEFT]) {
			if (*value > (min)) {
				*value -= 1;
			}
			KeyPressed[DPAD_LEFT] = false;
		}
		if (KeyPressed[DPAD_RIGHT]) {
			if (*value < (max)) {
				*value += 1;
			}
			KeyPressed[DPAD_RIGHT] = false;
		}
	}
	MaxScroll += 1;
}

Menu * menu;

