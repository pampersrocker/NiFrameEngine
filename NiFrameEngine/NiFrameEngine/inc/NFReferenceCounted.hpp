#pragma once
#ifndef NiFrameReferenceCounted_h__
#define NiFrameReferenceCounted_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCountPolicy.hpp"
#include "Platform/NFPlatform.hpp"

namespace nfe
{
  class RefCountAllocator : public IAllocator
  {
  public:
    RefCountAllocator(const char* name = "RefCountAllocator") :
      IAllocator(name)
    { }

    ~RefCountAllocator() { }

    void* AllocateBytes( uint32 size )
    {
      return Allocate( size );
    }
    void FreeBytes( void* pointer )
    {
      Deallocate( pointer );
    }

    virtual void* Allocate( uint64 size, uint32 alignment = 0 ) override
    {
      return GPlatform->GetDefaultAllocator()->Allocate( size );

    }

    virtual void Deallocate( void* address ) override
    {
      GPlatform->GetDefaultAllocator()->Deallocate( address );
    }

  };

  /**
  \brief Reference Counter class for copy on write functionality of the UTFString.

  */
  template< typename T, typename Allocator = RefCountAllocator, typename RefCountPolicy = DefaultRefCountPolicy >
  class ReferenceCounted
  {
  public:
    ReferenceCounted( void );
    explicit ReferenceCounted( T* pointer );
    ReferenceCounted( const ReferenceCounted< T, Allocator, RefCountPolicy > & refCount );
    ReferenceCounted( ReferenceCounted< T, Allocator, RefCountPolicy >&& refCount );
    ~ReferenceCounted();


    ReferenceCounted< T, Allocator, RefCountPolicy >& operator =( T* pointer );
    ReferenceCounted< T, Allocator, RefCountPolicy >& operator =( nullptr_t pointer );
    ReferenceCounted< T, Allocator, RefCountPolicy >& operator =( const ReferenceCounted< T, Allocator, RefCountPolicy >& refCount );
    ReferenceCounted< T, Allocator, RefCountPolicy >& operator =( ReferenceCounted< T, Allocator, RefCountPolicy >&& refCount );

    bool operator ==( const ReferenceCounted< T, Allocator, RefCountPolicy >& rhs ) const;
    bool operator !=( const ReferenceCounted< T, Allocator, RefCountPolicy >& rhs ) const;

    T* operator ->( );
    const T* operator ->( ) const;

    T& operator *( );

    T* Ptr( void ) const;

    T& operator []( uint32 idx );
    const T& operator []( uint32 idx ) const;

    void SetNull( void );

    bool Valid( void ) const;

    bool Null( void ) const;

    uint32 Count( void ) const;

  private:

    void IncRef( void );

    void DecRef( void );

    T* m_CountedPointer;

    uint32* m_Count;

    Allocator m_Alloc;

  };

#include "NFReferenceCounted.inl"

}

#endif // NiFrameReferenceCounted_h__
