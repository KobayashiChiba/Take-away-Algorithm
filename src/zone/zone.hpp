#ifndef ZONE_HPP_
#define ZONE_HPP_

#include "map/RandMap.hpp"


struct ZoneInfo {
  ZoneInfo(int num_orders = 0, int num_worker = 0) : num_orders(num_orders), num_worker(num_worker) {}
  int num_orders;
  int num_worker;
};

class ZoneMap {
public:
  ZoneMap(int w, int h, RandMap* map = nullptr);

  double KL_Divergence();
  
  ZoneMap balance();
private:
  const int w, h; // refer to x and y
  int total_num_order{0}, total_num_worker{0};
  std::vector<std::vector<ZoneInfo>> zone_info;
};

#endif