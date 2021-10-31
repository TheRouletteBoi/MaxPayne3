#pragma once
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/process.h>
#include "Util/Exports.hpp"
#include "Util/Memory.hpp"
#include "Util/Pattern.hpp"

class GameVariables
{
public:
   using SetVectorResults_t = void(*)(void* context);
   SetVectorResults_t RAGE_SetVectorResults{};

   using GetNativeHandler_t = void*(*)(uint32_t nativeHash);
   GetNativeHandler_t GetNativeHandler{};

   bool FindSignatures();

public:
   uintptr_t pNativeRegistration{};
   uintptr_t** pGlobalVars{};

};

extern GameVariables* g_GameVariables;