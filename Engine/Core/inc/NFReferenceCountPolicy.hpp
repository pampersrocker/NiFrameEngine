#pragma once
#include "NFEnginePCH.hpp"
#include "Memory/NFIAllocator.hpp"
namespace nfe
{
  struct NoRefCountPolicy
  {
    inline static void DecRef( uint32& )
    {
    }

    inline static void IncRef( uint32& )
    {
    }

    inline static void Destroy( IAllocator*, void*, uint32* )
    {
    }
  };

  struct DefaultRefCountPolicy
  {
    inline static void DecRef( uint32& count )
    {
      --count;
    }

    inline static void IncRef( uint32& count )
    {
      ++count;
    }

    inline static void Destroy( IAllocator* pAllocator, void* pCounted, uint32* pCount )
    {
      pAllocator->Deallocate( pCounted );
      pAllocator->Deallocate( pCount );
    }
  };
}
