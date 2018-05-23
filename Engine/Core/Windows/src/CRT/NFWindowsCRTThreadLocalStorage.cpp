#include "NFWindowsPCH.hpp"

#pragma section(".CRT$XLA",    long, read) // First Loader TLS Callback
#pragma section(".CRT$XLC",    long, read) // CRT TLS Constructor
#pragma section(".CRT$XLD",    long, read) // CRT TLS Terminator
#pragma section(".CRT$XLZ",    long, read) // Last Loader TLS Callback

#pragma section(".rdata$T",    long, read)

extern "C" {

  /* Thread Local Storage index for this .EXE or .DLL */

  ULONG _tls_index = 0;

  /* Special symbols to mark start and end of Thread Local Storage area. */

#pragma data_seg(".tls")

#if defined (_M_X64)
  CRTALLOCATION(".tls")
#endif  /* defined (_M_X64) */
    char _tls_start = 0;

#pragma data_seg(".tls$ZZZ")

#if defined (_M_X64)
  CRTALLOCATION(".tls$ZZZ")
#endif  /* defined (_M_X64) */
    char _tls_end = 0;

#pragma data_seg()

  /* Start section for TLS callback array examined by the OS loader code.
  * If dynamic TLS initialization is used, then a pointer to __dyn_tls_init
  * will be placed in .CRT$XLC by inclusion of tlsdyn.obj.  This will cause
  * the .CRT$XD? array of individual TLS variable initialization callbacks
  * to be walked.
  */

  CRTALLOCATION(".CRT$XLA") PIMAGE_TLS_CALLBACK __xl_a = 0;

  /* NULL terminator for TLS callback array.  This symbol, __xl_z, is never
  * actually referenced anywhere, but it must remain.  The OS loader code
  * walks the TLS callback array until it finds a NULL pointer, so this makes
  * sure the array is properly terminated.
  */

  CRTALLOCATION(".CRT$XLZ") PIMAGE_TLS_CALLBACK __xl_z = 0;

#ifdef _WIN64

  CRTALLOCATION(".rdata$T")
    extern const IMAGE_TLS_DIRECTORY64 _tls_used =
  {
    (ULONGLONG)&_tls_start,        // start of tls data
    (ULONGLONG)&_tls_end,          // end of tls data
    (ULONGLONG)&_tls_index,        // address of tls_index
    (ULONGLONG)(&__xl_a + 1),        // pointer to call back array
    (ULONG)0,                      // size of tls zero fill
    (ULONG)0                       // characteristics
  };

#else  /* _WIN64 */

  CRTALLOCATION(".rdata$T")
    extern const IMAGE_TLS_DIRECTORY _tls_used =
  {
    (ULONG)(ULONG_PTR)&_tls_start, // start of tls data
    (ULONG)(ULONG_PTR)&_tls_end,   // end of tls data
    (ULONG)(ULONG_PTR)&_tls_index, // address of tls_index
    (ULONG)(ULONG_PTR)(&__xl_a + 1), // pointer to call back array
    (ULONG)0,                      // size of tls zero fill
    (ULONG)0                       // characteristics
  };

#endif  /* _WIN64 */

} // extern "C"


CRITICAL_SECTION ThreadLocalStorageMutex;
CONDITION_VARIABLE ThreadLocalStorageConditionVariable;

const int Uninitialized = 0;
const int CurrentlyInitializing = -1;
const int EpochStart = (-2147483647 - 1);

extern "C"
{
  int GlobalEpoch = EpochStart;
  // The linker requires this to be named exactly like this
  __declspec(thread) int _Init_thread_epoch = EpochStart;


  void __cdecl _Init_thread_header(int* const pOnce) noexcept
  {
    EnterCriticalSection(&ThreadLocalStorageMutex);

    // Check if we are the first to enter and no one else is currently initializing static function variable
    if (*pOnce == Uninitialized)
    {
      *pOnce = CurrentlyInitializing;
    }
    // If not...
    else
    {
      // ... wait for the initialization to complete
      while (*pOnce == CurrentlyInitializing)
      {
        SleepConditionVariableCS(&ThreadLocalStorageConditionVariable, &ThreadLocalStorageMutex, INFINITE);
        // If still uninitialized, we can continue, otherwise someone else has initialized it, and we are done
        if (*pOnce == Uninitialized)
        {
          LeaveCriticalSection(&ThreadLocalStorageMutex);
          return;
        }
      }
      _Init_thread_epoch = GlobalEpoch;
    }
    LeaveCriticalSection(&ThreadLocalStorageMutex);
  }

  extern "C" void __cdecl _Init_thread_footer(int* const pOnce) noexcept
  {
    EnterCriticalSection(&ThreadLocalStorageMutex);
    ++GlobalEpoch;
    // Mark as initialization being complete
    *pOnce = GlobalEpoch;
    _Init_thread_epoch = GlobalEpoch;
    LeaveCriticalSection(&ThreadLocalStorageMutex);
    // We are done, notify all waiting threads, they can continue to initialize their variables
    WakeAllConditionVariable(&ThreadLocalStorageConditionVariable);
  }
}


void InitializeThreadLocalStorage()
{
  InitializeCriticalSectionEx(&ThreadLocalStorageMutex, 4000, 0);
  InitializeConditionVariable(&ThreadLocalStorageConditionVariable);
}

void ReleaseThreadLocalStorage()
{
  DeleteCriticalSection(&ThreadLocalStorageMutex);
  // Condition variables are not destroyed/uninitialized
}
