// Take-away Algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "rand/MersenneTwister.hpp"
#include "map/RandMap.hpp"
#include "zone/zone.hpp"

using namespace std;

int main()
{
	RandMap map;
	map.spawn();
	// map.show_map(800, 600);
	ZoneMap x = ZoneMap(16, 12, &map);
	std::cerr << x.KL_Divergence() << std::endl;
	// system("pause");
}