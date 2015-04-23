#pragma once
#ifndef NiFrameMacros_h__
#define NiFrameMacros_h__

#ifdef WIN32

#ifdef NIFRAME_DLL_BUILD
#define NIFRAME_DLL_EXPORT __declspec( dllexport )
#define NIFRAME_TPL_EXPORT
#else
#define NIFRAME_DLL_EXPORT __declspec( dllimport )
#define NIFRAME_TPL_EXPORT extern
#endif

#elif ORBIS

#define NIFRAME_DLL_EXPORT
#define NIFRAME_TPL_EXPORT

#endif

#ifdef WIN32
#define EXPORT_STL( tpl ) \
  namespace std{\
  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT tpl;\
  }


#define EXPORT_TPL( tpl ) \
  NIFRAME_TPL_EXPORT template class NIFRAME_DLL_EXPORT tpl;

#define TYPEDEF_EXPORT_REFCOUNT_PTR( tpl ) typedef ReferenceCounted< tpl > tpl ## Ptr; \
  EXPORT_TPL( ReferenceCounted< tpl > )
#elif ORBIS

#define EXPORT_STL( tpl ) \
  namespace std{\
  NIFRAME_TPL_EXPORT template NIFRAME_DLL_EXPORT tpl;\
        }


#define EXPORT_TPL( tpl ) \
  NIFRAME_TPL_EXPORT template NIFRAME_DLL_EXPORT tpl;

#define TYPEDEF_EXPORT_REFCOUNT_PTR( tpl ) typedef ReferenceCounted< tpl > tpl ## Ptr; \
  EXPORT_TPL( ReferenceCounted< tpl > )
#endif
#define SAFE_DELETE(pointer)  \
  if( pointer != nullptr )  \
  {              \
    delete pointer;      \
    pointer = nullptr;    \
  }

#endif // NiFrameMacros_h__
