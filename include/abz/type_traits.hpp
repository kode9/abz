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

/////////////////////////////////////////////////////////////////////////////////
// C++17 #P0006R0                                                              //
// Adopt Type Traits Variable Templates from Library Fundamentals TS for C++17 //
/////////////////////////////////////////////////////////////////////////////////

#ifdef __cpp_variable_templates

// 20.10.4.1, primary type categories
template <class T>
constexpr bool is_void_v = std::is_void<T>::value;
template <class T>
constexpr bool is_null_pointer_v = std::is_null_pointer<T>::value;
template <class T>
constexpr bool is_integral_v = std::is_integral<T>::value;
template <class T>
constexpr bool is_floating_point_v = std::is_floating_point<T>::value;
template <class T>
constexpr bool is_array_v = std::is_array<T>::value;
template <class T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;
template <class T>
constexpr bool is_lvalue_reference_v = std::is_lvalue_reference<T>::value;
template <class T>
constexpr bool is_rvalue_reference_v = std::is_rvalue_reference<T>::value;
template <class T>
constexpr bool is_member_object_pointer_v = std::is_member_object_pointer<T>::value;
template <class T>
constexpr bool is_member_function_pointer_v = std::is_member_function_pointer<T>::value;
template <class T>
constexpr bool is_enum_v = std::is_enum<T>::value;
template <class T>
constexpr bool is_union_v = std::is_union<T>::value;
template <class T>
constexpr bool is_class_v = std::is_class<T>::value;
template <class T>
constexpr bool is_function_v = std::is_function<T>::value;

// 20.10.4.2, composite type categories
template <class T>
constexpr bool is_reference_v = std::is_reference<T>::value;
template <class T>
constexpr bool is_arithmetic_v = std::is_arithmetic<T>::value;
template <class T>
constexpr bool is_fundamental_v = std::is_fundamental<T>::value;
template <class T>
constexpr bool is_object_v = std::is_object<T>::value;
template <class T>
constexpr bool is_scalar_v = std::is_scalar<T>::value;
template <class T>
constexpr bool is_compound_v = std::is_compound<T>::value;
template <class T>
constexpr bool is_member_pointer_v = std::is_member_pointer<T>::value;

// 20.10.4.3, type properties
template <class T>
constexpr bool is_const_v = std::is_const<T>::value;
template <class T>
constexpr bool is_volatile_v = std::is_volatile<T>::value;
template <class T>
constexpr bool is_trivial_v = std::is_trivial<T>::value;
template <class T>
constexpr bool is_trivially_copyable_v = std::is_trivially_copyable<T>::value;
template <class T>
constexpr bool is_standard_layout_v = std::is_standard_layout<T>::value;
template <class T>
constexpr bool is_pod_v = std::is_pod<T>::value;
template <class T>
constexpr bool is_literal_type_v = std::is_literal_type<T>::value;
template <class T>
constexpr bool is_empty_v = std::is_empty<T>::value;
template <class T>
constexpr bool is_polymorphic_v = std::is_polymorphic<T>::value;
template <class T>
constexpr bool is_abstract_v = std::is_abstract<T>::value;
template <class T>
constexpr bool is_final_v = std::is_final<T>::value;
template <class T>
constexpr bool is_signed_v = std::is_signed<T>::value;
template <class T>
constexpr bool is_unsigned_v = std::is_unsigned<T>::value;
template <class T, class... Args>
constexpr bool is_constructible_v = std::is_constructible<T, Args...>::value;
template <class T>
constexpr bool is_default_constructible_v = std::is_default_constructible<T>::value;
template <class T>
constexpr bool is_copy_constructible_v = std::is_copy_constructible<T>::value;
template <class T>
constexpr bool is_move_constructible_v = std::is_move_constructible<T>::value;
template <class T, class U>
constexpr bool is_assignable_v = std::is_assignable<T, U>::value;
template <class T>
constexpr bool is_copy_assignable_v = std::is_copy_assignable<T>::value;
template <class T>
constexpr bool is_move_assignable_v = std::is_move_assignable<T>::value;
template <class T>
constexpr bool is_destructible_v = std::is_destructible<T>::value;
template <class T, class... Args>
constexpr bool is_trivially_constructible_v = std::is_trivially_constructible<T, Args...>::value;
template <class T>
constexpr bool is_trivially_default_constructible_v
  = std::is_trivially_default_constructible<T>::value;
