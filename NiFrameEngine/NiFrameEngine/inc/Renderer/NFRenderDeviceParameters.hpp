#pragma once
#ifndef RenderDeviceParameters_h__
#define RenderDeviceParameters_h__

#include "NFEnginePCH.hpp"

namespace nfe
{
  class IStringableObject;

  typedef map< String, vector<IStringableObject*>* > RenderDeviceParameterList;

  class NIFRAME_DLL_EXPORT RenderDeviceParams
  {
    enum RenderDeviceParameter_t
    {
      ADAPTER = 0x00000001,
      DEVICE_TYPE = 0x00000002,
      FULLSCREEN = 0x00000004,
      VIDEO_MODE = 0x00000008,
      BUFFER_FORMAT = 0x00000010,
      Z_STENCIL_BUFFER_FORMAT = 0x00000020,
      MULTISAMPLE_TYPE = 0x00000040,
      MULTISAMPLE_QUALITY = 0x00000080,
    };

  public:
    RenderDeviceParams( RenderDeviceParameterList* paramList = nullptr );
    ~RenderDeviceParams();

    RenderDeviceParameterList* GetParameters( ) const;
    void SetParameters( RenderDeviceParameterList* val );

    vector< String > GetParametersNames() const;
    vector< IStringableObject* > GetParamterValues( const String& parameterName ) const;

  private:
    RenderDeviceParameterList* m_Parameters;

  };
}

#endif // RenderDeviceParameters_h__
