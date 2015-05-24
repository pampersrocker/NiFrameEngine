#include "NFEnginePCH.hpp"
#include "Platform/NFFile.hpp"


using namespace nfe;

nfe::uint64 nfe::File::Size() const
{
  return m_Size;
}

uint8* nfe::File::Data() const
{
  return m_Data;
}

nfe::String nfe::File::Filename() const
{
  return m_Filename;
}

IAllocator* nfe::File::Allocator() const
{
  return m_Allocator;
}

nfe::File::~File()
{
  nfdeleteArray( m_Data, m_Allocator );
  m_Allocator = nullptr;
  m_Data = nullptr;
  m_Size = 0U;
}

nfe::File::File( IAllocator* allocator, uint8* data, uint64 size, String fileName ) :
m_Allocator(allocator),
m_Data(data),
m_Size(size),
m_Filename(fileName)
{

}
