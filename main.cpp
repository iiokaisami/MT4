#include <Novice.h>

#include <MyMath.h>
#include <imgui.h>

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Vector3 normalizedAxis = Normalize(axis);
	float x = normalizedAxis.x;
	float y = normalizedAxis.y;
	float z = normalizedAxis.z;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	float oneMinusCos = 1.0f - cosAngle;

	Matrix4x4 rotationMatrix = {
	  cosAngle + x * x * oneMinusCos,       x * y * oneMinusCos + z * sinAngle, x * z * oneMinusCos - y * sinAngle, 0.0f,
	  y * x * oneMinusCos - z * sinAngle,   cosAngle + y * y * oneMinusCos,     y * z * oneMinusCos + x * sinAngle, 0.0f,
	  z * x * oneMinusCos + y * sinAngle,   z * y * oneMinusCos - x * sinAngle, cosAngle + z * z * oneMinusCos,     0.0f,
	  0.0f,                                 0.0f,                               0.0f,                               1.0f
	};

	return rotationMatrix;
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to)
{
	Vector3 fromNormalized = Normalize(from);
	Vector3 toNormalized = Normalize(to);
	float dotProduct = Dot(fromNormalized, toNormalized);

	// from と to が平行または反平行の場合の特別な処理
	if (dotProduct > 0.9999f) {
		// from と to が同じ方向を向いている場合、単位行列を返す
		return Matrix4x4{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
	else if (dotProduct < -0.9999f) {
		// from と to が反対方向を向いている場合、任意の垂直ベクトルを軸として180度回転行列を作成
		Vector3 orthogonalAxis = (fabs(fromNormalized.x) > fabs(fromNormalized.z)) ? Vector3{ -fromNormalized.y, fromNormalized.x, 0.0f } : Vector3{ 0.0f, -fromNormalized.z, fromNormalized.y };
		orthogonalAxis = Normalize(orthogonalAxis);
		return MakeRotateAxisAngle(orthogonalAxis, 3.14159265358979323846f); // 180度回転
	}

	Vector3 axis = Cross(fromNormalized, toNormalized);
	float angle = acos(dotProduct);
	return MakeRotateAxisAngle(axis, angle);
}

const char kWindowTitle[] = "LE2B_02_イイオカ_イサミ_MT4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 from0 = Normalize(Vector3{ 1.0f, 0.7f, 0.5f });
	Vector3 to0 = Vector3{ -from0.x, -from0.y, -from0.z };
	Vector3 from1 = Normalize(Vector3{ -0.6f, 0.9f, 0.2f });
	Vector3 to1 = Normalize(Vector3{ 0.4f,0.7f,-0.5f });
	Matrix4x4 rotateMatrix0 = DirectionToDirection(Normalize(Vector3{ 1.0f,0.0f,0.0f }), Normalize(Vector3{ -1.0f,0.0f,0.0f }));
	Matrix4x4 rotateMatrix1 = DirectionToDirection(from0, to0);
	Matrix4x4 rotateMatrix2 = DirectionToDirection(from1, to1);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Debug");

		ImGui::Text("Rotate Matrix0:");
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix0.m[0][0], rotateMatrix0.m[0][1], rotateMatrix0.m[0][2], rotateMatrix0.m[0][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix0.m[1][0], rotateMatrix0.m[1][1], rotateMatrix0.m[1][2], rotateMatrix0.m[1][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix0.m[2][0], rotateMatrix0.m[2][1], rotateMatrix0.m[2][2], rotateMatrix0.m[2][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix0.m[3][0], rotateMatrix0.m[3][1], rotateMatrix0.m[3][2], rotateMatrix0.m[3][3]);

		ImGui::Text("Rotate Matrix1:");
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix1.m[0][0], rotateMatrix1.m[0][1], rotateMatrix1.m[0][2], rotateMatrix1.m[0][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix1.m[1][0], rotateMatrix1.m[1][1], rotateMatrix1.m[1][2], rotateMatrix1.m[1][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix1.m[2][0], rotateMatrix1.m[2][1], rotateMatrix1.m[2][2], rotateMatrix1.m[2][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix1.m[3][0], rotateMatrix1.m[3][1], rotateMatrix1.m[3][2], rotateMatrix1.m[3][3]);

		ImGui::Text("Rotate Matrix2:");
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix2.m[0][0], rotateMatrix2.m[0][1], rotateMatrix2.m[0][2], rotateMatrix2.m[0][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix2.m[1][0], rotateMatrix2.m[1][1], rotateMatrix2.m[1][2], rotateMatrix2.m[1][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix2.m[2][0], rotateMatrix2.m[2][1], rotateMatrix2.m[2][2], rotateMatrix2.m[2][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix2.m[3][0], rotateMatrix2.m[3][1], rotateMatrix2.m[3][2], rotateMatrix2.m[3][3]);


		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
