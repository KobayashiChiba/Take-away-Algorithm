// Take-away Algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "map/MersenneTwister.h"
#include "map/RandMap.h"
using namespace std;

int main()
{
	RandMap map;
	map.spawn();
	map.show_map(800, 600);
	system("pause");
}