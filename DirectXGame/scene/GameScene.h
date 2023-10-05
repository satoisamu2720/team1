#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "ImGuiManager.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	// プレイヤー
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	int playerLife_ = 3;
	int playerTimer_ = 0;
	float playerSpeed_ = 0.05f;
	int playerMoveFlag_ = 0;
	// プレイヤー更新
	void PlayerUpdate();

	// ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = {};
	WorldTransform worldTransformBeam_[10];

	void BeamMove();
	void BeamUpdate();
	void BeamBorn();

	int beamFlag_[10] = {};
	int beamTimer_ = 0;


	// 敵
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = 0;
	WorldTransform worldTransformEnemy_[10];

	void EnemyMove();
	void EnemyUpdete();
	void EnemyBorn();

	int EnemyFlag_[10] = {};
	float enemySpeed_[10] = {}; // 敵のスピード
	int enemyTimer_[10] = {};

	void Collision();
	void CollisionPlayerEnemy();
	void CollisionBeamEnemy();


	int buttonTimer_ = 20;
	int buttonTimerFlag_ = 0;

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	// ビュープロジェクション(共通)
	ViewProjection playerViewProjection_;
	ViewProjection beamViewProjection_;
	ViewProjection enemyViewProjection_;
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
	void GamePlayUpdete();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void GamePlayDraw3D();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	float inputFloat[3]{0, 0, 0};
	
};
