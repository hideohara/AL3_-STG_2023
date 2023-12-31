﻿#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Beam.h"
#include "DebugText.h"
#include "Enemy.h"
#include "Player.h"
#include "Stage.h"

// ゲームプレイ
class GamePlay {
public:
	// コンストラクタ
	GamePlay();

	// デストラクタ
	~GamePlay();

	// 初期化
	void Initialize(ViewProjection viewProjection);

	// 更新
	int Update();

	// 3D描画
	void Draw3D();

	// 2D遠景描画
	void Draw2DFar();

	// 2D近景描画
	void Draw2DNear();

	// 衝突判定
	void Collision();

	// 衝突判定（プレイヤーと敵）
	void CollisionPlayerEnemy();

	// 衝突判定（ビームと敵）
	void CollisionBeamEnemy();

	// 開始
	void Start();

	// 射撃
	void Shot();

private:
	// ビュープロジェクション（共通）
	ViewProjection viewProjection_;

	// 各クラス
	Stage* stage_ = nullptr;     // ステージ
	Player* player_ = nullptr;   // プレイヤー
	Beam* beamTable_[10] = {};   // ビーム
	Enemy* enemyTable_[10] = {}; // 敵

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	int gameScore_ = 0;  // ゲームスコア
	int playerLife_ = 3; // プレイヤーライフ

	// インプットクラス
	Input* input_ = nullptr;

	// 射撃タイマー
	int shotTimer_;
};
