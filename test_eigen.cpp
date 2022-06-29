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

	cout << (v1 + v2) << '\n' << endl; // 向量加
	cout << (v1 *= 2) << '\n' << endl; // 向量数乘
	cout << (v1 /= 2) << '\n' << endl; // 向量除法
	cout << (v1.dot(v2)) << '\n' << endl; // 向量点乘
	cout << (v1.cross(v2)) << '\n' << endl; // 向量叉乘
	cout << (v1.normalized()) << '\n' << endl; // 向量单位化（自己不变，去掉d则改变自身）

	std::ptrdiff_t index;
	auto value1 = v2.maxCoeff(&index);
	cout << value1 << ' ' << index << '\n' << endl; // 向量最大元素以及索引
	auto value2 = v2.minCoeff(&index);
	cout << value2 << ' ' << index << '\n' << endl; // 向量最小元素以及索引

	cout << v2.cwiseAbs() << '\n' << endl; // 向量中元素取绝对值
	cout << v1.cwiseMax(v2) << '\n' << endl; // 两个向量最大元素构成的向量
	cout << v1.cwiseMin(v2) << '\n' << endl; // 两个向量最小元素构成的向量

	cout << Permute(v1, 2, 1, 0) << '\n' << endl; // 根据给定的索引构造新向量

	Vector3f b1 = Vector3f(1, 2, 3).normalized();
	Vector3f b2, b3;
	CoordinateSystem(b1, &b2, &b3); // 根据一个单位向量构造坐标基，写入后两个指针对应向量
	cout << b1 << '\n' << b2 << '\n' << b3 << '\n' << endl;
	cout << b1.dot(b2) << '\n' << b2.dot(b3) << '\n' << b3.dot(b1) << '\n' << endl;

	cout << FaceForward(-v1, v2) << '\n' << endl; //生成相同朝向的向量

	int tmp;
	cin >> tmp;

	return 0;
}