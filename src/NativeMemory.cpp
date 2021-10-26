#include "NativeMemory.hpp"

namespace NativeMemory
{
   inline uint16_t GetEntityBoneNameHash(const char* boneName)
   {
      uint32_t hash = 0;

      for (; *boneName; ++boneName)
      {
         hash = toupper(*boneName) + 16 * hash;
         if (hash & 0xF0000000)
            hash ^= hash & 0xF0000000 ^ ((hash & 0xF0000000) >> 24);
      }

      return hash % 0xFE8F + 0x170;
   }


   uintptr_t GetBlipAddress(Blip blip)
   {

      return 0;
   }

   uintptr_t GetInteriorAddress(Interior interior)
   {

      return 0;
   }

   uintptr_t GetObjectAddress(Object object)
   {
      // sub_1D08C0
      return 0;
   }

   uintptr_t GetPedAddress(Ped ped)
   {

      return 0;
   }

   uintptr_t GetVehicleAddress(Vehicle vehicle)
   {
      // sub_534EA8
      return 0;
   }

   int WorldGetAllBlips(Blip* arr, int arrSize)
   {

      return 0;
   }

   int WorldGetAllInteriors(Interior* arr, int arrSize)
   {

      return 0;
   }

   int WorldGetAllObjects(Object* arr, int arrSize)
   {
      // dword_14DA3B4
      return 0;
   }

   int WorldGetAllPeds(Ped* arr, int arrSize)
   {

      return 0;
   }

   int WorldGetAllVehicles(Vehicle* arr, int arrSize)
   {
      // dword_14E03C4
      return 0;
   }
}