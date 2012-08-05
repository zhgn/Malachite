#ifndef MLVECTOR_H
#define MLVECTOR_H

#include <stdint.h>
#include <emmintrin.h>
#include <cstdlib>
#include <new>
#include <QPointF>

#include "mlglobal.h"

#define ML_ALIGN_16BYTE \
public: \
	static void *operator new(size_t size) { \
		return mlAllocateAlignedMemory(size, 16); \
	} \
	static void operator delete(void *p) { \
		mlFreeAlignedMemory(p); \
	} \
	static void *operator new(size_t size, void *buf) { \
		Q_UNUSED(size); \
		return buf; \
	} \
	static void operator delete(void *p, void *buf) { \
		Q_UNUSED(p); \
		Q_UNUSED(buf); \
	} \
	static void *operator new[](size_t size) { \
		return mlAllocateAlignedMemory(size, 16); \
	} \
	static void operator delete[](void *p) { \
		mlFreeAlignedMemory(p); \
	} \
	static void *operator new[](size_t size, void *buf) { \
		Q_UNUSED(size); \
		return buf; \
	} \
	static void operator delete[](void *p, void *buf) { \
		Q_UNUSED(p); \
		Q_UNUSED(buf); \
	}

struct MLVec2I64
{
public:
	
	MLVec2I64() {}
	MLVec2I64(int64_t s)
	{
		e[0] = s;
		e[1] = s;
	}
	MLVec2I64(int64_t e0, int64_t e1)
	{
		e[0] = e0;
		e[1] = e1;
	}
	MLVec2I64(__v2di v) : v(v) {}
	
	int64_t &operator[](int i) { return e[i]; }
	const int64_t &operator[](int i) const { return e[i]; }
	operator __v2di() { return v; }
	operator const __v2di() const { return v; }
	
	MLVec2I64 &operator+=(const MLVec2I64 &other) { v += other.v; return *this; }
	MLVec2I64 &operator-=(const MLVec2I64 &other) { v -= other.v; return *this; }
	MLVec2I64 &operator*=(const MLVec2I64 &other) { v *= other.v; return *this; }
	MLVec2I64 &operator/=(const MLVec2I64 &other) { v /= other.v; return *this; }
	
	MLVec2I64 &operator+=(int value) { v += MLVec2I64(value).v; return *this; }
	MLVec2I64 &operator-=(int value) { v -= MLVec2I64(value).v; return *this; }
	MLVec2I64 &operator*=(int value) { v *= MLVec2I64(value).v; return *this; }
	MLVec2I64 &operator/=(int value) { v /= MLVec2I64(value).v; return *this; }
	
	MLVec2I64 operator+(const MLVec2I64 &other) const { MLVec2I64 r; r.v = v + other.v; return r; }
	MLVec2I64 operator-(const MLVec2I64 &other) const { MLVec2I64 r; r.v = v - other.v; return r; }
	MLVec2I64 operator*(const MLVec2I64 &other) const { MLVec2I64 r; r.v = v * other.v; return r; }
	MLVec2I64 operator/(const MLVec2I64 &other) const { MLVec2I64 r; r.v = v / other.v; return r; }
	
	union
	{
		struct
		{
			
			int64_t x;
			int64_t y;
		};
		int64_t e[2];
		__v2di v;
	};
};

struct MLVec4I32
{
public:
	
	MLVec4I32() {}
	MLVec4I32(int32_t s)
	{
		e[0] = s;
		e[1] = s;
		e[2] = s;
		e[3] = s;
	}
	MLVec4I32(int32_t e0, int32_t e1, int32_t e2, int32_t e3)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
		e[3] = e3;
	}
	MLVec4I32(__v4si v) : v(v) {}
	
	int32_t &operator[](int i) { return e[i]; }
	const int32_t &operator[](int i) const { return e[i]; }
	operator __v4si() { return v; }
	operator const __v4si() const { return v; }
	
	MLVec4I32 &operator+=(const MLVec4I32 &other) { v += other.v; return *this; }
	MLVec4I32 &operator-=(const MLVec4I32 &other) { v -= other.v; return *this; }
	MLVec4I32 &operator*=(const MLVec4I32 &other) { v *= other.v; return *this; }
	MLVec4I32 &operator/=(const MLVec4I32 &other) { v /= other.v; return *this; }
	
	MLVec4I32 &operator+=(int value) { v += MLVec4I32(value).v; return *this; }
	MLVec4I32 &operator-=(int value) { v -= MLVec4I32(value).v; return *this; }
	MLVec4I32 &operator*=(int value) { v *= MLVec4I32(value).v; return *this; }
	MLVec4I32 &operator/=(int value) { v /= MLVec4I32(value).v; return *this; }
	
	MLVec4I32 operator+(const MLVec4I32 &other) const { MLVec4I32 r; r.v = v + other.v; return r; }
	MLVec4I32 operator-(const MLVec4I32 &other) const { MLVec4I32 r; r.v = v - other.v; return r; }
	MLVec4I32 operator*(const MLVec4I32 &other) const { MLVec4I32 r; r.v = v * other.v; return r; }
	MLVec4I32 operator/(const MLVec4I32 &other) const { MLVec4I32 r; r.v = v / other.v; return r; }
	
	union
	{
		struct
		{
			int32_t x;
			int32_t y;
			int32_t z;
			int32_t w;
		};
		struct
		{
			int32_t b;
			int32_t g;
			int32_t r;
			int32_t a;
		};
		int32_t e[4];
		__v4si v;
	};
};

