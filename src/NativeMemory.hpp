#pragma once
#include "MaxPayne/Enums.hpp"
#include "Invoker.hpp"
#include "Game.hpp"

namespace NativeMemory
{
   inline uint16_t GetEntityBoneNameHash(const char* boneName);
   uintptr_t GetBlipAddress(Blip blip);
   uintptr_t GetInteriorAddress(Interior interior);
   uintptr_t GetObjectAddress(Object object);
   uintptr_t GetPedAddress(Ped ped);
   uintptr_t GetVehicleAddress(Vehicle vehicle);
   int WorldGetAllBlips(Blip* arr, int arrSize);
   int WorldGetAllInteriors(Interior* arr, int arrSize);
   int WorldGetAllObjects(Object* arr, int arrSize);
   int WorldGetAllPeds(Ped* arr, int arrSize);
   int WorldGetAllVehicles(Vehicle* arr, int arrSize);
}