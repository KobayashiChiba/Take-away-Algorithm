#pragma once
#include<vector>
using namespace std;

template<typename T>
class Vec2_
{
public:
    template<typename OtherType>
    Vec2_(OtherType x, OtherType y)
        : x(static_cast<T>(x)),
        y(static_cast<T>(y)) {}
    Vec2_() : x(0), y(0) {}

    template<typename OtherType>
    Vec2_(const Vec2_<OtherType>& rhs)
        : x(static_cast<T>(rhs.x)),
        y(static_cast<T>(rhs.y))
    {}

    template<typename OtherType>
    Vec2_<T>& operator=(const Vec2_<OtherType>& rhs)
    {
        x = static_cast<T>(rhs.x);
        y = static_cast<T>(rhs.y);
        return *this;
    }

    bool operator==(const Vec2_& pt) const
    {
        return (this->x == pt.x && this->y == pt.y);
    }

    Vec2_ operator*(T n) const { return { x * n, y * n }; }

    Vec2_ operator+(T n) const { return { x + n, y + n }; }

    Vec2_ operator+(Vec2_ n) const { return { x + n.x, y + n.y }; }

    Vec2_ operator-(Vec2_ n) const { return { x - n.x, y - n.y }; }

    // 获取归一化的向量
    Vec2_<double> Normalized()
    {
        auto len = Magnitude();
        if (len != 0)
        {
            auto n = 1 / len;
            return { x * n, y * n };
        }
        else
        {
            return { 0, 0 };
        }
    }

    // 获取向量的长度
    double Magnitude() { return sqrt(x * x + y * y); }

    // 类型转换
    template<typename OtherType>
    operator Vec2_<OtherType>()
    {
        return { static_cast<OtherType>(x), static_cast<OtherType>(y) };
    }

    T x; //坐标点的x值
    T y; //坐标点的y值
};

typedef Vec2_<double> Vec2;

vector<Vec2> FastPoissonDiscSampling(Vec2 range, int threshold);