struct MLVec8I16
{
public:
	
	MLVec8I16() {}
	MLVec8I16(int16_t s)
	{
		e[0] = s;
		e[1] = s;
		e[2] = s;
		e[3] = s;
		e[4] = s;
		e[5] = s;
		e[6] = s;
		e[7] = s;
	}
	MLVec8I16(int16_t e0, int16_t e1, int16_t e2, int16_t e3,
			  int16_t e4, int16_t e5, int16_t e6, int16_t e7)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
		e[3] = e3;
		e[4] = e4;
		e[5] = e5;
		e[6] = e6;
		e[7] = e7;
	}
	MLVec8I16(__v8hi v) : v(v) {}
	
	static MLVec8I16 pack(const MLVec4I32 &v0, const MLVec4I32 &v1)
	{
		return __builtin_ia32_packssdw128(v0, v1);
	}
	
	int16_t &operator[](int i) { return e[i]; }
	const int16_t &operator[](int i) const { return e[i]; }
	operator __v8hi() { return v; }
	operator const __v8hi() const { return v; }
	
	MLVec8I16 &operator+=(const MLVec8I16 &other) { v += other.v; return *this; }
	MLVec8I16 &operator-=(const MLVec8I16 &other) { v -= other.v; return *this; }
	MLVec8I16 &operator*=(const MLVec8I16 &other) { v *= other.v; return *this; }
	MLVec8I16 &operator/=(const MLVec8I16 &other) { v /= other.v; return *this; }
	
	MLVec8I16 &operator+=(int value) { v += MLVec8I16(value).v; return *this; }
	MLVec8I16 &operator-=(int value) { v -= MLVec8I16(value).v; return *this; }
	MLVec8I16 &operator*=(int value) { v *= MLVec8I16(value).v; return *this; }
	MLVec8I16 &operator/=(int value) { v /= MLVec8I16(value).v; return *this; }
	
	MLVec8I16 operator+(const MLVec8I16 &other) const { MLVec8I16 r; r.v = v + other.v; return r; }
	MLVec8I16 operator-(const MLVec8I16 &other) const { MLVec8I16 r; r.v = v - other.v; return r; }
	MLVec8I16 operator*(const MLVec8I16 &other) const { MLVec8I16 r; r.v = v * other.v; return r; }
	MLVec8I16 operator/(const MLVec8I16 &other) const { MLVec8I16 r; r.v = v / other.v; return r; }
	
	union
	{
		int16_t e[8];
		__v8hi v;
	};
};

