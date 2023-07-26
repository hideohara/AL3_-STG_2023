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

// 敵
class Enemy {
public:
	// コンストラクタ
	Enemy();

	// デストラクタ
	~Enemy();

	// 初期化
	void Initialize(ViewProjection viewProjection);

	// 更新
	void Update();

	// 3D描画
	void Draw3D();

	// 移動
	void Move();

	// 発生（発射）
	void Born();

	// X座標の獲得
	float GetX() { return worldTransformEnemy_.translation_.x; }

	// Z座標の獲得
	float GetZ() { return worldTransformEnemy_.translation_.z; }

	// 存在フラグの獲得
	int GetFlag() { return aliveFlag_; }

	// 衝突処理
	void Hit() { aliveFlag_ = 0; }

private:
	// ビュープロジェクション（共通）
	ViewProjection viewProjection_;

	// 敵
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_;

	// 存在フラグ
	int aliveFlag_ = 0;
};
