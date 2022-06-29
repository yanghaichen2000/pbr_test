#include <iostream>
#include <Eigen\Dense>

using namespace std;

typedef Eigen::Matrix<int, 3, 3> Matrix3i;

int aaa()
{
	/*
	Matrix�ĳ�ʼ������
	Eigen::Matrix<int, 3, 3>
	int ����Matrix���������ͣ�3��3 �ֱ���� rows�� cols
	Matrix3i m1;
	m1(0,0) = 1
	m1(0,1) = 2
	m1(0,2) = 3
	...
	������ m1 << 1,2,3 ...
	*/

	Matrix3i m1;
	m1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	cout << "m1 = \n" << m1 << endl;

	Matrix3i m2;
	m2 << 1, 0, 0, 0, 1, 0, 0, 0, 1;
	cout << "m2 = \n" << m2 << endl;

	cout << "m1 * m2 = \n" << (m1 * m2) << endl;

	int tmp;
	cin >> tmp;

	return 0;
}