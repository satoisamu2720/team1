#include "GameScene.h"
#include "MathUtilityForText.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete modelPlayer_; 
	delete modelBeam_;
	delete modelEnemy_;
	delete modelWall_;
	delete modelSkyDome_;
	delete modelGround_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//プレイヤービュープロジェクションの初期化
	playerViewProjection_.translation_.y = 1;
	playerViewProjection_.translation_.z = -6;
	playerViewProjection_.Initialize();
	//弾ビュープロジェクションの初期化
	beamViewProjection_.translation_.y = 1;
	beamViewProjection_.translation_.z = -6;
	beamViewProjection_.Initialize();
	//敵ビュープロジェクションの初期化
	enemyViewProjection_.translation_.y = 1;
	enemyViewProjection_.translation_.z = -6;
	enemyViewProjection_.Initialize();
	//壁ビュープロジェクションの初期化
	wallViewProjection_.translation_.y = 1;
	wallViewProjection_.translation_.z = -6;
	wallViewProjection_.Initialize();
	//スカイドーム
	SkyDomeViewProjection_.translation_.x = 0;
	SkyDomeViewProjection_.translation_.y = 0;
	SkyDomeViewProjection_.translation_.z = 0;
	SkyDomeViewProjection_.Initialize();
	//地面
	GroundViewProjection_.translation_.x = 1;
	GroundViewProjection_.translation_.y = 1;
	GroundViewProjection_.translation_.z = 1;
	GroundViewProjection_.Initialize();
	//ライフ
	for (int i = 0; i < 3; i++) {
		PlayerLifeViewProjection_[0].translation_.x =-0.5;
		PlayerLifeViewProjection_[1].translation_.x = 0;
		PlayerLifeViewProjection_[2].translation_.x = 0.5;
		PlayerLifeViewProjection_[i].translation_.y = 0.7f;
		PlayerLifeViewProjection_[i].translation_.z = -6;
		PlayerLifeViewProjection_[i].Initialize();
	}

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
	// 敵
	textureHandleEnemy_ = TextureManager::Load("enemy.png");
	modelEnemy_ = Model::Create();

	for (int e = 0; e < 10; e++) {
		worldTransformEnemy_[e].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransformEnemy_[e].Initialize();
	}
	// 壁
	textureHandleWall_ = TextureManager::Load("wall.png");
	modelWall_ = Model::Create();
	worldTransformWall_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransformWall_.Initialize();

	//天球
	modelSkyDome_ = Model::CreateFromOBJ("skydome", true);
	worldTransformSkyDome_.Initialize();

	//地面
	modelGround_ = Model::CreateFromOBJ("wall", true);
	worldTransformGround_.Initialize();
	
	//スコア文字表示
	textureHandleSCORE_ = TextureManager::Load("score.png");
	spriteScore_ = Sprite::Create(textureHandleSCORE_, {0.0f, 10});

	// スコア
	textureHandleNumber_ = TextureManager::Load("number.png");
	for (int i = 0; i < 4; i++) {
		spriteNumber_[i] = Sprite::Create(textureHandleNumber_, {130.0f + i * 26, 10});
	}

	//プレイヤーライフ
	textureHandlePlayerLife_ = TextureManager::Load("player.png");
	modelPlayerLife_ = Model::Create();
	for (int i = 0; i < 3; i++) 
	{
		worldTransformPlayerLife_[i].scale_ = {0.2f, 0.2f, 0.2f};
		worldTransformPlayerLife_[i].Initialize();
	}
}

void GameScene::GamePlayUpdate() { 
	PlayerLifeUpdate();
	PlayerUpdate(); 
	BeamUpdate();
	EnemyUpdate();
	WallUpdate();
	
	Collision();
}
// シーン切り替え

void GameScene::Update() {

	switch (sceneMode_) {
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		TitleUpdate();
		break;
	case 2:
		GameoverUpdate();
		break;
	}

	gameTimer_ += 1;
}


