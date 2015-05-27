#pragma once
#include "NFEnginePCH.hpp"
#include "NFSTL/NFVector.hpp"

namespace nfe
{
  struct NIFRAME_DLL_EXPORT DigitalButtonState
  {
    /* Is the button currently pressed ?*/
    bool Down;
    /* Is the button being pushed down in this frame ?*/
    bool Pressed;
    /* Is the button being released this frame ?*/
    bool Released;
  };

  class NIFRAME_DLL_EXPORT GamePad
  {
  public:
    GamePad();
    ~GamePad();

    GamePad& operator = ( const GamePad& rhs );

    const Vector<Vector2>& TwoDimensionalAxes() const;
    const Vector<float>& OneDimensionalAxes() const;
    const Vector<DigitalButtonState>& DigitalButtonStates() const;

    void GetArrays( Vector<Vector2>** twoDim, Vector<float>** oneDim, Vector<DigitalButtonState>** buttons );
  private:
    Vector<Vector2> m_TwoDimensionalAxes;
    Vector<float> m_OneDimensionalAxes;
    Vector<DigitalButtonState> m_DigitalButtonsState;
  };
}
