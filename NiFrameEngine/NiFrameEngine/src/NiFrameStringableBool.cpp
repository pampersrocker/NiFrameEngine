#include "NiFrameEnginePCH.hpp"
#include "NiFrameStringableBool.hpp"

NiFrame::StringableBool::StringableBool( bool value ) :
	m_Bool( value )
{

}

NiFrame::StringableBool::~StringableBool()
{

}


NiFrame::String NiFrame::StringableBool::ToString() const
{
	return m_Bool ? "Yes" : "No";
}

bool NiFrame::StringableBool::GetBool() const
{
	return m_Bool;
}

