#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// ゲームオーバー
class GameOver {
public:
	// コンストラクタ
	GameOver();

	// デストラクタ
	~GameOver();

	// 初期化
	void Initialize();

	// 更新
	int Update();

	// 2D近景描画
	void Draw2DNear();

private:
	// タイトル
	uint32_t textureHandleGameOver_ = 0;
	Sprite* spriteGameOver_ = nullptr;

	// エンター
	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	// タイマー
	int timer_;

	// インプットクラス
	Input* input_ = nullptr;
};
