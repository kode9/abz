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
#ifndef abz_chrono_thread_clock_hpp
#define abz_chrono_thread_clock_hpp

/// @file thread_clock.hpp
/// @brief Thread CPU clock.

#include "abz/detail/macros.hpp"

#include <chrono>

ABZ_NAMESPACE_BEGIN

namespace chrono {

/// @class thread_clock
/// @brief Thread CPU clock.
class thread_clock {
public:
  /// @name Member types
  /// @{

  using duration = std::chrono::nanoseconds; ///< The time interval of the clock.
  using rep = duration::rep;       ///< Type representing the number of ticks in the clock duration.
  using period = duration::period; ///< A std::ratio representing the number of ticks per second.
  using time_point = std::chrono::time_point<thread_clock>; ///< A std::time_point for the clock.

  /// @}

  /// @name Member constants
  /// @{

  static constexpr bool is_steady = true; ///< True if the clock is monotonic.

  /// @}

  /// @name Static functions
  /// @{

  /// Returns a time_point representing the current value of the clock.
  static time_point now() noexcept;

  /// @}
};

} // namespace chrono

ABZ_NAMESPACE_END

#endif // abz_chrono_thread_clock_hpp
