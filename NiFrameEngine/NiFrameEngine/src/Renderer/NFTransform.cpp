#include "NFEnginePCH.hpp"
#include "Renderer/NFTransform.hpp"

using namespace nfe;

void nfe::Transform::Rotation( const nfe::Rotator& val )
{
  m_Rotation = val;
}

const nfe::Rotator& nfe::Transform::Rotation() const
{
  return m_Rotation;
}

void nfe::Transform::Scale( const nfe::Vector3& val )
{
  m_Scale = val;
}

const nfe::Vector3& nfe::Transform::Scale() const
{
  return m_Scale;
}

void nfe::Transform::Position( const nfe::Vector3& val )
{
  m_Position = val;
}

const nfe::Vector3& nfe::Transform::Position() const
{
  return m_Position;
}

nfe::Transform::Transform( const Vector3& position /*= Vector3(0)*/, const Rotator& rotation /*= Rotator()*/, const Vector3& scale /*= Vector3( 0 ) */ ) :
m_Position(position),
m_Rotation(rotation),
m_Scale(scale)
{

}

nfe::Transform::~Transform()
{

}
