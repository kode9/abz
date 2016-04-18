// Copyright (C) 2015, 2016 Pierre-Luc Perrier <pluc-dev@the-pluc.net>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef abz_os_hpp
#define abz_os_hpp

/// @file os.hpp
/// @brief Operating system identification
///
/// This file contains preprocessor definitions to identify the
/// operating system at compile time. The following definitions are
/// available:
///
/// - @ref ABZ_OS_LINUX *
/// - @ref ABZ_OS_AIX
/// - @ref ABZ_OS_HPUX
/// - @ref ABZ_OS_SOLARIS
/// - @ref ABZ_OS_WINDOWS *
/// - @ref ABZ_OS_WIN32
/// - @ref ABZ_OS_WIN64
/// - @ref ABZ_OS_CYGWIN *
/// - @ref ABZ_OS_APPLE *
/// - @ref ABZ_OS_IOS_SIMULATOR
/// - @ref ABZ_OS_IOS
/// - @ref ABZ_OS_OSX
/// - @ref ABZ_OS_BSD
/// - @ref ABZ_OS_UNKNOWN
/// - @ref ABZ_OS_ANDROID *
/// - @ref ABZ_OS_UNIX *
/// - @ref ABZ_OS_POSIX *
///
/// The definitions marked with an (*) asterisk are not mutually
/// exclusive, for example ABZ_OS_LINUX and ABZ_OS_ANDROID will
/// (normally) both be defined at the same time.
///
/// This tables shows what preprocessor definitions can be defined by
/// compilers on the different architectures. This is a reminder to
/// build abz OS definitions. A ✓ check mark means the macro _must_ be
/// defined when building on the system, an ‽ interrobang means the
/// macro _might_ be defined.
///
/// Macro / Target     | LINUX | AIX | HP-UX | SOLARIS | WINDOWS | CYGWIN | APPLE | ANDROID | BSD |
/// :----------------- | :---: | :-: | :---: | :-----: | :-----: | :----: | :---: | :-----: | :-: |
///  __linux__         | ✓     |     |       |         |         |        |       | ✓       |     |
///  _AIX              |       | ✓   |       |         |         |        |       |         |     |
/// __hpux             |       |     | ✓     |         |         |        |       |         |     |
/// __sun __SVR4       |       |     |       | ✓       |         |        |       |         |     |
/// _WIN32 _WIN64      |       |     |       |         | ✓       | ‽      |       |         |     |
/// __CYGWIN__         |       |     |       |         |         | ✓      |       |         |     |
/// __APPLE__ __MACH__ |       |     |       |         |         |        | ✓     |         |     |
/// BSD                |       |     |       |         |         |        |       |         | ✓   |
/// __ANDROID__        |       |     |       |         |         |        |       | ✓       |     |
/// __unix__           | ✓     | ✓   | ✓     | ✓       | ‽       | ‽      | ✓     | ✓       | ✓   |
///
/// @warning I'm not 100% sure about watchOS stuff, it seems to exist
/// TARGET_OS_IOS and TARGET_OS_WATCH if necessary.
///
/// @reference
/// http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
/// @reference http://sourceforge.net/p/predef/wiki/Home/
/// @reference https://en.wikipedia.org/wiki/POSIX
/// @reference gcc -dD -E / clang -dD -E

// Mutually exclusive defines

#if defined(__linux__)
#define ABZ_OS_LINUX
#elif defined(_AIX)
#define ABZ_OS_AIX
#elif defined(__hpux)
#define ABZ_OS_HPUX
#elif defined(__sun) && defined(__SVR4)
#define ABZ_OS_SOLARIS
#elif defined(_WIN32)
#define ABZ_OS_WINDOWS
#define ABZ_OS_WIN32
#elif defined(_WIN64)
#define ABZ_OS_WINDOWS
#define ABZ_OS_WIN64
#elif defined(__CYGWIN__)
#define ABZ_OS_CYGWIN
#elif defined(__APPLE__) && defined(__MACH__)
#define ABZ_OS_APPLE
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#define ABZ_OS_IOS_SIMULATOR
#elif TARGET_OS_EMBEDDED == 1
#define ABZ_OS_IOS
#elif TARGET_OS_MAC == 1
#define ABZ_OS_OSX
#else
#warning Unknown Apple OS, please provide a bug report
#endif
#elif defined(__unix__)
#include <sys/param.h>
#if defined(BSD)
#define ABZ_OS_BSD
#endif
#else
#define ABZ_OS_UNKNOWN
#endif

// Non mutually exclusive defines

#if defined(__ANDROID__)
#define ABZ_OS_ANDROID
#endif

#if defined(ABZ_OS_CYGWIN) || defined(ABZ_OS_APPLE) || defined(__unix__) || defined(__unix)
#define ABZ_OS_UNIX
#include <unistd.h>
#if defined(_POSIX_VERSION)
#define ABZ_OS_POSIX
#endif
#endif

#if defined(ABZ_OS_UNKNOWN) && !defined(CPP_OS_UNIX)
#warning Unknown OS, please provide a bug report
#endif

// Documentation bellow

/// @def ABZ_OS_UNIX
/// UNIX-like OSs

/// @def ABZ_OS_POSIX
/// POSIX _compatible_ OSs

/// @def ABZ_OS_LINUX
/// Linux (including Android) (POSIX-compliant)

/// @def ABZ_OS_ANDROID
/// Android

/// @def ABZ_OS_BSD
/// BSD (POSIX-compliant)

/// @def ABZ_OS_AIX
/// IBM AIX (POSIX-certified)

/// @def ABZ_OS_HPUX
/// Hewlett-Packard HP-UX (POSIX-certified)

/// @def ABZ_OS_SOLARIS
/// Sun Microsystems Solaris (POSIX-certified)

/// @def ABZ_OS_APPLE
/// Apple OSs (OSX, iOS and watchOS)

/// @def ABZ_OS_OSX
/// Apple OSX

/// @def ABZ_OS_IOS
/// Apple iOS (iPhone, iPad and iWatch)

/// @def ABZ_OS_IOS_SIMULATOR
/// iPhone XCode simulator

/// @def ABZ_OS_CYGWIN
/// Cygwin

/// @def ABZ_OS_WINDOWS
/// Microsoft Windows (Both 32 and 64 bits)

/// @def ABZ_OS_WIN32
/// Microsoft Windows 32 bits

/// @def ABZ_OS_WIN64
/// Microsoft Windows 64 bits

/// @def ABZ_OS_UNKNOWN
/// Unknown OS (can still be POSIX or UNIX)

#if defined(ABZ_DOXYGEN)
#define ABZ_OS_LINUX
#define ABZ_OS_AIX
#define ABZ_OS_HPUX
#define ABZ_OS_SOLARIS
#define ABZ_OS_WINDOWS
#define ABZ_OS_WIN32
#define ABZ_OS_WIN64
#define ABZ_OS_CYGWIN
#define ABZ_OS_APPLE
#define ABZ_OS_IOS_SIMULATOR
#define ABZ_OS_IOS
#define ABZ_OS_OSX
#define ABZ_OS_BSD
#define ABZ_OS_UNKNOWN
#define ABZ_OS_ANDROID
#define ABZ_OS_UNIX
#define ABZ_OS_POSIX
#endif

#endif // abz_os_hpp
