@echo off
REM Build script for Maze Generator on Windows

echo.
echo =================================
echo Maze Generator - Build Script
echo =================================
echo.

REM Check for available compilers
where /q g++
if %ERRORLEVEL% EQU 0 (
    echo Found g++ compiler
    echo Compiling with g++...
    g++ -std=c++17 -Wall -Wextra -O2 -o maze_generator.exe main.cpp Cell.cpp Maze.cpp MazeGenerator.cpp MazeSolver.cpp MazeRenderer.cpp
    if %ERRORLEVEL% EQU 0 (
        echo Build successful!
        echo.
        echo Run with: maze_generator.exe
    ) else (
        echo Build failed!
    )
    goto end
)

where /q clang++
if %ERRORLEVEL% EQU 0 (
    echo Found clang++ compiler
    echo Compiling with clang++...
    clang++ -std=c++17 -Wall -Wextra -O2 -o maze_generator.exe main.cpp Cell.cpp Maze.cpp MazeGenerator.cpp MazeSolver.cpp MazeRenderer.cpp
    if %ERRORLEVEL% EQU 0 (
        echo Build successful!
        echo.
        echo Run with: maze_generator.exe
    ) else (
        echo Build failed!
    )
    goto end
)

where /q cl.exe
if %ERRORLEVEL% EQU 0 (
    echo Found MSVC compiler (cl.exe)
    echo Compiling with MSVC...
    cl.exe /std:c++17 /W4 /O2 /EHsc main.cpp Cell.cpp Maze.cpp MazeGenerator.cpp MazeSolver.cpp MazeRenderer.cpp /Fe:maze_generator.exe
    if %ERRORLEVEL% EQU 0 (
        echo Build successful!
        echo.
        echo Run with: maze_generator.exe
    ) else (
        echo Build failed!
    )
    goto end
)

echo.
echo ERROR: No C++ compiler found!
echo.
echo Please install one of the following:
echo - MinGW (g++): https://www.mingw-w64.org/
echo - LLVM/Clang: https://releases.llvm.org/
echo - Microsoft Visual Studio or Visual Studio Build Tools
echo.

:end
echo.
