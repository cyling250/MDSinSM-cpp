#include "Structure.h"
#include"Matrix.h"
#include"common.h"
Structure::Structure()
{
	this->size_of_K = 0;
	//����Ĳ��������г�ʼ������nodesΪ��ʱ������������Ĳ���
}

void Structure::link(Node& node1,Node& node2,Element& element,bool link_way1,bool link_way2,double E,double I,double A) 
{
	//Element�����Ǳ���ģ�Ҫ��Structure���ɸ˼�������Ҫ�и����ò������������ɵĲ���
	if (!(node1.flag && node2.flag)) { printf("Node is not initialized."); return; }
	//��ṹע����
	if (!index_node(&node1)) {
		this->nodes.push_back((DDWORD)&node1); 
		Node::number++;//�����������
		node1.NO = Node::number;//������1���
	}
	if (!index_node(&node2)) {
		this->nodes.push_back((DDWORD)&node2);
		Node::number++;//�����������
		node2.NO = Node::number;//������2���
	}
	//��ṹע��˼�
	this->elements.push_back((DDWORD)&element);
	Element::number++;
	element.NO = Element::number;//����˼����

	//��˼�ע����
	element.nodes.push_back((DDWORD)&node1);
	element.nodes.push_back((DDWORD)&node2);
	element.link_way[0] = link_way1;
	element.link_way[1] = link_way2;
	//����ע��˼�
	node1.elements.push_back((DDWORD)&element);
	node2.elements.push_back((DDWORD)&element);
	node1.link_way.push_back(link_way1);
	node2.link_way.push_back(link_way2);
	//�˼��������

	//����˼���������
	double length = pow(pow(node1.loca[0] - node2.loca[0], 2) + pow(node1.loca[1] - node2.loca[1], 2), 0.5);
	element.L = length;
	element.E = E; element.I = I; element.A = A;

	//���ɾֲ����굥Ԫ�նȾ���
	vector<vector<double>> temp = {
		{E * A / length, 0, 0, -E * A / length, 0, 0},
		{0, 12 * E * I / pow(length, 3), 6 * E * I / pow(length, 2), 0, -12 * E * I / pow(length, 3), 6 * E * I / pow(length, 2)},
		{ 0, 6 * E * I / pow(length, 2), 4 * E * I / length, 0, -6 * E * I / pow(length, 2), 2 * E * I / length},
		{ -E * A / length, 0, 0, E * A / length, 0, 0},
		{0, -12 * E * I / pow(length, 3), -6 * E * I / pow(length, 2), 0, 12 * E * I / pow(length, 3), -6 * E * I / pow(length, 2)},
		{0, 6 * E * I / pow(length, 2), 2 * E * I / length, 0, -6 * E * I / pow(length, 2), 4 * E * I / length} 
	};
	if (link_way1 && link_way2) {
		//˵���������ˣ�ֱ��Լ��
		temp = {
		{E * A / length, 0, 0, -E * A / length, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{ -E * A / length, 0, 0, E * A / length, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0}
		};
	}
	//���ɶ�λ����
	double cosa = (node2.loca[0] - node1.loca[0]) / length;
	double sina = (node2.loca[1] - node1.loca[1]) / length;
	element.T = {
		{cosa, sina, 0, 0, 0, 0},
		{-sina, cosa, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 0, cosa, sina, 0},
		{0, 0, 0, -sina, cosa, 0},
		{0, 0, 0, 0, 0, 1}
	};
	vector<vector<double>> Tt = transpose(element.T);
	element.k_e = Tt * temp * element.T;//���㵥Ԫ�նȾ���
	//��ʱ��element��ֻ��restrain, load, delta, forceû�б���ֵ
}

int Structure::index_node(Node* node)
{
	//�����Ѿ�����Ľ�㣬����ҵ���ֱ�Ӹ�������������ţ����򷵻�-1
	for (int i = 0; i < this->nodes.size(); i++) {
		if ((DDWORD)node == this->nodes[i])return i;
	}
	return false;
}

int Structure::get_freedom()
{
	int freedom_num = 0;//��ʼ�����ɶȱ��
	for (int i = 0; i < this->nodes.size(); i++) {

		int link_temp = 0;
		Node* temp_node = (Node*)this->nodes[i];

		if (temp_node->is_splice()) {
			//���i��ȫ�½ӵ㣬�����ý������и˼�
			for (int j = 0; j < temp_node->elements.size(); j++) {
				Element* temp_element = (Element*)temp_node->elements[j];
				if (temp_element->nodes[0] == (DDWORD)temp_node) {
					//����ǵ�һ�����
					temp_element->freedom[0] = freedom_num;
					temp_element->freedom[1] = freedom_num + 1;
					temp_element->freedom[2] = freedom_num + 2 + link_temp;
				}
				else {
					//����ǵڶ������
					temp_element->freedom[3] = freedom_num;
					temp_element->freedom[4] = freedom_num + 1;
					temp_element->freedom[5] = freedom_num + 2 + link_temp;
				}
				link_temp++;
			}
		}
		else {
			//���i����ȫ�½ӵ�
			bool add = true;
			for (int j = 0; j < temp_node->elements.size(); j++) {
				Element* temp_element = (Element*)temp_node->elements[j];
				if (temp_element->nodes[0] == (DDWORD)temp_node) {
					//������Ǹõ�Ԫ�ĵ�һ�����
					if (temp_node->link_way[j]) {
						//����ý����õ�Ԫ���ӷ�ʽΪ�½�
						temp_element->freedom[0] = freedom_num;
						temp_element->freedom[1] = freedom_num + 1;
						temp_element->freedom[2] = freedom_num + 2 + link_temp;
						link_temp++;
					}
					else {
						//����ýڵ���õ�Ԫ���ӷ�ʽΪ�ս�
						temp_element->freedom[0] = freedom_num;
						temp_element->freedom[1] = freedom_num + 1;
						temp_element->freedom[2] = freedom_num + 2;
						if (add) {
							//����ǵ�һ�����,�սڵ�Ҳ��Ҫ��linktemp+1
							link_temp++;
							add = false;
						}
					}
				}
				else {
					//���Ǹõ�Ԫ�ĵڶ������
					if (temp_node->link_way[j]) {
						//����ý����õ�Ԫ���ӷ�ʽΪ�½�
						temp_element->freedom[3] = freedom_num;
						temp_element->freedom[4] = freedom_num + 1;
						temp_element->freedom[5] = freedom_num + 2 + link_temp;
						link_temp++;
					}
					else {
						//����ýڵ���õ�Ԫ���ӷ�ʽΪ�ս�
						temp_element->freedom[3] = freedom_num;
						temp_element->freedom[4] = freedom_num + 1;
						temp_element->freedom[5] = freedom_num + 2;
						if (add) {
							//����ǵ�һ�����,�սڵ�Ҳ��Ҫ��linktemp+1
							link_temp++;
							add = false;
						}
					}
				}
			}
		}

		for (int k = freedom_num; k < freedom_num + 3 + link_temp; k++) {
			temp_node->freedom.push_back(k);
		}
		freedom_num += 2 + link_temp;
	}
	this->size_of_K = freedom_num;
	return freedom_num;
}

void Structure::get_K()
{
	//��ʼ��
	this->K = vector<vector<double>>(this->size_of_K, vector<double>(this->size_of_K));
	for (int k = 0; k < this->elements.size(); k++) {
		vector<int> Lambda = ((Element*)this->elements[k])->freedom;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				this->K[Lambda[i]][Lambda[j]] += ((Element*)this->elements[k])->k_e[i][j];
			}
		}
	}
}

