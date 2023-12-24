#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
#include <math.h>
#include "MersenneTwister.h"
using namespace std;

/*÷ɭ��ת�㷨����ȡ���������������*/
bool isInit;
int index;
unsigned int MT[624];  //624 * 32 - 31 = 19937

void srand(int seed)
{
    cout << seed << endl;
    index = 0;
    isInit = 1;
    MT[0] = seed;
    //�����������Ԫ�ؽ��г�ʼ��
    for (int i = 1; i < 624; i++)
    {
        unsigned int t = 1812433253 * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
        MT[i] = t & 0xffffffff;   //ȡ����32λ����MT[i]
    }
}

void generate()
{
    for (int i = 0; i < 624; i++)
    {
        // 2^31 = 0x80000000
        // 2^31-1 = 0x7fffffff
        unsigned int y = (MT[i] & 0x80000000) + (MT[(i + 1) % 624] & 0x7fffffff);
        MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
        if (y & 1)
            MT[i] ^= 2567483615;
    }
}

/*ʹ��÷ɭ��ת�㷨��ȡ�����*/
unsigned int Rand()
{
    if (!isInit)
        srand((int)time(NULL));//(int)time(NULL)
    if (index == 0)
        generate();
    unsigned int y = MT[index];
    y = y ^ (y >> 11);                 //y����11��bit
    y = y ^ ((y << 7) & 2636928640);   //y����7��bit��2636928640���룬����y�������
    y = y ^ ((y << 15) & 4022730752);  //y����15��bit��4022730752���룬����y�������
    y = y ^ (y >> 18);                 //y����18��bit����y�������
    index = (index + 1) % 624;
    return y;
}

unsigned int Rand(unsigned int max)    //�����ȡ������max��������
{
    unsigned int range = 4294967295 - 4294967296 % max;
    while (1)
    {
        unsigned int rand = Rand();
        if (rand <= range)
            return rand % max;
    }
}

unsigned int Rand(int max)              //�����ȡ������ |max| ��������
{
    unsigned int a = 4294967296 % ABS(max);
    unsigned int range = 4294967295 - 4294967296 % ABS(max);
    while (1)
    {
        unsigned int rand = Rand();
        if (rand <= range)
            return rand % ABS(max);
    }
}

int Rand(int min, int max)
{
    return Rand(max - min) + min;
}

double Rand(double max)                 //�����ȡ������max�ĸ�����
{
    return double(Rand()) * max / 4294967296.0;
}

double Rand(double min, double max)
{
    return Rand(max - min) + min;
}

double GaussRand(double exp, double var)
{
    double r1, r2, A, B, C, r;
    r1 = Rand(1.0);
    r2 = Rand(1.0);
    A = sqrt((-2) * log(r1));
    B = 2 * 3.1415926 * r2;
    C = A * cos(B);
    r = exp + C * var;    //E,D�ֱ��������ͷ���
    return r;
}
