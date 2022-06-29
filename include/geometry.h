#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include <Eigen\Dense>
#include "bounds.h"

using Eigen::Vector3f;


// 根据给定的索引构造新向量
Vector3f Permute(const Vector3f &v, int x, int y, int z)
{
	return Vector3f(v[x], v[y], v[z]);
}

// 根据一个向量构造基
// 其中v1必须为单位向量，v2,v3为传入的指针，存储另外两个基
inline void CoordinateSystem(const Vector3f &v1, Vector3f *v2, Vector3f *v3)
{
	if (std::abs(v1[0]) > std::abs(v1[1]))
		*v2 = Vector3f(-v1[2], 0, v1[0]) / std::sqrt(v1[0] * v1[0] + v1[2] * v1[2]);
	else
		*v2 = Vector3f(0, v1[2], -v1[1]) / std::sqrt(v1[1] * v1[1] + v1[2] * v1[2]);
	*v3 = v1.cross(*v2);
}

// 获得相同朝向的向量
// 输出n本身的复制或其反向，使其朝向和v一致
inline Vector3f FaceForward(const Vector3f &n, const Vector3f &v)
{
	return (n.dot(v) < 0.f) ? -n : n;
}

#endif