#pragma once

//インクルード
#include <DirectXMath.h>
#include "Graphics/Model.h"
#include "Graphics/Graphics.h"
#include <vector>
#include <set>
#include <imgui.h>

///////////////////デバッグ用define////////////////////////
//ImGui
#define DEBUGIMGUI

///////////////////Camera////////////////////////
#define MOUSECAMERA

/////////////Object////////////////////////
#define OBJECT

///////////////////Character////////////////////////

///Player
//プレイヤー
#define ALLPLAYER
//アニメーション
#define PLAYERANIMATION
//Jump
//#define JUMPFRAG
// 攻撃
#define PLAYERATTACK
//Player->Enemy 踏みつけダメージ
#define JUMPDAMAGE

//Enemy->Player 接触ダメージ
#define ENEMYHITTINGDAMAGE

///Enemy
//エネミー
#define ALLENEMY
// 攻撃
#define ENEMYATTACK

//ステートマシン
#define ENEMYSTATEMACHINE
//アニメーション
#define ENEMYANIMATION

/////////////Projectile////////////////////////


///////////////////UI////////////////////////

////HPゲージ
//#define HPGAUGE
//EnemyAdd
//#define ENEMYADD

///////////////////CATEGORY////////////////////////
#define PLAYERCATEGORY 0       //Player
#define ENEMYCATEGORY 1     //Enemy

///////////////////Stage////////////////////////

//全ステージ
#define ALLSTAGE
//動く床
//#define STAGEMOVE

//struct HitResult
//{
//    DirectX::XMFLOAT3 position = { 0,0,0 }; //レイとポリゴンの交点
//    DirectX::XMFLOAT3 normal = { 0,0,0 };   //衝突したポリゴンの法線ベクトル
//    float             distance = 0.0f;      //レイの始点から交点までの距離
//    int               materialIndex = -1;   //衝突したポリゴンのマテリアル番号
//    DirectX::XMFLOAT3 rotation = { 0,0,0 };   //角度
//};
//
//struct Sphere
//{
//    DirectX::XMFLOAT3 position = { 0,0,0 };
//    float             radius = 0.0f;
//    float             weight = 0.0f;
//};
//
//struct Cylinder
//{
//    Sphere            sphere;
//    float             height = 0.0f;
//};
//
//struct DelayTime
//{
//    float time;
//    bool checker = false;
//};