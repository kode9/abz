#ifndef abz_thread_clock_hpp
#define abz_thread_clock_hpp

/// @file thread_clock.hpp
/// Per-thread CPU clock

#include "abz/detail/macros.hpp"

#include <chrono>

ABZ_NAMESPACE_BEGIN

namespace chrono {

/// @class thread_clock
/// Per-thread CPU clock
class thread_clock {
public:
  /// @name Member types
  /// @{
  using duration = std::chrono::nanoseconds; ///< The time interval of the clock
  using rep = duration::rep;       ///<  Type representing the number of ticks in the clock duration
  using period = duration::period; ///< A std::ratio representing the number of ticks per second
  using time_point = std::chrono::time_point<thread_clock>; ///< A std::time_point for the clock
  /// @}

  /// @name Member constants
  /// @{
  static constexpr bool is_steady = true; ///< True if the clock is monotonic
  /// @}

  /// @name Static functions
  /// @{
  /// Returns a time_point representing the current value of the clock
  static time_point now() noexcept;
  /// @}
};

} // namespace chrono

ABZ_NAMESPACE_END

#endif // abz_thread_clock_hpp
