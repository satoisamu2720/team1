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
	
	// ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = {};
	WorldTransform worldTransformBeam_[10];
	int beamFlag_[10] = {};// ビーム
	int beamTimer_ = 0;// ビーム

	// 敵
	uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = 0;
	WorldTransform worldTransformEnemy_[10];
	int EnemyFlag_[10] = {};
	float enemySpeed_[10] = {}; // 敵のスピード
	int enemyTimer_[10] = {};

	// 壁
	uint32_t textureHandleWall_ = 0;
	Model* modelWall_ = nullptr;
	WorldTransform worldTransformWall_;
	int WallFlag_ = 1;// 壁フラグ
	int WallLife_ = 3;// 壁体力
	float WallSpeed_ = 0.02f; // 壁の速度
	int WallTime_ = 30;
	int WallTimeFlag_ = 0;

	// スカイドーム
	WorldTransform worldTransformSkyDome_;
	Model* modelSkyDome_ = nullptr;

	int buttonTimer_ = 20; //ボタンクールタイム
	int buttonTimerFlag_ = 0;//ボタンクールタイムフラグ

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	// ビュープロジェクション(共通)
	ViewProjection playerViewProjection_;
	ViewProjection beamViewProjection_;
	ViewProjection enemyViewProjection_;
	ViewProjection wallViewProjection_;
	ViewProjection SkyDomeViewProjection_;
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
	void GamePlayUpdate();//ゲーム更新
	void PlayerUpdate(); // プレイヤー更新
	void EnemyUpdate();//敵更新
	void EnemyMove();//敵行動
	void EnemyBorn();//
	void BeamUpdate(); // ビーム更新
	void BeamMove();   // ビーム行動
	void BeamBorn();   // ビーム
	void WallUpdate();// 壁更新
	void Collision();  // 当たり判定更新
	void CollisionPlayerEnemy(); // プレイヤーと敵の当たり判定
	void CollisionBeamEnemy();   // 弾と敵の当たり判定
	void CollisionBeamWall();
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
