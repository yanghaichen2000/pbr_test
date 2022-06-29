#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include <Eigen\Dense>
#include "bounds.h"

using Eigen::Vector3f;


// ���ݸ�������������������
Vector3f Permute(const Vector3f &v, int x, int y, int z)
{
	return Vector3f(v[x], v[y], v[z]);
}

// ����һ�����������
// ����v1����Ϊ��λ������v2,v3Ϊ�����ָ�룬�洢����������
inline void CoordinateSystem(const Vector3f &v1, Vector3f *v2, Vector3f *v3)
{
	if (std::abs(v1[0]) > std::abs(v1[1]))
		*v2 = Vector3f(-v1[2], 0, v1[0]) / std::sqrt(v1[0] * v1[0] + v1[2] * v1[2]);
	else
		*v2 = Vector3f(0, v1[2], -v1[1]) / std::sqrt(v1[1] * v1[1] + v1[2] * v1[2]);
	*v3 = v1.cross(*v2);
}

// �����ͬ���������
// ���n����ĸ��ƻ��䷴��ʹ�䳯���vһ��
inline Vector3f FaceForward(const Vector3f &n, const Vector3f &v)
{
	return (n.dot(v) < 0.f) ? -n : n;
}

#endif