#include "Quarantine.hpp"

SYS_MODULE_INFO( BO3_MP, 0, 1, 1);
SYS_MODULE_START( _BO3_MP_prx_entry );
SYS_MODULE_STOP( _BO3_MP_prx_exit );

sys_ppu_thread_t start_thread;
#pragma region .. Offhost ..
bool bRan = false;
void R_EndFrame_Detour() {
	uiInfoArray = (UiContext*)(0x026C0F90);
	clientUIActives = (clientUIActive_t*)(0x01198154);
	cg_entitiesArray = *(centity_t**)(0x00F57BFC);
	cgArray = *(cg_s**)(0x00F57BF4);
	stats_list = *(uint32_t*)(0x026B1FDC);

	//if (!bRan) {
	//	g_pRawFiles = (RawFileAsset*)(0x014B793C);
	//	int g_pRawFileCount = 0;
	//	while (g_pRawFileCount != 0x266) {
	//		PrintRawfile(&g_pRawFiles[g_pRawFileCount]);
	//		++g_pRawFileCount;
	//	}
	//	bRan = true;
	//}
	vars->MenuX = (uiInfoArray->screenWidth / 2) - 120;
	menu->RenderMenu();
	menu->RunControls();
}

int rainbow_color;
int line_count;
void R_SetDepthOfField_Detour(uint32_t viewInfo, uint32_t sceneParams) {
	if (isInGame()) {
		if (vars->bBulletTracers) {
			R_AddCmdDrawTextInternal(va("Lines: %i", line_count), 0x7FFFFFFF, CL_GetNormalFont(), 25, 25, 0.75f, 0.75f, 0, colorWhite, 0);
			line_count = 0;
			float out_pos[2][2];
			for (int i = 0; i < 300; i++) {
				if (bullet_tracers[i].time_to_draw >= 1) {

					if (WorldPosToScreenPos(0, bullet_tracers[i].start_pos, out_pos[0]) && WorldPosToScreenPos(0, bullet_tracers[i].stop_pos, out_pos[1])) {
						CL_DrawLine(out_pos[0][0], out_pos[0][1], out_pos[1][0], out_pos[1][1], CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[bullet_tracers[i].ownerClient]) ? colorGreenFaded : colorRedFaded, 1);
					}
					--bullet_tracers[i].time_to_draw;
					++line_count;
				}
			}
		}

		cg_entitiesArray = *(centity_t**)(0x00F57BFC);
		cgArray = *(cg_s**)(0x00F57BF4);
		float outPos[2];

		/*for (int i = 0; i < 1024; i++) {
			if (WorldPosToScreenPos(0, cg_entitiesArray[i].origin, outPos)) {
				if (cg_entitiesArray[i].eType == (int)vars->iEntityType) {
					CL_DrawLine(uiInfoArray->screenWidth / 2, uiInfoArray->screenHeight - 10, outPos[0], outPos[1], colorRedFaded, 1);
				}
			}
		}*/

		for (int i = 0; i < 12;i++) {
			if (WorldPosToScreenPos(0, cg_entitiesArray[i].origin, outPos)) {
				if (i != cgArray->clientNum) {
					if (cg_entitiesArray[i].eType == 1) {
						if (cg_entitiesArray[i].isAlive1 != 0) {
							if (vars->bLineESP) {
								if (vars->bFriendlyESP) {
									if (CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawLine(uiInfoArray->screenWidth / 2, uiInfoArray->screenHeight - 10, outPos[0], outPos[1], colorGreenFaded, 1);
									}
								}
								if (vars->bEnemyESP) {
									if (!CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawLine(uiInfoArray->screenWidth / 2, uiInfoArray->screenHeight - 10, outPos[0], outPos[1], colorRedFaded, 1);
									}
								}
							}
							if (vars->bBoneESP) {
								if (vars->bFriendlyESP) {
									if (CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawBones(i, colorGreenFaded);
									}
								}
								if (vars->bEnemyESP) {
									if (!CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawBones(i, colorRedFaded);
									}
								}
							}
							if (vars->bBoxESP) {
								if (vars->bFriendlyESP) {
									if (CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawBox(i, colorGreenFaded);
									}
								}
								if (vars->bEnemyESP) {
									if (!CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
										CL_DrawBox(i, colorRedFaded);
									}
								}
							}
						}
					}
				}
			}
		}
		if (vars->bAimbot) {
			float enemy[3];
			float coutn[3];
			float finalangles[3];

			if (menu->KeyPressed[BUTTON_LSHLDR]) {
				int closestPerson = nearestPlayer();
				if (closestPerson != -1) {
					//*(uint32_t*)(0x001CA408) = 0x60000000;
					//*(uint32_t*)(0x001CA410) = 0x60000000;
					AimTarget_GetTagPos(&cg_entitiesArray[closestPerson], SL_GetString("j_head", 0, 5), enemy);
					VectorSubtract(enemy, cgArray->refdef.viewOrigin, coutn);
					vectoangles(coutn, finalangles);
					VectorSubtract(finalangles, cgArray->delta_angles, finalangles);
					*(float*)(*(int*)(0x00E24C10) + 0x31A0) = finalangles[0];
					*(float*)(*(int*)(0x00E24C10) + 0x31A4) = finalangles[1];
				}
			}

		}
	}
	else {
		//if (rainbowname_ticker >= 80) {
		//	memcpy((void*)0x37EF8FD9, va("^%i", rainbow_color), 2);
		//	++rainbow_color;
		//	if (rainbow_color == 9) {
		//		rainbow_color = 0;
		//	}
		//	rainbowname_ticker = 0;
		//}
		//++rainbowname_ticker;
	}
}

