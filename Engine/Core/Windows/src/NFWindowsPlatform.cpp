// NFWindowsPlatform.cpp : Defines the exported functions for the DLL application.
//

#include "NFEnginePCH.hpp"
#include "NFWindowsPlatform.hpp"
#include "NFWin32NativeModule.hpp"

using namespace nfe;
// This is the constructor of a class that has been exported.
// see NFWindowsPlatform.h for the class definition
NFWindowsPlatform::NFWindowsPlatform()
{
}

nfe::INativeModule* NFWindowsPlatform::LoadModule(const char* modulePath)
{
  HMODULE module = LoadLibraryEx(modulePath, nullptr, 0);
  if (module)
  {
    return new NFWin32NativeModule(modulePath, module);
  }
  else
  {
    return nullptr;
  }
}

NFWindowsPlatform::~NFWindowsPlatform()
{

}

void NFWindowsPlatform::ReleaseModule(nfe::INativeModule* module)
{
  NFWin32NativeModule* nativeModule = static_cast<NFWin32NativeModule*>(module);
  FreeLibrary(nativeModule->GetHMODULE());
  delete nativeModule;
}

nfe::Resolution NFWindowsPlatform::GetNativeResolution(uint32 monitorIdx)
{
  // Data struct for lambda-value passing
  struct MonitorCBData
  {
    HMONITOR monitor = nullptr;
    uint32 idx = 0;
    uint32 monitorIndex = 0;
  };
  MonitorCBData data;
  // Enumerate all monitors until we find our idx
  EnumDisplayMonitors(
    nullptr,
    nullptr,
    [](HMONITOR enumMonitor, HDC, LPRECT, LPARAM param) -> BOOL
  {
    // Because captured lambdas are not allowed we need to pass our data ... somehow
    MonitorCBData* data = reinterpret_cast<MonitorCBData*>(param);
    if (data->idx++ == data->monitorIndex)
    {
      data->monitor = enumMonitor;
      // Stop enumerating
      return false;
    }
    else
    {
      // Continue enumerating
      return true;
    }
  },
    reinterpret_cast<LPARAM>(&data));
  MONITORINFO monitorInfo;
  MemZero(&monitorInfo, sizeof(MONITORINFO));
  GetMonitorInfo(data.monitor, &monitorInfo);

  return Resolution(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top - monitorInfo.rcMonitor.bottom, Rational());
}

nfe::IAllocator* nfe::NFWindowsPlatform::GetDefaultAllocator()
{
	return nullptr;
}

nfe::IAllocator* nfe::NFWindowsPlatform::GetGPUAllocator()
{
	return nullptr;

}

nfe::IAllocator* nfe::NFWindowsPlatform::GetDebugAllocator()
{
	return nullptr;

}

void nfe::NFWindowsPlatform::Initialize()
{

}

void nfe::NFWindowsPlatform::Update()
{

}

void nfe::NFWindowsPlatform::Release()
{

}

nfe::IThread* nfe::NFWindowsPlatform::CreateThread(IThread::IThreadFunc* func, uint32 threadAffinity, const std::string& name /*= ""*/)
{
	return nullptr;

}

void nfe::NFWindowsPlatform::DestroyThread(IThread* thread)
{

}

nfe::IBarrier* nfe::NFWindowsPlatform::CreateBarrier(uint32 count, const String& name /*= ""*/)
{
	return nullptr;

}

void nfe::NFWindowsPlatform::DestroyBarrier(IBarrier* barrier)
{

}

nfe::ISemaphore* nfe::NFWindowsPlatform::CreateSemaphore(uint32 semaphoreMaxCount, uint32 initialCount, SemaphoreQueueType type /*= SemaphoreQueueType::FIFO*/, const String& name /*= ""*/)
{
	return nullptr;

}

void nfe::NFWindowsPlatform::DestroySemaphore(ISemaphore* semaphore)
{

}

void nfe::NFWindowsPlatform::PushTraceMarker(const char* name)
{

}

void nfe::NFWindowsPlatform::PopTraceMarker()
{

}

void nfe::NFWindowsPlatform::Assert(bool assertion, const char* msg)
{

}

nfe::File* nfe::NFWindowsPlatform::OpenFile(const String& path, const String& mode, IAllocator* allocator /*= nullptr*/)
{
	return nullptr;

}

void nfe::NFWindowsPlatform::CloseFile(File* file)
{

}

void nfe::NFWindowsPlatform::OnAllocation(void* address, uint64 size)
{

}

void nfe::NFWindowsPlatform::OnDeallocation(void* address, uint64 size)
{

}

const nfe::GamePad& nfe::NFWindowsPlatform::GetGamePadStatus(uint8 playerIdx)
{
	return NFGenericPlatform::GetGamePadStatus(playerIdx);
}

void nfe::NFWindowsPlatform::USleepThread(uint32 uSeconds)
{

}
