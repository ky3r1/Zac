#pragma once

#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Character.h"
#include "ProjectileManager.h"
#include "Effect.h"
#include "Graphics/sprite.h"

class Player : public Character
{
public:
    Player();
    ~Player() override;
public:
    static Player& Instance();

    //�X�V����
    void Update(float olapsedTime);

    //�`�揈��
    void Render(ID3D11DeviceContext* dc, Shader* shader);

    //�f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive();

    //�f�o�b�O�pGUI
    void DrawDebugGUI() override;
private:
    //�����ړ��X�V����
    void UpdateVerticalMove(float elapsedTime)override;

    //�X�e�B�b�N���͒l����ړ��x�N�g�����擾
    DirectX::XMFLOAT3 GetMoveVec() const;

    //�v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
    void CollisionPlayerVsEnemies();

    void CollisionProjectilesVsEnemies();

    //�e�ۓ��͏���
    void InputProjectile();

    //�U���͈͗p�̍��W�ϊ�
    void AreaTransform();
private:
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

    //�U�����͏���
    bool InputAttack();
    //�U���X�e�[�g�֑J��
    void TransitionAttackState();
    //�U���X�e�[�g�X�V
    void UpdateAttackState(float elapsedTime);

    //�_���[�W���󂯂���
    void OnDamaged()override;
    //�_���[�W�X�e�[�g�J��
    void TransitionDamageState();
    //�_���[�W�X�e�[�g�X�V
    void UpdateDamageState(float elapsedTime);

public:
    //���S������
    void OnDead()override;
private:
    //���S�X�e�[�g�J��
    void TransitionDeathState();
    //���S�X�e�[�g�X�V
    void UpdateDeathState(float elapsedTime);

private:

    ProjectileManager projectileManager;

    float       moveSpeed = 7.0f;
    float       jumpSpeed = 20.0f;

    int         jumpCount = 0;
    int         jumpLimit = 2;

    //delay
    DelayTime projectile_auto;



    //Effect
    Effect* hitEffect = nullptr;

    GamePad& gamePad = Input::Instance().GetGamePad();

    //�A�j���[�V����:UnityChan
    enum Animation
    {
        Anim_Attack,
        Anim_Death,
        Anim_GetHit,
        Anim_Idle,
        Anim_IdleAnim,
        Anim_Running,
    };

    //�X�e�[�g
    enum class State
    {
        Idle,
        Move,
        Attack,
        Damage,
        Death,
    };
    State state = State::Idle;
};