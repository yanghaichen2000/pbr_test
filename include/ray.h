#ifndef _RAY_H_
#define _RAY_H_
#include <Eigen\Dense>

using Eigen::Vector3f;

// ��ʱû��ʹ��medium��֮����Ҫ���ĳ�Ա�����͹��캯��
class Ray
{
public:
	Vector3f o; // ���
	Vector3f d; // ��������
	mutable float tMax; // ������
	float time;
	//const Medium *medium;

	Ray() : tMax(FLT_MAX), time(0.f) {}
	Ray(const Vector3f &o_, const Vector3f &d_, float tMax_ = FLT_MAX, float time_ = 0.f)
		: o(o_), d(d_), tMax(tMax_), time(time_) {}

	Vector3f operator()(float t) const
	{
		return o + d * t;
	}
};

// ��¼�����������������ߵ�ray��
class RayDifferential : public Ray
{
public:
	bool hasDifferentials;
	Vector3f rxOrigin, ryOrigin;
	Vector3f rxDirection, ryDirection;

	RayDifferential() 
	{
		hasDifferentials = false;
	}

	RayDifferential(const Vector3f &o_, const Vector3f &d_, float tMax_ = FLT_MAX, float time_ = 0.f)
		: Ray(o_, d_, tMax_, time_)
	{
		hasDifferentials = false;
	}

	// ʹ��ray������
	RayDifferential(const Ray &ray) : Ray(ray)
	{
		hasDifferentials = false;
	}

	void ScaleDifferentials(float s) {
		rxOrigin = o + (rxOrigin - o) * s;
		ryOrigin = o + (ryOrigin - o) * s;
		rxDirection = d + (rxDirection - d) * s;
		ryDirection = d + (ryDirection - d) * s;
	}
};

#endif