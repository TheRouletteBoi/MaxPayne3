
#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <cell/pad.h>
#include "Util/NewDeleteOverride.hpp"
#include "Util/TimeHelpers.hpp"
#include "Game.hpp"
#include "Invoker.hpp"
#include "Script.hpp"

SYS_MODULE_INFO( MaxPayne3, 0, 1, 1);
SYS_MODULE_START( MaxPayne3_Main );
SYS_MODULE_STOP( MaxPayne3_Stop );

/***
* Features
* - Automatic Invincibility enabled
* - Automatic max pain killers
* - Press DPAD LEFT + X to receive MP5 SMG
* - Press DPAD RIGHT + X to explode all nearby peds
* 
* 
*/ 

sys_ppu_thread_t idMaxPayne3MainPpuThread = SYS_PPU_THREAD_ID_INVALID;

rage::scrNativeHandler OriginalNativeWait{};
int g_coreTimer{};

void NativeWaitHook(rage::scrNativeCallContext* context)
{
   if (g_coreTimer + 1 < MISC::GET_GAME_TIMER())
   {
      OnGameTick();
      g_coreTimer = MISC::GET_GAME_TIMER();
   }

   OriginalNativeWait(context);
}

CDECL_BEGIN
int MaxPayne3_Main(int argc, char* argv[])
{
   sys_ppu_thread_create(&idMaxPayne3MainPpuThread, [](uint64_t arg)
   {
      sleep_for(10000);

      g_GameVariables = new GameVariables();
      g_Invoker = new Invoker();

      if (!g_GameVariables->FindSignatures())
      {
         sys_ppu_thread_exit(0);
         return;
      }

      // wait for game to load natives
      while (g_Invoker->HookNativeFunction(0x7715C03B, NativeWaitHook, &OriginalNativeWait) == false)
         sleep_for(3000);

      sys_ppu_thread_exit(0);

   }, 0, 3000, 8192, SYS_PPU_THREAD_CREATE_JOINABLE, "MaxPayne3");

   return 0;
}

int MaxPayne3_Stop(int argc, char* argv[])
{
   uint64_t retVal;
   sys_ppu_thread_join(idMaxPayne3MainPpuThread, &retVal);

   return 0;
}
CDECL_END
