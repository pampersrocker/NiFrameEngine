#pragma once
#ifndef NiFrameD3DDevTypeStringable_h__
#define NiFrameD3DDevTypeStringable_h__

#include "NFRendererPCH.hpp"
#include "NFStringableObject.hpp"

namespace nfe
{
  class D3DDevTypeStringable : public IStringableObject
  {
  public:
    D3DDevTypeStringable( const D3DDEVTYPE& devType );
    ~D3DDevTypeStringable();

    virtual String ToString() const;

    D3DDEVTYPE GetType( ) const 
    { 
      return m_Type; 
    }

  private:
    D3DDEVTYPE m_Type;
  };

}

#endif // NiFrameD3DDevTypeStringable_h__
