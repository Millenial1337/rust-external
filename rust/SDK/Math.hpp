#include <Windows.h>
#include <math.h>
class Vector3
{
public:
	float x, y, z;

	inline Vector3() {
		x = y = z = 0.0f;
	}

	inline Vector3(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		//return sqrtf(powf(v.x - v.x, 2) + powf(v.y - v.y, 2));
		return sqrtf(powf((v.x - v.x), 2) + powf((v.y - v.y), 2) + powf((v.z - v.z), 2));

	//	return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline float Length() {
		return sqrtf(x * x + y * y + z * z);
	}

	inline bool operator==(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return true;
		else
			return false;
	}

	inline bool operator!=(const Vector3& v) const {
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return false;
		else
			return true;
	}
};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	void operator -= (Vector2 other)
	{
		// Update this vector's values
		x -= other.x;
		y -= other.y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}
};

class Vector4 {
public:
	float x, y, z, w;
};

struct Matrix4x4 {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		}; float m[4][4];
	};
}; inline Matrix4x4 pViewMatrix;

namespace Math
{
#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
	//#define atan2(a, b) ((float)FC_NTDLL(atan2, (double)(a), (double)(b)))
	static volatile const double Tiny = 0x1p-1022;
	static volatile const double Infinity = INFINITY;
	typedef struct { double d0, d1; } double2;

	static inline double2 Mul112(double a, double b)
	{
		static const double c = 0x1p27 + 1;

		double
			ap = a * c, bp = b * c,
			a0 = (a - ap) + ap, b0 = (b - bp) + bp,
			a1 = a - a0, b1 = b - b0,
			d0 = a * b,
			d1 = a0 * b0 - d0 + a0 * b1 + a1 * b0 + a1 * b1;
		return double2{ d0, d1 };
	}

	static inline double2 Mul222(double2 a, double2 b)
	{
		static const double c = 0x1p27 + 1;

		double
			ap = a.d0 * c, bp = b.d0 * c,
			a0 = (a.d0 - ap) + ap, b0 = (b.d0 - bp) + bp,
			a1 = a.d0 - a0, b1 = b.d0 - b0,
			m0 = a.d0 * b.d0,
			m1 = a0 * b0 - m0 + a0 * b1 + a1 * b0 + a1 * b1 + (a.d0 * b.d1 + a.d1 * b.d0),
			d0 = m0 + m1,
			d1 = m0 - d0 + m1;
		return double2{ d0, d1 };
	}

	static inline double Mul121Special(double a, double2 b)
	{
		static const double c = 0x1p27 + 1;

		double
			ap = a * c, bp = b.d0 * c,
			a0 = (a - ap) + ap, b0 = (b.d0 - bp) + bp,
			a1 = a - a0, b1 = b.d0 - b0,
			m1 = a0 * b0 - 1 + a0 * b1 + a1 * b0 + a1 * b1 + a * b.d1;
		return m1;
	}

	static inline double2 Add212RightSmaller(double2 a, double b)
	{
		double
			c0 = a.d0 + b,
			c1 = a.d0 - c0 + b + a.d1,
			d0 = c0 + c1,
			d1 = c0 - d0 + c1;
		return double2{ d0, d1 };
	}

	static inline double Add221RightSmaller(double2 a, double2 b)
	{
		double
			c0 = a.d0 + b.d0,
			c1 = a.d0 - c0 + b.d0 + b.d1 + a.d1,
			d0 = c0 + c1;
		return d0;
	}

