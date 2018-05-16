#include "NFEnginePCH.hpp"
#include "Async/NFSemaphore.hpp"

nfe::ISemaphore::~ISemaphore()
{

}

nfe::ISemaphore::ISemaphore()
{

}

void nfe::ISemaphore::Init( uint32 semaphoreMaxCount, uint32 initialCount, SemaphoreQueueType type /*= SemaphoreQueueType::FIFO*/, const String& name /*= "" */ )
{

}

const nfe::SemaphoreQueueType& nfe::ISemaphore::Type() const
{
  return m_Type;
}

const nfe::String& nfe::ISemaphore::Name() const
{
  return m_Name;
}

const nfe::uint32& nfe::ISemaphore::MaxCount() const
{
  return m_MaxCount;
}
