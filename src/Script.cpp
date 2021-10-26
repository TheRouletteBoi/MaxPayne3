#include "Script.hpp"

void OnGameTick()
{
   if (PLAYER::DOES_MAIN_PLAYER_EXIST())
   {
      Player player = PLAYER::GET_PLAYER_ID();
      Ped playerPed = PLAYER::GET_PLAYER_PED(player);

      PLAYER::SET_PLAYER_INVINCIBLE(player, true);

      int num = PLAYER::GET_PAYNEKILLER_AMT();
      if (num < MAX_PAINKILLERS)
      {
         PLAYER::SET_PAYNEKILLER_AMT(MAX_PAINKILLERS);
      }

      if (PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_LEFT) && PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RDOWN))
      {
         if (!WEAPON::HAS_PED_GOT_WEAPON(playerPed, WEAPON_SMG_MP5))
            WEAPON::GIVE_WEAPON_TO_PED(playerPed, WEAPON_SMG_MP5, MAX_AMMO, true);
      }

      if (PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RIGHT) && PAD::IS_CONTROL_JUST_PRESSED(2, INPUT_FRONTEND_RDOWN))
      {
         const int ARR_SIZE = 256;

         Ped peds[ARR_SIZE];
         int count = NativeMemory::WorldGetAllPeds(peds, ARR_SIZE);

         for (int i = 0; i < count; i++)
         {
            if (peds[i] != playerPed)
            {
               Vector3 coords = PED::GET_PED_COORDS(peds[i]);
               FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, EXP_TAG_MOLOTOV, 1.0f, true, false, 1.0f);
            }
         }
      }
   }
}