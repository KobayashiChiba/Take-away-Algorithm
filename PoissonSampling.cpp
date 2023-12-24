#include "PoissonSampling.h"
#include "MersenneTwister.h"

Vec2 InsideUnitSphere()
{
    double theta = Rand(360 * 1000) / 1000.0;
    double r = Rand(1000) / 1000.0;
    return { (sqrt(r) * cos(theta)), (sqrt(r) * sin(theta)) };
}

vector<Vec2> FastPoissonDiscSampling(Vec2 range, int threshold)
{
    // boost::timer t;
    vector<Vec2> list;
    // 重试次数上限
    constexpr int max_retry = 20;
    // n 的值等于 sqrt(维度)
    auto n = sqrt(2);
    // threshold 除上 sqrt(2)，可用保证每一个区块的斜边长为 threshold，
    // 从而确保一个区块内的任意两个点的距离都是小于 threshold 的。
    // 利用这个特性可用快速的确定两个采样点的间距小于 threshold。
    auto cell_size = threshold / n;
    // 划分区块
    int cols = ceil(range.x / cell_size);
    int rows = ceil(range.y / cell_size);
    // 区块矩阵
    vector<vector<int>> grids;
    grids.resize(rows);
    for (auto& row : grids)
    {
        row.resize(cols, -1);
    }

    // 开始
    // 随机选一个初始点
    auto start = Vec2{ Rand(range.x), Rand(range.y) };
    int col = floor(start.x / cell_size);
    int row = floor(start.y / cell_size);

    auto start_key = list.size();
    list.push_back(start);
    grids[row][col] = start_key;

    vector<int> active_list;
    active_list.push_back(start_key);

    double r = threshold;
    while (active_list.size() > 0)
    {
        // 在已经有的采样集合中取一个点, 在这个点周围生成新的采样点
        auto key = active_list[Rand(active_list.size())];
        // auto key = active_list[0];
        auto point = list[key];
        bool found = false;

        for (int i = 0; i < max_retry; i++)
        {
            auto direct = InsideUnitSphere();
            // 给原有的采样点 point 加上一个距离 [r, 2r) 的随机向量，成为新的采样点
            auto new_point = point + ((direct.Normalized() * r) + (direct * r));
            if ((new_point.x < 0 || new_point.x >= range.x) ||
                (new_point.y < 0 || new_point.y >= range.y))
            {
                continue;
            }

            col = floor(new_point.x / cell_size);
            row = floor(new_point.y / cell_size);
            if (grids[row][col] != -1) // 区块内已经有采样点类
            {
                continue;
            }

            // 检查新采样点周围区块是否存在距离小于 threshold 的点
            bool ok = true;
            int min_r = floor((new_point.y - threshold) / cell_size);
            int max_r = floor((new_point.y + threshold) / cell_size);
            int min_c = floor((new_point.x - threshold) / cell_size);
            int max_c = floor((new_point.x + threshold) / cell_size);
            [&]() {
                for (int r = min_r; r <= max_r; r++)
                {
                    if (r < 0 || r >= rows)
                    {
                        continue;
                    }
                    for (int c = min_c; c <= max_c; c++)
                    {
                        if (c < 0 || c >= cols)
                        {
                            continue;
                        }
                        int point_key = grids[r][c];
                        if (point_key != -1)
                        {
                            auto round_point = list[point_key];
                            auto dist = (round_point - new_point).Magnitude();
                            if (dist < threshold)
                            {
                                ok = false;
                                return;
                            }
                            // 当 ok 为 false 后，后续的循环检测都没有意义的了，
                            // 使用 return 跳出两层循环。
                        }
                    }
                }
            }();

            // 新采样点成功采样
            if (ok)
            {
                auto new_point_key = list.size();
                list.push_back(new_point);
                grids[row][col] = new_point_key;
                active_list.push_back(new_point_key);
                found = true;
                break;
            }
        }

        if (!found)
        {
            auto iter = find(active_list.begin(), active_list.end(), key);
            if (iter != active_list.end())
            {
                active_list.erase(iter);
            }
        }
    }
    return list;
}