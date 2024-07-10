#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"

class Player : public Character
{
public:
    Player();
    ~Player() override;
    //�C���X�^���X
    static Player& Instance();

    //�X�V����
    void Update(float olapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //�f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive();

    //�f�o�b�O�pGUI
    void DrawDebugGUI();
private:
    //�X�e�B�b�N���͒l����ړ��x�N�g�����擾
    DirectX::XMFLOAT3 GetMoveVec() const;

    //�v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
    void CollisionPlayerVsEnemies();
    //�v���C���[�ƃG�l�~�[�̏Փˏ���
    void CollisionProjectilesVsEnemies();
    //�m�[�h�ƃG�l�~�[�̏Փˏ���
    void CollisionNodeVsEnemies(const char* nodeName, float nodeRadius);

private:

    //�e�ۓ��͏���
    void InputProjectile();
    //�ҋ@�X�e�[�g�֑J��
    void TransitionIdleState();
    //�ҋ@�X�e�[�g�X�V����
    void UpdateIdleState(float elapsedTime);

    //�ړ����͏���
    bool InputMove(float elapsedTime);
    //�ړ��X�e�[�g�֑J��
    void TransitionMoveState();
    //�ړ��X�e�[�g�X�V����
    void UpdateMoveState(float elapsedTime);

    //�W�����v���͏���
    bool InputJump();
    //�W�����v�X�e�[�g�֑J��
    void TransitionJumpState();
    //�W�����v�X�e�[�g�X�V����
    void UpdateJumpState(float elapsedTime);
    //���n�X�e�[�g�֑J��
    void TransitionLandState();
    //���n�X�e�[�g�X�V����
    void UpdateLandState(float elapsedTime);

    //�U�����͏���
    bool InputAttack();
    //�U���X�e�[�g�֑J��
    void TransitionAttackState();
    //�U���X�e�[�g�X�V
    void UpdateAttackState(float elapsedTime);

    //�_���[�W�X�e�[�g�J��
    void TransitionDamageState();
    //�_���[�W�X�e�[�g�X�V
    void UpdateDamageState(float elapsedTime);

    //���S�X�e�[�g�J��
    void TransitionDeathState();
    //���S�X�e�[�g�X�V
    void UpdateDeathState(float elapsedTime);

    //�����X�e�[�g�J��
    void TransitionReviveState();
    //�����X�e�[�g�X�V
    void UpdateReviveState(float elapsedTime);

    //�X�e�[�g
    enum class State
    {
        Idle,
        Move,
        Jump,
        Land,
        Attack,
        Damage,
        Death,
        Revive
    };

protected:
    void OnLanding() override;
    void OnDamaged()override;
    void OnDead()override;
private:
    Model* model = nullptr;
    float       moveSpeed = 7.0f;
    float       turnSpeed = DirectX::XMConvertToRadians(720);
    float       jumpSpeed = 20.0f;
    /*float       gravity = -1.0f;
    DirectX::XMFLOAT3 velocity = { 0,0,0 };*/

    int         jumpCount = 0;
    int         jumpLimit = 2;

    State state = State::Idle;

    ProjectileManager projectileManager;

    Effect*     hitEffect = nullptr;
    Effect*     auraEffect = nullptr;
    
    //�A�j���[�V����
    enum Animation
    {
        Anim_Attack,
        Anim_Death,
        Anim_Falling,
        Anim_GetHit1,
        Anim_GetHit2,
        Anim_Idle,
        Anim_Jump,
        Anim_Jump_Flip,
        Anim_Landing,
        Anim_Revive,
        Anim_Running,
        Anim_Walking,
    };

    float leftHandRadius = 0.4f;
    bool attackCollisionFlag;
};