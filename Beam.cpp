#include "Beam.h"

// コンストクラタ
Beam::Beam() {}

// デストラクタ
Beam::~Beam() {
	delete modelBeam_; // ビーム
}

// 初期化
void Beam::Initialize(ViewProjection viewProjection, Player* player) {
	// メンバー変数に代入
	viewProjection_ = viewProjection;
	player_ = player;

	// ビーム
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();
	worldTransformBeam_.scale_ = {0.3f, 0.3f, 0.3f};
	worldTransformBeam_.Initialize();

	// インプットクラス
	input_ = Input::GetInstance();
}

// 更新
void Beam::Update() {

	// 移動
	Move();

	// 発生（発射）
	Born();

	// 変換行列を更新
	worldTransformBeam_.matWorld_ = MakeAffineMatrix(
	    worldTransformBeam_.scale_, worldTransformBeam_.rotation_,
	    worldTransformBeam_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformBeam_.TransferMatrix();
}

// 3D描画
void Beam::Draw3D() {
	// ビ－ム
	if (aliveFlag_ == 1) {
		modelBeam_->Draw(worldTransformBeam_, viewProjection_, textureHandleBeam_);
	}
}

// 移動
void Beam::Move() {
	// 存在フラグが1ならば
	if (aliveFlag_ == 1) {
		// ビームが奥へ移動する。
		worldTransformBeam_.translation_.z += 0.3f;
		// 回転
		worldTransformBeam_.rotation_.x += 0.1f;

		// 画面端まで移動したら
		if (worldTransformBeam_.translation_.z > 40) {
			// 存在フラグを０にする。
			aliveFlag_ = 0;
		}
	}
}

// 発生
void Beam::Born() {
	// スペースキーを押したらビームを発射する
	if (input_->PushKey(DIK_SPACE)) {
		// 存在フラグが０ならば
		if (aliveFlag_ == 0) {
			// ビーム座標にプレイヤー座標を代入する
			worldTransformBeam_.translation_.x = player_->GetX();
			worldTransformBeam_.translation_.z = 0;
			// 存在フラグを１にする。
			aliveFlag_ = 1;
		}
	}
}
