#include "RandMap.h"
#include "MersenneTwister.h"
#include <graphics.h>
#include <iostream>

double settlement::dr_rate = 0.5;
COLORREF c[] = {RGB(255,150,150), RGB(150,150,255) , RGB(255,100,255) ,RGB(255,0,0), RGB(0,0,255) , RGB(0,200,0) };

point settlement::spawn_point()
{
    point pr;
    pr.x = GaussRand(x, dvar);
    pr.y = GaussRand(y, dvar);
    pr.dr = dr_rate * dvar;
    switch (type)
    {
    case 0:
    case 1:
        pr.type = type;
        break;
    case 2:
        pr.type = Rand(2);
    }
    return pr;
}

settlement RandMap::spawn_settlement(Vec2 vec2, int type)
{
    settlement sr;
    sr.x = vec2.x + 0.1 * x_max;
    sr.y = vec2.y + 0.1 * y_max;
    double avg = (x_max + y_max) / 2;
    switch (type)
    {
    case 0:
        sr.dvar = Rand(rn_shop_min, rn_shop_max) * avg / 3;
        break;
    case 1:
        sr.dvar = Rand(rn_home_min, rn_home_max) * avg / 3;
        break;
    }
    sr.type = type;
    return sr;
}

int RandMap::spawn()
{
    /*
    vector<Vec2> vec2_list=FastPoissonDiscSampling({ 0.8*x_max,0.8*y_max }, 100);
    vector<Vec2> vec2_used = Draw(vec2_list, ns_shop + ns_home + ns_mix);
    cout << vec2_list.size();
    for (int i = 0; i < ns_shop + ns_home + ns_mix; i++)
    {
        if (i < ns_shop)
            settlement_list.push_back(spawn_settlement(vec2_used[i],0));
        else if (i < ns_shop + ns_home)
            settlement_list.push_back(spawn_settlement(vec2_used[i],1));
        else
            settlement_list.push_back(spawn_settlement(vec2_used[i],2));
    }*/

    vector<Vec2> s_shop_list = FastPoissonDiscSampling({ 0.8 * x_max,0.8 * y_max }, dn_shop);
    for (auto vec2 : s_shop_list)
    {
        settlement_list.push_back(spawn_settlement(vec2, 0));
    }
    vector<Vec2> s_home_list = FastPoissonDiscSampling({ 0.8 * x_max,0.8 * y_max }, dn_home);
    for (auto vec2 : s_home_list)
    {
        settlement_list.push_back(spawn_settlement(vec2, 1));
    }
    for (settlement s : settlement_list)
    {
        int n = 0;
        switch (s.type)
        {
        case 0:
            n = Rand(nn_shop_min, nn_shop_max);
            for (int i = 0; i < n; i++)
            {
                point_list.push_back(s.spawn_point());
            }
            break;
        case 1:
            n = Rand(nn_home_min, nn_home_max);
            for (int i = 0; i < n; i++)
            {
                point_list.push_back(s.spawn_point());
            }
            break;
        }
    }
    vector<Vec2> s_man_list = FastPoissonDiscSampling({ 0.8 * x_max,0.8 * y_max }, dn_man);
    for (auto vec2 : s_man_list)
    {
        point pr;
        pr.x = vec2.x + 0.1 * x_max;
        pr.y = vec2.y + 0.1 * x_max;
        pr.type = 2;
        point_list.push_back(pr);
    }
    return 0;
}

void RandMap::show_map(int w,int h)
{
    //生成白色背景的画布窗口
    initgraph(w, h);
    setfillcolor(RGB(255,255,255));
    solidrectangle(0, 0, w, h);

    //绘制全部聚落边界
    for (settlement s : settlement_list)
    {
        setlinecolor(c[s.type]);
        setlinestyle(PS_SOLID, 2);
        int zx = round(s.x / x_max * w);
        int zy = round(s.y / y_max * h);
        circle(zx, zy, 2 * s.dvar / x_max * w);
    }
    //绘制全部地点
    for (point p : point_list)
    {
        setfillcolor(c[p.type+3]);
        setlinestyle(PS_SOLID, 3);
        int zx = round(p.x / x_max * w);
        int zy = round(p.y / y_max * h);
        solidcircle(zx, zy, 2);
    }
}

