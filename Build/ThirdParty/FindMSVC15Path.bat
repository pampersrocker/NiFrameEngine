@echo off

set MSVCScriptPath=%~dp0
for /f "usebackq tokens=1* delims=" %%i in (`%MSVCScriptPath%vswhere.exe -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
	set VS2017DIR=%%i
)
set /p VCTOOLSVERSION=<"%VS2017DIR%\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt"

set MSVC15DIRX64=%VS2017DIR%\VC\Tools\MSVC\%VCTOOLSVERSION%\bin\HostX64\x64
set MSVC15DIRX86=%VS2017DIR%\VC\Tools\MSVC\%VCTOOLSVERSION%\bin\HostX86\x86
set MSVC15VCDIR=%VS2017DIR%\VC\Tools\MSVC\%VCTOOLSVERSION%
set WINDOWSSDKDIR=%ProgramFiles(x86)%\Windows Kits\8.1\
