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
#ifndef abz_type_traits_hpp
#define abz_type_traits_hpp

/// @file type_traits.hpp
/// @brief Compile-time type information.
///
/// This file provides additional type traits.

#include "abz/compiler.hpp"
#include "abz/detail/macros.hpp"

#include <type_traits> // IWYU pragma: export

ABZ_NAMESPACE_BEGIN

////////////////////////////////
// C++14 #WG21 N3655          //
// TransformationTraits Redux //
////////////////////////////////

// 20.9.7.1, const-volatile modifications:
template <class T>
using remove_const_t = typename std::remove_const<T>::type;
template <class T>
using remove_volatile_t = typename std::remove_volatile<T>::type;
template <class T>
using remove_cv_t = typename std::remove_cv<T>::type;
template <class T>
using add_const_t = typename std::add_const<T>::type;
template <class T>
using add_volatile_t = typename std::add_volatile<T>::type;
template <class T>
using add_cv_t = typename std::add_cv<T>::type;

// 20.9.7.2, reference modifications:
template <class T>
using remove_reference_t = typename std::remove_reference<T>::type;
template <class T>
using add_lvalue_reference_t = typename std::add_lvalue_reference<T>::type;
template <class T>
using add_rvalue_reference_t = typename std::add_rvalue_reference<T>::type;

// 20.9.7.3, sign modifications:
template <class T>
using make_signed_t = typename std::make_signed<T>::type;
template <class T>
using make_unsigned_t = typename std::make_unsigned<T>::type;

// 20.9.7.4, array modifications:
template <class T>
using remove_extent_t = typename std::remove_extent<T>::type;
template <class T>
using remove_all_extents_t = typename std::remove_all_extents<T>::type;

// 20.9.7.5, pointer modifications:
template <class T>
using remove_pointer_t = typename std::remove_pointer<T>::type;
template <class T>
using add_pointer_t = typename std::add_pointer<T>::type;

// 20.9.7.6, other transformations:
template <std::size_t Len, std::size_t Align = alignof(typename std::aligned_storage<Len>::type)>
using aligned_storage_t = typename std::aligned_storage<Len, Align>::type;
template <std::size_t Len, class... Types>
using aligned_union_t = typename std::aligned_union<Len, Types...>::type;
template <class T>
using decay_t = typename std::decay<T>::type;
template <bool b, class T = void>
using enable_if_t = typename std::enable_if<b, T>::type;
template <bool b, class T, class F>
using conditional_t = typename std::conditional<b, T, F>::type;
template <class... T>
using common_type_t = typename std::common_type<T...>::type;
template <class T>
using underlying_type_t = typename std::underlying_type<T>::type;
template <class F, class... ArgTypes>
using result_of_t = typename std::result_of<F(ArgTypes...)>::type;

ABZ_NAMESPACE_END

#endif // abz_type_traits_hpp