// プレイヤー更新処理
void GameScene::PlayerUpdate() {

	for (int i = 0; i < 3; i++) {

		if (++buttonTimer_ >= 20 && input_->PushKey(DIK_SPACE)) {
			playerMoveFlag_++;
			playerLifeMoveFlag_[0]++;

			buttonTimer_ = 0;
		}
		if (playerMoveFlag_ > 1 || playerLifeMoveFlag_[i] > 1) {
			playerMoveFlag_ = 0;
			playerLifeMoveFlag_[0] = 0;
		}
		// 右へ移動
		if (playerMoveFlag_ == 0) {
			worldTransformPlayerLife_[0].translation_.x += playerLifeSpeed_;
			worldTransformPlayerLife_[1].translation_.x += playerLifeSpeed_;
			worldTransformPlayerLife_[2].translation_.x += playerLifeSpeed_;
			worldTransformPlayer_.translation_.x += playerSpeed_;
			inputFloat[0] = worldTransformPlayer_.translation_.x;
			
			
		}
		// 左へ移動
		if (playerMoveFlag_ == 1) {
			worldTransformPlayerLife_[0].translation_.x -= playerLifeSpeed_;
			worldTransformPlayerLife_[1].translation_.x -= playerLifeSpeed_;
			worldTransformPlayerLife_[2].translation_.x -= playerLifeSpeed_;
			worldTransformPlayer_.translation_.x -= playerSpeed_;
			inputFloat[0] = worldTransformPlayer_.translation_.x;
			
			//worldTransformPlayerLife_[1].translation_.x -= playerLifeSpeed_;
		}
		// 左へ移動
		if (worldTransformPlayer_.translation_.x > 4) {
			playerMoveFlag_ = 1;
			playerLifeMoveFlag_[0] = 1;
		}
		// 右へ移動
		if (worldTransformPlayer_.translation_.x < -4) {
			playerMoveFlag_ = 0;
			playerLifeMoveFlag_[0] = 0;
		}
	}
	worldTransformPlayer_.translation_.x = inputFloat[0];
	worldTransformPlayer_.translation_.y = inputFloat[1];
	worldTransformPlayer_.translation_.z = inputFloat[2];

	//worldTransformPlayerLife_[0].translation_ = {1.0f,1.0f,1.0f};


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
	//ImGui::Text("DebugCamera Toggle : LEFT SHIFT");
	ImGui::SliderFloat3("Positions", inputFloat, -4.0f, 4.0f);
	// ImGui終わり
	ImGui::End();

	if (playerLife_ == 0) {
		sceneMode_ = 2;
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
			//worldTransformBeam_[i].translation_.y += 0.1f;
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

// 敵の更新処理
void GameScene::EnemyUpdate() {
	EnemyMove();
	EnemyBorn();
	EnemyJump();
	for (int e = 0; e < 10; e++) {
		if (EnemyFlag_[e] != 0)

			worldTransformEnemy_[e].matWorld_ = MakeAffineMatrix(
			    worldTransformEnemy_[e].scale_, worldTransformEnemy_[e].rotation_,
			    worldTransformEnemy_[e].translation_);

		// 変換行列を定数バッファに転送
		worldTransformEnemy_[e].TransferMatrix();
	}
}

// 　敵の移動
void GameScene::EnemyMove() {

	for (int e = 0; e < 10; e++) {
		if (EnemyFlag_[e] == 1) {
			worldTransformEnemy_[e].translation_.z -= 0.5f;
			//worldTransformEnemy_[e].translation_.y -= 0.1f;
		}
	}
}

// 敵
void GameScene::EnemyBorn() {

	for (int e = 0; e < 10; e++) {
		enemyTimer_[0]++;

		if (enemyTimer_[0] > 60) {
			enemyTimer_[0] = 0;
		}
		
		if (EnemyFlag_[e] == 0) {
			if (enemyTimer_[0] == 0) {

				int x = -4 + rand() % 8;
				float x2 = (float)x;
				worldTransformEnemy_[e].translation_.x = x2;
				worldTransformEnemy_[e].translation_.z = 40;
				worldTransformEnemy_[e].translation_.y = 0;

				if (rand() % 2 == 0) {
					enemySpeed_[e] = 0.05f;

				} else {
					enemySpeed_[e] = -0.05f;
				}
				EnemyFlag_[e] = 1;
				break;
			} 
		}
		
		//-5にいったら削除
		if (worldTransformEnemy_[e].translation_.z < -5) {
			EnemyFlag_[e] = 0;
			break;
		}
	}
}
void GameScene::EnemyJump() {
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 2) {
			//

			//
			worldTransformEnemy_[i].translation_.x += enemyJumpSpeed_[i];
			enemyJumpSpeed_[i] -= 0.1f;

			//
			// worldTransformEnemy_[i].translation_.x += enemySpeed_[i] * 4;
			worldTransformEnemy_[i].translation_.y += enemySpeed_[i] * 4;
			//

			if (worldTransformEnemy_[i].translation_.y < -3) {
				EnemyFlag_[i] = 0;
			}
		}
	}
}
// 壁更新
void GameScene::WallUpdate() {
	
	worldTransformWall_.translation_.z = 10;
	// 壁の移動
	worldTransformWall_.translation_.x += WallSpeed_;
	// 左へ移動
	if (worldTransformWall_.translation_.x > 4) {
		WallSpeed_ = -0.02f;

		if (WallLife_ == 2) {
			WallSpeed_ = -0.03f;
		}
	}
	// 右へ移動
	if (worldTransformWall_.translation_.x < -4) {
		WallSpeed_ = 0.02f;

		if (WallLife_ == 2) {
			WallSpeed_ = 0.03f;
		}
	}

	if (WallLife_ >= 0) {
		// 変換行列を更新
		worldTransformWall_.matWorld_ = MakeAffineMatrix(
		    worldTransformWall_.scale_, worldTransformWall_.rotation_,
		    worldTransformWall_.translation_);
		// 変換行列を定数バッファに転送
		worldTransformWall_.TransferMatrix();
	}
}

