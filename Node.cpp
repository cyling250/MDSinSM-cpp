#include "Node.h"
#include"common.h"
int Node::number = 0;//��ʼ����̬���ݳ�ԱΪ0��û�нڵ�
Node::Node()
{
	//����Ϊ��֧��������ʽ�Ĵ���������д�ĺ���
	this->NO = 0;//�Ƿ�Structure�����ı�־
	this->flag = false;//����Ƿ���Ч�ı�־
	this->loca = vector<double>(2);
	this->load = vector<double>(3);
}

Node::Node(double const node1, double const node2)
{
	//������ʼ���������꣬�����û�б�Structure���������ʼ�ղ���������
	this->loca.push_back(node1);
	this->loca.push_back(node2);
	this->load = vector<double>(3);
	this->flag = true;
}

void Node::set_loca(double const node1, double const node2)
{
	//������ʼ���������꣬�����û�б�Structure���������ʼ�ղ���������
	this->loca[0] = node1; this->loca[1] = node2;
	this->flag = true;
}

bool Node::is_splice()
{
	for (int i = 0; i < link_way.size(); i++) {
		//�����һ���սӣ�����ȫ�½ӵ㣬����ʽ����Ҫ���⴦��
		if (!this->link_way[i])return false;//��ȫ�½ӵ�
	}
	return true;//ȫ�½ӵ�
}

bool Node::is_rigid()
{
	for (int i = 0; i < link_way.size(); i++) {
		//�����һ���½ӣ�����ȫ�սӵ�
		if (this->link_way[i])return false;//��ȫ�սӵ�
	}
	return true;//ȫ�սӵ�
}

void Node::set_load(double load1,double load2,double load3)
{
	//��Ӻ���
	this->load[0] = load1;
	this->load[1] = load2;
	this->load[2] = load3;
	if (this->is_rigid() && load3 != 0) {
		printf("Warning: can't add moment to anti-rigid node.\n");
		this->load[2] = 0;
	}
}

void Node::print()
{
	if (this->NO == 0) {
		//ֻ�б��������Ľ����ܱ���ӡ
		printf("Can't print an uninitialized node.\n");
	}
	else {
		printf("Node:%d(%.2f,%.2f)\n", this->NO, this->loca[0], this->loca[1]);
	}
}

Node::~Node()
{
}