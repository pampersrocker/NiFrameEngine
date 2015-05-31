#pragma once

#include "NFEnginePCH.hpp"
#include "Memory/NFIAllocator.hpp"

namespace nfe
{
  class NIFRAME_API File
  {
  public:
    File( IAllocator* allocator, uint8* data, uint64 size, String fileName );
    ~File();

    friend class IPlatform;

    IAllocator* Allocator() const;
    nfe::String Filename() const;
    uint8* Data() const;
    nfe::uint64 Size() const;
  private:
    File& operator =( const File& ) = delete;
    File( const File& ) = delete;
    IAllocator* m_Allocator;
    String m_Filename;
    uint8* m_Data;
    uint64 m_Size;
  };
}
