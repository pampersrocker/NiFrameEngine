#include "NFWindowsPCH.hpp"
#include "NFWindowsPlatform.hpp"

void __cdecl
_invalid_parameter(
  _In_opt_z_ wchar_t const* const expression,
  _In_opt_z_ wchar_t const* const function_name,
  _In_opt_z_ wchar_t const* const file_name,
  _In_ unsigned int   const line_number,
  _In_ uintptr_t      const reserved)
{
#if DEBUG
  nfe::NFPlatform::DebugBreak();
#endif
}

extern "C" void __cdecl
_invalid_parameter_noinfo(void)
{
#if DEBUG
  nfe::NFPlatform::DebugBreak();
#endif

}

extern "C" __declspec(noreturn) void __cdecl
_invalid_parameter_noinfo_noreturn(void)
{
  nfe::NFPlatform::Assert(false, "Invalid parameter detected");
}

extern "C" __declspec(noreturn) void __cdecl
_invoke_watson(
  _In_opt_z_ wchar_t const* const expression,
  _In_opt_z_ wchar_t const* const function_name,
  _In_opt_z_ wchar_t const* const file_name,
  _In_ unsigned int   const line_number,
  _In_ uintptr_t      const reserved)
{
  nfe::NFPlatform::Assert(false, "Invalid parameter detected");
}
