#pragma once
#ifndef NiFrameMacros_h__
#define NiFrameMacros_h__

#if !defined(WIN32) && !defined(ORBIS)
#error "No Platform defined"
#endif

#ifdef WIN32

#ifdef NIFRAME_DLL_BUILD
#define NIFRAME_API __declspec( dllexport )
#define NIFRAME_TPL_EXPORT
#else
#define NIFRAME_API __declspec( dllimport )
#define NIFRAME_TPL_EXPORT extern
#endif

#elif ORBIS


#ifdef NIFRAME_DLL_BUILD
#define NIFRAME_API __declspec( dllexport )
#define NIFRAME_TPL_EXPORT
#else
#define NIFRAME_API __declspec( dllimport )
#define NIFRAME_TPL_EXPORT extern
#endif
#endif
#ifndef _DEBUG
#if defined(_MSC_VER)
#define NF_FORCE_INLINE inline __forceinline
#elif defined(__clang__)
#define NF_FORCE_INLINE inline __attribute__( ( always_inline ) )
#endif
#else
#define NF_FORCE_INLINE inline
#endif

#ifdef WIN32
#define EXPORT_STL( tpl ) \
  namespace std{\
  NIFRAME_TPL_EXPORT template class NIFRAME_API tpl;\
  }


#define EXPORT_TPL( tpl ) \
  NIFRAME_TPL_EXPORT template class NIFRAME_API tpl;

#define TYPEDEF_EXPORT_REFCOUNT_PTR( tpl ) typedef nfe::ReferenceCounted< tpl> tpl ## Ptr; \
  EXPORT_TPL( nfe::ReferenceCounted< tpl > )
#elif ORBIS

#define EXPORT_STL( tpl ) \
  namespace std{\
  NIFRAME_TPL_EXPORT template NIFRAME_API tpl;\
        }


#define EXPORT_TPL( tpl ) \
  NIFRAME_TPL_EXPORT template class NIFRAME_API tpl;

#define TYPEDEF_EXPORT_REFCOUNT_PTR( tpl ) typedef ReferenceCounted< tpl > tpl ## Ptr; \
  EXPORT_TPL( ReferenceCounted< tpl > )
#endif
#define SAFE_DELETE(pointer)  \
  if( pointer != nullptr )  \
  {              \
    delete pointer;      \
    pointer = nullptr;    \
  }
#ifdef _DEBUG
#define NF_ASSERT(assertion, msg) do{if(GPlatform!= nullptr){GPlatform->Assert( assertion, msg );}else{assert(assertion&& msg);}}while(0)
#else
#define NF_ASSERT(assertion, msg) (void*)0
#endif
#endif // NiFrameMacros_h__
