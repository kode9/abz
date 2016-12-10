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
#ifndef abz_random_random_hpp
#define abz_random_random_hpp

/// @file abz/random/random.hpp
/// Pseudorandom numbers generation.

#include "abz/detail/macros.hpp"
#include "abz/type_traits.hpp"

#include <cmath> // std::nextafter
#include <limits>
#include <random>
#include <type_traits>

ABZ_NAMESPACE_BEGIN

/// @cond ABZ_INTERNAL
namespace _ {

/// Returns a per-thread PRNG engine.
/// @return A reference to a thread local instance of Engine.
template <class Engine>
Engine &thread_local_engine()
{
  // NOTE(pluc) random_device can actually throw: "Throws an implementation-defined exception
  // derived from std::exception if a random number could not be generated."
  thread_local Engine g{std::random_device{}()};
  return g;
}

template <class T, class Engine, class Enabled = void>
struct uniform_distribution;

template <class Integral, class Engine>
struct uniform_distribution<Integral, Engine, typename std::enable_if<std::is_integral<Integral>::value>::type> {
  using distribution_type = std::uniform_int_distribution<Integral>;
  using param_type = typename distribution_type::param_type;
  using result_type = Integral;

  static inline constexpr result_type default_min() { return result_type{0}; }
  static inline constexpr result_type default_max()
  {
    return std::numeric_limits<result_type>::max();
  }
  static inline result_type get(Engine &g, const Integral a, const Integral b)
  {
    return distribution_type{}(g, param_type{a, b});
  }
};

template <class Real, class Engine>
struct uniform_distribution<Real, Engine, typename std::enable_if<std::is_floating_point<Real>::value>::type> {
  using distribution_type = std::uniform_real_distribution<Real>;
  using param_type = typename distribution_type::param_type;
  using result_type = Real;

  static inline constexpr result_type default_min() { return Real{0}; }
  static inline constexpr result_type default_max() { return Real{1}; }
  static inline result_type get(Engine &g, const Real a, const Real b)
  {
    return distribution_type{}(
      g, param_type{a, std::nextafter(b, std::numeric_limits<result_type>::max())});
  }
};

} // namespace _
/// @endcond ABZ_INTERNAL

namespace random {

/// @brief Seeds the internal thread local engine with a new value.
///
/// The seed value is generated using std::random_device.
///
/// The library keep a local thread instance of each engine. Multiple calls from the same thread and
/// using the same Engine type will use the same generator. This function seeds the Engine's
/// instance of the calling thread.
///
/// @tparam Engine The type of engine for which the instance will be seeded.
///
/// @see seed(const Engine::result_type) rand
template <class Engine = std::default_random_engine>
inline void seed()
{
  _::thread_local_engine<Engine>().seed(std::random_device{}());
}

/// @overload
///
/// @param value The new seed value
///
/// @see seed rand
template <class Engine = std::default_random_engine>
inline void seed(const typename Engine::result_type value)
{
  _::thread_local_engine<Engine>().seed(value);
}

} // namespace random

/// Gets a (pseudo) random number uniformly distributed on the interval \f$[a, b]\f$.
///
/// Default paramaters are
/// @li \f$\{0, MAX(T)\}\f$ for integral types
/// @li \f$\{0.0, 1.0\}\f$ for floating point types
///
/// Requires that
/// @li \f$a \leq b\f$ for integral types
/// @li \f$(a \leq b) \land (b < MAX(T)) \land ((b - a) < MAX(T))\f$ for floating point
/// types
///
/// @warning For floating point types, some existing implementations have a bug where they may
/// occasionally return b (that is, std::nextafter(b, std::numeric_limits<Real>::max()) for this
/// function). <a href="https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63176" target="_blank">GCC
/// #63176</a> <a href="https://llvm.org/bugs/show_bug.cgi?id=18767" target="_blank">#LLVM
/// #18767</a> <a href="http://open-std.org/JTC1/SC22/WG21/docs/lwg-active.html#2524"
/// target="_blank">LWG #2524</a>.
///
/// @param e A reference to a randon bit generator.
/// @param a, b The interval of the generated numbers
///
/// @tparam T The type of number to generate (must be integral or floating point).
/// @tparam Engine The random number generator type (must satisfy UniformRandomBitGenerator
/// concept).
template <class T, class Engine>
inline auto rand(Engine &e,
                 T const a = _::uniform_distribution<T, Engine>::default_min(),
                 T const b = _::uniform_distribution<T, Engine>::default_max()) ->
  typename _::uniform_distribution<T, Engine>::result_type
{
  return _::uniform_distribution<T, Engine>::get(e, a, b);
}

/// @overload
///
/// This overload uses a thread local random bit generator. To reinitialize this engine with a new
/// seed, see random::seed.
///
/// @see random::seed()
template <class T, class Engine = std::default_random_engine>
inline auto rand(T const a = _::uniform_distribution<T, Engine>::default_min(),
                 T const b = _::uniform_distribution<T, Engine>::default_max()) ->
  typename _::uniform_distribution<T, Engine>::result_type
{
  return rand(_::thread_local_engine<Engine>(), a, b);
}

/// Gets a (pseudo) random number distributed according to a given probability function.
///
/// @code
/// using Dist = std::normal_distribution<double>;
/// std::minstd_rand0 engine;     // The random bit generator
/// Dist::param_type params{0., 1.}; // The distribution parameters
/// const auto value = abz::rand<Dist>(engine, params);
/// @endcode
///
/// @param e A reference to a randon bit generator.
/// @param params The distribution parameters.
///
/// @tparam Distribution The statistical probability density function type
/// (RandomNumberDistribution).
/// @tparam Engine The random number generator type (UniformRandomBitGenerator).
template <class Distribution, class Engine>
inline auto rand(Engine &e, typename Distribution::param_type const &params) ->
  typename Distribution::result_type
{
  return Distribution{}(e, params);
}

/// @overload
///
/// This overload takes standalone distribution parameters.
///
/// @code
/// using Dist = std::normal_distribution<double>;
/// std::minstd_rand0 engine; // The random bit generator
/// const auto value = abz::rand<Dist>(engine, 0., 1.);
/// @endcode
template <class Distribution,
          class Engine,
          class... Params,
          class = typename std::enable_if<all<std::is_arithmetic<Params>...>::value>::type>
inline auto rand(Engine &e, Params &&... params) -> typename Distribution::result_type
{
  return rand<Distribution>(e, typename Distribution::param_type{std::forward<Params>(params)...});
}

/// @overload
///
/// This overload uses a thread local random bit generator.
///
/// @code
/// using Dist = std::normal_distribution<double>;
/// Dist::param_type params{0., 1.}; // The distribution parameters
/// const auto value = abz::rand<Dist>(0., 1.);
/// @endcode
template <class Distribution, class Engine = std::default_random_engine>
inline auto
rand(const typename Distribution::param_type &params) -> typename Distribution::result_type
{
  return rand<Distribution>(_::thread_local_engine<Engine>(), params);
}

/// @overload
///
/// This overload uses a thread local random bit generator and takes standalone distributions
/// parameters.
///
/// @code
/// using Dist = std::normal_distribution<double>;
/// const auto value = abz::rand<Dist>(0., 1.);
/// @endcode
template <class Distribution,
          class Engine = std::default_random_engine,
          class... Params,
          class = typename std::enable_if<all<std::is_arithmetic<Params>...>::value>::type>
inline auto rand(Params &&... params) -> typename Distribution::result_type
{
  return rand<Distribution>(typename Distribution::param_type{std::forward<Params>(params)...});
}

ABZ_NAMESPACE_END

#endif // abz_random_random_hpp
