#include "NFEnginePCH.hpp"
#include "String/NFString.hpp"

nfe::String::String()
  : Data(nullptr)
{

}

nfe::String nfe::String::operator+(const String& Suffix)
{
  NF_ASSERT(0, "Not implemented");
  return String();
}

nfe::String nfe::String::operator+(const char* Suffix)
{
  NF_ASSERT(0, "Not implemented");
  return String();
}

bool nfe::String::operator==(const String& Other) const
{
  NF_ASSERT(0, "Not implemented");
  return false;
}

bool nfe::String::operator!=(const String& Other) const
{
  return !(*this == Other);
}

const TCHAR* nfe::String::operator*() const
{
  return Data;
}

nfe::String::~String()
{

}

nfe::String::String(const char* ConstString)
{

}

nfe::String nfe::operator+(const char* Prefix, const String& String)
{
  NF_ASSERT(0, "Not Implemented");
  return nfe::String();
}
