#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

#include <Eigen\Dense>

using Eigen::Vector3f;

// ��Ȩ��ϣ�Ȩ�طֱ�Ϊ(1-t)��t
template <typename T>
inline T Lerp(float t, T v1, T v2)
{
	return (1 - t) * v1 + t * v2;
}

#endif