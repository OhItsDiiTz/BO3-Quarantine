#include "GameFunctions.hpp"

float colorWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float colorBlack[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
float colorBlackFaded[4] = { 0.0f, 0.0f, 0.0f, 0.75f };
float colorRedFaded[4] = { 1.0f, 0.0f, 0.0f, 0.75f };
float colorGreenFaded[4] = { 0.0f, 1.0f, 0.0f, 0.75f };
float colorGreyFaded[4] = { 0.19607843137f, 0.19607843137f, 0.19607843137f, 0.75f };

template <typename T> T(*GameCall(unsigned int address))(...) {
	int opd[2] = { address, 0x00E11ED8 };
	T(*func)(...) = (T(*)(...))&opd;
	return func;
}

void R_EndFrame() {
	GameCall<void>(0x00413314)();
}

void R_SetDepthOfField(uint32_t viewInfo, uint32_t sceneParams) {
	GameCall<uint32_t>(0x0041B568)(viewInfo, sceneParams);
}

void CL_WritePacket(int localClientNum) {
	GameCall<void>(0x001D5BBC)(localClientNum);
}

void CL_GamepadButtonEventForPort(int portIndex, int key, int buttonEvent, uint32_t time, int button) {
	GameCall<void>(0x001D55D8)(portIndex, key, buttonEvent, time, button);
}

void CG_PredictPlayerState(int localClientNum) {
	GameCall<void>(0x0011EAA8)(localClientNum);
}

bool CL_GetSnapshot(int localClientNum, int r4, int snapshot) {
	return GameCall<bool>(0x001CDD38)(localClientNum, r4, snapshot);
}


int va_t[2] = { 0x0063B138 , 0x00E11ED8 };
char *(*va)(const char * fmt, ...) = (char*(*)(const char *, ...))&va_t;

bool isInGame() {
	if (*(int*)(0x00F5865C) >= 1)
		return true;
	return false;
}

const char * killstreaks[] = {
	"killstreak_rcbomb",
	"killstreak_uav",
	"killstreak_counteruav",
	"killstreak_satellite",
	"killstreak_microwave_turret",
	"killstreak_emp",
	"killstreak_auto_turret",
	"killstreak_ai_tank_drop",
	"killstreak_combat_robot",
	"killstreak_raps",
	"killstreak_helicopter_comlink",
	"killstreak_drone_strike",
	"killstreak_sentinel",
	"killstreak_planemortar",
	"killstreak_remote_missile",
	"killstreak_dart",
	"killstreak_helicopter_player_gunner"
};

uint32_t R_TextWidth(const char *text, int maxChars, uint32_t font) {
	return GameCall<uint32_t>(0x00401688)(0, text, maxChars, font);
}

uint32_t CL_GetNormalFont() {
	return GameCall<uint32_t>(0x00401B48)();
}

uint32_t Material_RegisterHandle(const char *name, int imageTrack, bool errorIfMissing, int waitTime) {
	return GameCall<uint32_t>(0x0040A27C)(name, imageTrack, errorIfMissing, waitTime);
}

void R_AddCmdDrawStretchPicInternal(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, uint32_t material) {
	GameCall<void>(0x004119C8)(x, y, w, h, s0, t0, s1, t1, color, material);
}

void R_AddCmdDrawTextInternal(const char *text, int maxChars, uint32_t font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style) {
	GameCall<void>(0x00411E18)(text, maxChars, font, x, y, xScale, yScale, rotation, color, style);
}

void CG_DrawRotatedPicPhysical(int scrPlace, float x, float y, float width, float height, float angle, const float *color, int material) {
	GameCall<void>(0x000E2178)(scrPlace, x, y, width, height, angle, color, material);
}

uint32_t ScrPlace_GetView() {
	return GameCall<uint32_t>(0x001EC090)(0);
}

bool WorldPosToScreenPos(int localClientNum, const float * origin, float * outScreen) {
	return GameCall<bool>(0x007BB360)(localClientNum, origin, outScreen);
}

float Atan(float f) {
	return GameCall<float>(0x00913558)(f);
}

short SL_GetString(const char * str, int r4, int r5) {
	return GameCall<short>(0x001B332C)(str, r4, r5);
}

void AimTarget_GetTagPos(centity_t * targetEnt, short tag, float * outOrigin) {
	GameCall<void>(0x00036458)(targetEnt, tag, outOrigin);
}

void CL_DrawLine(float X1, float Y1, float X2, float Y2, const float * color, float Width) {
	float X, Y, Angle, L1, L2, H1;
	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrtf(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);
	Angle = Atan(H1 / L1) * (180 / 3.14159265358979323846);
	CG_DrawRotatedPicPhysical(ScrPlace_GetView(), X, Y, L2, Width, Angle, color, Material_RegisterHandle("white", 0, 0, -1));
}

float _mm_xor_ps(float v15, float _mask__NegFloat_) {
	return v15 * _mask__NegFloat_;
}

void CG_DrawRotatedQuadPic(uint32_t scrPlace, float x, float y, const float(*verts)[2], float angle, const float *color, uint32_t material) {
	GameCall<void>(0x000E22A0)(scrPlace, x, y, verts, angle, color, material);
}

bool CG_IsEntityFriendlyNotEnemy(int localClientNum, centity_t * ent) {
	return GameCall<bool>(0x0008A5D8)(localClientNum, ent);
}

void CL_DrawBone(int ent, const char * from, const char * to, const float * color) {
	float bone1[3], bone2[3];
	float fromPos[2], toPos[2];
	AimTarget_GetTagPos(&cg_entitiesArray[ent], SL_GetString(from, 0, 5), bone1);
	AimTarget_GetTagPos(&cg_entitiesArray[ent], SL_GetString(to, 0, 5), bone2);
	if (WorldPosToScreenPos(0, bone1, fromPos) && WorldPosToScreenPos(0, bone2, toPos)) {
		CL_DrawLine(fromPos[0], fromPos[1], toPos[0], toPos[1], color, 1);
	}
}

float vectoyaw(const float * vec) {
	return GameCall<float>(0x0061F420)(vec);
}

void CG_DrawWarningIcon(int localClientNum, float centerX, float centerY, const float *grenadeOffset, const float *color, uint32_t material, float radiusOffset) {
	GameCall<void>(0x000CE300)(localClientNum, centerX, centerY, grenadeOffset, color, material, radiusOffset);
}

usercmd_s * CL_GetUserCmd(int currentNum) {
	return (usercmd_s*)((*(int*)(0x00E24C10) + 0x231BC) + (currentNum & 0x7F) * 0x40);
}

void CL_DrawBones(int i, const float * color) {
	//left leg
	CL_DrawBone(i, "j_ball_le", "j_ankle_le", color);
	CL_DrawBone(i, "j_ankle_le", "j_knee_le", color);
	CL_DrawBone(i, "j_knee_le", "j_hip_le", color);
	CL_DrawBone(i, "j_hip_le", "j_spine4", color);

	//right leg
	CL_DrawBone(i, "j_ball_ri", "j_ankle_ri", color);
	CL_DrawBone(i, "j_ankle_ri", "j_knee_ri", color);
	CL_DrawBone(i, "j_knee_ri", "j_hip_ri", color);
	CL_DrawBone(i, "j_hip_ri", "j_spine4", color);

	//spine
	//CL_DrawBone(i, "j_spine4", "j_spineupper", color);
	CL_DrawBone(i, "j_spine4", "j_neck", color);
	CL_DrawBone(i, "j_neck", "j_head", color);

	//left arm
	//CL_DrawBone(i, "j_spine4", "j_shoulder_le", color);
	CL_DrawBone(i, "j_shoulder_le", "j_elbow_le", color);
	CL_DrawBone(i, "j_elbow_le", "j_wrist_le", color);

	//right arm
	//CL_DrawBone(i, "j_spine4", "j_shoulder_ri", color);
	CL_DrawBone(i, "j_shoulder_ri", "j_elbow_ri", color);
	CL_DrawBone(i, "j_elbow_ri", "j_wrist_ri", color);

	//shoulders
	CL_DrawBone(i, "j_neck", "j_shoulder_ri", color);
	CL_DrawBone(i, "j_neck", "j_shoulder_le", color);
}

void CL_DrawBox(int clientNum, const float *color) {
	float tagOriginHead[3];
	float headPos[2];
	float screen[2];
	AimTarget_GetTagPos(&cg_entitiesArray[clientNum], SL_GetString("j_head", 0, 5), tagOriginHead);
	tagOriginHead[2] += 9.0f;

	if (WorldPosToScreenPos(0, tagOriginHead, headPos) && WorldPosToScreenPos(0, cg_entitiesArray[clientNum].origin, screen))
	{
		float entWidth = (screen[1] - headPos[1]) / 5;

		CL_DrawLine(screen[0] - entWidth, screen[1], screen[0] + entWidth, screen[1], color, 1);
		CL_DrawLine(screen[0] - entWidth, headPos[1], screen[0] + entWidth, headPos[1], color, 1);
		CL_DrawLine(screen[0] - entWidth, screen[1], screen[0] - entWidth, headPos[1], color, 1);
		CL_DrawLine(screen[0] + entWidth, screen[1], screen[0] + entWidth, headPos[1], color, 1);
	}
}

void vectoangles(const float * in, float * out) {
	GameCall<void>(0x0061F620)(in, out);
}

bool AimTarget_isTargetVisible(int localClientNum, centity_t *cent) {
	return GameCall<bool>(0x00036700)(localClientNum, cent);
}

void CG_LocationalTrace(trace_t *results, const float *start, const float *end, int passEntityNum, int contentMask, bool checkRopes, void *context) {
	GameCall<void>(0x00198B74)(results, start, end, passEntityNum, contentMask, checkRopes, context);
}

void col_context_t_Constructor(col_context_t * tr) {
	GameCall<void>(0x005A6AE8)(tr);
}

bool IsTagVisible(int clientNum, const char * tag) {
	float tagpos[3] = {0, 0, 0};
	

	AimTarget_GetTagPos(&cg_entitiesArray[clientNum], SL_GetString(tag, 0, 5), tagpos);
	trace_t trace;
	memset(&trace, 0, sizeof(trace_t));
	CG_LocationalTrace(&trace, tagpos, cgArray->refdef.viewOrigin, clientNum, 0x803001, 0, 0);

	R_AddCmdDrawTextInternal(va("fraction: %.2f - %s - (%.2f, %.2f, %.2f)", trace.fraction, tag, tagpos[0], tagpos[1], tagpos[2]), 0x7FFFFFFF, CL_GetNormalFont(), 25, 25, 0.75f, 0.75f, 0, colorWhite, 0);

	if (trace.fraction >= 0.9499999f) {
		return true;
	}
	return false;
}

void VectorSubtract(const float * a, const float * b, float * c) {
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

uint32_t GetRandSeed() {
	return GameCall<uint32_t>(0x00623210)();
}

float distance2d(const float * v0, const float * v1) {
	return sqrtf((float)((float)((float)(v1[1] - v0[1]) * (float)(v1[1] - v0[1])) + (float)((float)(v1[0] - v0[0]) * (float)(v1[0] - v0[0]))) + (float)((float)(v1[3] - v0[3]) * (float)(v1[3] - v0[3])));
}

int nearestPlayer() {
	int nearest = -1;
	float distance = 9999999.0f;
	for (int i = 0; i < 12; i++) {
		if (i != cgArray->clientNum) {
			if (!CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
				if (cg_entitiesArray[i].isAlive1 != 0) {
					if (vars->bAutoBone) {
						float dist = distance2d(cg_entitiesArray[cgArray->clientNum].origin, cg_entitiesArray[i].origin);
						if (dist <= distance) {
							distance = dist;
							nearest = i;
						}
					}
					else {
						if (AimTarget_isTargetVisible(0, &cg_entitiesArray[i])) {
							float dist = distance2d(cg_entitiesArray[cgArray->clientNum].origin, cg_entitiesArray[i].origin);
							if (dist <= distance) {
								distance = dist;
								nearest = i;
							}
						}
					}
				}
			}
		}
	}
	return nearest;
}

int nPlayer() {
	int nearest = -1;
	float distance = 9999999.0f;
	for (int i = 0; i < 12; i++) {
		if (i != cgArray->clientNum) {
			if (!CG_IsEntityFriendlyNotEnemy(0, &cg_entitiesArray[i])) {
				if (cg_entitiesArray[i].isAlive1 != 0) {
					for (int ii = 0; ii < 13;ii++) {
						float dist = distance2d(cg_entitiesArray[cgArray->clientNum].origin, cg_entitiesArray[i].origin);
						if (dist <= distance) {
							distance = dist;
							nearest = i;
						}
					}
				}
			}
		}
	}
	return nearest;
}


void BG_EvaluateTrajectory(uint32_t trajectory, uint32_t time, float * outVec) {
	GameCall<void>(0x0072EE18)(trajectory, time, outVec);
}

void CL_AddReliableCommand(int localClientNum, const char *cmd) {
	GameCall<void>(0x001DF4F0)(localClientNum, cmd);
}

void SV_GameSendServerCommand(int clientNum, int reliable, const char * msg) {
	GameCall<void>(0x005EC544)(clientNum, reliable, msg);
}

void CG_GameMessage(int localClientNum, const char * msg) {
	GameCall<void>(0x00109090)(localClientNum, msg);
}

void CG_SetThirdPerson(int localClientNum, bool val) {
	GameCall<void>(0x000FE294)(localClientNum, val);
}

int GetDDL(int r3, int r4) {
	return GameCall<int>(0x004E20E4)(r3, r4);
}

const char * LiveStorage_GetStatsBufferWithCaller(int r3, const char * r4, const char * r5, int r6, int r7, int r8) {
	return GameCall<const char *>(0x004E9094)(r3, r4, r5, r6, r7, r8);
}

void LiveStorage_UploadStatsForController() {
	GameCall<void>(0x004EB7EC)(0);
}

int DDL_SetString(ddlState_t* search_state, const char * buffer, const char * value) {
	return GameCall<int>(0x006B40C0)(search_state, buffer, value);
}

int DDL_SetUInt(ddlState_t* search_state, const char * buffer, uint32_t value) {
	return GameCall<int>(0x006B392C)(search_state, buffer, value);
}

void StatSetValue(const char * stat, int value) {
	ddlState_t search;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "PlayerStatsList", stat, "StatValue")) {
		if (DDL_SetUInt(&search, buffer_state, value)) {
			LiveStorage_UploadStatsForController();
			SendClientHeartbeat(0, 1);
		}
	}
}

