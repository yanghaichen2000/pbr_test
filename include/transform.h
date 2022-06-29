#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <Eigen\Dense>

using Eigen::Matrix4f;

class Transform
{
private:
	// m为变换矩阵，mInv为m的逆矩阵
	// 存储mInv是为了防止重复进行矩阵求逆操作
	Matrix4f m, mInv;

public:
	Transform()
	{
		m << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
		mInv = m;
	}


};

#endif