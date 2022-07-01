#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <Eigen\Dense>

using Eigen::Matrix4f;
using Eigen::Matrix3f;
using Eigen::Vector3f;

class Transform
{
	friend Transform Inverse(const Transform &t);
	friend Transform Transpose(const Transform &t);

public:
	// mΪ�任����mInvΪm�������
	// �洢mInv��Ϊ�˷�ֹ�ظ����о����������
	Matrix4f m, mInv;

public:
	Transform()
	{
		m << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
		mInv = m;
	}


	Transform(const Matrix4f &m_)
	{
		m = m_;
		mInv = m.inverse();
	}

	Transform(const Matrix4f &m_, const Matrix4f &mInv_)
	{
		m = m_;
		mInv = mInv_;
	}

	// ���Transform�Ƿ��������Ч����û�з�����ֻ������ת��ƽ�ƣ�
	bool HasScale() const
	{
		Matrix3f mat3;
		mat3 << m(0, 0), m(0, 1), m(0, 2), m(1, 0), m(1, 1), m(1, 2), m(2, 0), m(2, 1), m(2, 2);
		Vector3f v[3];
		v[0] << 1, 0, 0;
		v[1] << 0, 1, 0;
		v[2] << 0, 0, 1;
		for (int i = 0; i < 3; i++)
		{
			Vector3f vtmp = mat3 * v[i];
			float f = vtmp.dot(vtmp);
			if (f < 0.999f or f > 1.001f) return true;
		}
		return false;
	}


};

Transform Inverse(const Transform &t)
{
	return Transform(t.mInv, t.m);
}

// ת��
Transform Transpose(const Transform &t)
{
	return Transform(t.m.transpose(), t.mInv.transpose());
}

// ��ȡƽ�Ʊ任
Transform Translate(const Vector3f &delta)
{
	Matrix4f m, mInv;
	m << 1, 0, 0, delta[0],
		0, 1, 0, delta[1],
		0, 0, 1, delta[2],
		0, 0, 0, 1;
	mInv << 1, 0, 0, -delta[0],
		0, 1, 0, -delta[1],
		0, 0, 1, -delta[2],
		0, 0, 0, 1;
	return Transform(m, mInv);
}

// ��ȡ�����任
Transform Scale(float x, float y, float z)
{
	Matrix4f m, mInv;
	m << x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1;
	mInv << 1.0f / x, 0, 0, 0,
		0, 1.0f / y, 0, 0,
		0, 0, 1.0f / z, 0,
		0, 0, 0, 1;
	return Transform(m, mInv);
}

#endif