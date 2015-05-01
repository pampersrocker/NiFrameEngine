#include "NFEnginePCH.hpp"
#include "Renderer/NFResolution.hpp"

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

  Resolution::Resolution( uint32 width, uint32 height, uint32 refreshRate ) :
    m_Width( width ),
    m_Height( height ),
    m_RefreshRate( refreshRate )
  {
  }

  Resolution::Resolution()
  {

  }

  Resolution::Resolution( Resolution&& rhs ) :
    m_Width(rhs.m_Width),
    m_Height(rhs.m_Height),
    m_RefreshRate(rhs.m_RefreshRate)
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
