#ifndef NODE_H
#define NODE_H
#include<Windows.h>
#include"Element.h"
#include<vector>
typedef __int64 DDWORD;
using namespace std;
class Node {
public:
	static int number;//�ڵ�����
	int NO;//�ڵ���
	bool flag;//��Ч��ָ��,false��ʾ�ý�㲻����,true��ʾ����
	//ֻҪ��������ȷ�������ͱ�Ϊ����
	vector<double> loca;//��Žڵ�����,��ʼ��Ϊ[0,0]
	vector<DDWORD> elements;//��Ԫ���ָ�룬ָ��Ԫ�ı������
	vector<bool> link_way;//���ӷ�ʽָ�룬�ս���false���½���true
	vector<double> load;//��Žڵ���أ��ڵ�ƽ��x��ƽ��y��ת��
	vector<int> freedom;//�ڵ����ɶȱ�ţ�һ��������Ԫ�أ���½ӵ������⴦����

	Node();//�չ��캯�������������ڵ��������
	Node(double,double);//����ͨ�����ýڵ���������ʼ���ڵ�
	void set_loca(double, double);//���ýڵ�����
	bool is_splice();//�ж��Ƿ���ȫ�½ڵ�
	bool is_rigid();//�ж��Ƿ���ȫ�սڵ�
	void set_load(double load1 = 0, double loda2 = 0, double load3 = 0);//�������Ӻ���
	void print();
	~Node();
};
#endif