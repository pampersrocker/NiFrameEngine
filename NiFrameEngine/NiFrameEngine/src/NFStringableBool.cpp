#include "NFEnginePCH.hpp"
#include "NFStringableBool.hpp"

nfe::StringableBool::StringableBool( bool value ) :
  m_Bool( value )
{

}

nfe::StringableBool::~StringableBool()
{

}


nfe::String nfe::StringableBool::ToString() const
{
  return m_Bool ? "Yes" : "No";
}

bool nfe::StringableBool::GetBool() const
{
  return m_Bool;
}