void StatSetValue(const char * stat, const char * value) {
	ddlState_t search;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "PlayerStatsList", stat, "StatValue")) {
		if (DDL_SetString(&search, buffer_state, value)) {
			LiveStorage_UploadStatsForController();
			SendClientHeartbeat(0, 1);
		}
	}
}

void SetChallengeValue(const char * stat, int value) {
	ddlState_t search;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "PlayerStatsList", stat, "ChallengeValue")) {
		if (DDL_SetUInt(&search, buffer_state, value)) {
			LiveStorage_UploadStatsForController();
			SendClientHeartbeat(0, 1);
		}
	}
}

void SetGamemodeChallengeValue(const char * gametype, const char * stat, int value) {
	ddlState_t search;
	ddlState_t search2;
	if (DDL_Lookup_MoveTo((ddlState_t*)GetDDL(1, 1), &search, "playerstatsbygametype")) {
		const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
		if (DDL_MoveTo(&search, &search2, 3, gametype, stat, "ChallengeValue")) {
			if (DDL_SetUInt(&search2, buffer_state, value)) {
				LiveStorage_UploadStatsForController();
				SendClientHeartbeat(0, 1);
			}
		}
	}
}

void SetItemStat(const char * itemIndex, const char * stat, int value) {
	ddlState_t search;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	//printf("%s %s %i\n", itemIndex, stat, value);
	if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "itemstats", atoi(itemIndex), stat)) {
		if (DDL_SetUInt(&search, buffer_state, value)) {
			LiveStorage_UploadStatsForController();
			SendClientHeartbeat(0, 1);
		}
	}
}

