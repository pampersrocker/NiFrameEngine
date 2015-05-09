
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

      THEN( "The data should not be a nullptr" )
      {
        REQUIRE( vector.Data() != nullptr );
      }

      THEN( "It should have the default allocator" )
      {
        REQUIRE( vector.Allocator() == GetDefaultAllocator() );
      }
    }

    WHEN( "A vector gets initialized with a reserved size" )
    {
      Vector<int> vec( 10 );
      THEN( "It should have this size reserved without any elements" )
      {
        REQUIRE( vec.ReservedSize() == 10 );
        REQUIRE( vec.Size() == 0 );
        REQUIRE( vec.Data() != nullptr );
      }
    }
  }
}

SCENARIO("Vector insertion", "[vector]")
{
  GIVEN("An empty default constructed vector")
  {
    Vector<int> vec;
    WHEN("Adding an element to it")
    {
      vec.Add( 1 );
      THEN( "Its size should have increased but not its reserved size" )
      {
        REQUIRE( vec.Size() == 1 );
        REQUIRE( vec.ReservedSize() == 2 );
      }

      THEN( "Its first value should be the added value" )
      {
        REQUIRE( vec[ 0 ] == 1 );
      }
    }

    WHEN("Adding two values to the vector")
    {
      vec.Add( 1 );
      vec.Add( 2 );
      THEN( "Its size should be 2 as well as its reserved Size" )
      {
        REQUIRE( vec.Size() == 2 );
        REQUIRE( vec.ReservedSize() == 2 );
        REQUIRE( vec.Data() != nullptr );
      }

      THEN("Its first value should be unchanged")
      {
        REQUIRE( vec[ 0 ] == 1 );
      }
      THEN("Its second value should be set")
      {
        REQUIRE( vec[ 1 ] == 2 );
      }
    }

    WHEN("Adding a third value to the vector")
    {
      vec.Add( 1 );
      vec.Add( 2 );
      vec.Add( 3 );
      THEN("Its Size should be 3, and the Reserved Size should be doubled")
      {
        REQUIRE(vec.Size() == 3);
        REQUIRE( vec.ReservedSize() == 4 );
      }

      THEN( "The first two values should be unchanged" )
      {
        REQUIRE( vec[ 0 ] == 1 );
        REQUIRE( vec[ 1 ] == 2 );
      }

      THEN("The third value should be set")
      {
        REQUIRE( vec[ 2 ] == 3 );
      }

    }
  }

  GIVEN("A vector with 5 elements")
  {
    Vector<int> vec( 5 );
    for( uint64 i = 0; i < 5; i++ )
    {
      vec.Add( static_cast<int>(i) );
    }

    for( uint64 i = 0; i < vec.Size(); i++ )
    {
      REQUIRE( vec[ i ] == i );
    }

    WHEN("Inserting a value at the first position")
    {
      vec.Insert( 0, -1 );

      THEN("The size of the vector should be changed")
      {
        REQUIRE( vec.Size() == 6 );
      }

      THEN("It should be at the first position")
      {
        REQUIRE( vec[ 0 ] == -1 );
      }

      THEN("All other elements should be offset by one")
      {
        for( uint64 i = 0; i < vec.Size() -1; i++ )
        {
          REQUIRE( vec[ i + 1 ] == i );
        }
      }
    }

  }
}
