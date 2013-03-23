#include "NiFrameEnginePCH.h"
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

bool NiFrame::StringableBool::GetBool() const
{
	return m_Bool;
}

