#include "abz/chrono/thread_clock.hpp"

/// @file chrono/thread_clock.cpp
/// @brief thread_clock implementation
///
/// @reference http://pubs.opengroup.org/onlinepubs/9699919799/
/// @reference http://www.boost.org/doc/libs/1_58_0/doc/html/chrono.html
/// @reference http://nadeausoftware.com/articles/2012/03/c_c_tip_how_measure_cpu_time_benchmarking
/// @reference https://stackoverflow.com/questions/7622371/getrusage-vs-clock-gettime
///
/// TODO:
///  - Windows implementation
///  - Apple implementation
///  - getrusage fallback when clock_gettime fails

#include "abz/os.hpp"

#if defined(ABZ_OS_POSIX)
// _POSIX_TIMERS (unistd.h) shall be defined to 200809L.
// _POSIX_THREAD_CPUTIME (unistd.h) shall be defined to -1, 0, or 200809L.
#if defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0) && defined(_POSIX_THREAD_CPUTIME)
#define ABZ_POSIX_THREAD_CPUTIME
#include <time.h> // clock_gettime, CLOCK_THREAD_CPUTIME_ID
#else
#warning Thread CPU time is not supported on your platform
#endif
#endif

ABZ_NAMESPACE_BEGIN

namespace chrono {

auto thread_clock::now() noexcept -> time_point
{
#if defined(ABZ_POSIX_THREAD_CPUTIME)
  struct ::timespec tp;
  if (::clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tp) != 0) {
    return time_point{};
  }
  return time_point{duration{std::chrono::seconds{tp.tv_sec} + std::chrono::nanoseconds{tp.tv_nsec}}};
#else
  return time_point{};
#endif
}

} // namespace chrono

ABZ_NAMESPACE_END