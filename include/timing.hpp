#pragma once

#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

namespace twm_timing
{
  using fn_t = std::function<void()>;
  using ns_t = std::chrono::nanoseconds;
  using clock_t = std::chrono::high_resolution_clock;

  /* waits until target time */
  template<
    typename T_clock = clock_t,
    typename T_fn = fn_t
  >
    auto wait_until(
      const T_fn& fn,
      const typename T_clock::time_point& target_time
    )
    ->void
  {
    while ( T_clock::now() < target_time )
      fn();
  }

  /* times function execution */
  template<
    typename T_duration = ns_t,
    typename T_clock = clock_t,
    typename T_fn = fn_t
  >
    auto time_fn(const T_fn& fn)
    -> T_duration
  {
    using std::chrono::duration_cast;
    auto start = T_clock::now();
    fn();
    return duration_cast<T_duration>(T_clock::now() - start);
  }

  /*
     adjusts the sleep time of the thread
     on which the function is running
  */
  template<
    typename T_duration = ns_t,
    typename T_clock = clock_t,
    typename T_fn = fn_t,
    typename T_target_duration = ns_t
  >
    auto adjust_time(
      const T_fn& fn,
      const T_target_duration target_time
    )
    -> T_duration
  {
    auto mt = time_fn<T_duration, T_clock, T_fn>(fn);
    auto dt = target_time - mt;
    std::this_thread::sleep_for(dt);
    return dt;
  }
}