void SetItemStat(const char * item_index, const char * stat_type, const char * stat_name, int value) {
	ddlState_t search2;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	//if (DDL_Lookup_MoveTo((ddlState_t*)GetDDL(1, 1), &search, "ItemStats")) {
		printf("%s\n", item_index);
		if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search2, 3, "itemstats", atoi(item_index), stat_type, stat_name, "ChallengeValue")) {
			if (DDL_SetUInt(&search2, buffer_state, value)) {
				LiveStorage_UploadStatsForController();
				SendClientHeartbeat(0, 1);
			}
		}
	//}
}

void SetSpecialStat(const char * item_index, const char * stat, int value) {
	ddlState_t search;
	ddlState_t search2;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	if (DDL_Lookup_MoveTo((ddlState_t*)GetDDL(1, 1), &search, "ItemStats")) {
		if (DDL_MoveTo(&search, &search2, 4, atoi(item_index), "stats", stat, "ChallengeValue")) {
			if (DDL_SetUInt(&search2, buffer_state, value)) {
				LiveStorage_UploadStatsForController();
				SendClientHeartbeat(0, 1);
			}
		}
	}
}

void SetAttachmentStat(const char * attachment, const char * stat_name, int value) {
	ddlState_t search;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 5, "attachments", attachment, "stats", stat_name, "ChallengeValue")) {
		if (DDL_SetUInt(&search, buffer_state, value)) {
			LiveStorage_UploadStatsForController();
			SendClientHeartbeat(0, 1);
		}
	}
}

