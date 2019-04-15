/*

This file is part of VROOM.

Copyright (c) 2015-2019, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include "structures/vroom/solution/solution.h"

namespace vroom {

Solution::Solution(unsigned code, std::string error)
  : code(code), error(error) {
}

Solution::Solution(unsigned code,
                   unsigned amount_size,
                   std::vector<Route>&& routes,
                   std::vector<Job>&& unassigned)
  : code(code),
    summary(unassigned.size(), amount_size),
    routes(std::move(routes)),
    unassigned(std::move(unassigned)) {

  for (const auto& route : this->routes) {
    summary.cost += route.cost;
    summary.amount += route.amount;
    summary.service += route.service;
    summary.duration += route.duration;
    summary.waiting_time += route.waiting_time;
  }
}

} // namespace vroom
