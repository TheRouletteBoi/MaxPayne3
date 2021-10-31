#include "Game.hpp"

GameVariables* g_GameVariables;

template <typename T>
void SetPat(const char* name, const char* pattern, const char* mask, T* out,
   int32_t relativeOffset = 0x00,
   bool getFromHighLow = false, int32_t highAdditive = 0x00, int32_t lowAdditive = 0x00)
{
   uintptr_t ptr = FindPatternInTextSegment((uint8_t*)pattern, mask);
   if (ptr == 0)
   {
      printf("Failed to find %s pattern.\n", name);
      *out = 0;
      return;
   }

   ptr = ptr + relativeOffset;

   if (getFromHighLow)
      ptr = ReadHighLow(ptr, highAdditive, lowAdditive);

   printf("found ptr %s at 0x%X\n", name, ptr);

   *out = (T)ptr;
}

template <typename T>
void SetFn(const char* name, const char* pattern, const char* mask, T* out,
   int32_t relativeOffset = 0x00, bool resolveBranch = false)
{
   uintptr_t ptr = FindPatternInTextSegment((uint8_t*)pattern, mask);
   if (ptr == 0)
   {
      printf("Failed to find %s pattern.\n", name);
      *out = nullptr;
      return;
   }

   static uint32_t opd[2]{};

   ptr = ptr + relativeOffset;

   if (resolveBranch)
      opd[0] = ResolveBranch(ptr);
   else
      opd[0] = ptr;

   opd[1] = GetCurrentToc();

   printf("found func %s at 0x%X\n", name, opd[0]);

   *out = (T)opd;
}

bool GameVariables::FindSignatures()
{
   // Signatures are from 1.10 update PS3   BLUS30557

   SetPat<uintptr_t>("NativeRegistration",
      "\x3B\x60\x00\x00\x2C\x04\x00\x00\x3B\x40\x00\x00\x63\x7C\x00\x00\x60\x7E\x00\x00\x60\x9F\x00\x00", "xx??xx??xx??xx??xx??xx??",
      &pNativeRegistration,
      0x00,
      true, 0x1C, 0x20);

   SetPat<uintptr_t**>("pGlobalVars",
      "\x38\x80\x00\x00\x80\x7F\x00\x00\x90\x9F\x00\x00\x4B\x00\x00\x00\x2C\x03\x00\x00\x90\x7F\x00\x00\x41\x00\x00\x00", "xx??xx??xx??x???xx??xx??x???",
      &pGlobalVars,
      0x00,
      true, 0x1C, 0x20);

   SetFn<GetNativeHandler_t>("GetNativeHandler",
      "\x3C\x80\x00\x00\x30\xE4\x00\x00\x80\xE7\x00\x00\x2C\x07\x00\x00\x40\x00\x00\x00", "xx??xx??xx??xx??x???",
      &GetNativeHandler);

   SetFn<SetVectorResults_t>("RAGE_SetVectorResults",
      "\x31\x03\x00\x00\x79\x08\x00\x00\x80\x88\x00\x00\x30\xA4\x00\x00", "xx??xx??xx??xx??",
      &RAGE_SetVectorResults);

   bool found = pNativeRegistration
      && pGlobalVars
      && GetNativeHandler
      && RAGE_SetVectorResults;

   return found;
}