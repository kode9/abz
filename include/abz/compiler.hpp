// Copyright (C) 2016 Pierre-Luc Perrier <pluc-dev@the-pluc.net>
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
#ifndef abz_compiler_hpp
#define abz_compiler_hpp

/// @file compiler.hpp
/// @brief Compiler identification macros.
///
/// This file contains preprocessor definitions to identify the compiler in use and its
/// capabilities.
///
/// Compiler identification:
///
/// @li @ref ABZ_COMPILER_GCC
/// @li @ref ABZ_COMPILER_CLANG
/// @li @ref ABZ_COMPILER_CLANG_APPLE
///
/// Compiler version:
///
/// @li @ref ABZ_COMPILER_MAJOR
/// @li @ref ABZ_COMPILER_MINOR
/// @li @ref ABZ_COMPILER_PATCH
///
/// C++ standard:
///
/// @li @ref ABZ_CXX98
/// @li @ref ABZ_CXX11 or @ref ABZ_NO_CXX11
/// @li @ref ABZ_CXX14 or @ref ABZ_NO_CXX14
/// @li @ref ABZ_CXX17 or @ref ABZ_NO_CXX17

#if defined(__clang__)
#define ABZ_COMPILER_CLANG 1
#if defined(__apple_build_version__)
#define ABZ_COMPILER_CLANG_APPLE 1
#endif
#define ABZ_COMPILER_MAJOR __clang_major__
#define ABZ_COMPILER_MINOR __clang_minor__
#define ABZ_COMPILER_PATCH __clang_patchlevel__
#elif defined(__GNUC__)
#define ABZ_COMPILER_GCC 1
#define ABZ_COMPILER_MAJOR __GNUC__
#define ABZ_COMPILER_MINOR __GNUC_MINOR__
#define ABZ_COMPILER_PATCH __GNUC_PATCHLEVEL__
#endif

#if (__cplusplus >= 199711L)
#define ABZ_CXX98 1
#endif

#if (__cplusplus >= 201103L)
#define ABZ_CXX11 1
#else
#define ABZ_NO_CXX11 1
#endif

#if (__cplusplus >= 201402L)
#define ABZ_CXX14 1
#else
#define ABZ_NO_CXX14 1
#endif

// As of version 3.9.0 clang uses 201406 for C++17.
#if (__cplusplus >= 201500L) || (defined(ABZ_COMPILER_CLANG) && (__cplusplus >= 201406L))
#define ABZ_CXX17 1
#else
#define ABZ_NO_CXX17 1
#endif

//////////////////////////
// Documentation bellow //
//////////////////////////

/// @def ABZ_COMPILER_CLANG
/// CLang compiler.

/// @def ABZ_COMPILER_CLANG_APPLE
/// CLang compiler (Apple build).

/// @def ABZ_COMPILER_GCC
/// GNU GCC C/C++ compiler.

/// @def ABZ_COMPILER_MAJOR
/// The major version of the compiler.

/// @def ABZ_COMPILER_MINOR
/// The minor version of the compiler.

/// @def ABZ_COMPILER_PATCH
/// The patch version of the compiler.

/// @def ABZ_CXX98
/// The compiler supports at least C++98 standard.

/// @def ABZ_CXX11
/// The compiler supports at least C++11 standard.

/// @def ABZ_NO_CXX11
/// The compiler does not support C++11 standard.

/// @def ABZ_CXX14
/// The compiler supports at least C++14 standard.

/// @def ABZ_NO_CXX14
/// The compiler does not support C++14 standard.

/// @def ABZ_CXX17
/// The compiler supports at least C++17 standard.

/// @def ABZ_NO_CXX17
/// The compiler does not support C++17 standard.

#if defined(ABZ_DOXYGEN)
#define ABZ_COMPILER_CLANG
#define ABZ_COMPILER_CLANG_APPLE
#define ABZ_COMPILER_GCC
#define ABZ_COMPILER_MAJOR
#define ABZ_COMPILER_MINOR
#define ABZ_COMPILER_PATCH
#define ABZ_CXX98
#define ABZ_CXX11
#define ABZ_NO_CXX11
#define ABZ_CXX14
#define ABZ_NO_CXX14
#define ABZ_CXX17
#define ABZ_NO_CXX17
#endif

#endif // abz_compiler_hpp
