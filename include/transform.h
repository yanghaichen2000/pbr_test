#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <Eigen\Dense>

using Eigen::Matrix4f;

class Transform
{
private:
	// mΪ�任����mInvΪm�������
	// �洢mInv��Ϊ�˷�ֹ�ظ����о����������
	Matrix4f m, mInv;

public:
	Transform()
	{
		m << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
		mInv = m;
	}


};

#endif