template <class T>
constexpr bool is_trivially_copy_constructible_v = std::is_trivially_copy_constructible<T>::value;
template <class T>
constexpr bool is_trivially_move_constructible_v = std::is_trivially_move_constructible<T>::value;
template <class T, class U>
constexpr bool is_trivially_assignable_v = std::is_trivially_assignable<T, U>::value;
template <class T>
constexpr bool is_trivially_copy_assignable_v = std::is_trivially_copy_assignable<T>::value;
template <class T>
constexpr bool is_trivially_move_assignable_v = std::is_trivially_move_assignable<T>::value;
template <class T>
constexpr bool is_trivially_destructible_v = std::is_trivially_destructible<T>::value;
template <class T, class... Args>
constexpr bool is_nothrow_constructible_v = std::is_nothrow_constructible<T, Args...>::value;
template <class T>
constexpr bool is_nothrow_default_constructible_v = std::is_nothrow_default_constructible<T>::value;
template <class T>
constexpr bool is_nothrow_copy_constructible_v = std::is_nothrow_copy_constructible<T>::value;
template <class T>
constexpr bool is_nothrow_move_constructible_v = std::is_nothrow_move_constructible<T>::value;
template <class T, class U>
constexpr bool is_nothrow_assignable_v = std::is_nothrow_assignable<T, U>::value;
template <class T>
constexpr bool is_nothrow_copy_assignable_v = std::is_nothrow_copy_assignable<T>::value;
template <class T>
constexpr bool is_nothrow_move_assignable_v = std::is_nothrow_move_assignable<T>::value;
template <class T>
constexpr bool is_nothrow_destructible_v = std::is_nothrow_destructible<T>::value;
template <class T>
constexpr bool has_virtual_destructor_v = std::has_virtual_destructor<T>::value;

// See 20.10.5, type property queries
template <class T>
constexpr std::size_t alignment_of_v = std::alignment_of<T>::value;
template <class T>
constexpr std::size_t rank_v = std::rank<T>::value;
template <class T, unsigned I = 0>
constexpr std::size_t extent_v = std::extent<T, I>::value;

// See 20.10.6, type relations
template <class T, class U>
constexpr bool is_same_v = std::is_same<T, U>::value;
template <class Base, class Derived>
constexpr bool is_base_of_v = std::is_base_of<Base, Derived>::value;
template <class From, class To>
constexpr bool is_convertible_v = std::is_convertible<From, To>::value;

#endif // __cpp_variable_templates

/// @cond ABZ_INTERNAL
namespace _ {

// NOT
template <class T>
struct negate : std::conditional<T::value, std::false_type, std::true_type>::type {
};

// AND
template <class...>
struct all;
template <>
struct all<> : std::true_type {
};
template <class T>
struct all<T> : T {
};
template <class Head, class... Tail>
struct all<Head, Tail...> : std::conditional<Head::value, all<Tail...>, std::false_type>::type {
};

// OR
template <class...>
struct any;
template <>
struct any<> : std::false_type {
};
template <class T>
struct any<T> : T {
};
template <class Head, class... Tail>
struct any<Head, Tail...> : std::conditional<Head::value, std::true_type, any<Tail...>>::type {
};

// NOT any
template <class...>
struct none;
template <>
struct none<> : std::false_type {
};
template <class T>
struct none<T> : negate<T> {
};
template <class Head, class... Tail>
struct none<Head, Tail...> : std::conditional<Head::value, std::false_type, none<Tail...>>::type {
};

} // namespace _
///@endcond

/// Checks if every type has a @c type member that evaluates to true.
template <class T>
struct negate : _::negate<T> {
};

/// Checks if every type has a @c type member that evaluates to true.
template <class... T>
struct all : _::all<T...> {
};

/// Checks if at least one type has a @c type member that evaluates to true.
template <class... T>
struct any : _::any<T...> {
};

/// Checks if every type has a @c type member that evaluates to false.
template <class... T>
struct none : _::none<T...> {
};

#ifdef __cpp_variable_templates

/// @relates negate
template <class T>
constexpr bool negate_v = negate<T>::value;

/// @relates all
template <class... T>
constexpr bool all_v = all<T...>::value;

/// @relates any
template <class... T>
constexpr bool any_v = any<T...>::value;

/// @relates none
template <class... T>
constexpr bool none_v = none<T...>::value;

#endif // __cpp_variable_templates

ABZ_NAMESPACE_END

#endif // abz_type_traits_hpp
