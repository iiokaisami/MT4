#include <Novice.h>

#include <MyMath.h>
#include <imgui.h>
#include <Quaternion.h>

const char kWindowTitle[] = "LE2B_02_イイオカ_イサミ_MT4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Quaternion rotation0 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.0f, 0.71f }, 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

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

		ImGui::Text("Quaternion interpolate0:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);

		ImGui::Text("Quaternion interpolate1:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);

		ImGui::Text("Quaternion interpolate2:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);

		ImGui::Text("Quaternion interpolate3:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);

		ImGui::Text("Quaternion interpolate4:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);

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
