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