struct MLVec16I8
{
	MLVec16I8() {}
	MLVec16I8(int8_t s)
	{
		e[0] = s;
		e[1] = s;
		e[2] = s;
		e[3] = s;
		e[4] = s;
		e[5] = s;
		e[6] = s;
		e[7] = s;
		e[8] = s;
		e[9] = s;
		e[10] = s;
		e[11] = s;
		e[12] = s;
		e[13] = s;
		e[14] = s;
		e[15] = s;
	}
	MLVec16I8(int8_t e0, int8_t e1, int8_t e2, int8_t e3,
			  int8_t e4, int8_t e5, int8_t e6, int8_t e7,
			  int8_t e8, int8_t e9, int8_t e10, int8_t e11,
			  int8_t e12, int8_t e13, int8_t e14, int8_t e15)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
		e[3] = e3;
		e[4] = e4;
		e[5] = e5;
		e[6] = e6;
		e[7] = e7;
		e[8] = e8;
		e[9] = e9;
		e[10] = e10;
		e[11] = e11;
		e[12] = e12;
		e[13] = e13;
		e[14] = e14;
		e[15] = e15;
	}
	MLVec16I8(__v16qi v) : v(v) {}
	
	static MLVec16I8 pack(const MLVec8I16 &v0, const MLVec8I16 &v1)
	{
		return MLVec16I8(__builtin_ia32_packsswb128(v0, v1));
	}
	
	int8_t &operator[](int i) { return e[i]; }
	const int8_t &operator[](int i) const { return e[i]; }
	operator __v16qi() { return v; }
	operator const __v16qi() const { return v; }
	
	MLVec16I8 &operator+=(const MLVec16I8 &other) { v += other.v; return *this; }
	MLVec16I8 &operator-=(const MLVec16I8 &other) { v -= other.v; return *this; }
	MLVec16I8 &operator*=(const MLVec16I8 &other) { v *= other.v; return *this; }
	MLVec16I8 &operator/=(const MLVec16I8 &other) { v /= other.v; return *this; }
	
	MLVec16I8 &operator+=(int value) { v += MLVec16I8(value).v; return *this; }
	MLVec16I8 &operator-=(int value) { v -= MLVec16I8(value).v; return *this; }
	MLVec16I8 &operator*=(int value) { v *= MLVec16I8(value).v; return *this; }
	MLVec16I8 &operator/=(int value) { v /= MLVec16I8(value).v; return *this; }
	
	MLVec16I8 operator+(const MLVec16I8 &other) const { MLVec16I8 r; r.v = v + other.v; return r; }
	MLVec16I8 operator-(const MLVec16I8 &other) const { MLVec16I8 r; r.v = v - other.v; return r; }
	MLVec16I8 operator*(const MLVec16I8 &other) const { MLVec16I8 r; r.v = v * other.v; return r; }
	MLVec16I8 operator/(const MLVec16I8 &other) const { MLVec16I8 r; r.v = v / other.v; return r; }
	
	union
	{
		int8_t e[16];
		__v16qi v;
	};
};

struct MLVec16U8
{
	MLVec16U8() {}
	MLVec16U8(uint8_t s)
	{
		e[0] = s;
		e[1] = s;
		e[2] = s;
		e[3] = s;
		e[4] = s;
		e[5] = s;
		e[6] = s;
		e[7] = s;
		e[8] = s;
		e[9] = s;
		e[10] = s;
		e[11] = s;
		e[12] = s;
		e[13] = s;
		e[14] = s;
		e[15] = s;
	}
	MLVec16U8(uint8_t e0, uint8_t e1, uint8_t e2, uint8_t e3,
			  uint8_t e4, uint8_t e5, uint8_t e6, uint8_t e7,
			  uint8_t e8, uint8_t e9, uint8_t e10, uint8_t e11,
			  uint8_t e12, uint8_t e13, uint8_t e14, uint8_t e15)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
		e[3] = e3;
		e[4] = e4;
		e[5] = e5;
		e[6] = e6;
		e[7] = e7;
		e[8] = e8;
		e[9] = e9;
		e[10] = e10;
		e[11] = e11;
		e[12] = e12;
		e[13] = e13;
		e[14] = e14;
		e[15] = e15;
	}
	MLVec16U8(__v16qi v) : v(v) {}
	
	static MLVec16U8 pack(const MLVec8I16 &v0, const MLVec8I16 &v1)
	{
		return MLVec16U8(__builtin_ia32_packuswb128(v0, v1));
	}
	
	uint8_t &operator[](int i) { return e[i]; }
	const uint8_t &operator[](int i) const { return e[i]; }
	operator __v16qi() { return v; }
	operator const __v16qi() const { return v; }
	
	union
	{
		uint8_t e[16];
		__v16qi v;
	};
};

struct MLVec4F
{
public:
	
	MLVec4F() {}
	MLVec4F(float s) { e[0] = s; e[1] = s; e[2] = s; e[3] = s; }
	MLVec4F(float e0, float e1, float e2, float e3) { e[0] = e0; e[1] = e1; e[2] = e2; e[3] = e3; }
	MLVec4F(__v4sf v) : v(v) {}
	
