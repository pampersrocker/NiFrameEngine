#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class ISubsystem
  {
  public:

    inline ISubsystem() :
      object(nullptr),
      init(nullptr),
      release(nullptr),
      update(nullptr)
    { }

    inline ISubsystem( void* object,
      void( *init_func )( void* ),
      void( *release_func )( void* ),
      void( *update_func )( void*, Real ) ) :
      object( object ),
      init( init_func ),
      release( release_func ),
      update( update_func )
    {

    }

    inline ISubsystem( const ISubsystem& rhs ) :
      object( rhs.object ),
      init( rhs.init ),
      release( rhs.release ),
      update( rhs.update )
    {

    }
    inline ISubsystem& operator = ( const ISubsystem& rhs )
    {
      object = rhs.object;
      init = rhs.init;
      release = rhs.release;
      update = rhs.update;
      return *this;
    }

    inline bool operator ==( const ISubsystem& rhs ) const
    {
      return object == rhs.object;
    }
    inline bool operator !=( const ISubsystem& rhs ) const
    {
      return !(*this == rhs);
    }

    inline void Initialize()
    {
      NF_ASSERT( object != nullptr, "No Object defined!" );
      NF_ASSERT( init != nullptr, "No init defined!" );
      init( object );
    }
    inline void Release()
    {

      NF_ASSERT( object != nullptr, "No Object defined!" );
      NF_ASSERT( release != nullptr, "No release defined!" );
      release( object );
    }
    inline void Update( Real elapsedTime )
    {

      NF_ASSERT( object != nullptr, "No Object defined!" );
      NF_ASSERT( update != nullptr, "No update defined!" );
      update( object, elapsedTime );
    }

    void* object;
    void( *init )( void* );
    void( *release )( void* );
    void( *update )( void*, Real );
  };
}
