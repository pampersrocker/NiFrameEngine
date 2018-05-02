#include "NFEnginePCH.hpp"
#include "NFSTL/NFThreadingPolicy.hpp"




void nfe::NoSTLThreadingPolicy::Unlock()
{

}

void nfe::NoSTLThreadingPolicy::Lock()
{
}

nfe::STLLockingThreadingPolicy::STLLockingThreadingPolicy()
{
  NF_ASSERT( GPlatform, "No platform available!" );
  m_Semaphore = GPlatform->CreateSemaphore( 1, 1, SemaphoreQueueType::FIFO, "ThreadingPolicySemaphore" );
}

nfe::STLLockingThreadingPolicy::~STLLockingThreadingPolicy()
{
  NF_ASSERT( GPlatform, "No platform available!" );
  GPlatform->DestroySemaphore( m_Semaphore );
}

void nfe::STLLockingThreadingPolicy::Lock()
{
  m_Semaphore->Wait();
}

void nfe::STLLockingThreadingPolicy::Unlock()
{
  m_Semaphore->Signal();
}
