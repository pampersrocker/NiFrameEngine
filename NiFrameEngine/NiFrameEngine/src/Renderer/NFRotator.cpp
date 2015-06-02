#include "Renderer/NFRotator.hpp"


void nfe::Rotator::Yaw( const nfe::Radian& val )
{
  m_Yaw = val;
}

const nfe::Radian& nfe::Rotator::Yaw() const
{
  return m_Yaw;
}

void nfe::Rotator::Pitch( const nfe::Radian& val )
{
  m_Pitch = val;
}

const nfe::Radian& nfe::Rotator::Pitch() const
{
  return m_Pitch;
}

void nfe::Rotator::Roll( const nfe::Radian& val )
{
  m_Roll = val;
}

const nfe::Radian& nfe::Rotator::Roll() const
{
  return m_Roll;
}

nfe::Rotator::Rotator(
  const Radian& roll /*= Radian( 0 )*/, const Radian& pitch /*= Radian( 0 )*/, const Radian& yaw /*= Radian( 0 ) */ ) :
m_Roll(roll),
m_Pitch(pitch),
m_Yaw(yaw)
{
}

nfe::Rotator::~Rotator()
{

}

nfe::Vector3 nfe::Rotator::GetRadianVector() const
{
  return Vector3( m_Roll.AsRadianValue(), m_Pitch.AsRadianValue(), m_Yaw.AsRadianValue() );
}

nfe::Vector3 nfe::Rotator::GetDegreeVector() const
{
  return Vector3( m_Roll.AsDegreeValue(), m_Pitch.AsDegreeValue(), m_Yaw.AsDegreeValue() );
}
