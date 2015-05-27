#include "NFEnginePCH.hpp"
#include "IO/NFGamePad.hpp"

using namespace nfe;

const Vector<DigitalButtonState>& nfe::GamePad::DigitalButtonStates() const
{
  return m_DigitalButtonsState;
}

const Vector<float>& nfe::GamePad::OneDimensionalAxes() const
{
  return m_OneDimensionalAxes;
}

const Vector<Vector2>& nfe::GamePad::TwoDimensionalAxes() const
{
  return m_TwoDimensionalAxes;
}

nfe::GamePad::GamePad()
{

}

nfe::GamePad::~GamePad()
{

}

void nfe::GamePad::GetArrays( Vector<Vector2>** twoDim, Vector<float>** oneDim, Vector<DigitalButtonState>** buttons )
{
  *twoDim = &m_TwoDimensionalAxes;
  *oneDim = &m_OneDimensionalAxes;
  *buttons= &m_DigitalButtonsState;
}

GamePad& nfe::GamePad::operator=( const GamePad& rhs )
{
  m_TwoDimensionalAxes = rhs.m_TwoDimensionalAxes;
  m_OneDimensionalAxes = rhs.m_OneDimensionalAxes;
  m_DigitalButtonsState = rhs.m_DigitalButtonsState;
  return *this;
}
