#include "NFEnginePCH.hpp"
#include "Memory/NFIAllocator.hpp"


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
