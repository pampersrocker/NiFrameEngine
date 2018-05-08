#include "NFEnginePCH.hpp"
#include "Memory/NFIAllocator.hpp"
#include <NFEngine.hpp>
#include "Platform/NFPlatform.hpp"

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
  return ::nfe::NFPlatform::GetDefaultAllocator();
}

NFSize nfe::alignedSize(NFSize size, uint32 alignment )
{
  if( size == 0 )
  {
    return alignment;
  }
  return ( ( size + alignment - 1 ) / alignment ) * alignment;
}
