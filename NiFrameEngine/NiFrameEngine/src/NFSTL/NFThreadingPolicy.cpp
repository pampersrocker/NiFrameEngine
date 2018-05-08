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
  m_Semaphore = NFPlatform::CreateSemaphore( 1, 1, SemaphoreQueueType::FIFO, "ThreadingPolicySemaphore" );
}

nfe::STLLockingThreadingPolicy::~STLLockingThreadingPolicy()
{
  NFPlatform::DestroySemaphore( m_Semaphore );
}

void nfe::STLLockingThreadingPolicy::Lock()
{
  m_Semaphore->Wait();
}

void nfe::STLLockingThreadingPolicy::Unlock()
{
  m_Semaphore->Signal();
}
