#include "Enemy.h"

// コンストクラタ
Enemy::Enemy() {}

// デストラクタ
Enemy::~Enemy() {
	delete modelEnemy_; // 敵
}

// 初期化
void Enemy::Initialize(ViewProjection viewProjection) {
	// メンバー変数に代入
	viewProjection_ = viewProjection;

	// 敵
	textureHandleEnemy_ = TextureManager::Load("Enemy.png");
	modelEnemy_ = Model::Create();
	worldTransformEnemy_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformEnemy_.Initialize();
}

// 更新
void Enemy::Update() {

	// 移動
	Move();

	// 発生（発射）
	Born();

	//// 変換行列を更新
	worldTransformEnemy_.matWorld_ = MakeAffineMatrix(
	    worldTransformEnemy_.scale_, worldTransformEnemy_.rotation_,
	    worldTransformEnemy_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformEnemy_.TransferMatrix();
}

// 3D描画
void Enemy::Draw3D() {
	if (aliveFlag_ == 1) {
		modelEnemy_->Draw(worldTransformEnemy_, viewProjection_, textureHandleEnemy_);
	}
}

// 移動
void Enemy::Move() {
	// 存在フラグが1ならば
	if (aliveFlag_ == 1) {
		// 敵が手前へ移動する。
		worldTransformEnemy_.translation_.z -= 0.2f;
		// 回転
		worldTransformEnemy_.rotation_.x -= 0.1f;
		// 横移動
		worldTransformEnemy_.translation_.x += xSpeed_;
		if (worldTransformEnemy_.translation_.x > 4) {
			xSpeed_ = -0.1f;
		}
		if (worldTransformEnemy_.translation_.x < -4) {
			xSpeed_ = 0.1f;
		}

		// 画面端まで移動したら
		if (worldTransformEnemy_.translation_.z < -5) {
			// 存在フラグを０にする。
			aliveFlag_ = 0;
		}
	}
}

// 発生
void Enemy::Born() {
	// 乱数で発生
	if (rand() % 10 == 0) {

		// 存在フラグが０ならば
		if (aliveFlag_ == 0) {
			// 乱数でＸ座標の指定
			int x = rand() % 80; // 80は4の10倍の2倍
			float x2 = (float)x / 10 - 4;
			// 10で割り、4を引く
			worldTransformEnemy_.translation_.x = x2;
			worldTransformEnemy_.translation_.z = 40;
			// 存在フラグを１にする。
			aliveFlag_ = 1;
			// 敵スピード
			if (rand() % 2 == 0) {
				xSpeed_ = 0.1f;
			} else {
				xSpeed_ = -0.1f;
			}
		}
	}
}

// 開始
void Enemy::Start() {
	// 存在しない
	aliveFlag_ = 0;
}
