@echo off

REM This script build the project and then runs the generated executable

REM Path to the build directory
set "BUILD_PATH=%~dp0%build"

REM Path to the build.bat file
set "BUILD_BAT_PATH=%~dp0%build.bat"

REM Path to the resulting executable
set "EXE_PATH=%BUILD_PATH%\isp1.exe"

REM If the command line argument wasn't set or was empty.
REM That's an error.
If "%~1"=="" goto ERROR

REM "Debug" is acceptable.
If "%~1"=="Debug" (
    goto OK
)

REM "Release" is acceptable.
If "%~1"=="Release" (
    goto OK
)

REM Anything not "Debug" or "Release" is not acceptable
goto ERROR

REM Label to handle invalid input.
:ERROR
    echo "Invalid command line arguments. You must pass Debug or Release."
    EXIT /B 1

REM Label to handle valid input.
:OK
    REM call the build script
    call %BUILD_BAT_PATH% %1

    REM run the .exe
    %EXE_PATH%

    REM Exit with success.
    EXIT /B 0
