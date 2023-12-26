#include "zone.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

void ZoneMap::print() {
  fprintf(stderr, "[");
  for(int i = 0; i < w; i ++) for(int j = 0; j < h; j ++) {
    fprintf(stderr, "[%3d, %3d],%c", zone_info[i][j].num_orders, zone_info[i][j].num_worker, (j == h - 1 ? '\n' : ' '));
    // std::cerr << zone_info[i][j].num_orders << "," << zone_info[i][j].num_worker << (j == h - 1 ? '\n' : ' ');
  }
  fprintf(stderr, "]\n");
}

ZoneMap::ZoneMap(int w, int h, RandMap* map): w(w), h(h) {
  // WE WILL ASSUME AT LEAST ONE WORKER AT EACH ZONE.
  zone_info = std::vector<std::vector<ZoneInfo>>(w, std::vector<ZoneInfo>(h, ZoneInfo(0, 1)));
  total_num_worker += w * h;
  if(map == nullptr) return;
  width_x = map->get_x_max() / w;
  width_y = map->get_y_max() / h;
  
  for(auto pt : map->get_point_list()) {
    int x = std::min(w - 1, (int)floor(pt.x / width_x));
    int y = std::min(h - 1, (int)floor(pt.y / width_y));
    switch(pt.type) {
      case 1: // an order
        zone_info[x][y].num_orders ++, total_num_order ++; break;
      case 0: // a worker
        zone_info[x][y].num_worker ++, total_num_worker ++; break;
    }
  }
  print();
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

double ZoneMap::divergance(int i, int j) {
  
  double px = 1.00 * zone_info[i][j].num_orders / total_num_order;
  double qx = 1.00 * zone_info[i][j].num_worker / total_num_worker;
  
  if(zone_info[i][j].num_orders)
    return (1.00 * zone_info[i][j].num_orders / total_num_order) * std::log(px / qx);
  else
    return 0.0f;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
struct Changes {
  int to[4] {0, 0, 0, 0};
};

double ZoneMap::balance(double alpha, double beta) { // alpha * dist + beta * divergance * total_num_order
  std::mt19937 rd(time(0));

  std::vector < std::vector<Changes> > changes(w, std::vector<Changes>(h));
  
  int amount = round(1.00 * total_num_worker / w / h * 20);
  double base = beta * total_num_order * KL_Divergance();
  std::cerr << "base cost = " << base << std::endl;
  int people = 1 << 10;
  int n_try = 100000;
  double success_rate = 0.4;
  for(int epoch = 0; epoch < 10; epoch ++, n_try *= 1.1) {
    people /= 2;
    for(int tr = 0; tr < n_try; tr ++) {
      int i = rd()%w, j = rd()%h, dir = rd()%4;
      int ni = i + dx[dir], nj = j + dy[dir];
      if(!(ni >= 0 && ni < w && nj >= 0 && nj < h))
        continue;
      if(people < zone_info[i][j].num_worker) {
        double dist = std::abs(i - ni) * width_x + std::abs(j - nj) * width_y;
        
        double prev= divergance(i, j) + divergance(ni, nj);
        
        int n_cancel = std::min(people, changes[ni][nj].to[dir ^ 1]);
        int cnt = people - 2 * n_cancel;
        
        
        zone_info[i][j].num_worker -= people;
        zone_info[ni][nj].num_worker += people;
        double cur = divergance(i, j) + divergance(ni, nj);
        zone_info[i][j].num_worker += people;
        zone_info[ni][nj].num_worker -= people;

        if((cur - prev) * beta * total_num_order + dist * alpha <= 0.0f) {
          // std::cerr << "?" << std::endl;
          zone_info[i][j].num_worker -= people;
          zone_info[ni][nj].num_worker += people;
          changes[i][j].to[dir] += people - std::min(people, changes[ni][nj].to[dir ^ 1]);
          changes[ni][nj].to[dir^1] -= std::min(people, changes[ni][nj].to[dir ^ 1]);
          base += (cur - prev) * beta * total_num_order + dist * alpha;
        }
        // else {
        //   if(std::uniform_real_distribution<double>(0, 1)(rd) < success_rate) {
        //     zone_info[i][j].num_worker -= people;
        //     zone_info[ni][nj].num_worker += people;
        //     changes[i][j].to[dir] += people - std::min(people, changes[ni][nj].to[dir ^ 1]);
        //     changes[ni][nj].to[dir^1] -= std::min(people, changes[ni][nj].to[dir ^ 1]);
        //     base += (cur - prev) * beta + dist * alpha;
        //   }
        // }
      }
    }
    // people *= 0.7;
    success_rate *= 0.7;
    // n_try;
  }
  std::cerr << "final cost: " << base << std::endl;
  print();
  return base;
  // return ZoneMap(w, h, nullptr);
}