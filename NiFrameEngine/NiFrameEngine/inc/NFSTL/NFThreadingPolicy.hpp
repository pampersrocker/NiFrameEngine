#pragma once

#include "NFEnginePCH.hpp"
#include "Async\NFSemaphore.hpp"
namespace nfe
{
  class NIFRAME_API NoSTLThreadingPolicy
  {
  public:

    void Lock();
    void Unlock();
  };

  class NIFRAME_API STLLockingThreadingPolicy
  {
  public:

    STLLockingThreadingPolicy();
    ~STLLockingThreadingPolicy();

    void Lock();
    void Unlock();

  private:
    ISemaphore* m_Semaphore;
  };
}
