#include "Element.h"
#include"common.h"
#include"Matrix.h"
int Element::number = 0;//��ʼ����̬���ݳ�Ա
Element::Element()
{
	//Ϊ�˷��㹹�쵥Ԫ���飬��Ҫд�Ĺ��캯��
	this->NO = 0;//��ʼ����Ԫ���Ϊ0
	this->link_way = vector<bool>(2);
	this->freedom = vector<int>(6);//Each element has 6 freedoms
	this->E = 0; this->I = 0; this->L = 0; this->A = 0;
	this->k_e = vector<vector<double>>(6,vector<double>(6));//k_e is 6*6
	this->T = vector<vector<double>>(6, vector<double>(6));//T is 6*6
	this->restrain = vector<int>(6);
	this->load = vector<double>(6);
	this->delta = vector<double>(6);
	this->force = vector<double>(6);
}

void Element::add_restrain(vector<int> restrain)
{
	this->restrain = restrain;
}

void Element::set_load(vector<double> load)
{
	if (load[0] == 0) {
		//���ϼ��к��ص���ʽ[0,Fp,a],Fp�����Ĵ�С��a�Ǽ��������˼���������˵ľ���
		double b = this->L - load[2];
		double a = load[2];
		double fp = load[1];
		vector<double>arr = {
			0, -fp * pow(b,2) * (1 + 2 * a / L) / pow(L,2), -fp * a * pow(b,2) / pow(L,2),
			0, -fp * pow(a,2) * (1 + 2 * b / L) / pow(L,2), fp * a * pow(b,2) / pow(L,2)
		};
		this->load += arr;
	}
	else if (load[0]==1) {
		//1��ʾ�˶���أ�Load[1]��Ÿ�������,Load[2]��Ÿ��Ҷ����
		this->load[2] -= load[1];
		this->load[5] -= load[2];
	}
	else if (load[0] == 2) {
		//2��ʾ�������أ�Load[1]��ž������صĴ�С
		double q = load[1];
		vector<double>arr = {
			0., -q * L / 2., -q * pow(L,2) / 12.,
			0., -q * L / 2., q* pow(L,2) / 12.
		};
		this->load += arr;
	}
	else if (load[0] == 3) {
		//3��ʾ���е�б�ȵľ�������
		double q = load[1];
		double cosa = this->T[0][0];
		vector<double>arr = {
			0., -q * L / 2. * cosa, -q * pow(L,2) / 12. * pow(cosa,2),
			0., -q * L / 2. * cosa, q * pow(L,2) / 12. * pow(cosa,2)
		};
		this->load = this->load + this->T * arr;
	}
}

void Element::print()
{
	if (this->NO == 0) {
		//ֻ�б��������ĸ˼����ܱ���ӡ
		printf("Can't print an uninitialized element.\n");
	}
	else {
		printf("Element:%d\nLink nodes:\n", this->NO);
		((Node*)this->nodes[0])->print();
		((Node*)this->nodes[1])->print();
		printf("link_way:%s,", this->link_way[0] ? "Hinge" : "Rigid");
		printf("%s\n", this->link_way[1] ? "Hinge" : "Rigid");
		printf("E=%.2f, I=%.2f, A=%.2f, L=%.2f\n\n", this->E, this->I, this->A,this->L);
	}
}

Element::~Element()
{

}