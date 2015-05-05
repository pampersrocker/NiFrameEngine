#pragma once
#include "NFEnginePCH.hpp"

namespace nfe
{

  class NIFRAME_DLL_EXPORT Rational
  {
  public:
    Rational();
    Rational( int32 nominator, int32 denominator );
    ~Rational();
    nfe::int32 GetNominator() const;
    void SetNominator( nfe::int32 val );
    nfe::int32 GetDenominator() const;
    void SetDenominator( nfe::int32 val );

    Real AsReal() const;

  private:

    int32 m_Nominator;
    int32 m_Denominator;
  };

}