void GameScene::PlayerLifeUpdate() {

	for (int i = 0; i < 3; i++) {

		// 変換行列を更新
		worldTransformPlayerLife_[i].matWorld_ = MakeAffineMatrix(
		    worldTransformPlayerLife_[i].scale_, worldTransformPlayerLife_[i].rotation_,
		    worldTransformPlayerLife_[i].translation_);
		// 変換行列を定数バッファに転送
		worldTransformPlayerLife_[i].TransferMatrix();
	}
}

void GameScene::Collision() {
	// 衝突判定（プレイヤーと敵）
	CollisionPlayerEnemy();
	// 衝突判定（ビームと敵）
	CollisionBeamEnemy();
	//衝突判定　（ビームと壁）
	CollisionBeamWall();
}

// プレイヤーと敵の当たり判定
void GameScene::CollisionPlayerEnemy() {
	// 敵が存在すれば
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] == 1) {
			// 差を求める
			float dx =
			    abs(worldTransformPlayer_.translation_.x - worldTransformEnemy_[i].translation_.x);
			float dz =
			    abs(worldTransformPlayer_.translation_.z - worldTransformEnemy_[i].translation_.z);
			// 衝突したら
			if (dx < 1 && dz < 1) {
				// 存在しない
				EnemyFlag_[i] = 0;
				playerLife_ -= 1;
				playerTimer_ = 60;
				// BGM切り替え
			}
			if (playerLife_ <= 0) {
				beamFlag_[i] = 0;
				EnemyFlag_[i] = 0;
			}
		}
	}
}

// 敵とビームの当たり判定
void GameScene::CollisionBeamEnemy() {
	// 敵が存在すれば
	for (int i = 0; i < 10; i++) {
		if (EnemyFlag_[i] != 0) {
			for (int b = 0; b < 10; b++) {
				if (beamFlag_[b] == 1) {
					// 差を求める
					float dx =
					    abs(worldTransformBeam_[b].translation_.x -
					        worldTransformEnemy_[i].translation_.x);
					float dz =
					    abs(worldTransformBeam_[b].translation_.z -
					        worldTransformEnemy_[i].translation_.z);
					// 衝突したら
					if (dx < 1 && dz < 1) {
						// 存在しない
						gameScore_ += 1;
						EnemyFlag_[i] = 0;
						beamFlag_[b] = 0;
					}
				}
			}
		}
	}
}
void GameScene::CollisionBeamWall() {
	// 壁が存在すれば
	for (int b = 0; b < 10; b++) {
		if (WallFlag_ == 1 && WallTimeFlag_ == 0) {
			// 差を求める
			float dx =
			    abs(worldTransformBeam_[b].translation_.x - worldTransformWall_.translation_.x);
			float dz =
			    abs(worldTransformBeam_[b].translation_.z - worldTransformWall_.translation_.z);
			// 衝突したら
			if (dx < 1 && dz < 1) {
				WallLife_ -= 1;
				WallTimeFlag_ = 1;
				beamFlag_[b] = 0;
				worldTransformBeam_[b].translation_.z = -20;
			}

			
			if (WallLife_ <= 0) {
				WallFlag_ = 0;
				gameScore_ += 2;
			}
		}
		if (WallTimeFlag_ == 1) {
			WallTime_--;
		}
		if (WallTime_ == 0) {
			WallTimeFlag_ = 0;
			WallTime_ = 30;
			
		}
		
	}
}

