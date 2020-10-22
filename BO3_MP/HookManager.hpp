#pragma once
#include "Quarantine.hpp"


uint32_t BranchLinked(uint32_t branchFrom, uint32_t branchTo);

void SetupHookHandler();
void MakeCall(uint32_t address);
uint32_t MainHookData(uint32_t r3, uint32_t r4, uint32_t r5, uint32_t r6, uint32_t r7, uint32_t r8, uint32_t r9, uint32_t r10, uint32_t r11, uint32_t r12, uint32_t r13, uint32_t r14, uint32_t r15, uint32_t r16, uint32_t r17, uint32_t r18, uint32_t r19, uint32_t r20, uint32_t r21, uint32_t r22, uint32_t r23, uint32_t r24, uint32_t r25, uint32_t r26, uint32_t r27, uint32_t r28, uint32_t r29, uint32_t r30, uint32_t r31);
