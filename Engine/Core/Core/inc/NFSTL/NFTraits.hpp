#pragma once
#include "NFPrerequisites.hpp"
namespace nfe
{
  class IAllocator;
  template<class F>
  struct function_traits;

  template<class ...Types>
  class tuple;

  template<>
  class tuple<>
  {
    //Empty version
  };

  template<class ThisType, class... Others>
  class tuple<ThisType, Others...> :
    private tuple<Others...>
  {

  };

  template< NFSize I, class T >
  struct tuple_element;

  // recursive case
  template< NFSize I, class Head, class... Tail >
  struct tuple_element<I, tuple<Head, Tail...>>
    : tuple_element<I - 1, tuple<Tail...>> { };

  // base case
  template< class Head, class... Tail >
  struct tuple_element<0, tuple<Head, Tail...>> {
    typedef Head type;
  };

  template <class T, T Constant>
  struct IntegralConstant
  {
    static constexpr T value = Constant;
    using type = IntegralConstant;
  };

  template<bool Constant>
  using BoolConstant = IntegralConstant<bool, Constant>;

  using FalseType = BoolConstant<false>;
  using TrueType = BoolConstant<true>;

  template<bool Condition,
    class TypeIfTrue,
    class TypeIfFalse>
    struct Conditional
  {
    using Type = TypeIfFalse;
  };

  template<
    class TypeIfTrue,
    class TypeIfFalse>
    struct Conditional<true, TypeIfTrue, TypeIfFalse>
  {
    using Type = TypeIfTrue;
  };

  template<class T>
  struct IsConst
    : FalseType
  {	
  };

  template<class T>
  struct IsConst<const T>
    : TrueType
  {	
  };

  template<class T>
  struct IsPointer
    : FalseType
  {
  };

  template<class T>
  struct IsPointer<T*>
    : TrueType
  {
  };

  template<class T>
  struct IsReference
    : FalseType
  {
  };

  template<class T>
  struct IsReference<T&>
    : TrueType
  {
  };

#if PLATFORM_WINDOWS
  template<class T, class ...ConstructorArguments>
  struct IsConstructible :
    BoolConstant<__is_constructible(T, ConstructorArguments...)>
  {};

  template<class To,
    class From>
    struct IsAssignable
    : BoolConstant<__is_assignable(To, From)>
  {	
  };
#else
#error "Need platform template implementation"
#endif


  template<class... _Types>
  using void_t = void;

  template<class T,
    class = void>
    struct AddReference
  {
    using Lvalue = T;
    using Rvalue = T;
  };


  template<class T>
  struct AddReference<T, void_t<T&>>
  {
    using Lvalue = T&;
    using Rvalue = T&&;
  };

  template<class T>
  struct AddLValueReference
  {
    using type = typename AddReference<T>::Lvalue;
  };

  template<class T>
  using AddLValueReferenceType = typename AddLValueReference<T>::type;

  template<class T>
  struct AddRValueReference
  {
    using type = typename AddReference<T>::Rvalue;
  };

  template<class T>
  using AddRValueReferenceType = typename AddRValueReference<T>::type;


  template<class T>
  struct IsCopyAssignable
    : IsAssignable<
    AddLValueReferenceType<T>,
    AddLValueReferenceType<const T>
    >::type
  {	
  };



  // function pointer
  template<class R, class ...Args>
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
      using type = typename tuple_element<N, tuple<Args...>>::type;
      using isConst = IsConst < type > ;
      using isPointer = IsPointer < type > ;
      using isReference = IsReference< type > ;
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
    void construct_( T* ptr, IAllocator* allocator, TrueType*, Args...arguments )
  {
    new (ptr) T( allocator, arguments... );
  }

  template<typename T, typename ...Args>
  inline
    void construct_( T* ptr, IAllocator* allocator, FalseType*, Args...arguments )
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
    static_assert( IsConstructible<T, Args...>::value || IsConstructible<T, IAllocator*, Args...>::value,
      "A type of T can not constructed with the given arguments, with or without allocator" );
    construct_( ptr, allocator,
      static_cast< typename Conditional <
      IsConstructible< T, IAllocator*, Args...>::value, TrueType, FalseType>::Type* >( nullptr ),
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
