#include "NFEnginePCH.hpp"
#include "Async/NFBarrier.hpp"

const nfe::uint32& nfe::IBarrier::Count() const
{
  return m_Count;
}

void nfe::IBarrier::Init( uint32 count, const String& name /*= ""*/ )
{
  m_Count = count;
  m_Name = name;
}

nfe::IBarrier::IBarrier()
{

}

nfe::IBarrier::~IBarrier()
{

}
