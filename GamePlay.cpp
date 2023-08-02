#include "GamePlay.h"

// コンストクラタ
GamePlay::GamePlay() {}

// デストラクタ
GamePlay::~GamePlay() {
	// 各クラスの削除
	delete stage_;  // ステージ
	delete player_; // プレイヤー
	delete beam_;   // ビーム
	delete enemy_;  // 敵
}

// 初期化
void GamePlay::Initialize(ViewProjection viewProjection) {
	// メンバー変数に代入
	viewProjection_ = viewProjection;

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
int GamePlay::Update() {
	// 各クラスの更新
	stage_->Update();  // ステージ
	player_->Update(); // プレイヤー
	beam_->Update();   // ビーム
	enemy_->Update();  // 敵

	Collision(); // 衝突判定

	// HP
	if (playerLife_ <= 0) {
		// ゲームオーバーへ移行
		return 2;
	}

	// ゲームプレイを継続
	return 0;
}

// 3D描画
void GamePlay::Draw3D() {
	stage_->Draw3D();  // 背景の描画
	player_->Draw3D(); // プレイヤーの描画
	beam_->Draw3D();   // ビームの描画
	enemy_->Draw3D();  // 敵の描画
}

// 2D遠景描画
void GamePlay::Draw2DFar() { stage_->Draw2DFar(); }

// 2D近景描画
void GamePlay::Draw2DNear() {
	// ゲームスコア
	char str[100];
	sprintf_s(str, "SCORE %d", gameScore_);
	debugText_->Print(str, 200, 10, 2);

	sprintf_s(str, "LIFE %d", playerLife_);
	debugText_->Print(str, 800, 10, 2);

	debugText_->DrawAll();
}

// 衝突判定
void GamePlay::Collision() {
	// 衝突判定（プレイヤーと敵）
	CollisionPlayerEnemy();
	// 衝突判定（ビームと敵）
	CollisionBeamEnemy();
}

// 衝突判定（プレイヤーと敵）
void GamePlay::CollisionPlayerEnemy() {
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
void GamePlay::CollisionBeamEnemy() {
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

// 開始
void GamePlay::Start() {
	playerLife_ = 3;
	gameScore_ = 0;
	player_->Start();
	beam_->Start();
	enemy_->Start();
}
