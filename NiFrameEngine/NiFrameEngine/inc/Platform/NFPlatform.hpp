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

  class NIFRAME_API IPlatform
  {
  public:
    IPlatform();
    virtual ~IPlatform() {}

    virtual INativeModule* LoadModule(const char* modulePath) = 0;
    virtual void ReleaseModule( INativeModule* module ) = 0;

    virtual IAllocator* GetDefaultAllocator() const = 0;
    /**
    @brief Gets a specific GPU allocator if the platform supports memory allocation specific for a GPU
    */
    virtual IAllocator* GetGPUAllocator() const = 0;

    /**
    @brief Gets a specific Debug Allocator which can be used for debug purpose, this allocator will not be available in shipping builds

    @return IAllocator*
    */
    virtual IAllocator* GetDebugAllocator() const = 0;
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Release() = 0;

    virtual IThread* CreateThread( IThread::IThreadFunc* func, uint32 threadAffinity = 0, const std::string& name = "" ) = 0;
    /**
    @brief Destroys the thread handle, but does not stop the thread

    */
    virtual void DestroyThread( IThread* thread ) = 0;

    virtual IBarrier* CreateBarrier( uint32 count, const String& name = "" ) = 0;

    /**
    @brief Destroys a barrier

    \note The barrier must be empty (no threads waiting for it) before it can be destroyed.

    @param barrier The barrier to destroy

    */
    virtual void DestroyBarrier( IBarrier* barrier ) = 0;

    virtual ISemaphore* CreateSemaphore(
      uint32 semaphoreMaxCount,
      uint32 initialCount,
      SemaphoreQueueType type = SemaphoreQueueType::FIFO,
      const String& name = "" ) = 0;

    virtual void DestroySemaphore(ISemaphore* semaphore) = 0;

    virtual void PushTraceMarker( const char* name ) = 0;
    virtual void PopTraceMarker() = 0;

    virtual void Assert( bool assertion, const char* msg ) = 0;

    virtual Resolution GetNativeResolution( uint32 monitorIdx ) const = 0;

    virtual File* OpenFile( const String& path, const String& mode, IAllocator* allocator = nullptr ) = 0;
    virtual void CloseFile( File* file) = 0;

    virtual void OnAllocation( void* address, uint64 size ) = 0;
    virtual void OnDeallocation( void* address, uint64 size ) = 0;

    virtual const GamePad& GetGamePadStatus( uint8 playerIdx ) = 0;

    virtual void USleepThread( uint32 uSeconds ) = 0;


  private:

  };

  extern NIFRAME_API IPlatform* GPlatform;
}
