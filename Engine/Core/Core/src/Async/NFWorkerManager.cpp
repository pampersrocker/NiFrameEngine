#include "NFEnginePCH.hpp"
#include "Async/NFWorkerManager.hpp"

using namespace nfe;

nfe::WorkerManager::WorkerManager( IAllocator* allocator /*= nullptr */ ) :
m_Status(),
m_TaskGroups(allocator),
m_Threads(allocator),
m_Allocator(allocator),
m_TracePushed(false)
{
  if( !m_Allocator )
  {
    m_Allocator = NFPlatform::GetDefaultAllocator();
  }
  m_Status.CurrentTaskGroup = nullptr;
  m_Status.Manager = this;
  m_Status.Jobs = Vector<IJob*, STLLockingThreadingPolicy>( allocator );
}

void nfe::WorkerManager::AddTaskGroup( TaskGroup* group )
{
  m_TaskGroups.Add( group );

}

void* WorkerManagerFunc( void* data )
{
  WorkerManagerStatus* status = static_cast< WorkerManagerStatus* >( data );
  while( !status->Terminate )
  {

    IJob* job;
    if( status->Jobs.TryPop( &job ) )
    {
      job->Run();
      job->SetDone();
    }

    else
    {
      status->Manager->m_ConsumerSemaphore->Wait();
    }
  }
  return nullptr;
}

void nfe::WorkerManager::Initialize( uint32 numWorkers )
{
  NF_ASSERT( numWorkers > 0, "Need at least 1 worker" );
  m_Threads.Resize( numWorkers );
  uint32 threadId = 0;
  m_ConsumerSemaphore = NFPlatform::CreateSemaphore( 1024, 0, SemaphoreQueueType::FIFO, "Worker Semaphore" );
  for( IThread*& thread : m_Threads )
  {
    thread = NFPlatform::CreateThread( &WorkerManagerFunc, 0, "Worker Thread " + StringUtils::ToString( threadId++ ) );
    thread->Run( &m_Status );
  }
}

void nfe::WorkerManager::UpdateTaskGroups()
{
  bool taskGroupDone = true;
  if( m_Status.CurrentTaskGroup != nullptr )
  {

    for( IJob* job : m_Status.CurrentTaskGroup->Jobs )
    {
      if( !job->IsDone() )
      {
        taskGroupDone = false;
        break;
      }
    }
  }
  if( (taskGroupDone || m_Status.CurrentTaskGroup == nullptr) && m_Status.Jobs.Size() == 0 )
  {
    if( m_Status.CurrentTaskGroup != nullptr )
    {
		  NFPlatform::PopTraceMarker();
      m_TracePushed = false;
    }
    if( m_TaskGroups.Size() > 0 )
    {
      TaskGroup* taskGroup;
      taskGroup = m_TaskGroups[ 0 ];
      m_TaskGroups.RemoveAt( 0 );

      NFPlatform::PushTraceMarker( *( "Worker Task " + taskGroup->Name ) );
      NF_ASSERT( m_TracePushed == false, "too much pushes" );
      m_TracePushed = true;
      m_Status.CurrentTaskGroup = taskGroup;
      NF_ASSERT( m_Status.Jobs.Size() == 0, "" );
      for( IJob* job : taskGroup->Jobs )
      {
        m_Status.Jobs.Add( job );
      }
      m_ConsumerSemaphore->Signal( static_cast<uint32>(taskGroup->Jobs.Size()) );
    }
    else
    {
      m_Status.CurrentTaskGroup = nullptr;
    }
  }
}

void nfe::WorkerManager::Update()
{
  bool wait = true;
  do
  {
    wait = false;
    UpdateTaskGroups();
    wait = m_TaskGroups.Size() > 0;
    if( m_Status.CurrentTaskGroup != nullptr )
    {

      for( IJob* job : m_Status.CurrentTaskGroup->Jobs )
      {
        if( !job->IsDone() )
        {
          wait = true;
          break;
        }
      }
    }
  } while( wait );
  if( m_TracePushed )
  {
    NFPlatform::PopTraceMarker();
    m_TracePushed = false;
  }
  m_Status.CurrentTaskGroup = nullptr;
}

nfe::WorkerManager::~WorkerManager()
{

}

void nfe::WorkerManager::Release()
{
  m_Status.Terminate = true;
  m_ConsumerSemaphore->Signal(static_cast<uint32>(m_Threads.Size()) );
  for( auto* thread : m_Threads )
  {
    NFPlatform::DestroyThread( thread );
  }
  m_Threads.Clear();
  NFPlatform::DestroySemaphore( m_ConsumerSemaphore );
}

nfe::IJob::IJob() :
m_Done(false)
{
}

nfe::IJob::~IJob()
{
}

void nfe::IJob::SetDone()
{
  m_Done = true;
}

void nfe::IJob::Reset()
{
  m_Done = false;
}

bool nfe::IJob::IsDone()
{
  bool done = m_Done;

  return done;
}

nfe::TaskGroup::TaskGroup( IAllocator* allocator ):
m_Allocator(allocator),
Jobs( allocator )
{

}

void nfe::TaskGroup::ResetTaskGroup()
{
  for( IJob* job : Jobs )
  {
    job->Reset();
  }
}

nfe::TaskGroup::~TaskGroup()
{
  Jobs.Clear();
}

bool nfe::TaskGroup::AreJobsDone() const
{
  for( IJob* job : Jobs )
  {
    if( !job->IsDone() )
    {
      return false;
    }
  }
  return true;
}