void CL_WritePacket_Detour(uint32_t r3) {

	//int currentCmd = *(int*)(*(int*)(0x00E24C10) + 0x251BC);
	//usercmd_s *oldCmd = CL_GetUserCmd(currentCmd - 1);
	//usercmd_s *curCmd = CL_GetUserCmd(currentCmd);
	//usercmd_s *newCmd = CL_GetUserCmd(currentCmd + 1);
	//printf("aimbot called\n");

	

	//*(float*)(*(int*)(0x00E24C10) + 0x31A0) = finalangles[0];
	//*(float*)(*(int*)(0x00E24C10) + 0x31A4) = finalangles[1];

	CL_WritePacket(r3);
}

void CL_GamepadButtonEventForPort_Detour(int portIndex, int key, int buttonEvent, uint32_t time, int button) {

	if (buttonEvent) {
		menu->KeyPressed[key] = true;
		//printf("%i\n", key);
	}
	else {
		menu->KeyPressed[key] = false;
	}

	if (menu->MenuOpened()) {
		if (key == BUTTON_A || key == BUTTON_B || key == DPAD_UP || key == DPAD_DOWN || key == DPAD_LEFT || key == DPAD_RIGHT || key == BUTTON_LSHLDR || key == BUTTON_RSHLDR) {
			buttonEvent = 0;
		}
	}

	CL_GamepadButtonEventForPort(portIndex, key, buttonEvent, time, button);
}

void CG_PredictPlayerState_Detour(int localClientNum) {
	clientUIActives = (clientUIActive_t*)(0x01198154);
	if (isInGame()) {

		memset((void*)(*(uint32_t*)(0x00F57BF4) + 0x54FDC), 0, 20);

		int currentCmd = *(int*)(*(int*)(0x00E24C10) + 0x251BC);
		usercmd_s *oldCmd = CL_GetUserCmd(currentCmd - 1);
		usercmd_s *curCmd = CL_GetUserCmd(currentCmd);
		usercmd_s *newCmd = CL_GetUserCmd(currentCmd + 1);

		if (vars->bAirstuck && !menu->isMenuOpen && clientUIActives->connectionState == 11 && clientUIActives->keyCatchers == 0) {
			if (menu->KeyPressed[DPAD_DOWN]) {
				vars->bAirstuckToggle = !vars->bAirstuckToggle;
				CG_GameMessage(0, vars->bAirstuckToggle ? "Airstuck: ^2ON" : "Airstuck: ^1OFF");
				menu->KeyPressed[DPAD_DOWN] = false;
			}
		}

		if (!vars->bAirstuck) {
			vars->bAirstuckToggle = false;
		}

		if (vars->bAirstuckToggle) {
			*oldCmd = *curCmd = *newCmd;
			oldCmd->serverTime -= 2;
			curCmd->serverTime -= 1;
		}

	}
	else {
		vars->bAirstuckToggle = false;
	}

	CG_PredictPlayerState(localClientNum);
}

char * MSG_ReadString_Stub(uint32_t r3, char * string, uint32_t maxChars) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}

char * MSG_ReadString_Hook(uint32_t r3, char * string, uint32_t maxChars) {
	char * mods = MSG_ReadString_Stub(r3, string, maxChars);

	if (strcmp(string, "P2PConnectivityTest")) {
		printf("%s - 0x%X\n", string, __builtin_return_address());
	}

	return mods;
}


void MGS_WriteString_Stub(uint32_t r3, const char * s) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}

void MGS_WriteString_Hook(uint32_t r3, const char * s) {

	if (strcmp(s, "P2PConnectivityTest")) {
		printf("%s - 0x%X\n", s, __builtin_return_address());
	}
	MGS_WriteString_Stub(r3, s);
}

