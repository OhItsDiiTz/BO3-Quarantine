#pragma once
#include "Quarantine.hpp"

#define AngleToShort(a) ((int)((a)*(65536/360.0f))&65535)

#define JOIN_HELPER(x, y) x##y
#define JOIN(x, y) JOIN_HELPER(x, y)

#define TYPE_PAD(size) char JOIN(_pad_, __COUNTER__)[size]
#define TYPE_VARIADIC_BEGIN(name) name { union {
#define TYPE_BEGIN(name, size) name { union { TYPE_PAD(size)
#define TYPE_END(...) }; } __VA_ARGS__
#define TYPE_FIELD(field, offset) struct { TYPE_PAD(offset); field; }
#define TYPE_FZERO(field, offset) struct { field; }

struct UiContext {
	int contextIndex;
	float bias;
	int realTime;
	int frameTime;
	char __padding000[0xC];
	int screenWidth;
	int screenHeight;
	float screenAspect;
	float FPS;
};

struct clientUIActive_t {
	int flags;
	int keyCatchers;
	int connectionState;
	int nextScrollTime;
	int migrationState;
};

struct centity_t {
	short lightingHandle;//0x0
	char eType;//0x2
	char eTypeUnion;//0x3
	char __pad000[0x24];
	float origin[3];//0x28
	char __pad001[0x100];
	float isAlive0;//
	char __pad002[0xF0];
	int lerpeFlags;//0x228
	char __pad003[0xE0];
	int renderfx; //0x30C
	char __pad005[0x78];
	int weapon;//0x388
	char __pad006[0x7C];
	int itemexists;//0x408
	char __pad007[0x58];
	int grenadeexists;
	char __pad008[0x1C6];
	int isAlive1;
	int unk;
};

//TYPE_BEGIN(struct centity_t, 0x638);
//TYPE_FIELD(char eType, 0x03);
//TYPE_FIELD(float origin[3], 0x28);
//TYPE_FIELD(float oldPos[3], 0x1BC);
//
//TYPE_FIELD(int isAlive1, 0x684);
//
//TYPE_END();

struct refDef_t {
	char __pad000[0x008];
	int screenwidth;
	int screenheight;
	char __pad001[0x078];
	float viewOrigin[3];
	char __pad002[0x010];
	float viewAxis[3][3];
};

struct cg_s {
	int clientNum;
	char __pad000[0x80];
	int ping;
	char __pad001[0xC4];
	float delta_angles[3];
	char __pad002[0x329F4];
	refDef_t refdef;
};

struct usercmd_s {
	int serverTime;
	int button_bits[3];
	int angles[3];
};

struct RawFileAsset {
	const char * name;
	int file_size;
	char * buffer;
};

struct trace_t {
	float normal[4];
	float fraction;
	int sflags;
	int cflags;
	int hitType;
	unsigned short hitId;
	unsigned short modelIndex;
	unsigned short partName;
	unsigned short boneIndex;
	unsigned short partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
};

struct col_context_t {
	int mask;
	void *prims;
	int nprims;
	void *ignoreEntParams;
	int passEntityNum0;
	int passEntityNum1;
	int staticmodels;
	int locational;
	char *priorityMap;
	int(__cdecl *collide_entity_func)(int);
};


extern char * clanname_array[];

extern RawFileAsset * g_pRawFiles;

extern UiContext * uiInfoArray;
extern clientUIActive_t * clientUIActives;
extern centity_t * cg_entitiesArray;
extern cg_s * cgArray;

