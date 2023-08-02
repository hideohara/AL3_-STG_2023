#include "GameOver.h"

// コンストクラタ
GameOver::GameOver() {}

// デストラクタ
GameOver::~GameOver() {
	delete spriteGameOver_; // ゲームオーバー
	delete spriteEnter_;    // エンター
}

// 初期化
void GameOver::Initialize() {
	// BG(2Dスプライト)
	textureHandleGameOver_ = TextureManager::Load("gameover.png");
	spriteGameOver_ = Sprite::Create(textureHandleGameOver_, {0, 0});
	// エンター(2Dスプライト)
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	// インプットクラス
	input_ = Input::GetInstance();
}

// 更新
int GameOver::Update() {
	// タイマー加算
	timer_ += 1;

	// エンターキーを押した瞬間
	if (input_->TriggerKey(DIK_RETURN)) {
		// タイトルへ移行
		return 1;
	}

	// ゲームオーバーを継続
	return 2;
}

// 2D近景描画
void GameOver::Draw2DNear() {
	// 背景
	spriteGameOver_->Draw();
	// エンター
	if (timer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}
