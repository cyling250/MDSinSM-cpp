#ifndef ELEMENT_H
#define ELEMENT_H
#include"Node.h"
#include<vector>
typedef __int64 DDWORD;
using namespace std;
class Element {
public:
	static int number;//��Ԫ����������Ϊ��̬���ݳ�Ա
	int NO;//�Ƿ�Structure�����ı�־
	vector<DDWORD> nodes;//���ָ��
	vector<bool> link_way;
	vector<int> freedom;//���ɶ�����
	double E;//����ģ��
	double I;//������Ծ�
	double L;//�˼�����
	double A;//�������
	vector<vector<double>> k_e; //�˼��ľֲ��նȾ���
	vector<vector<double>> T; //�˼�������ת������
	vector<int> restrain;//�˼�Լ��
	vector<double> load;//�˼�����
	vector<double> delta;//�˶�λ��
	vector<double> force;//�˶�����

	Element();
	void add_restrain(vector<int>);//Add restrain to element
	void set_load(vector<double>);//Element Load
	void print();
	~Element();
};
#endif