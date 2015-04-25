#include "NFEnginePCH.hpp"
#include "Platform/NFPlatformManager.hpp"
#include <Platform/NFPlatform.hpp>

using namespace nfe;



IPlatform* PlatformManager::m_Platform = nullptr;


IPlatform* nfe::PlatformManager::GetPlatform()
{
  return m_Platform;
}

void nfe::PlatformManager::SetPlatform( IPlatform* platform )
{
  m_Platform = platform;
  nfe::GPlatform = m_Platform;
}