void Structure::get_load()
{
	this->load = vector<double>(this->size_of_K);
	//�ȴ��������
	for (int i = 0; i < this->nodes.size(); i++) {
		Node* temp_node = (Node*)this->nodes[i];
		vector<int> Lambda = temp_node->freedom;
		for (int j = 0; j < 3; j++) {
			this->load[Lambda[j]] += temp_node->load[j];//��㲻��Ҫ����
		}
	}
	//�ٴ����Ч����
	for (int i = 0; i < this->elements.size(); i++) {
		Element* temp_element = (Element*)this->elements[i];
		vector<int>Lambda = temp_element->freedom;
		vector<vector<double>> T = temp_element->T;
		temp_element->load = -(transpose(T) * temp_element->load);
		for (int j = 0; j < 6; j++) {
			this->load[Lambda[j]] += temp_element->load[j];
		}
	}
}

void Structure::add_restrain()
{
	//���Լ������ֻ�ܶԸ˼����Լ���������Լ��ֱ�ӽ��л��л���
	vector<int>delete_temp;//��Ҫɾ�������ɶ�
	this->in_result = vector<int>(this->size_of_K);
	for (int i = 0; i < this->elements.size(); i++) {
		Element* temp_element = (Element*)this->elements[i];
		for (int j = 0; j < 6; j++) {
			if (temp_element->restrain[j] == -1) {
				//˵�������ɶȱ�Լ��ס��
				this->in_result[temp_element->freedom[j]] = -1;
				if (!is_exist(delete_temp, temp_element->freedom[j]))
					delete_temp.push_back(temp_element->freedom[j]);
			}
		}
	}

	int real_size = this->size_of_K - delete_temp.size();
	vector<vector<double>> temp_k = vector<vector<double>>(real_size, vector<double>(real_size));
	vector<double> temp_load = vector<double>(real_size);
	int count_i = 0, count_j = 0;
	for (int i = 0; i < this->size_of_K; i++) {
		if (is_exist(delete_temp, i))continue;
		for (int j = 0; j < this->size_of_K; j++) {
			if (is_exist(delete_temp, j))continue;
			temp_k[count_i][count_j] = this->K[i][j];//ֻ�е�����������delete_temp�о�δ����ʱ������д��
			count_j++;
		}
		temp_load[count_i] = this->load[i];
		count_i++;
		count_j = 0;
	}
	this->load = temp_load;
	this->K = temp_k;
}

Structure::~Structure()
{
}
