#pragma once
#include "NFVector.hpp"

namespace nfe
{
  template< class Vector >
  class VectorIterator
  {
  public:

    typedef typename Vector::DataType DataType;

    VectorIterator( const Vector& str, uint64 m_uiPos );

    VectorIterator( const VectorIterator< Vector >& it );

    VectorIterator& operator =( const VectorIterator< Vector >& it );

    DataType& operator *( void );

    bool Valid( void ) const;

    bool operator ==( const VectorIterator< Vector >& rhs ) const;
    bool operator !=( const VectorIterator< Vector >& rhs ) const;
    bool operator <=( const VectorIterator< Vector >& rhs ) const;
    bool operator <( const VectorIterator< Vector >& rhs ) const;
    bool operator >=( const VectorIterator< Vector >& rhs ) const;
    bool operator >( const VectorIterator< Vector >& rhs ) const;

    VectorIterator< Vector >& operator ++( void );
    VectorIterator< Vector > operator ++( int );


    VectorIterator< Vector >& operator --( void );
    VectorIterator< Vector > operator --( int );

    ~VectorIterator();


  protected:
  private:

    const Vector& m_T;
    uint64 m_uiPos;
  };
}
#include "NFSTL/NFVectorIterator.inl"
