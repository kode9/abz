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
#ifndef abz_random_algorithm_hpp
#define abz_random_algorithm_hpp

/// @file abz/random/algorithm.hpp
/// Pseudorandom numbers algorithms.

#include "abz/detail/macros.hpp"
#include "abz/random/random.hpp"

#include <algorithm>
#include <iterator>

ABZ_NAMESPACE_BEGIN

namespace random {

/// @name fill
/// Filling a range with random numbers.
/// @{

/// Fills a range with random values.
///
/// Assigns each element in the range \f$[first, last)\f$ a random value. The values are generated
/// with @ref abz::rand using default parameters.
///
/// Note that each element is assigned a <b>different</b> value. If you want to assign all elements
/// the same random value, use <tt>std::fill(first, last, abz::rand())</tt>.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill(values.begin(), values.end());
/// @endcode
///
/// @param first, last The range of elements to assign a value.
/// @tparam ForwardIterator An iterator type that satisfies the ForwardIterator concept.
template <class ForwardIterator>
inline void fill(ForwardIterator first, ForwardIterator last)
{
  using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
  std::generate(first, last, []() { return abz::rand<value_type>(); });
}

/// Fills a container with random values.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill(values);
/// @endcode
///
/// @param [in,out] c A reference to the container to fill.
/// @tparam Container A type that satisfies the Container concept.
template <class Container>
inline void fill(Container &c)
{
  using value_type = typename Container::value_type;
  std::generate(std::begin(c), std::end(c), []() { return abz::rand<value_type>(); });
}

/// Fills a range with random values uniformly distributed on the interval \f$[a, b]\f$.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill(values.begin(), values.end(), -1., 1.);
/// @endcode
///
/// @param first, last The range of elements to assign a value.
/// @param a, b The interval of the generated numbers.
/// @tparam ForwardIterator An iterator type that satisfies the ForwardIterator concept.
template <class ForwardIterator>
inline void fill(ForwardIterator first,
                 ForwardIterator last,
                 typename std::iterator_traits<ForwardIterator>::value_type a,
                 typename std::iterator_traits<ForwardIterator>::value_type b)
{
  using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
  std::generate(first, last, [=]() { return abz::rand<value_type>(a, b); });
}

/// Fills a container with random values uniformly distributed on the interval \f$[a, b]\f$.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill(values, -1., 1.);
/// @endcode
///
/// @param [in,out] c A reference to the container to fill.
/// @param a, b The interval of the generated numbers.
/// @tparam Container A type that satisfies the Container concept.
template <class Container>
inline void fill(Container &c, typename Container::value_type a, typename Container::value_type b)
{
  using value_type = typename Container::value_type;
  std::generate(std::begin(c), std::end(c), [=]() { return abz::rand<value_type>(a, b); });
}

/// @} fill

/// @name fill_n
/// Filling a range with <tt>N</tt> random numbers.
/// @{

/// Fills the first N elements of a range with random values.
///
/// Assigns each element in the range \f$[first, first + count)\f$ a random value. The values are
/// generated with @ref abz::rand using default parameters.
///
/// Note that each element is assigned a <b>different</b> value. If you want to assign all elements
/// the same random value, use <tt>std::fill_n(first, count, abz::rand())</tt>.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill_n(values.begin(), 10);
/// @endcode
///
/// @param first The beginning of the range of elements to fill.
/// @param count Number of elements to assign a value to.
/// @tparam OutputIterator An iterator type that satisfies the OutputIterator concept.
template <class OutputIterator, class Size>
inline void fill_n(OutputIterator first, Size count)
{
  using value_type = typename std::iterator_traits<OutputIterator>::value_type;
  std::generate_n(first, count, []() { return abz::rand<value_type>(); });
}

/// Fills the first N elements of a range with random values uniformly distributed on the interval
/// \f$[a, b]\f$.
///
/// @code
/// std::vector<double> values(10);
/// abz::random::fill_n(values.begin(), 10, -1., 1.);
/// @endcode
///
/// @param first The beginning of the range of elements to fill.
/// @param count Number of elements to assign a value to.
/// @param a, b The interval of the generated numbers.
/// @tparam OutputIterator An iterator type that satisfies the OutputIterator concept.
template <class OutputIterator, class Size>
inline void fill_n(OutputIterator first,
                   Size count,
                   typename std::iterator_traits<OutputIterator>::value_type a,
                   typename std::iterator_traits<OutputIterator>::value_type b)
{
  using value_type = typename std::iterator_traits<OutputIterator>::value_type;
  std::generate_n(first, count, [=]() { return abz::rand<value_type>(a, b); });
}

/// @} fill_n

} // namespace random

ABZ_NAMESPACE_END

#endif // abz_random_algorithm_hpp
