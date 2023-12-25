#include "zone.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

ZoneMap::ZoneMap(int w, int h, RandMap* map): w(w), h(h) {
  // WE WILL ASSUME AT LEAST ONE WORKER AT EACH ZONE.
  zone_info = std::vector<std::vector<ZoneInfo>>(w, std::vector<ZoneInfo>(h, ZoneInfo(0, 1)));
  total_num_worker += w * h;
  if(map == nullptr) return;
  double width_x = map->get_x_max() / w;
  double width_y = map->get_y_max() / h;
  
  for(auto pt : map->get_point_list()) {
    int x = std::min(w - 1, (int)floor(pt.x / width_x));
    int y = std::min(h - 1, (int)floor(pt.y / width_y));
    switch(pt.type) {
      case 0: // an order
        zone_info[x][y].num_orders ++, total_num_order ++; break;
      case 1: // a worker
        zone_info[x][y].num_worker ++, total_num_worker ++; break;
    }
  }
  for(int i = 0; i < w; i ++) for(int j = 0; j < h; j ++) {
    std::cerr << zone_info[i][j].num_orders << "," << zone_info[i][j].num_worker << (j == h - 1 ? '\n' : ' ');
  }
}

double ZoneMap::KL_Divergance() {
  double ans = 0;
  for(int i = 0; i < w; i ++) for(int j = 0; j < h; j ++) {
    double px = 1.00 * zone_info[i][j].num_orders / total_num_order;
    double qx = 1.00 * zone_info[i][j].num_worker / total_num_worker;
    if(zone_info[i][j].num_orders)
    ans += (1.00 * zone_info[i][j].num_orders / total_num_order) * std::log(px / qx);
  }
  return ans;
} 

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
struct Changes {
  int to[4] {0, 0, 0, 0};
};

ZoneMap ZoneMap::balance(double alpha, double beta) { // alpha * dist + beta * divergance * total_num_order
  std::mt19937 rd(time(0));

  std::vector < std::vector<Changes> > changes(w, std::vector<Changes>(h));
  double temperature = 0.0;
  
  for(int i = 0; i < w; i ++) {
    for(int j = 0; j < h; j ++) {
      
    }
  }
  
  return ZoneMap(w, h, nullptr);
}