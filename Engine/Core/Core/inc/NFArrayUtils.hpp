#pragma once
#include "NFEnginePCH.hpp"
namespace nfe
{
  template <typename T, uint32 size>
  inline
  uint32 arraySize(T (& array)[size])
  {
    return size;
  }

}
