#include <Novice.h>

#include <MyMath.h>
#include <imgui.h>
#include <Quaternion.h>

const char kWindowTitle[] = "LE2B_02_イイオカ_イサミ_MT4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion norml = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);

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

		ImGui::Text("Identity :");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", identity.x, identity.y, identity.z, identity.w);

		ImGui::Text("Conjugate :");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", conj.x, conj.y, conj.z, conj.w);

		ImGui::Text("Inverse :");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", inv.x, inv.y, inv.z, inv.w);

		ImGui::Text("Normalize :");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", norml.x, norml.y, norml.z, norml.w);

		ImGui::Text("q1 * q2:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", mul1.x, mul1.y, mul1.z, mul1.w);

		ImGui::Text("q2 * q1:");
		ImGui::Text("x: %f, y: %f, z: %f, w: %f", mul2.x, mul2.y, mul2.z, mul2.w);

		ImGui::Text("Norm : %f", norm);

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
