#pragma once

//�C���N���[�h
#include <DirectXMath.h>
#include "Graphics/Model.h"
#include "Graphics/Graphics.h"
#include <vector>
#include <set>
#include <imgui.h>

///////////////////�f�o�b�O�pdefine////////////////////////
//ImGui
#define DEBUGIMGUI

///////////////////Camera////////////////////////
#define MOUSECAMERA

///////////////////Character////////////////////////

///Player
//�v���C���[
#define ALLPLAYER
//�A�j���[�V����
#define PLAYERANIMATION
//Jump
//#define JUMPFRAG
// �U��
#define PLAYERATTACK
//Player->Enemy ���݂��_���[�W
#define JUMPDAMAGE

//Enemy->Player �ڐG�_���[�W
#define ENEMYHITTINGDAMAGE

///Enemy
//�G�l�~�[
#define ALLENEMY
////�X�|�[��
//#define SPOWNENEMY

////01
//#define ENEMY01 
////02
//#define ENEMY02
////03
//#define ENEMY03 
//BOSS
//#define ENEMYBOSS 

// �U��
#define ENEMYATTACK

//�X�e�[�g�}�V��
#define ENEMYSTATEMACHINE
//�A�j���[�V����
#define ENEMYANIMATION

/////////////Projectile////////////////////////
//�e�̃_���[�W
#define PROJECTILEDAMAGE
//�e�̏Ռ�
#define PROJECTILEHIT

///////////////////UI////////////////////////

////HP�Q�[�W
//#define HPGAUGE
//EnemyAdd
//#define ENEMYADD

///////////////////CATEGORY////////////////////////
#define PLAYERCATEGORY 0       //Player
#define ENEMYCATEGORY 1     //Enemy

///////////////////Stage////////////////////////

//�S�X�e�[�W
#define ALLSTAGE
//������
//#define STAGEMOVE

struct HitResult
{
    DirectX::XMFLOAT3 position = { 0,0,0 }; //���C�ƃ|���S���̌�_
    DirectX::XMFLOAT3 normal = { 0,0,0 };   //�Փ˂����|���S���̖@���x�N�g��
    float             distance = 0.0f;      //���C�̎n�_�����_�܂ł̋���
    int               materialIndex = -1;   //�Փ˂����|���S���̃}�e���A���ԍ�
    DirectX::XMFLOAT3 rotation = { 0,0,0 };   //�p�x
};

struct Sphere
{
    DirectX::XMFLOAT3 position = { 0,0,0 };
    float             radius = 0.0f;
    float             weight = 0.0f;
};

struct Cylinder
{
    Sphere            sphere;
    float             height = 0.0f;
};