@echo off
REM Batch file for building AUTOSAR ComStack Project
REM This script provides an easy way to build, clean, and run the project on Windows

REM Set console to UTF-8 encoding
chcp 65001 >nul
setlocal enabledelayedexpansion

REM Configuration
set TARGET=ComStack.exe
set BUILD_DIR=build
set CC=gcc
set CFLAGS=-Wall -Wextra -std=c99 -g -O2

REM Source files - Auto detect all .c files
set SOURCES=
for %%f in (*.c) do (
    set SOURCES=!SOURCES! %%f
)

REM Check if gcc is available
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: gcc compiler not found in PATH
    echo Please install MinGW-w64 or add gcc to your PATH
    pause
    exit /b 1
)

REM Parse command line arguments
if "%1"=="" goto :build
if "%1"=="clean" goto :clean
if "%1"=="run" goto :run
if "%1"=="rebuild" goto :rebuild
if "%1"=="help" goto :help
goto :build

:build
echo Building AUTOSAR ComStack Project...
echo.

REM Create build directory
if not exist "%BUILD_DIR%" (
    echo Creating build directory...
    mkdir "%BUILD_DIR%"
)

REM Compile source files
echo Compiling source files...
set OBJECTS=
for %%f in (%SOURCES%) do (
    echo   Compiling %%f...
    %CC% %CFLAGS% -c %%f -o "%BUILD_DIR%\%%~nf.o"
    if !errorlevel! neq 0 (
        echo ERROR: Failed to compile %%f
        pause
        exit /b 1
    )
    set OBJECTS=!OBJECTS! "%BUILD_DIR%\%%~nf.o"
)

REM Link object files
echo.
echo Linking %TARGET%...
%CC% %OBJECTS% -o %TARGET%
if %errorlevel% neq 0 (
    echo ERROR: Failed to link %TARGET%
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo Executable: %TARGET%
goto :end

:clean
echo Cleaning build artifacts...
if exist "%BUILD_DIR%" (
    echo Removing build directory...
    rmdir /s /q "%BUILD_DIR%"
)
if exist "%TARGET%" (
    echo Removing %TARGET%...
    del "%TARGET%"
)
echo Clean completed!
goto :end

:run
call :build
if %errorlevel% neq 0 goto :end
echo.
echo Running %TARGET%...
echo.
%TARGET%
goto :end

:rebuild
call :clean
call :build
goto :end

:help
echo AUTOSAR ComStack Build Script
echo.
echo Usage: build.bat [option]
echo.
echo Options:
echo   (no option)  - Build the project
echo   clean        - Remove all build artifacts
echo   run          - Build and run the program
echo   rebuild      - Clean and build
echo   help         - Show this help message
echo.
echo Examples:
echo   build.bat
echo   build.bat clean
echo   build.bat run
echo   build.bat rebuild
goto :end

:end
endlocal
