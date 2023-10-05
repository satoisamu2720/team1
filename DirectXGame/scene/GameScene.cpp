#include "GameScene.h"
#include "MathUtilityForText.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete modelPlayer_; 
	delete modelBeam_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ビュープロジェクションの初期化
	viewProjection_.translation_.y = 2;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	// プレイヤー
	textureHandlePlayer_ = TextureManager::Load("player.png");
	modelPlayer_ = Model::Create();
	worldTransformPlayer_.scale_ = {0.2f, 0.2f, 0.2f};
	worldTransformPlayer_.Initialize();
	// ビーム
	textureHandleBeam_ = TextureManager::Load("beam.png");
	modelBeam_ = Model::Create();

	for (int b = 0; b < 10; b++) {
		worldTransformBeam_[b].scale_ = {0.3f, 0.3f, 0.3f};
		worldTransformBeam_[b].Initialize();
	}
}
void GameScene::GamePlayUpdete() { 
	PlayerUpdate(); 
	BeamUpdate();
}
void GameScene::Update() { 
	GamePlayUpdete(); 
}

// プレイヤー更新処理
void GameScene::PlayerUpdate() {

	// 移動
	worldTransformPlayer_.translation_.x += playerSpeed_;
	// 左へ移動
	if (worldTransformPlayer_.translation_.x > 4) {
		playerSpeed_ = -0.05f;
	}
	// 右へ移動
	if (worldTransformPlayer_.translation_.x < -4) {
		playerSpeed_ = 0.05f;
	}

	// 変換行列を更新
	worldTransformPlayer_.matWorld_ = MakeAffineMatrix(
	    worldTransformPlayer_.scale_, worldTransformPlayer_.rotation_,
	    worldTransformPlayer_.translation_);
	// 変換行列を定数バッファに転送
	worldTransformPlayer_.TransferMatrix();

	if (playerTimer_ > 0) {
		playerTimer_ -= 1;
	}
}

// ビーム更新処理
void GameScene::BeamUpdate() {
	BeamMove();
	BeamBorn();
	// 変換行列を更新
	for (int i = 0; i < 10; i++) {
		if (beamFlag_[i] == 1)

			worldTransformBeam_[i].matWorld_ = MakeAffineMatrix(
			    worldTransformBeam_[i].scale_, worldTransformBeam_[i].rotation_,
			    worldTransformBeam_[i].translation_);
		// 変換行列を定数バッファに転送
		worldTransformBeam_[i].TransferMatrix();
	}
}

// ビーム移動
void GameScene::BeamMove() {

	for (int i = 0; i < 10; i++) {
		if (beamFlag_[i] == 1) {
			worldTransformBeam_[i].translation_.z += 0.5f;
			worldTransformBeam_[i].translation_.y += 0.1f;
			// 回転　
			worldTransformBeam_[i].rotation_.x += 0.1f;
		}
	}
}

// ビーム
void GameScene::BeamBorn() {
	// スペースキーで発射
	for (int b = 0; b < 10; b++) {
		if (beamTimer_ == 0) {

			if (input_->PushKey(DIK_SPACE) && beamFlag_[b] == 0) {
				worldTransformBeam_[b].translation_.x = worldTransformPlayer_.translation_.x;
				worldTransformBeam_[b].translation_.y = worldTransformPlayer_.translation_.y;
				worldTransformBeam_[b].translation_.z = worldTransformPlayer_.translation_.z;

				beamTimer_ = 1;
				beamFlag_[b] = 1;
				break;
			}

		} else {

			if (beamTimer_ >= 1) {
				beamTimer_++;

				if (beamTimer_ > 30) {
					beamTimer_ = 0;
				}
				break;
			}
		}

		// // 40以上で削除
		if (worldTransformBeam_[b].translation_.z > 40) {
			beamFlag_[b] = 0;
			beamTimer_ = 0;
		}
	}
}

void GameScene::GamePlayDraw3D() {
	//プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_, textureHandlePlayer_);
	//弾
	for (int b = 0; b < 10; b++) {
		if (beamFlag_[b] == 1) {
			modelBeam_->Draw(worldTransformBeam_[b], viewProjection_, textureHandleBeam_);
		}
	}
}
	void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

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
	 GamePlayDraw3D();
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
