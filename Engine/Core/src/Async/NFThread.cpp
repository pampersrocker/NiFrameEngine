#include "NFEnginePCH.hpp"
#include "Async/NFThread.hpp"




void nfe::IThread::Init( IThreadFunc* func, uint32 affinity, const std::string& name /*= "" */ )
{
  NF_ASSERT( func != nullptr, "No func given to a thread to execute" );
  m_Func = func;
  m_Name = name;
  m_Affinity = affinity;
}

void nfe::IThread::Name( const std::string& val )
{
  m_Name = val;
}

const std::string& nfe::IThread::Name() const
{
  return m_Name;
}

nfe::IThread::IThread()
{

}

nfe::IThread::~IThread()
{

}
