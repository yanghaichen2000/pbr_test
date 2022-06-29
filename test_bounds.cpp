#include <iostream>
#include <Eigen\Dense>
#include "include/geometry.h"
#include "include/ray.h"
#include "include/bounds.h"

using std::cin;
using std::cout;
using std::endl;
using Eigen::Vector3f;

int main()
{
	Vector3f v1(1, 3, 2);
	Vector3f v2(3, 4, -1);

	Bounds3f b1(v1, v2);
	cout << b1.pMin << '\n' << b1.pMax << '\n' << endl;
	cout << b1[0] << '\n' << b1[1] << '\n' << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "corner " << i << endl;
		cout << b1.Corner(i) << '\n' << endl;
	}

	Vector3f v3(2, 2, 3);
	Bounds3f b2 = Union(b1, v3);
	cout << b2.pMin << '\n' << b2.pMax << '\n' << endl;

	Bounds3f b3 = Union(b1, b2);
	cout << b3.pMin << '\n' << b3.pMax << '\n' << endl;

	cout << b3.SurfaceArea() << '\n' << endl;

	cout << b1.Offset(Vector3f(2, 3.5, 0.5)) << '\n' << endl;

	Vector3f *center = new Vector3f;
	float *radius = new float;
	b1.BoundingSphere(center, radius);
	cout << *center << '\n' << *radius << '\n' << endl;

	int tmp;
	cin >> tmp;

	return 0;
}