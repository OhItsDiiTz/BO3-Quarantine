#include "HookManager.hpp"

uint32_t BranchLinked(uint32_t branchFrom, uint32_t branchTo) {
	uint32_t branch;
	if (branchTo > branchFrom)
		branch = 0x48000001 + (branchTo - branchFrom);
	else
		branch = 0x4C000001 - (branchFrom - branchTo);
	return branch;
}

void SetupHookHandler() {
	uint32_t hook_data[4] = { 0x3C000000 + (((uint32_t)*(uint32_t*)(MainHookData) >> 16) & 0xFFFF), 0x60000000 + ((uint32_t)*(uint32_t*)(MainHookData) & 0xFFFF), 0x7C0903A6, 0x4E800420 };
	memcpy((void*)(0x007D5DB4), hook_data, 0x10);
}
void MakeCall(uint32_t address) {
	*(uint32_t*)(address) = BranchLinked(address, 0x007D5DB4);
}


uint32_t MainHookData(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10, uint32_t r11, uint32_t r12, uint32_t r13, uint32_t r14, uint32_t r15, uint32_t r16, uint32_t r17, uint32_t r18, uint32_t r19, uint32_t r20, uint32_t r21, uint32_t r22, uint32_t r23, uint32_t r24, uint32_t r25, uint32_t r26, uint32_t r27, uint32_t r28, uint32_t r29, uint32_t r30, uint32_t r31) {
	uint32_t link_register = (uint32_t)__builtin_return_address();

	if (link_register == 0x001EA600) {
		R_EndFrame_Detour();
		R_EndFrame();
	}

	if (link_register == 0x005998B0 || link_register == 0x00599938) {
		CL_GamepadButtonEventForPort_Detour((int)r3, (int)r4, (int)r5, r6, (int)r7);
	}

	if (link_register == 0x0041E76C) {
		R_SetDepthOfField_Detour(r3, r4);
		R_SetDepthOfField(r3, r4);
	}

	if (link_register == 0x001C86B8) {
		CL_WritePacket_Detour(r3);
	}

	if (link_register == 0x00173FBC) {
		CG_PredictPlayerState_Detour(r3);
	}
	
	if (link_register == 0x00158CD0) {
		return CL_GetSnapshot_Detour(r3, r4, r5);
	}

	if (link_register == 0x002B0694) {

	}

	return 0;
}