void SetSpecialStatAllClient(const char * item_index, const char * stat, ddlValue_t value) {
	ddlState_t search;
	ddlState_t search2;
	const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
	for (int i = 0; i < 12; i++) {
		if (DDL_Lookup_MoveTo((ddlState_t*)GetDDL(1, 1), &search, "ItemStats")) {
			if (DDL_MoveTo(&search, &search2, 4, atoi(item_index), "stats", stat, "ChallengeValue")) {

				SV_SetClientStat(i, &search2, value, 0);
			}
		}
	}
}

void StatSetValueAllClient(const char * stat, ddlValue_t value) {
	ddlState_t search;
	for (int i = 0; i < 12; i++) {
		const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
		if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "PlayerStatsList", stat, "StatValue")) {
			
				SV_SetClientStat(i, &search, value, 0);
		}
	}
}

void SetItemStatAllClient(const char * itemIndex, const char * stat, ddlValue_t value) {
	ddlState_t search;
	for (int i = 0; i < 12; i++) {
		const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
		//printf("%s %s %i\n", itemIndex, stat, value);
		if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "itemstats", atoi(itemIndex), stat)) {

			SV_SetClientStat(i, &search, value, 0);
		}
	}
}

void SetChallengeValueAllClient(const char * stat, int value) {
	ddlState_t search;
	for (int i = 0; i < 12; i++) {
		const char * buffer_state = LiveStorage_GetStatsBufferWithCaller(0, "", "", 0, 1, 0);
		if (DDL_MoveTo((ddlState_t*)GetDDL(1, 1), &search, 3, "PlayerStatsList", stat, "ChallengeValue")) {
			ddlValue_t val;
			val.intValue = value;

			SV_SetClientStat(i, &search, val, 0);
		}
	}
}