bool CL_GetSnapshot_Detour(int localClientNum, int r4, int snapshot) {

	return CL_GetSnapshot(localClientNum, r4, snapshot);
}

void CG_BulletHitEvent_Stub(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, const float *startPos, const float *position, const float *normal, const float *seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}

/*
//bullet_tracers[bullet_tracer_count].start_pos[0] = startPos[0];
//bullet_tracers[bullet_tracer_count].start_pos[1] = startPos[1];
//bullet_tracers[bullet_tracer_count].start_pos[2] = startPos[2];

//bullet_tracers[bullet_tracer_count].stop_pos[0] = position[0];
//bullet_tracers[bullet_tracer_count].stop_pos[1] = position[1];
//bullet_tracers[bullet_tracer_count].stop_pos[2] = position[2];
*/

void CG_BulletHitEvent_Hook(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, const float *startPos, const float *position, const float *normal, const float *seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex) {

	if (vars->bBulletTracers) {
		bullet_tracers[bullet_tracer_count].ownerClient = sourceEntityNum;
		memcpy((void*)(bullet_tracers[bullet_tracer_count].start_pos), startPos, 0xC);
		memcpy((void*)(bullet_tracers[bullet_tracer_count].stop_pos), position, 0xC);
		
		bullet_tracers[bullet_tracer_count].time_to_draw = 200;
		++bullet_tracer_count;

		if (bullet_tracer_count == 299) {
			bullet_tracer_count = 0;
		}
	}

	CG_BulletHitEvent_Stub(localClientNum, sourceEntityNum, targetEntityNum, weapon, startPos, position, normal, seeThruDecalNormal, surfType, event, eventParam, hitContents, boneIndex);
}

/*struct challengeTableRow_t {
	const char * challengeStatName;
	uint32_t statNameHash;
	int __padding000;
	int maxVal;
	uint16_t unk0;
	uint16_t unk1;
}; //0x54 - size

challengeTableRow_t * CL_GetChallengeRowByIndex_Stub(uint32_t r3, uint32_t r4) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
challengeTableRow_t * CL_GetChallengeRowByIndex_Hook(uint32_t r3, uint32_t r4) {
	challengeTableRow_t * ret = CL_GetChallengeRowByIndex_Stub(r3, r4);

	
	return ret;
}*/

int DDL_SetString_Stub(ddlState_t* search_state, const char * buffer, const char * value) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
int DDL_SetString_Hook(ddlState_t* search_state, const char * buffer, const char * value) {
	int ret = DDL_SetString_Stub(search_state, buffer, value);

	printf("0x%X - 0x%X - %s\n", search_state, buffer, value);

	return ret;
}
#pragma endregion

void PrintRawfile(RawFileAsset * pRawfile) {
	//printf("0x%X | %s | %i\n", pRawfile, pRawfile->name, pRawfile->file_size);
	int fd;
	if (cellFsOpen(va("%s%s", DUMP_PATH, pRawfile->name), CELL_FS_O_CREAT | CELL_FS_O_RDWR, &fd, 0, 0) == 0) {
		if (cellFsWrite(fd, pRawfile->buffer, pRawfile->file_size, 0) == 0) {
			printf("dumped %s with success\n", pRawfile->name);
			cellFsClose(fd);
		}
	}
}

void LUI_SetTableString_Stub(const char * table_value, const char * value, int lua_state) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}

void LUI_SetTableString_Hook(const char * table_value, const char * value, int lua_state) {
	
	
	if (!strstr(value, "process_events") &&
		!strstr(value, "transition_complete_default") &&
		!strstr(value, "transition_complete_hide_primary_status") &&
		!strstr(value, "gamepad_button") &&
		!strstr(value, "streamed_image_ready") &&
		!strstr(value, "transition_ccomplete_hide_secondary_statuss") &&
		!strstr(table_value, "button") &&

		!strstr(value, "transition_complete_keyframe")) {
		printf("%s - %s - 0x%X\n", table_value, value, __builtin_return_address());
	}

	if (!strcmp(table_value, "gamertag")) {
		printf("changing '%s' to 'testing'\n", value);
		value = "testing";
	}


	LUI_SetTableString_Stub(table_value, value, lua_state);
}

