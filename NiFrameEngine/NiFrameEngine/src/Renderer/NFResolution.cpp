#include "NFEnginePCH.hpp"
#include "NFResolution.hpp"

namespace nfe
{
  nfe::String Resolution::ToString() const
  {
    return StringUtils::ToString( m_Width )
         + "x"
         + StringUtils::ToString( m_Height )
         + " @ "
         + StringUtils::ToString( m_RefreshRate )
         + "Hz";
  }

  Resolution::Resolution( uint32 wdith, uint32 height, uint32 refreshRate ) :
    m_Width( wdith ),
    m_Height( height ),
    m_RefreshRate( refreshRate )
  {
  }

  Resolution::~Resolution()
  {
  }

  nfe::uint32 Resolution::GetWidth( void ) const
  {
    return m_Width;
  }

  nfe::uint32 Resolution::GetHeight( void ) const
  {
    return m_Height;
  }

  nfe::uint32 Resolution::GetRefreshRate( void ) const
  {
    return m_RefreshRate;
  }
}
