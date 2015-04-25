#include "stdafx.h"
#include "NFEnginePCH.hpp"
#include <Platform/NFPlatform.hpp>
#include <Platform/NFNativeModule.hpp>

class NIFRAMEWIN32PLATFORM_API NiFrameWin32Platform : public nfe::IPlatform
{
public:
	NiFrameWin32Platform(void);
  virtual ~NiFrameWin32Platform();

  virtual nfe::INativeModule* LoadModule( const char* modulePath ) override;

  virtual void ReleaseModule( nfe::INativeModule* module ) override;

};