void SV_SetClientStat(int clientNum, ddlState_t *searchState, ddlValue_t value, int location) {
	GameCall<void>(0x005E7644)(clientNum, searchState, value, location);
}

void SendClientHeartbeat(int localClientNum, int r4) {
	GameCall<void>(0x004F7A60)(localClientNum, r4);
}

void StringTable_GetCoreAsset(int table_index, StringTable ** table) {
	GameCall<void>(0x00627A9C)(table_index, table);
}

const char * StringTable_GetColumnValueForRow(StringTable * table, const int row, const int column) {
	return GameCall<const char *>(0x00627378)(table, row, column);
}

int atoi(const char * str) {
	return GameCall<int>(0x0095C79C)(str, 0, 10);
}

int DDL_MoveTo_t[2] = { 0x006B3760, 0x00E11ED8 };
int(*DDL_MoveTo)(ddlState_t* search_state, ddlState_t * search_result, int arg_count, ...) = (int(*)(ddlState_t*, ddlState_t *, int, ...))&DDL_MoveTo_t;

int DDL_Lookup_MoveTo(ddlState_t *searchState, ddlState_t *resultState, const char *name) {
	return GameCall<int>(0x006B35EC)(searchState, resultState, name);
}

const char * LiveStats_GetGameTypeName(int gametype_index) {
	return GameCall<const char *>(0x005B6A44)(gametype_index);
}

const char * LookupItemIndex(const char * itemName) {
	StringTable * table;
	StringTable_GetCoreAsset(CORE_TABLE_STATS, &table);
	for (int i = 0; i < table->rowCount; i++) {
		if (!strcmp(StringTable_GetColumnValueForRow(table, i, 4), itemName)) {
			const char * ret = StringTable_GetColumnValueForRow(table, i, 0);
			//printf("%s - %s - %s\n", StringTable_GetColumnValueForRow(table, i, 4), itemName, ret);
			return ret;
		}
	}
	return "(NULL)";
}

void Cbuf_AddText(int localClientNum, const char * cmd) {
	GameCall<void>(0x005B1A7C)(localClientNum, cmd);
}

const char* strstr(const char* _String, const char* _SubString) {
	return GameCall<const char *>(0x00959108)(_String, _SubString);
}

uint32_t sub_4FC9E0(int r3, int r4) {
	return GameCall<uint32_t>(0x004FC9E0)(r3, r4);
}

template<typename ...Args> void LUI_LuaCall_Function(int * r3, int r4, int r5, int r6, Args... args) {
	GameCall<void>(0x009BD504)(r3, r4, r5, r6, ...args);
}



