#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// ビーム
class Beam {
public:
	// コンストラクタ
	Beam();

	// デストラクタ
	~Beam();

	// 初期化
	void Initialize(ViewProjection viewProjection, Player* player);

	// 更新
	void Update();

	// 3D描画
	void Draw3D();

	// 移動
	void Move();

	// 発生（発射）
	void Born();

	// X座標の獲得
	float GetX() { return worldTransformBeam_.translation_.x; }

	// Z座標の獲得
	float GetZ() { return worldTransformBeam_.translation_.z; }

	// 存在フラグの獲得
	int GetFlag() { return aliveFlag_; }

	// 衝突処理
	void Hit() { aliveFlag_ = 0; }

	// 開始
	void Start();

private:
	// ビュープロジェクション（共通）
	ViewProjection viewProjection_;

	// ビ－ム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = nullptr;
	WorldTransform worldTransformBeam_;

	// インプットクラス
	Input* input_ = nullptr;

	// 存在フラグ
	int aliveFlag_ = 0;

	// プレイヤー
	Player* player_ = nullptr;
};
