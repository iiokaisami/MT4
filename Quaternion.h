#pragma once

#include "MyMath.h"

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	// 演算子オーバーロードの宣言
	Quaternion operator+(const Quaternion& other) const;
	Quaternion operator-(const Quaternion& other) const;
	Quaternion operator*(float scalar) const;
	Quaternion operator*(const Quaternion& other) const;
};

// Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

// 単位Quaternionの作成を返す
Quaternion IdentityQuaternion();

// 共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion);

// Quaternionのnormを返す
float Norm(const Quaternion& quaternion);

// 正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion);

//逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion);

// 任意軸回転を表すQuaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

// ベクトルをQuaternionで回転させた結果のベクトルを返す
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

// Quaternionから回転行列を求める
Matrix4x4 MakeRotationMatrix(const Quaternion& quaternion);

// 球面線形補間
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);