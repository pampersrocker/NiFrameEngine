#pragma once
#include "NFPrerequisites.hpp"

namespace nfe
{
  class IAllocator;
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
    new (ptr) T( allocator, arguments... );
  }

  template<typename T, typename ...Args>
  inline
    void construct_( T* ptr, IAllocator* allocator, std::false_type*, Args...arguments )
  {
    new (ptr) T(arguments...);
  }


  /**
  @brief Checks if Type T is constructible with an allocator as its first parameter at compile time.

  If so pass the allocator given to construct the object itself to the objects constructor
  If thats not the case check if its possible to construct the object with the given parameters, otherwise a static_assert will fail.

  @param ptr The pointer to construct (placement new)
  @param allocator The allocator which should be passed to the object if possible
  @param arguments Other optional arguments for the constructor

  */
  template<typename T, typename ...Args>
  inline
    void constructWithAllocatorIfPossible( T* ptr, IAllocator* allocator, Args...arguments )
  {
    static_assert( std::is_constructible<T, Args...>::value || std::is_constructible<T, IAllocator*, Args...>::value,
      "A type of T can not constructed with the given arguments, with or without allocator" );
    construct_( ptr, allocator,
      static_cast< typename std::conditional <
      std::is_constructible< T, IAllocator*, Args...>::value, typename std::true_type, std::false_type>::type* >( nullptr ),
      arguments... );
  }

  /**
  @brief If type T is a pointer itself just initialize it with null
  */
  template<typename T, typename ...Args>
  inline
    void constructWithAllocatorIfPossible( T** ptr, IAllocator* allocator, Args...arguments )
  {
    *ptr = nullptr;
  }

}
