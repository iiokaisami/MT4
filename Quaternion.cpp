#include "Quaternion.h"

// 演算子オーバーロードの実装
Quaternion Quaternion::operator+(const Quaternion& other) const {
	return Quaternion{ x + other.x, y + other.y, z + other.z, w + other.w };
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
	return Quaternion{ x - other.x, y - other.y, z - other.z, w - other.w };
}

Quaternion Quaternion::operator*(float scalar) const {
	return Quaternion{ x * scalar, y * scalar, z * scalar, w * scalar };
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	return Multiply(*this, other);
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion result;
	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
	return result;
}

Quaternion IdentityQuaternion()
{
	return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	return Quaternion{ -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
}

float Norm(const Quaternion& quaternion)
{
	return std::sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y + quaternion.z * quaternion.z + quaternion.w * quaternion.w);
}

Quaternion Normalize(const Quaternion& quaternion)
{
	float norm = Norm(quaternion);
	return Quaternion{ quaternion.x / norm, quaternion.y / norm, quaternion.z / norm, quaternion.w / norm };
}

Quaternion Inverse(const Quaternion& quaternion)
{
	float norm = Norm(quaternion);
	Quaternion conjugate = Conjugate(quaternion);
	return Quaternion{ conjugate.x / (norm * norm), conjugate.y / (norm * norm), conjugate.z / (norm * norm), conjugate.w / (norm * norm) };
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = std::sin(halfAngle);
	return Quaternion{ axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle, std::cos(halfAngle) };
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion)
{
	Quaternion q = quaternion;
	Quaternion v = Quaternion{ vector.x, vector.y, vector.z, 0.0f };
	Quaternion qInv = Inverse(q);
	Quaternion result = Multiply(Multiply(q, v), qInv);
	return Vector3{ result.x, result.y, result.z };
}

Matrix4x4 MakeRotationMatrix(const Quaternion& quaternion)
{
	Quaternion q = Normalize(quaternion);
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float w = q.w;
	Matrix4x4 result = {
	result.m[0][0] = 1.0f - 2.0f * y * y - 2.0f * z * z, result.m[0][1] = 2.0f * x * y + 2.0f * z * w, result.m[0][2] = 2.0f * x * z - 2.0f * y * w, result.m[0][3] = 0.0f,
	result.m[1][0] = 2.0f * x * y - 2.0f * z * w, result.m[1][1] = 1.0f - 2.0f * x * x - 2.0f * z * z, result.m[1][2] = 2.0f * y * z + 2.0f * x * w, result.m[1][3] = 0.0f,
	result.m[2][0] = 2.0f * x * z + 2.0f * y * w, result.m[2][1] = 2.0f * y * z - 2.0f * x * w,result.m[2][2] = 1.0f - 2.0f * x * x - 2.0f * y * y, result.m[2][3] = 0.0f,
	result.m[3][0] = 0.0f, result.m[3][1] = 0.0f, result.m[3][2] = 0.0f, result.m[3][3] = 1.0f,
	};
	return result;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion q1Copy = q1;
	float dot = q0.x * q1Copy.x + q0.y * q1Copy.y + q0.z * q1Copy.z + q0.w * q1Copy.w;
	if (dot < 0.0f)
	{
		q1Copy = Quaternion{ -q1Copy.x, -q1Copy.y, -q1Copy.z, -q1Copy.w };
		dot = -dot;
	}
	const float EPSOLOM = 0.9995f;
	if (dot >= EPSOLOM)
	{
		Quaternion result = q0 + (q1Copy - q0) * t;
		return Normalize(result);
	}
	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);
	float s0 = std::sin((1.0f - t) * theta) / sinTheta;
	float s1 = std::sin(t * theta) / sinTheta;
	return q0 * s0 + q1Copy * s1;
}
