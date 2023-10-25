#include "Player.h"


Player::Player() {}

Player::~Player() { delete modelPlayer_; }

void Player::Initialize() {
// プレイヤービュープロジェクションの初期化
	playerViewProjection_.translation_.y = 1;
	playerViewProjection_.translation_.z = -6;
	playerViewProjection_.Initialize();

	modelPlayer_ = Model::CreateFromOBJ("player", true);
	worldTransformPlayer_.scale_ = {0.2f, 0.2f, 0.2f};
	worldTransformPlayer_.Initialize();
}

void Player::Update() {
	for (int i = 0; i < 3; i++) {

		if (++buttonTimer_ >= 40 && input_->PushKey(DIK_SPACE)) {
			playerMoveFlag_++;
			playerLifeMoveFlag_[i]++;

			buttonTimer_ = 0;
		}
		if (playerMoveFlag_ > 1 || playerLifeMoveFlag_[i] > 1) {
			playerMoveFlag_ = 0;
			playerLifeMoveFlag_[i] = 0;
		}
		// 右へ移動
		if (playerMoveFlag_ == 0) {
			worldTransformPlayerLife_[0].translation_.x += playerLifeSpeed_;
			worldTransformPlayerLife_[1].translation_.x += playerLifeSpeed_;
			worldTransformPlayerLife_[2].translation_.x += playerLifeSpeed_;
			worldTransformPlayer_.translation_.x += playerSpeed_;
			inputFloat[0] = worldTransformPlayer_.translation_.x;
		}
		if (playerLifeMoveFlag_ == 0) {
		}
		// 左へ移動
		if (playerMoveFlag_ == 1) {
			worldTransformPlayerLife_[0].translation_.x -= playerLifeSpeed_;
			worldTransformPlayerLife_[1].translation_.x -= playerLifeSpeed_;
			worldTransformPlayerLife_[2].translation_.x -= playerLifeSpeed_;
			worldTransformPlayer_.translation_.x -= playerSpeed_;
			inputFloat[0] = worldTransformPlayer_.translation_.x;
		}
		if (playerLifeMoveFlag_[i] == 1) {
		}
		// 左へ移動
		if (worldTransformPlayer_.translation_.x > 4) {
			playerMoveFlag_ = 1;
			playerLifeMoveFlag_[i] = 1;
		}
		// 右へ移動
		if (worldTransformPlayer_.translation_.x < -4) {
			playerMoveFlag_ = 0;
			playerLifeMoveFlag_[i] = 0;
		}
	}
	worldTransformPlayer_.translation_.x = inputFloat[0];
	inputFloat[1] = WallTime_;
	worldTransformPlayer_.translation_.z = inputFloat[2];

	// worldTransformPlayerLife_[0].translation_ = {1.0f,1.0f,1.0f};

	// 変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformPlayer_.TransferMatrix();

	if (playerTimer_ > 0) {
		playerTimer_ -= 1;
	}
	// ImGuiスライダー
	ImGui::Begin("PlayerDebug");
	// ImGui::Text("DebugCamera Toggle : LEFT SHIFT");
	ImGui::SliderFloat3("Positions", inputFloat, -4.0f, 4.0f);
	// ImGui終わり
	ImGui::End();

	if (playerLife_ == 0) {
		sceneMode_ = 2;
	}
}

void Player::Draw() {}






