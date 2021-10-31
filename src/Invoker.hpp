#pragma once
#include <stdint.h>
#include <string>
#include "Util/Exports.hpp"
#include "MaxPayne/Native.hpp"
#include "Game.hpp"

struct NativeContext : public rage::scrNativeCallContext
{
   NativeContext()
   {
      Reset();
   }

   void Reset()
   {
      m_Return = &m_ReturnData[0];
      m_ArgCount = 0;
      m_Args = &m_ArgumentData[0];
      m_DataCount = 0;

      memset((void*)m_LocalVectors, 0, sizeof(m_LocalVectors));
      memset((void*)m_VectorResults, 0, sizeof(m_VectorResults));
      memset((void*)m_ReturnData, 0, sizeof(m_ReturnData));
      memset((void*)m_ArgumentData, 0, sizeof(m_ArgumentData));
   }

   template <typename T>
   void Push(T value)
   {
      std::uintptr_t data{};
      *(T*)(&data) = value;
      m_ArgumentData[m_ArgCount++] = data;
   }

private:
   void SetVectorResult()
   {
      while (m_DataCount > 0)
      {
         m_DataCount--;
         m_LocalVectors[m_DataCount]->x = m_VectorResults[m_DataCount].x;
         m_LocalVectors[m_DataCount]->y = m_VectorResults[m_DataCount].y;
         m_LocalVectors[m_DataCount]->z = m_VectorResults[m_DataCount].z;
      }
   }

public:
   template <typename T>
   T GetReturnValue()
   {
      SetVectorResult();
      //g_GameVariables->RAGE_SetVectorResults(this);
      return *static_cast<T*>(m_Return);
   }

private:
   std::uintptr_t m_ReturnData[6] = {};
   std::uintptr_t m_ArgumentData[32] = {};
};

class Invoker
{
public:
   bool HookNativeFunction(rage::scrNativeHash hash, rage::scrNativeHandler nativeFunction, rage::scrNativeHandler* original)
   {
      rage::scrNativeHandler handler = (rage::scrNativeHandler)g_GameVariables->GetNativeHandler(hash);

      if (handler != nullptr)
      {
         *original = handler;
         handler = nativeFunction;
         return true;
      }

      return false;
   }


   void BeginCall()
   {
      m_Context.Reset();
   }

   template <typename T>
   void Push(T& value)
   {
      m_Context.Push(value);
   }
   template <typename T, typename... TArgs>
   void Push(T& value, TArgs&... args)
   {
      Push(value);
      Push(args...);
   }

   template <typename T>
   T GetReturn()
   {
      return m_Context.GetReturnValue<T>();
   }

   void EndCall(rage::scrNativeHash hash)
   {
      if (auto handler = (rage::scrNativeHandler)g_GameVariables->GetNativeHandler(hash))
      {
         handler(&m_Context);
      }
   }

private:
   NativeContext m_Context;
};

extern Invoker* g_Invoker;