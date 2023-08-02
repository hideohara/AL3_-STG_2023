#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

// コンストラクタ
GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {

	// 各シーンの削除
	delete gamePlay_; // ゲームプレイ
	delete title_;    // タイトル
	delete gameOver_; // ゲームオーバー
}

// 初期化
void GameScene::Initialize() {

	srand((unsigned int)time(NULL));

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	// 各シーンの生成
	gamePlay_ = new GamePlay();
	title_ = new Title();
	gameOver_ = new GameOver();

	// 各シーンの初期化
	gamePlay_->Initialize(viewProjection_); //	ゲ－ムプレイ
	title_->Initialize();                   //	タイトル
	gameOver_->Initialize();                //	ゲ－ムオーバー
}

// 更新
void GameScene::Update() {
	// 現在のモードを記録
	int oldSceneMode = sceneMode_;

	// 各シーン更新
	switch (sceneMode_) {
	case 0:
		sceneMode_ = gamePlay_->Update(); // ゲームプレイ
		break;
	case 1:
		sceneMode_ = title_->Update(); // タイトル
		break;
	case 2:
		sceneMode_ = gameOver_->Update(); // ゲームオーバー
		break;
	}

	// シーン変更ならば
	if (oldSceneMode != sceneMode_) {
		switch (sceneMode_) {
		case 0:
			gamePlay_->Start(); // ゲームプレイ
			break;
		}
	}
}

// 描画
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// 背景の描画
	// 各シーン2D背景描画
	switch (sceneMode_) {
	case 0:
		gamePlay_->Draw2DFar(); // ゲームプレイ
		break;
	case 2:
		gamePlay_->Draw2DFar(); // ゲームプレイ
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 各シーン３D描画
	switch (sceneMode_) {
	case 0:
		gamePlay_->Draw3D(); // ゲームプレイ
		break;
	case 2:
		gamePlay_->Draw3D(); // ゲームプレイ
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// 各シーン2D前景描画
	switch (sceneMode_) {
	case 0:
		gamePlay_->Draw2DNear(); // ゲームプレイ
		break;
	case 1:
		title_->Draw2DNear(); // タイトル
		break;
	case 2:
		gamePlay_->Draw2DNear(); // ゲームプレイ
		gameOver_->Draw2DNear(); // ゲームオーバー
		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
