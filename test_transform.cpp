#include <iostream>
#include <Eigen\Dense>
#include "include/geometry.h"
#include "include/ray.h"
#include "include/bounds.h"
#include "include/transform.h"

using std::cin;
using std::cout;
using std::endl;
using Eigen::Vector3f;
using Eigen::Matrix3f;
using Eigen::Matrix4f;

int main()
{
	Matrix4f m1;
	m1 << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
	Transform t1(m1);
	cout << t1.m << "\n\n";
	cout << t1.mInv << "\n\n";

	Transform t2 = Transpose(t1);
	cout << t2.m << "\n\n";
	cout << t2.mInv << "\n\n";

	cout << t2.HasScale() << "\n\n";

	int tmp;
	cin >> tmp;

	return 0;
}