#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
using namespace std;
template<typename T>
vector<vector<T>> transpose(vector<vector<T>> matrix) {
	//����ת��
	vector<vector<T>> array;
	vector<T> temparay;
	for (int i = 0; i < matrix[0].size(); ++i)// m*n ά����
	{
		for (int j = 0; j < matrix.size(); ++j) {
			temparay.push_back(matrix[j][i]);
		}
		array.push_back(temparay);
		temparay.erase(temparay.begin(), temparay.end());
	}
	return array;
}

template<typename T>
vector<T> operator+(vector<T> const& arr_a, vector<T> const& arr_b) {
	//���������
	int length = arr_a.size();
	vector<T>result(length);
	for (int i = 0; i < length; i++) {
		result[i] = arr_a[i] + arr_b[i];
	}
	return result;
}

template<typename T>
vector<T>& operator+=(vector<T>& arr_a, vector<T>& const arr_b) {
	//�����Լ�
	int length = arr_a.size();
	for (int i = 0; i < length; i++) {
		arr_a[i] += arr_b[i];
	}
	return arr_a;
}

template<typename T>
vector<vector<T>> operator+(vector<vector<T>> const& arr_a, vector<vector<T>> const& arr_b) {
	//���������
	int length = arr_a.size();
	vector<vector<T>>result(length);
	for (int i = 0; i < length; i++) {
		result[i] = arr_a[i] + arr_b[i];
	}
	return result;
}

template<typename T>
vector<vector<T>>& operator+=(vector<vector<T>>& arr_a, vector<vector<T>>const& arr_b) {
	//�����Լ�
	int length = arr_a.size();
	for (int i = 0; i < length; i++) {
		arr_a[i] += arr_b[i];
	}
	return arr_a;
}

template<typename T>
vector<T> operator-(vector<T> const& arr_a) {
	//���������ĸ�ֵ
	int length = arr_a.size();
	vector<T>result(length);
	for (int i = 0; i < length; i++) {
		result[i] = -arr_a[i];
	}
	return result;
}

template<typename T>
T operator*(vector<T> const& arr_a, vector<T> const& arr_b) {
	//����������
	T result = 0;
	for (int i = 0; i < arr_a.size(); i++) {
		result += arr_a[i] * arr_b[i];
	}
	return result;
}

template<typename T>
vector<T> operator*(vector<vector<T>>const& arr_a, vector<T>const& arr_b) {
	//���������
	vector<T> result(arr_a.size());
	for (int i = 0; i < arr_a.size(); i++) {
		result[i] = arr_a[i] * arr_b;
	}
	return result;
}

template<typename T>
vector<vector<T>> operator*(vector<vector<T>>const& arr_a, vector<vector<T>>const& arr_b) {
	//����˾���
	int row = arr_a.size();
	int col = arr_b[0].size();
	vector<vector<T>> temp = transpose(arr_b);
	vector<vector<T>> result = vector<vector<double>>(row, vector<double>(col));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result[i][j] = arr_a[i] * temp[j];
		}
	}
	return result;
}

template<typename T>
bool is_exist(vector<T> &arr,T data) {
	for (int i = 0; i < arr.size(); i++) {
		if (data == arr[i])return true;
	}
	return false;
}
#endif // !MATRIX_H