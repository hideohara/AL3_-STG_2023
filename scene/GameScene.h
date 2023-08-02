#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "GameOver.h"
#include "GamePlay.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Title.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// 各シーン
	GamePlay* gamePlay_ = nullptr; // ゲームプレイ
	Title* title_ = nullptr;       // タイトル
	GameOver* gameOver_ = nullptr; // ゲームオーバー

	// ビュープロジェクション（共通）
	ViewProjection viewProjection_;

	int sceneMode_ = 1; // シーンモード（0:ゲームプレイ　1:タイトル）
};
