# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Architecture Overview

This is a containerized C++ development environment specifically designed for AtCoder competitive programming. The architecture uses Docker for consistent cross-platform environments, VSCode for development workflow, and Node.js for orchestration.

### Key Architectural Components
- **Containerized Build System**: Docker environment with Ubuntu 22.04, GCC/G++, and MinGW64 for cross-compilation
- **Structured Source Organization**: `src/` directory for source files, `scripts/` for utilities, `output/` for binaries
- **VSCode Integration**: Complete build/run/debug workflow through F5 key and task system
- **Code Quality Enforcement**: GCC compiler warnings configured for C++ Core Guidelines compliance

## Essential Commands

### Primary Development Workflow
- **F5 in VSCode**: Complete build and run cycle using `src/input.txt` as stdin
- **Ctrl+Shift+P → "Tasks: Run Task" → "Build with Docker"**: Build only
- **Ctrl+Shift+P → "Tasks: Run Task" → "Run with input"**: Execute with input
- **Ctrl+Shift+P → "Tasks: Run Task" → "Lint with Core Guidelines"**: Static analysis with strict compiler warnings

### Docker Commands
```bash
# Start/rebuild environment
docker-compose up -d --build

# Manual compilation (Linux)
docker-compose exec atcoder g++ -std=c++17 -O2 -Wall -Wextra src/main.cpp -o output/main

# Manual compilation (Windows with MinGW64)  
docker-compose exec atcoder x86_64-w64-mingw32-g++ -std=c++17 -O2 src/main.cpp -o output/main.exe

# Execute with input
docker-compose exec -T atcoder bash -c "./output/main < src/input.txt"

# Code quality check
docker-compose exec atcoder g++ -std=c++17 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -fsyntax-only src/main.cpp

# Stop environment
docker-compose down
```

## Code Architecture

### Container Environment
- **Base**: Ubuntu 22.04 with GCC/G++ and MinGW64 for cross-compilation
- **AtCoder Library**: Pre-installed in `/usr/local/include/` and MinGW include paths
- **Build flags**: `-std=c++17 -O2 -Wall -Wextra -I/usr/local/include`
- **Code Quality**: Strict compiler warnings enabled (`-Wpedantic -Wconversion -Wsign-conversion`)

### Execution Flow
1. VSCode F5 → triggers launch.json configuration
2. Pre-launch task → "Build with Docker" (ensures container running, compiles source)
3. Node.js launcher → scripts/runner.js executes binary with src/input.txt
4. Docker container → runs executable with piped input

### File Organization
- **Source files**: `src/` directory (e.g., `src/main.cpp`, `src/problem_a.cpp`)
- **Output binaries**: `output/` directory (auto-created)
- **Test input**: `src/input.txt`
- **Utilities**: `scripts/` directory (execution scripts)
- **Configuration**: `.vscode/` directory with tasks.json and launch.json

### Code Quality Standards
- **Type Safety**: Use `static_cast<std::size_t>()` for int to size_t conversions
- **Initialization**: Always initialize variables (`int height = 0;`)
- **Modern C++**: Prefer `auto` for type deduction, `const` for immutable data
- **Namespace Usage**: Use anonymous namespaces for internal types and utilities

## Development Workflow

### Competitive Programming Pattern
1. Create/edit source file in `src/` (e.g., `src/main.cpp`, `src/problem_a.cpp`)
2. Prepare test input in `src/input.txt`
3. Press F5 to build and run with input
4. Check output in integrated terminal
5. Use "Lint with Core Guidelines" task for code quality verification

### Cross-Platform Compilation
- **Linux compilation**: Standard GCC (`g++`)
- **Windows compilation**: MinGW64 (`x86_64-w64-mingw32-g++`)
- **Environment variables**: `CC`, `CXX`, `MINGW_CC`, `MINGW_CXX` pre-configured in container

### AtCoder Library Integration
- Use `#include <atcoder/all>` for AtCoder Library functions
- Library pre-installed during Docker build
- Available in both GCC and MinGW environments

### Error Handling and Debugging
- Build errors appear in VSCode terminal with problem matching
- Runtime errors are captured and displayed
- Exit codes properly propagated through execution chain
- Static analysis warnings integrated into VSCode problems panel

## Container Environment

The Docker container includes:
- Ubuntu 22.04 base image
- GCC/G++ compiler suite with C++17 support
- MinGW64 for Windows cross-compilation
- AtCoder Library (ACL) pre-installed
- Development tools (git, vim, gdb, curl)
- Node.js runtime for orchestration scripts

Environment variables configured in container:
- `CC=gcc`
- `CXX=g++` 
- `MINGW_CC=x86_64-w64-mingw32-gcc`
- `MINGW_CXX=x86_64-w64-mingw32-g++`

## Important Notes for Claude Code

### Code Style Requirements
- **Always initialize variables**: Use `int height = 0;` instead of `int height;`
- **Handle type conversions safely**: Use `static_cast<std::size_t>()` for int to size_t conversions to avoid compiler warnings
- **Use proper compiler flags**: The environment enforces strict warnings (`-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion`)
- **Namespace organization**: Place utility types and functions in anonymous namespaces

### VSCode Configuration Notes
- **C++ IntelliSense is disabled** to avoid conflicts with Windows MinGW includes
- **Code analysis relies on GCC compiler warnings** rather than clang-tidy
- **Use the "Lint with Core Guidelines" task** for static analysis before committing code

### File Operations
- **Always place source files in `src/`** directory
- **Test input goes in `src/input.txt`**
- **Binary outputs automatically placed in `output/`**
- **Use F5 key for complete build-run cycle**