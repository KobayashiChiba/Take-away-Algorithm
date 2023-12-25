#include "RandMap.hpp"
#include "rand/MersenneTwister.hpp"
// #include <graphics.h>
#include <iostream>

double settlement::dr_rate = 0.5;
// COLORREF c[] = {RGB(255,150,150), RGB(150,150,255) , RGB(255,100,255) ,RGB(255,0,0), RGB(0,0,255) , RGB(0,200,0) };

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
    for(auto p : point_list) {
        std::cout << p.x << " " << p.y << " " << p.type << std::endl;
    }
}

