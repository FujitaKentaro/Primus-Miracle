#pragma once
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "ConvertXM.h"
#include "Easing.h"

//#include "WorldTransform.h"

/// <summary>
/// アフィン行列 （角度指定：度数法）
/// </summary>
namespace Affin {

	// 単位行列 set
	Matrix4 matUnit();


	// 平行移動
	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	Matrix4 matTrans(Vector3 move);

	// 回転
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);
	Matrix4 matRotation(Vector3 rotate);

	//拡縮
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);
	Matrix4 matScale(Vector3 scale);

	//拡縮 -> 回転 -> 移動
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);

	//	ワールド座標取得
	Vector3 GetWorldTrans(Matrix4 matrix);

	// W 除算
	const Vector3 division(const Vector3& v, Matrix4 mat);
	Vector3 wDivision(Vector3 vector, Matrix4 matrix);

	// ベクトルと行列の掛け算
	Vector3 VecMat3D(Vector3 vec, Matrix4 mat);
	// ベクトルと行列の掛け算
	Vector3 VecMat(Vector3 vec, Matrix4 mat);

} // namespace Affin