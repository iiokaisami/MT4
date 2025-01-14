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

const char kWindowTitle[] = "LE2B_02_イイオカ_イサミ_MT4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 axis = { 1.0f, 1.0f, 1.0f };
	float angle = 0.44f;
	Matrix4x4 rotationMatrix = MakeRotateAxisAngle(axis, angle);

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

		ImGui::Text("Rotation Matrix:");
		ImGui::Text("[ %f, %f, %f, %f ]", rotationMatrix.m[0][0], rotationMatrix.m[0][1], rotationMatrix.m[0][2], rotationMatrix.m[0][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotationMatrix.m[1][0], rotationMatrix.m[1][1], rotationMatrix.m[1][2], rotationMatrix.m[1][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotationMatrix.m[2][0], rotationMatrix.m[2][1], rotationMatrix.m[2][2], rotationMatrix.m[2][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotationMatrix.m[3][0], rotationMatrix.m[3][1], rotationMatrix.m[3][2], rotationMatrix.m[3][3]);

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
