#include <iostream>
#include "../include/timing.hpp"

using twm_timing::time_fn;
using twm_timing::wait_until;
using twm_timing::adjust_time;
using namespace std::chrono_literals;

void fn()
{
  for ( size_t i = 0; i < 1'000; ++i );
}

int main()
{
  auto _fn_t = time_fn(fn);
  std::cout << _fn_t.count() << "[ns]" << '\n';

  wait_until([&]() 
  {
    auto dt = adjust_time(fn, 200ms);
    std::cout << "time: "<< dt.count() << "[ns]" << '\n';
  }, twm_timing::clock_t::now() + 2000ms);
}
