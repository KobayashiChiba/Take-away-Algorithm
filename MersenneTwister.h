#pragma once
#include <vector>
using namespace std;

#define ABS(x) ((x)>=0?(x):-(x))

void srand(int seed);
void generate();

unsigned int Rand();					//使用梅森旋转算法获取随机数

unsigned int Rand(unsigned int n);		//随机获取不超过 n 的整数

unsigned int Rand(int n);				//随机获取不超过|n|的整数

int Rand(int min,int max);              //随机获取[min,max]区间内的整数

double Rand(double n);					//随机获取不超过 n 的浮点数

double Rand(double min,double max);		//随机获取[min,max]区间内的整数

double GaussRand(double exp, double var);

/*在一维对象数组中抽签返回某一对象*/
template<class Type>
Type& Draw(int n, Type object[])        //等概率抽签
{
    return object[Rand(n)];
}

template<class Type>
Type& Draw(vector<Type>& object)       //在vector容器中等概率抽签
{
    return object[Rand(object.size())];
}

template<class Type>
vector<Type> Draw(vector<Type>& object,int n)       //在vector容器中等概率抽取n个样本
{
    if (n >= object.size())
    {
        return object;
    }
    else
    {
        int nd = 0;
        vector<int> nums;
        vector<Type> result;
        while (nd < n)
        {
            int r=Rand(object.size());
            bool repeat = false;
            for (int i : nums)
            {
                if (r == i)
                {
                    repeat = true;
                    break;
                }
            }
            if (repeat)
            {
                continue;
            }
            else
            {
                nums.push_back(r);
                result.push_back(object[r]);
                nd++;
            }
        }
        return result;
    }
}

template<class Type>
Type& Draw(int n, Type object[], int weight[])      //加权重抽签
{
    int* weight_sum = new int[n];
    weight_sum[0] = weight[0];
    for (int i = 1; i < n; i++)
    {
        weight_sum[i] = weight_sum[i - 1] + weight[i];
    }
    int rand = Rand(weight_sum[n - 1]);
    int i = 0;
    while (rand > weight_sum[i])
    {
        i++;
    }
    return object[i];
}

template<class Type>
Type& Draw(int n, Type object[], int& rand)        //等概率抽签,同时返回抽中的序号
{
    rand = Rand(n);
    return object[rand - 1];
}

template<class Type>
Type& Draw(int n, Type object[], int weight[], int& rand)      //加权重抽签,同时返回抽中的序号
{
    int* weight_sum = new int[n];
    weight_sum[0] = weight[0];
    for (int i = 1; i < n; i++)
    {
        weight_sum[i] = weight_sum[i - 1] + weight[i];
    }
    int rand = Rand(weight_sum[n - 1]);
    int i = 0;
    while (rand > weight_sum[i])
    {
        i++;
    }
    return object[i];
}