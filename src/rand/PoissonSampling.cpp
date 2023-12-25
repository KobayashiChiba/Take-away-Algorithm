#include "PoissonSampling.hpp"
#include "MersenneTwister.hpp"

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
    // ���Դ�������
    constexpr int max_retry = 20;
    // n ��ֵ���� sqrt(ά��)
    auto n = sqrt(2);
    // threshold ���� sqrt(2)�����ñ�֤ÿһ�������б�߳�Ϊ threshold��
    // �Ӷ�ȷ��һ�������ڵ�����������ľ��붼��С�� threshold �ġ�
    // ����������Կ��ÿ��ٵ�ȷ������������ļ��С�� threshold��
    auto cell_size = threshold / n;
    // ��������
    int cols = ceil(range.x / cell_size);
    int rows = ceil(range.y / cell_size);
    // �������
    vector<vector<int>> grids;
    grids.resize(rows);
    for (auto& row : grids)
    {
        row.resize(cols, -1);
    }

    // ��ʼ
    // ���ѡһ����ʼ��
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
        // ���Ѿ��еĲ���������ȡһ����, ���������Χ�����µĲ�����
        auto key = active_list[Rand(unsigned int(active_list.size()))];
        // auto key = active_list[0];
        auto point = list[key];
        bool found = false;

        for (int i = 0; i < max_retry; i++)
        {
            auto direct = InsideUnitSphere();
            // ��ԭ�еĲ����� point ����һ������ [r, 2r) �������������Ϊ�µĲ�����
            auto new_point = point + ((direct.Normalized() * r) + (direct * r));
            if ((new_point.x < 0 || new_point.x >= range.x) ||
                (new_point.y < 0 || new_point.y >= range.y))
            {
                continue;
            }

            col = floor(new_point.x / cell_size);
            row = floor(new_point.y / cell_size);
            if (grids[row][col] != -1) // �������Ѿ��в�������
            {
                continue;
            }

            // ����²�������Χ�����Ƿ���ھ���С�� threshold �ĵ�
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
                            // �� ok Ϊ false �󣬺�����ѭ����ⶼû��������ˣ�
                            // ʹ�� return ��������ѭ����
                        }
                    }
                }
            }();

            // �²�����ɹ�����
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