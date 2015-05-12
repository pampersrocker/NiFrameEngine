#include "NFEnginePCH.hpp"
#include "Memory/NFIAllocator.hpp"
#include <NFEngine.hpp>

using namespace nfe;

const char* nfe::IAllocator::GetName() const
{
  return m_Name;
}

nfe::IAllocator::~IAllocator()
{
  m_Name = nullptr;
}

nfe::IAllocator::IAllocator( const char* name ) :
m_Name(name)
{

}

IAllocator* nfe::GetDefaultAllocator()
{
  return nfe::GEngine->GetDefaultAllocator();
}

nfe::uint64 nfe::alignedSize( uint64 size, uint32 alignment )
{
  return ( ( size + alignment - 1 ) / alignment ) * alignment;
}
