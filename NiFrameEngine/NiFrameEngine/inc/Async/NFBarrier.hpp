#pragma once
#include "NFEnginePCH.hpp"

namespace nfe
{
  class NIFRAME_API IBarrier
  {
  public:

    IBarrier();

    virtual ~IBarrier();

    virtual void Init(uint32 count, const String& name = "");


    /**
    @brief Waits on the barrier until the specified threads arrive


    @return \c true If this was the thread that causes the barrier to activate all threads to continue, \c false otherwise
    */
    virtual bool Wait() = 0;

    const nfe::uint32& Count() const;
  private:

    String m_Name;
    uint32 m_Count;
  };
}
