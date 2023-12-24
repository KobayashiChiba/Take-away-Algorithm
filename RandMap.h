#pragma once
#include <vector>
#include "PoissonSampling.h"
using namespace std;

class point
{
public:
	double x = 0;			//x坐标
	double y = 0;			//y坐标
	double dr = 0;			//随机距离浮动（可以理解为该点上下楼等额外距离）
	int type = 0;			//地点类型，0-商铺，1-客户，2-外卖员
	int settlement = 0;		//聚落编号
};

class settlement
{
	static double dr_rate;	//生成点时随机浮动dr与dvar的比值
public:
	double x = 0;			//x坐标
	double y = 0;			//y坐标
	double dvar = 0;		//距离方差，聚落的密集程度
	int type = 0;			//聚落类型，0-商铺，1-客户，2-混合
	point spawn_point();	//生成随机点
};

class RandMap
{
	/*调参区域*/
	double x_max=8000;		//地图宽度（m）
	double y_max=6000;		//地图高度（m）
	double dn_shop = 1000;	//商圈间距
	double dn_home = 800;	//小区间距
	double dn_man = 200;	//外卖员间距
	double rn_shop_min = 0.04;		//商圈范围最小值，商圈半径与地图长宽均值的比
	double rn_shop_max = 0.06;		//商圈范围最大值
	double rn_home_min = 0.07;		//小区范围最小值
	double rn_home_max = 0.10;		//小区范围最大值
	int nn_shop_min = 30;		//商圈密度最小值，商圈中包含店铺的数量
	int nn_shop_max = 50;		//商圈密度最大值
	int nn_home_min = 50;		//小区密度最小值
	int nn_home_max = 100;		//小区密度最大值
	vector<settlement> settlement_list;
	vector<point> point_list;
public:
	int spawn();
	settlement spawn_settlement(Vec2 vec2,int type);
	void show_map(int w,int h);
};