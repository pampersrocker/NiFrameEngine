#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class Pascal;
  class KgM2S2Mixin;
  class KgM2Mixin;
  class Acceleration;
  class Density;
  class Metre;
  class VolumeVelocity;
  class Seconds;
  class M3_S2Mixin;
  class SquareMetre;
  class Volume;

#define FRIEND_SI\
  friend class Pascal;\
  friend class KgM2S2Mixin;\
  friend class KgM2Mixin;\
  friend class Acceleration;\
  friend class Density;\
  friend class Metre;\
  friend class VolumeVelocity;\
  friend class Seconds;\
  friend class M3_S2Mixin;\
  friend class SquareMetre;\
  friend class Volume

}

#include "NFSIMetre.hpp"
#include "NFSIPascal.hpp"
#include "NFSIDensity.hpp"
#include "NFSIAcceleration.hpp"
#include "NFSISeconds.hpp"
#include "NFSIVolumeVelocity.hpp"
#include "NFSIKgM2Mixin.hpp"
#include "NFSIKgM2S2Mixin.hpp"
#include "NFSISquareMetre.hpp"
#include "NFSIM3_S2Mixin.hpp"
#include "NFSIVolume.hpp"

#include "NFSIMetre.inl"
#include "NFSIPascal.inl"
#include "NFSIDensity.inl"
#include "NFSIAcceleration.inl"
#include "NFSISeconds.inl"
#include "NFSIVolumeVelocity.inl"
#include "NFSIKgM2Mixin.inl"
#include "NFSIKgM2S2Mixin.inl"
#include "NFSISquareMetre.inl"
#include "NFSIM3_S2Mixin.inl"
#include "NFSIVolume.inl"
