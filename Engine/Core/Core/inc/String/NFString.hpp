#pragma once

namespace nfe
{
  class NIFRAME_API String
  {
  public:
    String();
    ~String();

    String(const char* ConstString);

    const TCHAR* operator *() const;
    bool operator ==(const String& Other) const;
    bool operator !=(const String& Other) const;
    String operator +(const char* Suffix);
    String operator +(const String& Suffix);


  private:

    const TCHAR* Data;
  };

  String operator +(const char* Prefix, const String& String);

}