extern "C" int _BO3_MP_prx_entry(void) {

	uiInfoArray = (UiContext*)(0x026C0F90);
	menu = new Menu();
	vars = new Variables();
	addresses = new Addresses();
	bullet_tracers = (BulletTracers*)malloc(sizeof(BulletTracers) * 300);
	SetupHookHandler();


	MakeCall(0x001EA5FC); //R_EndFrame
	MakeCall(0x0041E768); //DOF hook
	MakeCall(0x005998AC); //CL_GamepadButtonEventForPort pressed
	MakeCall(0x00599934); //CL_GamepadButtonEventForPort released
	MakeCall(0x001C86B4); //CL_WritePacket
	MakeCall(0x00173FB8); //CG_PredictPlayerState
	MakeCall(0x00158CCC); //CL_GetSnapshot
	///MakeCall(0x002B0690); //ClientThink_real
	
	//Cbuf_AddText(0, "set lobbyTimerStatusVotingInterval 0; set lobbyTimerStartInterval 0;set lobbyTimerStatusStartInterval 0;set lobbyTimerStatusBeginInterval 0;set lobbySearchSkip 1;set party_minplayers 1;");

	HookFunctionStart(0x00181860, *(uint32_t*)(CG_BulletHitEvent_Hook), *(uint32_t*)(CG_BulletHitEvent_Stub));
	///HookFunctionStart(0x005247AC, *(uint32_t*)(LUI_SetTableString_Hook), *(uint32_t*)(LUI_SetTableString_Stub));
	///HookFunctionStart(0x006B40C0, *(uint32_t*)(DDL_SetString_Hook), *(uint32_t*)(DDL_SetString_Stub));
	///HookFunctionStart(0x001E21D8, *(uint32_t*)(CL_GetChallengeRowByIndex_Hook), *(uint32_t*)(CL_GetChallengeRowByIndex_Stub));
	///HookFunctionStart(0x005C9364, *(uint32_t*)(MSG_ReadString_Hook), *(uint32_t*)(MSG_ReadString_Stub));
	///HookFunctionStart(0x005C8F10, *(uint32_t*)(MGS_WriteString_Hook), *(uint32_t*)(MGS_WriteString_Stub));

	return SYS_PRX_RESIDENT;
}

extern "C" int _BO3_MP_prx_exit(void) {
	*(uint32_t*)(0x001EA5FC) = 0x48228D19;
	*(uint32_t*)(0x0041E768) = 0x4BFFCE01;
	*(uint32_t*)(0x005998AC) = 0x4BC3BD2D;
	*(uint32_t*)(0x00599934) = 0x4BC3BCA5;
	*(uint32_t*)(0x001C86B4) = 0x4800D509;
	*(uint32_t*)(0x00173FB8) = 0x4BFAAAF1;
	*(uint32_t*)(0x00158CCC) = 0x4807506D;
	*(uint32_t*)(0x002B0690) = 0x4803E011;
	
	UnHookFunctionStart(0x00181860, *(uint32_t*)(CG_BulletHitEvent_Stub));
	///UnHookFunctionStart(0x005247AC, *(uint32_t*)(LUI_SetTableString_Stub));
	///UnHookFunctionStart(0x006B40C0, *(uint32_t*)(DDL_SetString_Stub));
	///UnHookFunctionStart(0x001E21D8, *(uint32_t*)(CL_GetChallengeRowByIndex_Stub));

	///UnHookFunctionStart(0x005C9364, *(uint32_t*)(MSG_ReadString_Stub));
	///UnHookFunctionStart(0x005C8F10, *(uint32_t*)(MGS_WriteString_Stub));

	delete menu;
	delete vars;
	delete addresses;
	memset((void*)(bullet_tracers), 0, sizeof(BulletTracers) * 300);
	free(bullet_tracers);

	return SYS_PRX_RESIDENT;
}

void * operator new(size_t r3) {
	return malloc(r3);
}

void * operator new[](size_t r3) {
	return malloc(r3);
}

void operator delete(void * r3) {
	free(r3);
}

void operator delete[](void * r3) {
	free(r3);
}


void write_memory(uint64_t address, void* data, size_t size) {
	sys_dbg_write_process_memory_ps3mapi(address, data, size);
	sys_dbg_write_process_memory(address, data, size);
}
int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}

void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub) {
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(functionStartAddress, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	write_memory(functionStub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	write_memory(functionStartAddress, hookFunctionStub, 0x10);
}

void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
}

uint32_t ReverseInt(uint32_t address) {
	uint32_t val = address;
	uint32_t p1, p2, p3, p4;
	p1 = (val >> 24) & 0xFF;
	p2 = (val >> 16) & 0xFF;
	p3 = (val >> 8) & 0xFF;
	p4 = (val >> 0) & 0xFF;

	p1 <<= 0; // 24;
	p2 <<= 8; // 16;
	p3 <<= 16; //;
	p4 <<= 24; //;
	return p1 + p2 + p3 + p4;
}
