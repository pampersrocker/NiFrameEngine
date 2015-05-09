#pragma once
#include "NFEnginePCH.hpp"
#include <utility>
#include <tuple>

namespace nfe
{

  template<class F>
  struct function_traits;

  // function pointer
  template<class R, class... Args>
  struct function_traits<R( *)( Args... )> : public function_traits < R( Args... ) >
  {};

  template<class R, class... Args>
  struct function_traits < R( Args... ) >
  {
    using return_type = R;

    static const uint64 arity = sizeof...( Args );

    template <uint64 N>
    struct argument
    {
      static_assert( N < arity, "error: invalid parameter index." );
      using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
      using isConst = std::is_const < type > ;
      using isPointer = std::is_pointer < type > ;
      using isReference = std::is_reference< type > ;
    };
  };

  // member function pointer
  template<class C, class R, class... Args>
  struct function_traits<R( C::* )( Args... )> : public function_traits < R( C&, Args... ) >
  {};

  // const member function pointer
  template<class C, class R, class... Args>
  struct function_traits<R( C::* )( Args... ) const> : public function_traits < R( C&, Args... ) >
  {};

  // member object pointer
  template<class C, class R>
  struct function_traits<R( C::* )> : public function_traits < R( C& ) >
  {};

  template<typename T, typename ...Args>
  inline
    void construct_( T* ptr, IAllocator* allocator, std::true_type*, Args...arguments )
  {
    *ptr = T( allocator, arguments... );
  }

  template<typename T, typename ...Args>
  inline
    void construct_( T* ptr, IAllocator* allocator, std::false_type*, Args...arguments )
  {
    *ptr = T(arguments...);
  }

  template<typename T, typename ...Args>
  inline
    void constructWithAllocatorIfPossible( T* ptr, IAllocator* allocator, Args...arguments )
  {
    static_assert( std::is_constructible<T, Args...>::value,
      "A type of T can not constructed with the given arguments, with or without allocator" );
    construct_( ptr, allocator,
      static_cast< std::conditional <
      std::is_constructible<T, IAllocator, Args...>::value, std::true_type, std::false_type>::type* >( nullptr ),
      arguments... );
  }

}
