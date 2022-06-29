#include <iostream>
#include <Eigen\Dense>
#include "include/geometry.h"

using std::cin;
using std::cout;
using std::endl;
using Eigen::Vector3f;

int main()
{
	Vector3f v1(1, 3, 2);
	Vector3f v2(3, 4, -1);

	cout << (v1 + v2) << '\n' << endl; // ������
	cout << (v1 *= 2) << '\n' << endl; // ��������
	cout << (v1 /= 2) << '\n' << endl; // ��������
	cout << (v1.dot(v2)) << '\n' << endl; // �������
	cout << (v1.cross(v2)) << '\n' << endl; // �������
	cout << (v1.normalized()) << '\n' << endl; // ������λ�����Լ����䣬ȥ��d��ı�����

	std::ptrdiff_t index;
	auto value1 = v2.maxCoeff(&index);
	cout << value1 << ' ' << index << '\n' << endl; // �������Ԫ���Լ�����
	auto value2 = v2.minCoeff(&index);
	cout << value2 << ' ' << index << '\n' << endl; // ������СԪ���Լ�����

	cout << v2.cwiseAbs() << '\n' << endl; // ������Ԫ��ȡ����ֵ
	cout << v1.cwiseMax(v2) << '\n' << endl; // �����������Ԫ�ع��ɵ�����
	cout << v1.cwiseMin(v2) << '\n' << endl; // ����������СԪ�ع��ɵ�����

	cout << Permute(v1, 2, 1, 0) << '\n' << endl; // ���ݸ�������������������

	Vector3f b1 = Vector3f(1, 2, 3).normalized();
	Vector3f b2, b3;
	CoordinateSystem(b1, &b2, &b3); // ����һ����λ���������������д�������ָ���Ӧ����
	cout << b1 << '\n' << b2 << '\n' << b3 << '\n' << endl;
	cout << b1.dot(b2) << '\n' << b2.dot(b3) << '\n' << b3.dot(b1) << '\n' << endl;

	cout << FaceForward(-v1, v2) << '\n' << endl; //������ͬ���������

	int tmp;
	cin >> tmp;

	return 0;
}