#pragma once
#ifndef NiFrameReferenceCounted_h__
#define NiFrameReferenceCounted_h__

#include "NFEnginePCH.hpp"
#include "NFReferenceCountPolicy.hpp"
#include "Platform/NFPlatform.hpp"

namespace nfe
{
  class NIFRAME_API RefCountAllocator : public IAllocator
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

    virtual void* Allocate( NFSize size, uint32 alignment = 0 ) override
    {
      return NFPlatform::GetDefaultAllocator()->Allocate( size );

    }

    virtual void Deallocate( void* address ) override
    {
      NFPlatform::GetDefaultAllocator()->Deallocate( address );
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

    template<typename Other>
    ReferenceCounted< Other, Allocator, RefCountPolicy> StaticCastTo();
    template<typename Other>
    ReferenceCounted< Other, Allocator, RefCountPolicy> DynamicCastTo();
    template<typename Other>
    ReferenceCounted< Other, Allocator, RefCountPolicy> FastCastTo();

    template <typename Other, typename OtherAllocator, typename OtherRefCountPolicy>
    friend class ReferenceCounted;

  private:
    ReferenceCounted( T* pointer, uint32* count );


    void IncRef( void );

    void DecRef( void );

    T* m_CountedPointer;

    uint32* m_Count;

    Allocator m_Alloc;

  };

  template< typename Other, typename T, typename Allocator, typename RefCountPolicy>
  inline
    ReferenceCounted< Other, Allocator, RefCountPolicy > StaticCast( const ReferenceCounted<T, Allocator, RefCountPolicy >& ptr )
  {
    return ptr. template StaticCastTo<Other>();
  }
  template< typename Other, typename T, typename Allocator, typename RefCountPolicy>
  inline
    ReferenceCounted< Other, Allocator, RefCountPolicy > DynamicCast( const ReferenceCounted<T, Allocator, RefCountPolicy >& ptr )
  {
    return ptr. template DynamicCastTo<Other>();
  }
  template< typename Other, typename T, typename Allocator, typename RefCountPolicy>
  inline
    ReferenceCounted< Other, Allocator, RefCountPolicy > FastCast( const ReferenceCounted<T, Allocator, RefCountPolicy >& ptr )
  {
    return ptr. template FastCastTo<Other>();
  }

#include "NFReferenceCounted.inl"

}

#endif // NiFrameReferenceCounted_h__
