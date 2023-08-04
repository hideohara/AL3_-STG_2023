#include "GamePlay.h"

// コンストクラタ
GamePlay::GamePlay() {}

// デストラクタ
GamePlay::~GamePlay() {
	// 各クラスの削除
	delete stage_;  // ステージ
	delete player_; // プレイヤー
	for (Beam* beam : beamTable_) {
		delete beam; // ビーム
	}
	for (Enemy* enemy : enemyTable_) {
		delete enemy; // 敵
	}
}

// 初期化
void GamePlay::Initialize(ViewProjection viewProjection) {
	// メンバー変数に代入
	viewProjection_ = viewProjection;

	// 各クラスの生成
	stage_ = new Stage();   // ステージ
	player_ = new Player(); // プレイヤー
	for (int i = 0; i < 10; i++) {
		beamTable_[i] = new Beam(); // ビーム
	}
	for (int i = 0; i < 10; i++) {
		enemyTable_[i] = new Enemy(); // 敵
	}
	// 各クラスの初期化
	stage_->Initialize(viewProjection_);  // ステージ
	player_->Initialize(viewProjection_); // プレイヤー
	for (Beam* beam : beamTable_) {
		beam->Initialize(viewProjection_, player_); // ビーム
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Initialize(viewProjection_); // 敵
	}
	// デバッグテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	// インプットクラス
	input_ = Input::GetInstance();
}

// 更新
int GamePlay::Update() {
	// 各クラスの更新
	stage_->Update();  // ステージ
	player_->Update(); // プレイヤー
	for (Beam* beam : beamTable_) {
		beam->Update(); // ビーム
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Update(); // 敵
	}
	// 射撃
	Shot();

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
	for (Beam* beam : beamTable_) {
		beam->Draw3D(); // ビームの描画
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Draw3D(); // 敵の描画
	}
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
	for (Enemy* enemy : enemyTable_) {
		// 敵が存在すれば
		if (enemy->GetFlag() == 1) {
			// 差を求める
			float dx = abs(player_->GetX() - enemy->GetX());
			float dz = abs(player_->GetZ() - enemy->GetZ());
			// 衝突したら
			if (dx < 1 && dz < 1) {
				// 衝突処理
				enemy->Hit();
				// ライフ減算
				playerLife_ -= 1;
			}
		}
	}
}

// 衝突判定（ビームと敵）
void GamePlay::CollisionBeamEnemy() {
	for (Beam* beam : beamTable_) {
		// ビームが存在すれば
		if (beam->GetFlag() == 1) {
			for (Enemy* enemy : enemyTable_) {
				// 敵が存在すれば
				if (enemy->GetFlag() == 1) {
					// 差を求める
					float dx = abs(beam->GetX() - enemy->GetX());
					float dz = abs(beam->GetZ() - enemy->GetZ());
					// 衝突したら
					if (dx < 1 && dz < 1) {
						// 衝突処理
						enemy->Hit();
						beam->Hit();
						// 点数加算
						gameScore_ += 1;
					}
				}
			}
		}
	}
}

// 開始
void GamePlay::Start() {
	playerLife_ = 3;
	gameScore_ = 0;
	player_->Start();
	for (Beam* beam : beamTable_) {
		beam->Start();
	}
	for (Enemy* enemy : enemyTable_) {
		enemy->Start();
	}
	Update();
}

// 射撃
void GamePlay::Shot() {
	// 射撃タイマーが0ならば
	if (shotTimer_ == 0) {

		// スペースキーを押したら
		if (input_->PushKey(DIK_SPACE)) {
			// ビームでループ
			for (Beam* beam : beamTable_) {
				// 存在しなければ
				if (beam->GetFlag() == 0) {
					// 発射（発生）
					beam->Born();
					beam->Update();
					// 射撃タイマー
					shotTimer_ = 1;

					break;
				}
			}
		}
	}
	// 発射できない状態
	else {
		// タイマー加算
		shotTimer_++;

		// 一定時間で
		if (shotTimer_ > 10) {
			// 発射できる状態
			shotTimer_ = 0;
		}
	}
}
