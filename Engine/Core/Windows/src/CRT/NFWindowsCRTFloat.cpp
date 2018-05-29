
extern "C"
{
  int _fltused;
#if PLATFORM_X64

  _Check_return_ float __CRTDECL log10f(_In_ float _X)
  {
    return (float)log10(_X);
  }

  _Check_return_ float __CRTDECL logf(_In_ float _X)
  {
    return (float)log(_X);
  }

  _Check_return_ float __CRTDECL powf(_In_ float _X, _In_ float _Y)
  {
    return (float)pow(_X, _Y);
  }

  _Check_return_ float __CRTDECL sinf(_In_ float _X)
  {
    return (float)sin(_X);
  }

  _Check_return_ float __CRTDECL sinhf(_In_ float _X)
  {
    return (float)sinh(_X);
  }

  _Check_return_ float __CRTDECL sqrtf(_In_ float _X)
  {
    return (float)sqrt(_X);
  }

  _Check_return_ float __CRTDECL tanf(_In_ float _X)
  {
    return (float)tan(_X);
  }

  _Check_return_ float __CRTDECL tanhf(_In_ float _X)
  {
    return (float)tanh(_X);
  }

  _Check_return_ float __CRTDECL acosf(_In_ float _X)
  {
    return (float)acos(_X);
  }

  _Check_return_ float __CRTDECL asinf(_In_ float _X)
  {
    return (float)asin(_X);
  }

  _Check_return_ float __CRTDECL atan2f(_In_ float _Y, _In_ float _X)
  {
    return (float)atan2(_Y, _X);
  }

  _Check_return_ float __CRTDECL atanf(_In_ float _X)
  {
    return (float)atan(_X);
  }

  _Check_return_ float __CRTDECL ceilf(_In_ float _X)
  {
    return (float)ceil(_X);
  }

  _Check_return_ float __CRTDECL cosf(_In_ float _X)
  {
    return (float)cos(_X);
  }

  _Check_return_ float __CRTDECL coshf(_In_ float _X)
  {
    return (float)cosh(_X);
  }

  _Check_return_ float __CRTDECL expf(_In_ float _X)
  {
    return (float)exp(_X);
  }

#endif

}
