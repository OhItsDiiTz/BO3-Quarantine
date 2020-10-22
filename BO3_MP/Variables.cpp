#include "Variables.hpp"

Variables::Variables() {
	MenuX = (uiInfoArray->screenWidth / 2) - 120;
	MenuY = 200;
	MenuWidth = 250;

	fFOV = 65.0f;

	//sAimTag[0] = { "", "", "" };
	sAimTag[0] = "j_neck";
	sAimTag[1] = "j_head";
	sAimTag[2] = "j_spineupper";

}

Variables::~Variables() {
	memset(this, 0, sizeof(Variables));
}

Variables * vars;