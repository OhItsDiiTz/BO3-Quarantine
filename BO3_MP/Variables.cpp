#include "Variables.hpp"

Variables::Variables() {
	MenuX = (uiInfoArray->screenWidth / 2) - 120;
	MenuY = 200;
	MenuWidth = 250;

	//sAimTag[0] = { "", "", "" };
	sBestTag = "j_head";
	
	sBonePos[0] = "j_head";
	sBonePos[1] = "j_neck";
	sBonePos[2] = "j_helmet";
	sBonePos[3] = "j_shoulder_ri";
	sBonePos[4] = "j_shoulder_le";
	sBonePos[5] = "j_elbow_ri";
	sBonePos[6] = "j_elbow_le";
	sBonePos[7] = "j_hip_ri";
	sBonePos[8] = "j_hip_le";
	sBonePos[9] = "j_knee_ri";
	sBonePos[10] = "j_knee_le";
	sBonePos[11] = "j_ankle_ri";
	sBonePos[12] = "j_ankle_le";
	
	sAimTag[0] = "j_neck";
	sAimTag[1] = "j_head";
	sAimTag[2] = "j_helmet";
	sAimTag[3] = "j_spineupper";
	sAimTag[4] = "pelvis";

	sFovType[0] = "Default";
	sFovType[1] = "Low";
	sFovType[2] = "Medium";
	sFovType[3] = "High";

}

Variables::~Variables() {
	memset(this, 0, sizeof(Variables));
}

Variables * vars;