	static double Tail(double x)
	{
		if (1 <= x)
			return 1 == x
			// If x is 1, generate inexact and return Pi/2 rounded down.
			? 0x3.243f6a8885a308d313198a2e03707344ap-1 + Tiny
			// If x is outside the domain, generate invalid and return NaN.
			: Infinity - Infinity;

		static const double p01 = 0.2145993335526539017488949;
		static const double p02 = -0.0890259194305537131666744;
		static const double p03 = 0.0506659694457588602631748;
		static const double p04 = -0.0331919619444009606270380;
		static const double p05 = 0.0229883479552557203133368;
		static const double p06 = -0.0156746038587246716524035;
		static const double p07 = 0.0097868293573384001221447;
		static const double p08 = -0.0052049731575223952626203;
		static const double p09 = 0.0021912255981979442677477;
		static const double p10 = -0.0006702485124770180942917;
		static const double p11 = 0.0001307564187657962919394;
		static const double p12 = -0.0000121189820098929624806;

		double polynomial = ((((((((((((
			+p12) * x
			+ p11) * x
			+ p10) * x
			+ p09) * x
			+ p08) * x
			+ p07) * x
			+ p06) * x
			+ p05) * x
			+ p04) * x
			+ p03) * x
			+ p02) * x
			+ p01) * x;

#if UseLongDouble
		static const long double HalfPi = 0x3.243f6a8885a308d313198a2ep-1L;
		static const long double p00 = -1.5707961988153774692344105L;

		return HalfPi + sqrtl(1 - x) * (polynomial + p00);
#else	// #if UseLongDouble
		static const double2
			HalfPi = { 0x1.921fb54442d18p+0, 0x1.1a62633145c07p-54 },
			p00 = { -0x1.921fb31e97d96p0, +0x1.eab77149ad27cp-54 };

		// Estimate 1 / sqrt(1-x).
		double e = 1 / sqrt(1 - x);

		double2 ex = Mul112(e, 1 - x);		// e * x.
		double e2x = Mul121Special(e, ex);	// e**2 * x - 1.

		// Set t0 to an improved approximation of sqrt(1-x) with Newton-Raphson.
		double2 t0 = Add212RightSmaller(ex, ex.d0 * -.5 * e2x);

		// Calculate pi/2 + sqrt(1-x) * p(x).
		return Add221RightSmaller(HalfPi, Mul222(
			t0,
			Add212RightSmaller(p00, polynomial)));
#endif	// #if UseLongDouble
	}

	__forceinline float abs(float a) {
		if (a < 0.f) return -a;
		else return a;
	}

	__forceinline float asin(float x) {
		float negate = float(x < 0);
		x = abs(x);
		float ret = -0.0187293;
		ret *= x;
		ret += 0.0742610;
		ret *= x;
		ret -= 0.2121144;
		ret *= x;
		ret += 1.5707288;
		ret = 3.14159265358979 * 0.5 - sqrt(1.0 - x) * ret;
		return ret - 2 * negate * ret;
	}

	__forceinline float Dot(const Vector3& Vec1, const Vector3& Vec2) {
		return Vec1[0] * Vec2[0] + Vec1[1] * Vec2[1] + Vec1[2] * Vec2[2];
	}

	__forceinline float Calc3D_Dist(const Vector3& Src, const Vector3& Dst) {
		return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
	}

	__forceinline float Calc2D_Dist(const Vector2& Src, const Vector2& Dst) {
		return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
	}

#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
	__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst) {
		Vector3 dir = Src - Dst;
		float length = dir.Length();
		return Vector2{ RAD2DEG(asin(dir.y / length)), RAD2DEG(-atan2(dir.x, -dir.z)) };
	}

	//__forceinline void Normalize(float& Yaw, float& Pitch) {
	//	if (Pitch < -89) Pitch = -89;
	//	else if (Pitch > 89) Pitch = 89;
	//	if (Yaw < -360) Yaw += 360;
	//	else if (Yaw > 360) Yaw -= 360;
	//}

	float Normalize(float angle) {
		while (angle > 360.0f) {
			angle -= 360.0f;
		}
		while (angle < 0.0f) {
			angle += 360.0f;
		}
		return angle;
	}
	Vector3 Normalize(Vector3 angles) {
		angles.x = Normalize(angles.x);
		angles.y = Normalize(angles.y);
		angles.z = Normalize(angles.z);
		return angles;
	}
	__forceinline float Distance(const Vector3* value1, const Vector3* value2)
	{
		float num1 = value1->x - value2->x;
		float num2 = value1->y - value2->y;
		float num3 = value1->z - value2->z;

		return (float)sqrt(num1 * num1 + num2 * num2 + num3 * num3);
	}
}