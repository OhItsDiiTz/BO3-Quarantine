#pragma once
#include "Quarantine.hpp"

extern float colorWhite[4];
extern float colorBlack[4];
extern float colorBlackFaded[4];
extern float colorRedFaded[4];
extern float colorGreenFaded[4];
extern float colorGreyFaded[4];

struct centity_t;
struct usercmd_s;
struct trace_t;
struct col_context_t;

void R_EndFrame();
void R_SetDepthOfField(uint32_t viewInfo, uint32_t sceneParams);
void CL_WritePacket(int localClientNum);
void CL_GamepadButtonEventForPort(int portIndex, int key, int buttonEvent, uint32_t time, int button);
void CG_PredictPlayerState(int localClientNum);
bool CL_GetSnapshot(int localClientNum, int r4, int snapshot);

template <typename T> extern T(*GameCall(unsigned int address))(...);


extern int va_t[2];
extern char *(*va)(const char * fmt, ...);

bool isInGame();

extern const char * killstreaks[];

uint32_t R_TextWidth(const char *text, int maxChars, uint32_t font);
uint32_t CL_GetNormalFont();
uint32_t Material_RegisterHandle(const char *name, int imageTrack, bool errorIfMissing, int waitTime);
void R_AddCmdDrawStretchPicInternal(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, uint32_t material);
void R_AddCmdDrawTextInternal(const char *text, int maxChars, uint32_t font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
void CG_DrawRotatedPicPhysical(int scrPlace, float x, float y, float width, float height, float angle, const float *color, int material);
uint32_t ScrPlace_GetView();
bool WorldPosToScreenPos(int localClientNum, const float * origin, float * outScreen);
float Atan(float f);
short SL_GetString(const char * str, int r4, int r5);
void AimTarget_GetTagPos(centity_t * targetEnt, short tag, float * outOrigin);
void CL_DrawLine(float X1, float Y1, float X2, float Y2, const float * color, float Width);
float _mm_xor_ps(float v15, float _mask__NegFloat_);
void CG_DrawRotatedQuadPic(uint32_t scrPlace, float x, float y, const float(*verts)[2], float angle, const float *color, uint32_t material);
bool CG_IsEntityFriendlyNotEnemy(int localClientNum, centity_t * ent);
void CL_DrawBone(int ent, const char * from, const char * to, const float * color);
float vectoyaw(const float * vec);
void CG_DrawWarningIcon(int localClientNum, float centerX, float centerY, const float *grenadeOffset, const float *color, uint32_t material, float radiusOffset);
usercmd_s * CL_GetUserCmd(int currentNum);
void CL_DrawBones(int i, const float * color);
void CL_DrawBox(int clientNum, const float *color);
void vectoangles(const float * in, float * out);
bool AimTarget_isTargetVisible(int localClientNum, centity_t *cent);
void CG_LocationalTrace(trace_t *results, const float *start, const float *end, int passEntityNum, int contentMask, bool checkRopes, void *context);
void col_context_t_Constructor(col_context_t * tr);
bool IsTagVisible(int clientNum, const char * tag);
void VectorSubtract(const float * a, const float * b, float * c);
float distance2d(const float * v0, const float * v1);
int nearestPlayer();
int nPlayer();
void BG_EvaluateTrajectory(uint32_t trajectory, uint32_t time, float * outVec);
void CL_AddReliableCommand(int localClientNum, const char *cmd);
void SV_GameSendServerCommand(int clientNum, int reliable, const char * msg);
void CG_GameMessage(int localClientNum, const char * msg);
void CG_SetThirdPerson(int localClientNum, bool val);

int GetDDL(int r3, int r4);

struct ddlState_t {
	int unk0;
	int absoluteOffset;
	int unk1;
	int member;
	int ddl;
};

enum CoreStringTable
{
	CORE_TABLE_GUNLEVELS = 3,
	CORE_TABLE_STATS = 4,
	CORE_TABLE_MILESTONE_1 = 8,
	CORE_TABLE_MILESTONE_2 = 9,
	CORE_TABLE_MILESTONE_3 = 10,
	CORE_TABLE_MILESTONE_4 = 11,
};

struct StringTable {
	const char * name;
	int columnCount;
	int rowCount;
	int values;
	int cellIndex;
};

union ddlValue_t {
	float fixedPointValue;
	int intValue;
	unsigned int uintValue;
	unsigned long long int64Value;
	float floatValue;
	const char *stringPtr;
};

const char * LiveStorage_GetStatsBufferWithCaller(int r3, const char * r4, const char * r5, int r6, int r7, int r8);
void LiveStorage_UploadStatsForController();
int DDL_SetString(ddlState_t* search_state, const char * buffer, const char * value);
int DDL_SetUInt(ddlState_t* search_state, const char * buffer, uint32_t value);

void StatSetValue(const char * stat, int value);
void StatSetValue(const char * stat, const char * value);
void SetChallengeValue(const char * stat, int value);
void SetGamemodeChallengeValue(const char * gametype, const char * stat, int value);
void SetItemStat(const char * itemIndex, const char * stat, int value);
void SetItemStat(const char * item_index, const char * stat_type, const char * stat_name, int value);
void SetSpecialStat(const char * item_index, const char * stat, int value);
void SetAttachmentStat(const char * attachment, const char * stat_name, int value);

void SetSpecialStatAllClient(const char * item_index, const char * stat, ddlValue_t value);
void StatSetValueAllClient(const char * stat, ddlValue_t value);
void SetItemStatAllClient(const char * itemIndex, const char * stat, ddlValue_t value);
void SetChallengeValueAllClient(const char * stat, int value);

void SV_SetClientStat(int clientNum, ddlState_t *searchState, ddlValue_t value, int location);

void SendClientHeartbeat(int localClientNum, int r4);

void StringTable_GetCoreAsset(int table_index, StringTable ** table);
const char * StringTable_GetColumnValueForRow(StringTable * table, const int row, const int column);

int atoi(const char * str);

extern int DDL_MoveTo_t[2];
extern int(*DDL_MoveTo)(ddlState_t* search_state, ddlState_t* search_result, int arg_count, ...);

int DDL_Lookup_MoveTo(ddlState_t *searchState, ddlState_t *resultState, const char *name);

const char * LiveStats_GetGameTypeName(int gametype_index);

const char * LookupItemIndex(const char * itemName);

void Cbuf_AddText(int localClientNum, const char * cmd);

const char* strstr(const char* _String, const char* _SubString);

uint32_t sub_4FC9E0(int r3, int r4);
template<typename ...Args> void LUI_LuaCall_Function(int * r3, int r4, int r5, int r6, Args... args);