	static MLVec4I32 equal(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpeqps(v0, v1)); }
	static MLVec4I32 notEqual(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpneqps(v0, v1)); }
	static MLVec4I32 lessThan(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpltps(v0, v1)); }
	static MLVec4I32 lessThanOrEqual(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpleps(v0, v1)); }
	static MLVec4I32 greaterThan(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpltps(v1, v0)); }
	static MLVec4I32 greaterThanOrEqual(const MLVec4F &v0, const MLVec4F &v1) { return MLVec4I32(__builtin_ia32_cmpleps(v1, v0)); }
	
	float &operator[](int i) { return e[i]; }
	const float &operator[](int i) const { return e[i]; }
	operator __v4sf() { return v; }
	operator const __v4sf() const { return v; }
	
	MLVec4F &operator+=(const MLVec4F &other) { v += other.v; return *this; }
	MLVec4F &operator-=(const MLVec4F &other) { v -= other.v; return *this; }
	MLVec4F &operator*=(const MLVec4F &other) { v *= other.v; return *this; }
	MLVec4F &operator/=(const MLVec4F &other) { v /= other.v; return *this; }
	
	MLVec4F &operator+=(float value) { v += MLVec4F(value).v; return *this; }
	MLVec4F &operator-=(float value) { v -= MLVec4F(value).v; return *this; }
	MLVec4F &operator*=(float value) { v *= MLVec4F(value).v; return *this; }
	MLVec4F &operator/=(float value) { v /= MLVec4F(value).v; return *this; }
	
	MLVec4F operator+(const MLVec4F &other) const { MLVec4F r; r.v = v + other.v; return r; }
	MLVec4F operator-(const MLVec4F &other) const { MLVec4F r; r.v = v - other.v; return r; }
	MLVec4F operator*(const MLVec4F &other) const { MLVec4F r; r.v = v * other.v; return r; }
	MLVec4F operator/(const MLVec4F &other) const { MLVec4F r; r.v = v / other.v; return r; }
	
	MLVec4F &operator=(const MLVec4I32 &iv) { v = __builtin_ia32_cvtdq2ps(iv.v); return *this; }
	
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct
		{
			float b;
			float g;
			float r;
			float a;
		};
		float e[4];
		__v4sf v;
	};
};

struct MLVec2D
{
public:
	
	MLVec2D() {}
	MLVec2D(double s) { x = s; y = s; }
	MLVec2D(double x, double y) { x = x; y = y; }
	MLVec2D(const QPointF &p) { x = p.x(); y = p.y(); }
	MLVec2D(__v2df v) : v(v) {}
	
	
	
	static MLVec2I64 equal(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmpeqpd(v0, v1)); }
	static MLVec2I64 notEqual(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmpneqpd(v0, v1)); }
	static MLVec2I64 lessThan(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmpltpd(v0, v1)); }
	static MLVec2I64 lessThanOrEqual(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmplepd(v0, v1)); }
	static MLVec2I64 greaterThan(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmpltpd(v1, v0)); }
	static MLVec2I64 greaterThanOrEqual(const MLVec2D &v0, const MLVec2D &v1) { return MLVec2I64(__builtin_ia32_cmplepd(v1, v0)); }
	
	double &operator[](int i) { return e[i]; }
	const double &operator[](int i) const { return e[i]; }
	operator __v2df() { return v; }
	operator const __v2df() const { return v; }
	
	MLVec2D &operator+=(const MLVec2D &other) { v += other.v; return *this; }
	MLVec2D &operator-=(const MLVec2D &other) { v -= other.v; return *this; }
	MLVec2D &operator*=(const MLVec2D &other) { v *= other.v; return *this; }
	MLVec2D &operator/=(const MLVec2D &other) { v /= other.v; return *this; }
	
	MLVec2D &operator+=(float value) { v += MLVec2D(value).v; return *this; }
	MLVec2D &operator-=(float value) { v -= MLVec2D(value).v; return *this; }
	MLVec2D &operator*=(float value) { v *= MLVec2D(value).v; return *this; }
	MLVec2D &operator/=(float value) { v /= MLVec2D(value).v; return *this; }
	
	MLVec2D operator+(const MLVec2D &other) const { MLVec2D r; r.v = v + other.v; return r; }
	MLVec2D operator-(const MLVec2D &other) const { MLVec2D r; r.v = v - other.v; return r; }
	MLVec2D operator*(const MLVec2D &other) const { MLVec2D r; r.v = v * other.v; return r; }
	MLVec2D operator/(const MLVec2D &other) const { MLVec2D r; r.v = v / other.v; return r; }
	
	MLVec2D &operator=(const MLVec4I32 &iv) { v = __builtin_ia32_cvtdq2pd(iv.v); return *this; }
	
	union
	{
		struct
		{
			double x;
			double y;
		};
		double e[2];
		__v2df v;
	};
};


inline MLVec4I32 round(const MLVec4F &v)
{
	return MLVec4I32(__builtin_ia32_cvtps2dq(v));
}

inline MLVec4I32 round(const MLVec2D &v)
{
	return MLVec4I32(__builtin_ia32_cvtpd2dq(v));
}

inline MLVec4F sqrt(const MLVec4F &v)
{
	return MLVec4F(__builtin_ia32_sqrtps(v));
}

inline MLVec2D sqrt(const MLVec2D &v)
{
	return MLVec2D(__builtin_ia32_sqrtpd(v));
}





#endif // MLVECTOR_H