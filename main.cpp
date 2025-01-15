#include <Novice.h>

#include <MyMath.h>
#include <imgui.h>
#include <Quaternion.h>

const char kWindowTitle[] = "LE2B_02_イイオカ_イサミ_MT4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f, 0.4f, -0.2f }), 0.45f);
	Vector3 pointV = { 2.1f, -0.9f, 1.3f };
	Matrix4x4 rotateMatrix = MakeRotationMatrix(rotation);
	Vector3 rotatedByQuaternion = RotateVector(pointV, rotation);
	Vector3 rotatedByMatrix = Transform(pointV, rotateMatrix);

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

		ImGui::Text("Quaternion rotation:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", rotation.x, rotation.y, rotation.z, rotation.w);

		ImGui::Text("Matrix4x4 rotateMatrix:");
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3]);
		ImGui::Text("[ %f, %f, %f, %f ]", rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);

		ImGui::Text("Vector3 rotatedByQuaternion:");
		ImGui::Text("x: %f, y: %f, z: %f", rotatedByQuaternion.x, rotatedByQuaternion.y, rotatedByQuaternion.z);

		ImGui::Text("Vector3 rotatedByMatrix:");
		ImGui::Text("x: %f, y: %f, z: %f", rotatedByMatrix.x, rotatedByMatrix.y, rotatedByMatrix.z);


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
