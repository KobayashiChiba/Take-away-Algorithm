#ifndef RANDMAP_HPP_
#define RANDMAP_HPP_

#include <vector>
#include "rand/PoissonSampling.hpp"
using namespace std;

class point
{
public:
	double x = 0;			//x����
	double y = 0;			//y����
	double dr = 0;			//������븡������������Ϊ�õ�����¥�ȶ�����룩
	int type = 0;			//�ص����ͣ�0-���̣�1-�ͻ���2-����Ա
	int settlement = 0;		//������
};

class settlement
{
	static double dr_rate;	//���ɵ�ʱ�������dr��dvar�ı�ֵ
public:
	double x = 0;			//x����
	double y = 0;			//y����
	double dvar = 0;		//���뷽�������ܼ��̶�
	int type = 0;			//�������ͣ�0-���̣�1-�ͻ���2-���
	point spawn_point();	//���������
};

class RandMap
{
public:
	int spawn();
	
	settlement spawn_settlement(Vec2 vec2,int type);
	
	void show_map(int w,int h);

	double get_x_max() {return x_max;}
	double get_y_max() {return x_max;}
	vector<settlement>& get_settlement_list() {return settlement_list;}
	vector<point>& get_point_list() {return point_list;}
private:
	/*��������*/
	double x_max=8000;		//��ͼ���ȣ�m��
	double y_max=6000;		//��ͼ�߶ȣ�m��
	double dn_shop = 1000;	//��Ȧ���
	double dn_home = 800;	//С�����
	double dn_man = 200;	//����Ա���
	double rn_shop_min = 0.04;		//��Ȧ��Χ��Сֵ����Ȧ�뾶���ͼ������ֵ�ı�
	double rn_shop_max = 0.06;		//��Ȧ��Χ���ֵ
	double rn_home_min = 0.07;		//С����Χ��Сֵ
	double rn_home_max = 0.10;		//С����Χ���ֵ
	int nn_shop_min = 30;		//��Ȧ�ܶ���Сֵ����Ȧ�а������̵�����
	int nn_shop_max = 50;		//��Ȧ�ܶ����ֵ
	int nn_home_min = 50;		//С���ܶ���Сֵ
	int nn_home_max = 100;		//С���ܶ����ֵ
	vector<settlement> settlement_list;
	vector<point> point_list;
};

#endif