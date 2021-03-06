#pragma once
#ifndef NiFrameMultiSample_h__
  #define NiFrameMultiSample_h__

  #include "NFRendererPCH.hpp"
  #include "NFStringableObject.hpp"

namespace nfe
{
  class D3DMultiSample :
    public IStringableObject
  {
  public:

    D3DMultiSample( const D3DMULTISAMPLE_TYPE& multiSampleType );
    ~D3DMultiSample();

    D3DMULTISAMPLE_TYPE GetMultiSampleType() const;

    virtual String ToString() const;

  private:

    D3DMULTISAMPLE_TYPE m_MultiSampleType;
  };
}

#endif  // NiFrameMultiSample_h__
