#include "GameScene.h"
#include "TextureManager.h"
#include "MathUtilityForText.h"
#include <cassert>
#include "time.h"

GameScene::GameScene() {}

GameScene::~GameScene() { 

	delete modelEnemy_; 
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();

	textureHandle_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();

	for (int e = 0; e < 10; e++) 
	{
		worldTransformEnemy_[e].scale_ = {0.2f, 0.2f, 0.2f};
		worldTransformEnemy_[e].Initialize();
	}
}

void GameScene::GamePlayUpdate() { 
	EnemyUpdate(); 
}

void GameScene::Update() 
{
	switch (sceneMode_) 
	{
	case 0:
		GamePlayUpdate();
		break;
	}
}

void GameScene::EnemyUpdate() {
	EnemyMove();
	EnemyBorn();
	for (int e = 0; e < 10; e++) {
		if (EnemyFlag_[e] != 0)

			worldTransformEnemy_[e].matWorld_ = MakeAffineMatrix(
			    worldTransformEnemy_[e].scale_, worldTransformEnemy_[e].rotation_,
			    worldTransformEnemy_[e].translation_);

		// 変換行列を定数バッファに転送
		worldTransformEnemy_[e].TransferMatrix();
	}
}

void GameScene::EnemyBorn() {

}

void GameScene::EnemyMove() {

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
