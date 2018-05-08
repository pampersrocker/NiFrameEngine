#include "NFEnginePCH.hpp"
#include "Platform/NFGenericPlatform.hpp"

using namespace nfe;


nfe::NFGenericPlatform::NFGenericPlatform()
{

}

nfe::INativeModule* nfe::NFGenericPlatform::LoadModule(const char* modulePath)
{
  return nullptr;
}

void nfe::NFGenericPlatform::ReleaseModule(INativeModule* module)
{

}

nfe::IAllocator* nfe::NFGenericPlatform::GetDefaultAllocator()
{
  return nullptr;
}

nfe::IAllocator* nfe::NFGenericPlatform::GetGPUAllocator()
{
  return nullptr;

}

nfe::IAllocator* nfe::NFGenericPlatform::GetDebugAllocator()
{
  return nullptr;

}

void nfe::NFGenericPlatform::Initialize()
{

}

void nfe::NFGenericPlatform::Update()
{

}

void nfe::NFGenericPlatform::Release()
{

}

nfe::IThread* nfe::NFGenericPlatform::CreateThread(IThread::IThreadFunc* func, uint32 threadAffinity, const std::string& name /*= ""*/)
{
  return nullptr;

}

void nfe::NFGenericPlatform::DestroyThread(IThread* thread)
{

}

nfe::IBarrier* nfe::NFGenericPlatform::CreateBarrier(uint32 count, const String& name /*= ""*/)
{
  return nullptr;

}

void nfe::NFGenericPlatform::DestroyBarrier(IBarrier* barrier)
{

}

nfe::ISemaphore* nfe::NFGenericPlatform::CreateSemaphore(uint32 semaphoreMaxCount, uint32 initialCount, SemaphoreQueueType type /*= SemaphoreQueueType::FIFO*/, const String& name /*= ""*/)
{
  return nullptr;

}

void nfe::NFGenericPlatform::DestroySemaphore(ISemaphore* semaphore)
{

}

void nfe::NFGenericPlatform::PushTraceMarker(const char* name)
{

}

void nfe::NFGenericPlatform::PopTraceMarker()
{

}

void nfe::NFGenericPlatform::Assert(bool assertion, const char* msg)
{

}

nfe::Resolution nfe::NFGenericPlatform::GetNativeResolution(uint32 monitorIdx)
{
  return Resolution();
}

nfe::File* nfe::NFGenericPlatform::OpenFile(const String& path, const String& mode, IAllocator* allocator /*= nullptr*/)
{
  return nullptr;

}

void nfe::NFGenericPlatform::CloseFile(File* file)
{

}

void nfe::NFGenericPlatform::OnAllocation(void* address, uint64 size)
{

}

void nfe::NFGenericPlatform::OnDeallocation(void* address, uint64 size)
{

}

const nfe::GamePad& nfe::NFGenericPlatform::GetGamePadStatus(uint8 playerIdx)
{
  static GamePad DummyGamePad;

  return DummyGamePad;
}

void nfe::NFGenericPlatform::USleepThread(uint32 uSeconds)
{

}
