
#include "stdafx.h"
#include "NFEngine.hpp"
#include "NFSTL/NFVector.hpp"
#include "catch.hpp"


using namespace nfe;

SCENARIO( "Vector initialization", "[vector][constructor]" )
{
  GIVEN( "Nothing" )
  {

    WHEN( "A Vector gets initialized as default" )
    {
      Vector<int> vector;
      THEN( "It should have a size of zero and a reservation of 2" )
      {
        REQUIRE( vector.Size() == 0 );
        REQUIRE( vector.ReservedSize() == 2 );
      }

      THEN( "The data should not be a nullptr" );
      {
        REQUIRE( vector.Data() != nullptr );
      }

      THEN("It should have the default allocator")
      {
        REQUIRE( vector.Allocator() == GetDefaultAllocator() );
      }
    }
  }
}
