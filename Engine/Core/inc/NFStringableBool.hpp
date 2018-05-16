#pragma once
#include "NFEnginePCH.hpp"
#include "NFStringableObject.hpp"
#ifndef FullScreen_h__
#define FullScreen_h__

namespace nfe
{
  class NIFRAME_API StringableBool : public IStringableObject
  {
  public:
    StringableBool( bool value );
    ~StringableBool();

    virtual String ToString() const;
    bool GetBool( ) const;

  private:

    bool m_Bool;


  };
}

#endif // FullScreen_h__
