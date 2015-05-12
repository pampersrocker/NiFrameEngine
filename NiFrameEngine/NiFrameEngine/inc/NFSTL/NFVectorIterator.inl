#pragma once

namespace nfe
{
  template< class Vector >
  VectorIterator< Vector > VectorIterator< Vector >::operator--( int )
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_uiPos > 0 )
    {
      VectorIterator it( *this );
      --*this;
      return it;
    }
    else
    {
      NF_ASSERT(false, "Iterator not decrementable" );
      return *this;
    }
#else

    VectorIterator it( *this );
    --*this;
    return it;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  VectorIterator< Vector >& VectorIterator< Vector >::operator--( void )
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_uiPos > 0 )
    {
      --m_uiPos;
      return *this;
    }
    else
    {
      NF_ASSERT( false,  "Iterator not decrementable" );
      return *this;
    }
#else

    --m_uiPos;
    return *this;
#endif // _ITERATOR_DEBUG_LEVEL == 2

  }

  template< class Vector >
  VectorIterator< Vector >& VectorIterator< Vector >::operator=( const VectorIterator< Vector >& it )
  {
    m_T = it.m_T;
    m_uiPos = it.m_uiPos;
  }

  template< class Vector >
  VectorIterator< Vector > VectorIterator< Vector >::operator++( int )
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_uiPos < m_T.m_Size )
    {
      VectorIterator it( *this );
      ++*this;
      return it;
    }
    else
    {
      NF_ASSERT( false,  "Iterator not incrementable" );
      return *this;
    }
#else

    VectorIterator it( *this );
    ++*this;
    return it;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  VectorIterator< Vector >& VectorIterator< Vector >::operator++( void )
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_uiPos < m_T.m_Size )
    {
      ++m_uiPos;
      return *this;
    }
    else
    {
      NF_ASSERT( false,  "Iterator not incrementable" );
      return *this;
    }
#else

    ++m_uiPos;
    return *this;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  bool VectorIterator< Vector >::operator>( const VectorIterator< Vector >& rhs ) const
  {

#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on > comparison" );
      return false;
    }
    else
    {
      return m_uiPos > rhs.m_uiPos;
    }
#else
    return m_uiPos > rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2

  }

  template< class Vector >
  bool VectorIterator< Vector >::operator>=( const VectorIterator< Vector >& rhs ) const
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on >= comparison" );
      return false;
    }
    else
    {
      return m_uiPos >= rhs.m_uiPos;
    }
#else
    return m_uiPos >= rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  bool VectorIterator< Vector >::operator<( const VectorIterator< Vector >& rhs ) const
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on < comparison" );
      return false;
    }
    else
    {
      return m_uiPos < rhs.m_uiPos;
    }
#else
    return m_uiPos < rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  bool VectorIterator< Vector >::operator<=( const VectorIterator< Vector >& rhs ) const
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on <= comparison" );
      return false;
    }
    else
    {
      return m_uiPos <= rhs.m_uiPos;
    }
#else
    return m_uiPos <= rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  bool VectorIterator< Vector >::operator!=( const VectorIterator< Vector >& rhs ) const
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on != comparison" );
      return false;
    }
    else
    {
      return m_uiPos != rhs.m_uiPos;
    }
#else
    return m_uiPos != rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  bool VectorIterator< Vector >::operator==( const VectorIterator< Vector >& rhs ) const
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( m_T.m_Data != rhs.m_T.m_Data )
    {
      NF_ASSERT( false,  "UTFIterator mismatch on == comparison" );
      return false;
    }
    else
    {
      return m_uiPos == rhs.m_uiPos;
    }
#else
    return m_uiPos == rhs.m_uiPos;
#endif // _ITERATOR_DEBUG_LEVEL == 2
  }

  template< class Vector >
  typename VectorIterator< Vector >::DataType& VectorIterator< Vector >::operator*( )
  {
#if _ITERATOR_DEBUG_LEVEL == 2
    if( Valid() )
    {
      return *( m_T.m_Data + m_uiPos );
    }
    else
    {
      NF_ASSERT( false,  "Iterator not dereferenceable" );
      return *( m_T.m_Data + m_uiPos );
    }
#else
    return *( m_T.m_Data + m_uiPos );
#endif

  }

  template< class Vector >
  bool VectorIterator< Vector >::Valid( void ) const
  {
    return m_uiPos < m_T.m_Size;
  }

  template< class Vector >
  VectorIterator< Vector >::~VectorIterator()
  {
    m_uiPos = 0U;
  }

  template< class Vector >
  VectorIterator< Vector >::VectorIterator( const typename Vector& data, uint64 uiPos ) :
    m_T( data ),
    m_uiPos( uiPos )
  {
  }

  template< class Vector >
  VectorIterator< Vector >::VectorIterator( const VectorIterator< Vector >& it ) :
    m_T( it.m_T ),
    m_uiPos( it.m_uiPos )
  {

  }
}
