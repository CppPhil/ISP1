@echo off

REM This script builds the project

REM Path to the build directory
set "BUILD_PATH=%~dp0%build"

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
    REM Delete the build directory if it exists.
    call :delete_directory_if_exists %BUILD_PATH%
    REM Create the build directory
    mkdir %BUILD_PATH%
    REM Go into the build directory
    cd %BUILD_PATH%
    REM Create the native build scripts
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%1 %~dp0
    REM Invoke the native build scripts
    mingw32-make
    REM Go back to the directory containing this script
    cd %~dp0
    REM Exit with success.
    EXIT /B 0

REM Function to delete a directory if it exists.
REM Make sure to use the call keyword to call this function!
:delete_directory_if_exists
    REM If the directory given exists, remove it.
    IF EXIST "%~1%" (
        rmdir /s /q "%~1%"
    )
    REM Return from this function with success.
    EXIT /B 0
