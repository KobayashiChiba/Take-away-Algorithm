#ifndef MERSENNETWISTER_HPP_
#define MERSENNETWISTER_HPP_

#include <vector>
// using namespace std;

#define ABS(x) ((x)>=0?(x):-(x))

void srand(int seed);
void generate();

unsigned int Rand();					//ʹ��÷ɭ��ת�㷨��ȡ�����

unsigned int Rand(unsigned int n);		//�����ȡ������ n ������

unsigned int Rand(int n);				//�����ȡ������|n|������

int Rand(int min,int max);              //�����ȡ[min,max]�����ڵ�����

double Rand(double n);					//�����ȡ������ n �ĸ�����

double Rand(double min,double max);		//�����ȡ[min,max]�����ڵ�����

double GaussRand(double exp, double var);

/*��һά���������г�ǩ����ĳһ����*/
template<class Type>
Type& Draw(int n, Type object[])        //�ȸ��ʳ�ǩ
{
    return object[Rand(n)];
}

template<class Type>
Type& Draw(std::vector<Type>& object)       //��vector�����еȸ��ʳ�ǩ
{
    return object[Rand(object.size())];
}

template<class Type>
std::vector<Type> Draw(std::vector<Type>& object,int n)       //��vector�����еȸ��ʳ�ȡn������
{
    if (n >= object.size())
    {
        return object;
    }
    else
    {
        int nd = 0;
        std::vector<int> nums;
        std::vector<Type> result;
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
Type& Draw(int n, Type object[], int weight[])      //��Ȩ�س�ǩ
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
Type& Draw(int n, Type object[], int& rand)        //�ȸ��ʳ�ǩ,ͬʱ���س��е����
{
    rand = Rand(n);
    return object[rand - 1];
}

template<class Type>
Type& Draw(int n, Type object[], int weight[], int& rand)      //��Ȩ�س�ǩ,ͬʱ���س��е����
{
    int* weight_sum = new int[n];
    weight_sum[0] = weight[0];
    for (int i = 1; i < n; i++)
    {
        weight_sum[i] = weight_sum[i - 1] + weight[i];
    }
    rand = Rand(weight_sum[n - 1]);
    int i = 0;
    while (rand > weight_sum[i])
    {
        i++;
    }
    return object[i];
}

#endif