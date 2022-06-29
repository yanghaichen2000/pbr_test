#ifndef _BOUNDS_H_
#define _BOUNDS_H_
#include <Eigen\Dense>

using Eigen::Vector3f;

class Bounds3f
{
public:
	Vector3f pMin, pMax;

	// 默认构造函数，生成最反的bounds
	Bounds3f()
	{
		float min_num = std::numeric_limits<float>::lowest();
		float max_num = std::numeric_limits<float>::max();
		pMax = Vector3f(min_num, min_num, min_num);
		pMin = Vector3f(max_num, max_num, max_num);
	}

	// 使用一个坐标构造，生成大小为0的bounds
	Bounds3f(const Vector3f &p) : pMin(p), pMax(p) {}

	// 使用两个坐标构造
	Bounds3f(const Vector3f &p1, const Vector3f &p2) :
		pMin(std::min(p1[0], p2[0]), std::min(p1[1], p2[1]), std::min(p1[2], p2[2])),
		pMax(std::max(p1[0], p2[0]), std::max(p1[1], p2[1]), std::max(p1[2], p2[2])) {}

	// 获取pMin或者pMax
	const Vector3f &operator[](int i) const
	{
		if (i == 0) return pMin;
		else return pMax;
	}
	Vector3f &operator[](int i)
	{
		if (i == 0) return pMin;
		else return pMax;
	}

	// 获取顶点坐标
	// corner \in [0, 7]
	Vector3f Corner(int corner) const
	{
		return Vector3f((*this)[(corner & 1)][0],
						(*this)[(corner & 2) ? 1 : 0][1],
						(*this)[(corner & 4) ? 1 : 0][2]);
	}

	// 获取从pMin到pMax的向量
	Vector3f Diagnal() const
	{
		return pMax - pMin;
	}

	// 求表面积
	float SurfaceArea() const
	{
		Vector3f d = Diagnal();
		return 2 * (d[0] * d[1] + d[0] * d[2] + d[2] * d[1]);
	}

	// 求体积
	float Volume() const
	{
		Vector3f d = Diagnal();
		return d[0] * d[1] * d[2];
	}

	// 获取最长边
	int MaximumExtent() const
	{
		Vector3f d = Diagnal();
		if (d[0] > d[1] and d[0] > d[2])
			return 0;
		else if (d[1] > d[2])
			return 1;
		else
			return 2;
	}

	// 加权混合
	Vector3f Lerp(const Vector3f &t) const 
	{
		return Vector3f(
			pMin[0] * (1 - t[0]) + pMax[0] * t[0],
			pMin[1] * (1 - t[1]) + pMax[1] * t[1],
			pMin[2] * (1 - t[2]) + pMax[2] * t[2]
		);
	}

	// 获取点在bounds的相对坐标，相当于Lerp的逆操作
	Vector3f Offset(const Vector3f &p) const
	{
		Vector3f t = p - pMin;
		if (pMax[0] > pMin[0])
			t[0] = t[0] / (pMax[0] - pMin[0]);
		if (pMax[1] > pMin[1])
			t[1] = t[1] / (pMax[1] - pMin[1]);
		if (pMax[0] > pMin[0])
			t[2] = t[2] / (pMax[2] - pMin[2]);
		return t;
	}

	// 求解bounds的外接球
	// 数据记录在传入的指针对应的位置
	void BoundingSphere(Vector3f *center, float *radius) const;


};


// 将一个点并入bounds
Bounds3f Union(const Bounds3f &b, const Vector3f &p)
{
	return Bounds3f(
		Vector3f(std::min(b.pMin[0], p[0]), std::min(b.pMin[1], p[1]), std::min(b.pMin[2], p[2])),
		Vector3f(std::max(b.pMax[0], p[0]), std::max(b.pMax[1], p[1]), std::max(b.pMax[2], p[2]))
	);
}

// 合并两个bounds
Bounds3f Union(const Bounds3f &b1, const Bounds3f &b2)
{
	return Bounds3f(
		Vector3f(std::min(b1.pMin[0], b2.pMin[0]), std::min(b1.pMin[1], b2.pMin[1]), std::min(b1.pMin[2], b2.pMin[2])),
		Vector3f(std::max(b1.pMax[0], b2.pMax[0]), std::max(b1.pMax[1], b2.pMax[1]), std::max(b1.pMax[2], b2.pMax[2]))
	);
}

// 两个bounds求交
Bounds3f Intersect(const Bounds3f &b1, const Bounds3f &b2)
{
	return Bounds3f(
		Vector3f(std::max(b1.pMin[0], b2.pMin[0]), std::max(b1.pMin[1], b2.pMin[1]), std::max(b1.pMin[2], b2.pMin[2])),
		Vector3f(std::min(b1.pMax[0], b2.pMax[0]), std::min(b1.pMax[1], b2.pMax[1]), std::min(b1.pMax[2], b2.pMax[2]))
	);
}

// 判断两个bounds是否有交集
bool Overlaps(const Bounds3f &b1, const Bounds3f &b2)
{
	bool tmp_1 = (b1.pMax[0] >= b2.pMin[0]) and (b1.pMin[0] <= b2.pMax[0]);
	bool tmp_2 = (b1.pMax[1] >= b2.pMin[1]) and (b1.pMin[1] <= b2.pMax[1]);
	bool tmp_3 = (b1.pMax[2] >= b2.pMin[2]) and (b1.pMin[2] <= b2.pMax[2]);

	return (tmp_1 && tmp_2 && tmp_3);
}

// 判断点是否在bounds内
bool Inside(const Vector3f &p, const Bounds3f &b)
{
	bool tmp_1 = (p[0] >= b.pMin[0]) and (p[0] <= b.pMax[0]);
	bool tmp_2 = (p[1] >= b.pMin[1]) and (p[1] <= b.pMax[1]);
	bool tmp_3 = (p[2] >= b.pMin[2]) and (p[2] <= b.pMax[2]);

	return (tmp_1 && tmp_2 && tmp_3);
}

// 判断点是否在bounds内（不含边界）
// 对于float该函数与Inside等效
bool InsideExclusive(const Vector3f &p, const Bounds3f &b)
{
	bool tmp_1 = (p[0] > b.pMin[0]) and (p[0] < b.pMax[0]);
	bool tmp_2 = (p[1] > b.pMin[1]) and (p[1] < b.pMax[1]);
	bool tmp_3 = (p[2] > b.pMin[2]) and (p[2] < b.pMax[2]);

	return (tmp_1 && tmp_2 && tmp_3);
}

// 将bounds向外扩展delta
inline Bounds3f Expand(const Bounds3f &b, float delta)
{
	return Bounds3f(b.pMin - Vector3f(delta, delta, delta), b.pMax + Vector3f(delta, delta, delta));
}

void Bounds3f::BoundingSphere(Vector3f *center, float *radius) const
{
	*center = (pMin + pMax) / 2;
	*radius = Inside(*center, *this) ? std::sqrt((*center - pMax).dot(*center - pMax)) : 0;
}

#endif