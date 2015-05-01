#include "stdafx.h"
#include "NFEnginePCH.hpp"
#include <Platform/NFPlatform.hpp>
#include <Platform/NFNativeModule.hpp>

#define NF_ASSERT_HR( result ) NF_ASSERT( result == S_OK, "Win32 Result was not S_OK!" )

class NIFRAMEWIN32PLATFORM_API NiFrameWin32Platform : public nfe::IPlatform
{
public:
	NiFrameWin32Platform(void);
  virtual ~NiFrameWin32Platform();

  virtual nfe::INativeModule* LoadModule( const char* modulePath ) override;

  virtual void ReleaseModule( nfe::INativeModule* module ) override;

};
