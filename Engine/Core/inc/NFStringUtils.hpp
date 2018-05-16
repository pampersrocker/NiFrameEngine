#pragma once
#ifndef StringUtils_h__
#define StringUtils_h__

#include "NFEnginePCH.hpp"
#include "Utils/NFRational.hpp"

namespace nfe
{

  class StringUtils
  {
  public:


    static String ToString( unsigned int );
    static String ToString( int );
    static String ToString( Real );
    static String ToString( const Rational& );

  private:

    StringUtils() {}
    ~StringUtils() {}

  };

}

#endif // StringUtils_h__
