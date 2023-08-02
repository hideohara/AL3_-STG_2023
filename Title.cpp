#include "Title.h"

// コンストクラタ
Title::Title() {}

// デストラクタ
Title::~Title() {
	delete spriteTitle_; // タイトル
	delete spriteEnter_; // エンター
}

// 初期化
void Title::Initialize() {
	// BG(2Dスプライト)
	textureHandleTitle_ = TextureManager::Load("title.png");
	spriteTitle_ = Sprite::Create(textureHandleTitle_, {0, 0});
	// エンター(2Dスプライト)
	textureHandleEnter_ = TextureManager::Load("enter.png");
	spriteEnter_ = Sprite::Create(textureHandleEnter_, {400, 500});

	// インプットクラス
	input_ = Input::GetInstance();
}

// 更新
int Title::Update() {
	// タイマー加算
	timer_ += 1;

	// エンターキーを押した瞬間
	if (input_->TriggerKey(DIK_RETURN)) {
		// ゲームプレイへ移行
		return 0;
	}

	// タイトルを継続
	return 1;
}

// 2D近景描画
void Title::Draw2DNear() {
	// 背景
	spriteTitle_->Draw();
	// エンター
	if (timer_ % 40 >= 20) {
		spriteEnter_->Draw();
	}
}
