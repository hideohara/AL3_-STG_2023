#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	// 各クラスの削除
	delete stage_;  // ステージ
	delete player_; // プレイヤー
	delete beam_;   // ビーム
	delete enemy_;  // 敵
}

// 初期化
void GameScene::Initialize() {

	srand((unsigned int)time(NULL));

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	// 各クラスの生成
	stage_ = new Stage();   // ステージ
	player_ = new Player(); // プレイヤー
	beam_ = new Beam();     // ビーム
	enemy_ = new Enemy();   // 敵

	// 各クラスの初期化
	stage_->Initialize(viewProjection_);         // ステージ
	player_->Initialize(viewProjection_);        // プレイヤー
	beam_->Initialize(viewProjection_, player_); // ビーム
	enemy_->Initialize(viewProjection_);         // 敵

	// デバッグテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();
}

// 更新
void GameScene::Update() {
	// 各クラスの更新
	stage_->Update();  // ステージ
	player_->Update(); // プレイヤー
	beam_->Update();   // ビーム
	enemy_->Update();  // 敵

	Collision(); // 衝突判定
}

// 描画
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// 背景の描画
	stage_->Draw2DFar();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	stage_->Draw3D();  // 背景の描画
	player_->Draw3D(); // プレイヤーの描画
	beam_->Draw3D();   // ビームの描画
	enemy_->Draw3D();  // 敵の描画

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// ゲームスコア
	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 800, 10, 2);

	debugText_->DrawAll();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// ************************************************

// 衝突判定
void GameScene::Collision() {
	// 衝突判定（プレイヤーと敵）
	CollisionPlayerEnemy();
	// 衝突判定（ビームと敵）
	CollisionBeamEnemy();
}

// 衝突判定（プレイヤーと敵）
void GameScene::CollisionPlayerEnemy() {
	// 敵が存在すれば
	if (enemy_->GetFlag() == 1) {
		// 差を求める
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());
		// 衝突したら
		if (dx < 1 && dz < 1) {
			// 衝突処理
			enemy_->Hit();
			// ライフ減算
			playerLife_ -= 1;
		}
	}
}

// 衝突判定（ビームと敵）
void GameScene::CollisionBeamEnemy() {
	// ビームが存在すれば
	if (beam_->GetFlag() == 1) {
		// 敵が存在すれば
		if (enemy_->GetFlag() == 1) {
			// 差を求める
			float dx = abs(beam_->GetX() - enemy_->GetX());
			float dz = abs(beam_->GetZ() - enemy_->GetZ());
			// 衝突したら
			if (dx < 1 && dz < 1) {
				// 衝突処理
				enemy_->Hit();
				beam_->Hit();
				// 点数加算
				gameScore_ += 1;
			}
		}
	}
}
