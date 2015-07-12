#include "Async/NFWorkerManager.hpp"

using namespace nfe;

nfe::WorkerManager::WorkerManager( IAllocator* allocator /*= nullptr */ ) :
m_Status(),
m_TaskGroups(allocator),
m_Threads(allocator),
m_Allocator(allocator)
{
  if( !m_Allocator )
  {
    m_Allocator = GPlatform->GetDefaultAllocator();
  }
  m_Status.CurrentTaskGroup = nullptr;
  m_Status.Manager = this;
  m_Status.Jobs = Vector<IJob*, STLLockingThreadingPolicy>( allocator );
}

void nfe::WorkerManager::AddTaskGroup( TaskGroup* group )
{
  m_TaskGroups.Add( group );
  UpdateTaskGroups();

}

void* WorkerManagerFunc( void* data )
{
  WorkerManagerStatus* status = static_cast< WorkerManagerStatus* >( data );
  while ( !status->Terminate )
  {
    if( status->Jobs.Size() > 0 )
    {
      IJob* job;
      if( status->Jobs.TryPop(&job) )
      {
        job->Run();
        job->SetDone();
        //status->Manager->UpdateTaskGroups();
      }
      else
      {

      }
    }
    else
    {
      // Wait for jobs to arrive
      GPlatform->USleepThread( 10 );
    }
  }
  return nullptr;
}

void nfe::WorkerManager::Initialize( uint32 numWorkers )
{
  NF_ASSERT( numWorkers > 0, "Need at least 1 worker" );
  m_Threads.Resize( numWorkers );
  uint32 threadId = 0;
  for( IThread*& thread : m_Threads )
  {
    thread = GPlatform->CreateThread( &WorkerManagerFunc, "Worker Thread " + std::to_string( threadId++ ) );
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
    if( m_TaskGroups.Size() > 0 )
    {


      TaskGroup* taskGroup;
      if( m_TaskGroups.TryPop( &taskGroup ) )
      {
        m_Status.CurrentTaskGroup = taskGroup;
        NF_ASSERT( m_Status.Jobs.Size() == 0, "" );
        for( IJob* job : taskGroup->Jobs )
        {
          m_Status.Jobs.Add( job );
        }
        for( size_t i = 0; i < m_Status.CurrentTaskGroup->Jobs.Size(); i++ )
        {

          //NF_ASSERT( m_Status.Jobs[ i ] == m_Status.CurrentTaskGroup->Jobs[ i ], "" );
        }
        //NF_ASSERT( m_Status.Jobs.Size() > 0, "" );
      }
      else
      {
        m_Status.CurrentTaskGroup = nullptr;
      }
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
    GPlatform->USleepThread( 100 );
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
  m_Status.CurrentTaskGroup = nullptr;
}

nfe::WorkerManager::~WorkerManager()
{

}

void nfe::WorkerManager::Release()
{
  m_Status.Terminate = true;
  for( auto* thread : m_Threads )
  {
    GPlatform->DestroyThread( thread );
  }
  m_Threads.Clear();
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
