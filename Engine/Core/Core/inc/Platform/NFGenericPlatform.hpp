#pragma once

#include "NFEnginePCH.hpp"
#include <Renderer/NFResolution.hpp>
#include "Memory/NFIAllocator.hpp"
#include "NFFile.hpp"
#include "IO/NFGamePad.hpp"
#include "Async/NFThread.hpp"
#include "Async/NFSemaphore.hpp"

namespace nfe
{
  class INativeModule;
  class IBarrier;

  class NIFRAME_API NFGenericPlatform
  {
  public:
    NFGenericPlatform();
    ~NFGenericPlatform() {}

    static INativeModule* LoadModule(const char* modulePath);
    static void ReleaseModule(INativeModule* module);

	  static IAllocator* GetDefaultAllocator();
    /**
    @brief Gets a specific GPU allocator if the platform supports memory allocation specific for a GPU
    */
	  static IAllocator* GetGPUAllocator();

    /**
    @brief Gets a specific Debug Allocator which can be used for debug purpose, this allocator will not be available in shipping builds

    @return IAllocator*
    */
	  static IAllocator* GetDebugAllocator();
	  static void Initialize();
	  static void Update();
	  static void Release();

	  static IThread* CreateThread(IThread::IThreadFunc* func, uint32 threadAffinity, const std::string& name = "");
    /**
    @brief Destroys the thread handle, but does not stop the thread

    */
	  static void DestroyThread(IThread* thread);

	  static IBarrier* CreateBarrier(uint32 count, const String& name = "");

    /**
    @brief Destroys a barrier

    \note The barrier must be empty (no threads waiting for it) before it can be destroyed.

    @param barrier The barrier to destroy

    */
	  static void DestroyBarrier(IBarrier* barrier);

	  static ISemaphore* CreateSemaphore(
      uint32 semaphoreMaxCount,
      uint32 initialCount,
      SemaphoreQueueType type = SemaphoreQueueType::FIFO,
      const String& name = "");

	  static void DestroySemaphore(ISemaphore* semaphore);

	  static void PushTraceMarker(const char* name);
	  static void PopTraceMarker();

	  static void Assert(bool assertion, const char* msg);
	  static Resolution GetNativeResolution(uint32 monitorIdx);


	  static File* OpenFile(const String& path, const String& mode, IAllocator* allocator = nullptr);
	  static void CloseFile(File* file);

	  static void OnAllocation(void* address, uint64 size);
	  static void OnDeallocation(void* address, uint64 size);

	  static const GamePad& GetGamePadStatus(uint8 playerIdx);

	  static void USleepThread(uint32 uSeconds);


  private:

  };
}
