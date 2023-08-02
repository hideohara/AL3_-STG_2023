#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// タイトル
class Title {
public:
	// コンストラクタ
	Title();

	// デストラクタ
	~Title();

	// 初期化
	void Initialize();

	// 更新
	int Update();

	// 2D近景描画
	void Draw2DNear();

private:
	// タイトル
	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	// エンター
	uint32_t textureHandleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	// タイマー
	int timer_;

	// インプットクラス
	Input* input_ = nullptr;
};
