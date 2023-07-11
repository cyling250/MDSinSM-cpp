#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<vector>
#include"Node.h"
#include"Element.h"
typedef __int64 DDWORD;
class Structure {
public:
	//�ṹ����Ҫ����˼������࣬�������ɽṹ�๹��
	vector<DDWORD> nodes;
	vector<DDWORD> elements;

	int size_of_K;//����նȾ���ά��
	vector<int> in_result;//λ�ƶ�λ����Э����������
	vector<vector<double>> K;//����նȾ���
	vector<double> load;//�����������
	vector<double>result;//������λ�ƾ���

	Structure();
	void link(Node&, Node&, Element&, bool link_way1 = false, bool link_way2 = false, double E = 1, double I = 1, double A = 1);//���Ӹ˼�
	int index_node(Node*);//�ڽ�������в��ҽ�㣬�ҵ��򷵻ؽ���ţ����򷵻�NULL
	int get_freedom();//Ϊÿ���˼����ɶ�λ����
	void get_K();//��������նȾ���
	void get_load();//������������
	void add_restrain();//���Լ����������նȾ�����������������л���
	~Structure();
};
#endif