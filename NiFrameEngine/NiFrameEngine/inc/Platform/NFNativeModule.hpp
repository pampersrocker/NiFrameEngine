#pragma once

namespace nfe
{
  class NIFRAME_DLL_EXPORT INativeModule
  {
  public:

    virtual ~INativeModule() { }

    template <typename T>
    T* GetModuleFunctionPointer(const char* name );

    virtual const String& GetName() const = 0;

  protected:

    virtual void* GetNativeModuleFunctionPointer( const char* name ) = 0;

  private:

  };

  template <typename T>
  inline
  T* nfe::INativeModule::GetModuleFunctionPointer( const char* name )
  {
    return static_cast< T* >( GetNativeModuleFunctionPointer( name ) );
  }

}
