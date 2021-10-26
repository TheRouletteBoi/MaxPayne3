#pragma once
#include <stdint.h>
#include "../MaxPayne/Vector.hpp"

namespace rage
{
#pragma pack(push, 1)
   struct scrNativeCallContext
   {
   public:
      template <typename T>
      T& GetArg(std::size_t index)
      {
         return *reinterpret_cast<T*>(reinterpret_cast<std::uint32_t*>(m_Args) + index);
      }
      template <typename T>
      void SetArg(std::size_t index, T& value)
      {
         *reinterpret_cast<T*>(reinterpret_cast<std::uint32_t*>(m_Args) + index) = value;
      }
      template <typename T>
      void SetReturnValue(T& value)
      {
         *reinterpret_cast<T*>(m_Return) = value;
      }

      void* m_CurrentThread;        // 0x00
      void* m_Return;					// 0x04
      std::uint32_t m_ArgCount;		// 0x08
      void* m_Args;						// 0x0C
      std::uint32_t m_DataCount;		// 0x10
      scrVector* m_LocalVectors[4];	// 0x18 expected 0x20
      scrVector m_VectorResults[4];
   };
#pragma pack(pop)

   using scrNativeHash = uint32_t;
   using scrNativeHandler = void(*)(scrNativeCallContext*);

#pragma pack(push, 1)
   struct scrNativeRegistration
   {
      scrNativeHash m_Hash;
      scrNativeHandler m_Handler;
   };
#pragma pack(pop)
}

using Void = std::uint32_t;
using BOOL = std::int32_t;
using Any = std::uint32_t;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using Pickup = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Group = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;
using Weapon = std::int32_t;
using FireId = std::int32_t;
using Rope = std::int32_t;
using Vector3 = rage::scrVector;

struct Request_s
{
   int index;
   int unk;
};