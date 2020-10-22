#pragma once
#include "Quarantine.hpp"

extern int bullet_tracer_count;

struct BulletTracers {
	int ownerClient;
	int time_to_draw;
	float start_pos[3];
	float stop_pos[3];
};

extern BulletTracers *bullet_tracers;