void GameScene::GamePlayDraw2DNear() 
{
	// ライフ
	/*for (int i = 0; i < 3; i++) 
	{ 
		spriteLife_[i] = Sprite::Create(textureHandlePlayer_,{worldTransformPlayer_.translation_.x + i * 20 + playerSpeed_, worldTransformPlayer_.translation_.y + 450});
		spriteLife_[i]->SetSize({20, 20});
	}*/

	//描画
	
	spriteScore_->Draw();
	DrawScore();
}

void GameScene::DrawScore() {
	int eachNumber[4] = {};
	int number = gameScore_;

	int keta = 1000;
	for (int i = 0; i < 4; i++) {
		eachNumber[i] = number / keta;
		number = number % keta;
		keta = keta / 10;
	}

	for (int i = 0; i < 4; i++) {
		spriteNumber_[i]->SetSize({32, 64});
		spriteNumber_[i]->SetTextureRect({32.0f * eachNumber[i], 0}, {32, 64});
		spriteNumber_[i]->Draw();
	}
}
// タイトル
void GameScene::TitleUpdate() {
	for (int i = 0; i < 10; i++) {
		if (input_->TriggerKey(DIK_RETURN)) {
			// リセット
			//worldTransformPlayer_.translation_.x = 0;
			PlayerLifeViewProjection_[0].translation_.x = -0.5f;
			PlayerLifeViewProjection_[1].translation_.x = 0;
			PlayerLifeViewProjection_[2].translation_.x = 0.5f;
			gameScore_ = 0;
			beamFlag_[i] = 0;
			playerLife_ = 3;
			sceneMode_ = 0;
			EnemyFlag_[i] = 0;
			beamFlag_[i] = 0;
			gameTimer_ = 0;
			playerTimer_ = 0;
			GamePlayUpdate();
		}
	}
}
void GameScene::GameoverUpdate() {
	for (int i = 0; i < 10; i++) {
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneMode_ = 1;

			}
	}
}

// タイトル
void GameScene::TitleDraw2DNear() {
	spriteTitle_->Draw();

	if (gameTimer_ % 40 >= 20) {
		    spriteEnter_->Draw();
	}
}

void GameScene::GameOverDraw2DNear() {
	spriteGameover_->Draw();

	if (gameTimer_ % 40 >= 20) {
		    spriteEnter_->Draw();
	}
}


void GameScene::GamePlayDraw3D() {
	//プレイヤー
	modelPlayer_->Draw(worldTransformPlayer_, playerViewProjection_, textureHandlePlayer_);
	//弾
	for (int b = 0; b < 10; b++) {
		if (beamFlag_[b] == 1) {
			modelBeam_->Draw(worldTransformBeam_[b], beamViewProjection_, textureHandleBeam_);
		}
	}
	// 敵描画　
	for (int e = 0; e < 10; e++) {
		if (EnemyFlag_[e] != 0) {
			modelEnemy_->Draw(worldTransformEnemy_[e], enemyViewProjection_, textureHandleEnemy_);
		}
	}
	// 壁
	if (WallFlag_ == 1) {
		modelWall_->Draw(worldTransformWall_, wallViewProjection_, textureHandleWall_);
	}

	//天球
	modelSkyDome_->Draw(worldTransformSkyDome_, SkyDomeViewProjection_);

	//地面
	modelGround_->Draw(worldTransformGround_, GroundViewProjection_);


	for (int i = 0; i < 3; i++) {
		if (playerLife_ >= 3) {
			modelPlayerLife_->Draw(
			    worldTransformPlayerLife_[0], PlayerLifeViewProjection_[0], textureHandlePlayer_);
		}
		if (playerLife_ >= 2) {
			modelPlayerLife_->Draw(
			    worldTransformPlayerLife_[1], PlayerLifeViewProjection_[1], textureHandlePlayer_);
		}
		if (playerLife_ >= 1) {
			modelPlayerLife_->Draw(
			    worldTransformPlayerLife_[2], PlayerLifeViewProjection_[2], textureHandlePlayer_);
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

	GamePlayDraw2DNear();

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
