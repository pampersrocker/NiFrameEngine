#include "NiFrameRendererPCH.h"
#include "NiFrameStringableBool.h"

NiFrame::StringableBool::StringableBool( bool value ) :
	m_Bool( value )
{

}

NiFrame::StringableBool::~StringableBool()
{

}


NiFrame::String NiFrame::StringableBool::ToString() const
{
	return std::to_string( m_Bool );
}

