#pragma once
#include "NFEnginePCH.hpp"

namespace nfe
{
  enum class SemaphoreQueueType
  {
    FIFO,
    ThreadPriority
  };

  class NIFRAME_API ISemaphore
  {
  public:

    ISemaphore();

    virtual ~ISemaphore();

    virtual void Init(
      uint32 semaphoreMaxCount,
      uint32 initialCount,
      SemaphoreQueueType type = SemaphoreQueueType::FIFO,
      const String& name = "" );

    virtual bool Poll( uint32 neededCount = 1 ) = 0;
    virtual void Wait( uint32 neededCount = 1, uint32 uSecondsWaitTime = -1 ) = 0;

    virtual void Signal( uint32 signalCount = 1 ) = 0;
    const nfe::uint32& MaxCount() const;
    const nfe::String& Name() const;
    const nfe::SemaphoreQueueType& Type() const;
  private:

    String m_Name;

    SemaphoreQueueType m_Type;

    uint32 m_MaxCount;
  };

}
