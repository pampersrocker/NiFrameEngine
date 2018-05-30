#pragma once

// Startup
void InitializeThreadLocalStorage();
void InitializeStaticInitializers();

// Initialized state


// Shutdown
void ShutdownStaticInitializers();
void RunAtExitFunctions();
void ReleaseThreadLocalStorage();
