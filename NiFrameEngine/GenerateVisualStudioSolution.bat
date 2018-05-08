@echo off
set scriptpath=%~dp0

echo Generating Visual Studio Solution....

call "%scriptpath%Build\ThirdParty\FindMSVC15Path.bat"


call "%scriptpath%Build\ThirdParty\FBuild.exe" solution

echo Done

pause