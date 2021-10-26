#pragma once
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/process.h>
#include "Util/Exports.hpp"
#include "Util/Memory.hpp"

class GameVariables
{
public:
   // offsets are from BLUS30557 1.10

   uint32_t RAGE_SetVectorResultsOpd[2] = { 0x1121B60, GetCurrentToc() };
   using SetVectorResults_t = void(*)(void* context);
   SetVectorResults_t RAGE_SetVectorResults = (SetVectorResults_t)RAGE_SetVectorResultsOpd;

   uintptr_t pNativeRegistration = (uintptr_t)0x1D96D00;
   uintptr_t** pGlobalVars = (uintptr_t**)0x1D973E8;
};

extern GameVariables* g_GameVariables;