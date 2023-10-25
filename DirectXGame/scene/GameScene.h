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
	//uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	int playerLife_ = 3;
	int playerTimer_ = 0;
	float playerSpeed_ = 0.02f;
	int playerMoveFlag_ = 0;
	
	// ビーム
	//uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = {nullptr};
	WorldTransform worldTransformBeam_[10];
	int beamFlag_[10] = {};// ビーム
	int beamTimer_ = 0;// ビーム

	// 敵
	//uint32_t textureHandleEnemy_ = 0;
	Model* modelEnemy_ = nullptr;
	WorldTransform worldTransformEnemy_[10];
	int EnemyFlag_[10] = {};
	float enemySpeed_[10] = {}; // 敵のスピード
	int enemyTimer_[10] = {};
	float enemyJumpSpeed_[10] = {};

	// 壁
	//uint32_t textureHandleWall_ = 0;
	Model* modelWall_ = nullptr;
	WorldTransform worldTransformWall_;
	int WallFlag_ = 1;// 壁フラグ
	int WallLife_ = 3;// 壁体力
	float WallSpeed_ = 0.04f; // 壁の速度
	float WallTime_ = 0;
	int WallTimeFlag_ = 0;

	// スカイドーム
	WorldTransform worldTransformSkyDome_;
	Model* modelSkyDome_ = nullptr;

	//地面
	WorldTransform worldTransformGround_;
	Model* modelGround_ = nullptr;

	int buttonTimer_ = 40; //ボタンクールタイム
	int buttonTimerFlag_ = 0;//ボタンクールタイムフラグ

	//ナンバー
	uint32_t textureHandleNumber_ = 0;
	Sprite* spriteNumber_[4] = {};
	 
	//スコア
	uint32_t textureHandleSCORE_ = 0;
	Sprite* spriteScore_ = {};
	int gameScore_ = 0;

	int gameTimer_ = 0;

	//ライフ表示
	/*orldTransform WorldTransformLife_ ;
	Model* modelLife_[3] = {nullptr};
	Sprite* spriteLife_[3] = {};*/

	// プレイヤーライフ
	//uint32_t textureHandlePlayerLife_ = 0;
	Model* modelPlayerLife_ ={ nullptr};
	WorldTransform worldTransformPlayerLife_[3];

	int playerTimerLife_ = 0;
	float playerLifeSpeed_ = 0.02f;
	int playerLifeMoveFlag_[3] = {};

	//シーン切り替え
	int sceneMode_ = 1;

	//タイトル
	void TitleUpdate();
	void TitleDraw2DNear();

	//タイトル（スプライト）
	uint32_t textureHandleTitle_ = 0;
	Sprite* spriteTitle_ = nullptr;

	//タイトル（文字）
	uint32_t textureHandleTitleEnter_ = 0;
	Sprite* spriteEnter_ = nullptr;

	//ゲームオーバー
	void GameoverUpdate();

	uint32_t textureHandleGameover_ = 0;
	Sprite* spriteGameover_ = nullptr;

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
	ViewProjection GroundViewProjection_;
	ViewProjection PlayerLifeViewProjection_[3];
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
	void PlayerLifeUpdate();
	void EnemyUpdate();//敵更新
	void EnemyMove();//敵行動
	void EnemyBorn();//
	void EnemyJump();
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
	void DrawScore(); //スコア表示
	void GamePlayDraw2DNear();
	void GameOverDraw2DNear();//ゲームオーバー
	void GamePlayDraw3D();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	float inputFloat[3]{0, 0, 0};
	
};
