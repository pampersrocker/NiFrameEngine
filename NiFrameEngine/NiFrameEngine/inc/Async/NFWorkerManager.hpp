#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class TaskGroup;
  class WorkerManager;
  class IJob;
  class NIFRAME_API TaskGroup
  {
  public:
    TaskGroup( IAllocator* allocator );

    ~TaskGroup();

    IAllocator* m_Allocator;

    Vector< IJob*, STLLockingThreadingPolicy > Jobs;

    void ResetTaskGroup();

    bool AreJobsDone() const;
  };

  class NIFRAME_API IJob
  {
  public:
    IJob();
    virtual ~IJob();

    virtual void Run() = 0;

    void SetDone();

    void Reset();

    bool IsDone();

  private:

    volatile bool m_Done;
  };

  // Internally used by the WorkerManager to communicate with threads
  struct WorkerManagerStatus
  {
    Vector<IJob*, STLLockingThreadingPolicy> Jobs;
    volatile bool Terminate;
    WorkerManager* Manager;
    TaskGroup* CurrentTaskGroup;
  };

  class NIFRAME_API WorkerManager
  {
  public:
    WorkerManager( IAllocator* allocator = nullptr );
    ~WorkerManager();

    void Release();

    void Initialize( uint32 numWorkers );

    void AddTaskGroup( TaskGroup* group );

    void Update();

    void UpdateTaskGroups();
    ISemaphore* m_ConsumerSemaphore;
  private:

    WorkerManagerStatus m_Status;
    Vector< TaskGroup*, STLLockingThreadingPolicy > m_TaskGroups;
    Vector< IThread* > m_Threads;
    IAllocator* m_Allocator;
  };

}
