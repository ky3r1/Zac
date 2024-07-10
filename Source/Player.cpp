#include <imgui.h>
#include "Player.h"
#include "Input/Input.h"
#include "Camera.h"
#include "Graphics/Graphics.h"
#include "EnemyManager.h"
#include "Collision.h"
#include "ProjectileStraight.h"
#include "ProjectileHoming.h"

static Player* instance = nullptr;

Player::Player()
{
    instance = this;
    model = new Model("Data/Model/Jammo/Jammo.mdl");
    
    scale.x = scale.y = scale.z = 0.01f;

    //�q�b�g�G�t�F�N�g�ǂݍ���
    //hitEffect = new Effect("Data/Effect/GP3_sample.efk"); 
    hitEffect = new Effect("Data/Effect/testEFK.efkefc");
    //auraEffect= new Effect("Data/Effect/aura.efkefc");
    //�ҋ@�X�e�[�g�ւ̑J��
    TransitionIdleState();
}

Player::~Player()
{
    delete hitEffect;
    delete auraEffect;

    delete model;
}

Player& Player::Instance()
{
    return *instance;
}

void Player::Update(float elapsedTime)
{
    switch (state)
    {
    case State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case State::Move:
        UpdateMoveState(elapsedTime);
        break;
    case State::Jump:
        UpdateJumpState(elapsedTime);
        break;
    case State::Land:
        UpdateLandState(elapsedTime);
        break;
    case State::Attack:
        UpdateAttackState(elapsedTime);
        break;
    case State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    case State::Death:
        UpdateDeathState(elapsedTime);
        break;
    case State::Revive:
        UpdateReviveState(elapsedTime);
        break;
    }

    //���͏����X�V
    UpdateVelocity(elapsedTime);

    UpdateInvincibleTime(elapsedTime);

    //�e�ۍX�V����
    projectileManager.Update(elapsedTime);

    //�v���C���[�ƓG�Ƃ̏Փˏ���
    CollisionPlayerVsEnemies();

    //�e�ۂƓG�̏Փˏ���
    CollisionProjectilesVsEnemies();

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    //auraEffect->Play(position);

    //���f���A�j���[�V�����X�V����
#ifdef Player_Animation
    model->UpdateAnimation(elapsedTime);
#endif // Player_Animation

    //���f���s��X�V
    model->UpdateTransform(transform);
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);

    //�e�ە`�揈��
    projectileManager.Render(dc, shader);
}

void Player::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    ImGui::Begin("Player");
    ImGui::SetNextTreeNodeOpen(true);
    if (ImGui::TreeNode("Player"))
    {
        ImGui::SliderFloat3("position", &position.x, -5, 5);
        ImGui::SliderFloat3("scale", &scale.x, 0.01f, 4.0f);
        ImGui::SliderFloat3("angle", &angle.x, -3.14f, 3.14f);
        ImGui::SliderFloat3("velocity", &velocity.x, -5.0f, 5.0f);
        ImGui::SliderFloat("movespeed", &moveSpeed, 0.0f, 10.0f);
        ImGui::TreePop();
    }
    ImGui::End();
}
//�f�o�b�O�v���~�e�B�u�`��
void Player::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    ////�Փ˔���p�̃f�o�b�O����`��
    //debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

    //�e�ۃf�o�b�O�v���~�e�B�u�`��
    projectileManager.DrawDebugPrimitive();

    //�U���Փ˗p�̍���m�[�h�̃f�o�b�O����`��
    if (attackCollisionFlag)
    {
        Model::Node* leftHandBone = model->FindNode("mixamorig:LeftHand");
        debugRenderer->DrawSphere(DirectX::XMFLOAT3(
            leftHandBone->worldTransform._41,
            leftHandBone->worldTransform._42,
            leftHandBone->worldTransform._43),
            leftHandRadius,
            DirectX::XMFLOAT4(1, 0, 0, 1));
    }
}

void Player::CollisionPlayerVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    //���ׂĂ̓G�Ƒ�������ŏՓ˔���
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < enemyCount; i++)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);

        //�Փˏ���
        DirectX::XMFLOAT3 outPosition;
        if (Collision::IntersectCylinderVsSphere(
            position, radius,height,
            enemy->GetPosition(), enemy->GetRadius(),enemy->GetHeight(),
            outPosition))
        {
            health--;
            enemy->SetPosition(outPosition);
            if (position.y >= (enemy->GetPosition().y + enemy->GetHeight())-0.1f)
            {
                Jump(jumpSpeed);
                enemy->ApplyDamage(1, 0.5f);
            }
        }
    }
}

void Player::CollisionProjectilesVsEnemies()
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    //���ׂĂ̒e�ۂƂ��ׂĂ̓G������������ŏՓˏ���
    int projectileCount = projectileManager.GetProjectileCount();
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < projectileCount; ++i)
    {
        Projectile* projectile = projectileManager.GetProjectile(i);

        for (int j = 0; j < enemyCount; ++j)
        {
            Enemy* enemy = enemyManager.GetEnemy(j);

            //�Փˏ���
            DirectX::XMFLOAT3 outPosition;
            if (Collision::IntersectSphereVsCylinder(
                projectile->GetPosition(),
                projectile->GetRadius(),
                enemy->GetPosition(),
                enemy->GetRadius(),
                enemy->GetHeight(),
                outPosition))
            {
                //�_���[�W��^����
                if (enemy->ApplyDamage(1, 0.5f))
                {
                    //������΂�
                    {
                        DirectX::XMFLOAT3 impulse;
                        //������΂���
                        const float power = 10.0f;

                        //�G�̈ʒu
                        DirectX::XMVECTOR eVec = DirectX::XMLoadFloat3(&enemy->GetPosition());
                        //�e�̈ʒu
                        DirectX::XMVECTOR pVec = DirectX::XMLoadFloat3(&projectile->GetPosition());
                        //�e����G�ւ̕����x�N�g�����v�Z�i�G - �e�j
                        auto v = DirectX::XMVectorSubtract(eVec, pVec);
                        //�����x�N�g���𐳋K��
                        v = DirectX::XMVector3Normalize(v);

                        DirectX::XMFLOAT3 vec;
                        DirectX::XMStoreFloat3(&vec, v);

                        impulse.x = power * vec.x;
                        impulse.y = power * 0.5f;
                        impulse.z = power * vec.z;

                        enemy->AddImpulse(impulse);
                    }

                    //�q�b�g�G�t�F�N�g�Đ�
                    {
                        DirectX::XMFLOAT3 e = enemy->GetPosition();
                        e.y += enemy->GetHeight() * 0.5f;
                        hitEffect->Play(e);
                    }
                    //�e�۔j��
                    projectile->Destroy();
                }
            }
        }
    }
}
void Player::CollisionNodeVsEnemies(const char* nodeName, float nodeRadius)
{
    //�m�[�h�擾
    Model::Node* node = model->FindNode(nodeName);

    //�m�[�h�̈ʒu�擾
    DirectX::XMFLOAT3 nodePosition;
    nodePosition.x = node->worldTransform._41;
    nodePosition.y = node->worldTransform._42;
    nodePosition.z = node->worldTransform._43;

    //�w��m�[�h�ƑS�Ă̓G�𑍓�����ŏՓˏ���
    EnemyManager& enemyManager = EnemyManager::Instance();
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < enemyCount; i++)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);

        float dis = sqrtf(
            ((nodePosition.x - enemy->GetPosition().x) * (nodePosition.x - enemy->GetPosition().x)) +
            ((nodePosition.y - enemy->GetPosition().y) * (nodePosition.y - enemy->GetPosition().y)) +
            ((nodePosition.z - enemy->GetPosition().z) * (nodePosition.z - enemy->GetPosition().z))
        );
        if (dis < nodeRadius + enemy->GetRadius())
        {
            //�_���[�W��^����
            enemy->ApplyDamage(1, 0.5f);
            //�q�b�g�G�t�F�N�g�Đ�
            DirectX::XMFLOAT3 e = enemy->GetPosition();
            e.y += enemy->GetHeight() * 0.5f;
            hitEffect->Play(e);
        }
    }
}

DirectX::XMFLOAT3 Player::GetMoveVec() const
{
    //���͏��̎擾
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //�J���������ƃX�e�B�b�N�̓��͂ɂ���Đi�s�������v�Z����
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

    //�ړ��x�N�g����XY���ʂɐ����ȃx�N�g���ɂȂ�悤�ɂ���

    //�J�����E�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraRightX = cameraRight.x;
    float cameraRightZ = cameraRight.z;
    float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
    if (cameraRightLength > 0.0f)
    {
        //�P�ʃx�N�g����
        cameraRightX /=  cameraRightLength;
        cameraRightZ /=  cameraRightLength;
    }

    //�J�����O�����x�N�g����XZ�P�ʃx�N�g���ɕϊ�
    float cameraFrontX = cameraFront.x;
    float cameraFrontZ = cameraFront.z;
    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
    if (cameraFrontLength > 0.0f)
    {
        cameraFrontX /= cameraFrontLength;
        cameraFrontZ /= cameraFrontLength;
    }

    //�X�e�B�b�N�̐������͒l���J�����̉E�����ɔ��f���A
    //�X�e�B�b�N�̐������͒l���J�����̑O�����ɔ��f���A
    //�i�s�x�N�g�����v�Z����
    DirectX::XMFLOAT3 vec;
    vec.x = (cameraRightX*ax) + (cameraFrontX*ay);
    vec.z = (cameraRightZ*ax) + (cameraFrontZ*ay);
    //Y�������ɂ͈ړ����Ȃ�
    vec.y = 0.0f;

    return vec;
}


void Player::TransitionIdleState()
{
#ifdef Player_Animation
    state = State::Idle;
    //�ҋ@�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Idle, true);
#endif // Player_Animation
}
void Player::UpdateIdleState(float elapsedTime)
{
    //�ړ����͏���
    if (InputMove(elapsedTime))
    {
        TransitionMoveState();
    }

    //�W�����v����
    if(InputJump())
    {
        TransitionJumpState();
    }

    //�U������
    if (InputAttack())
    {
        TransitionAttackState();
    }

    //�e�ۓ��͏���
    InputProjectile();
}


bool Player::InputMove(float elapsedTime)
{
    //�i�s�x�N�g���擾
    DirectX::XMFLOAT3 moveVec = GetMoveVec();

    //�ړ�����
    Move(moveVec.x, moveVec.z, moveSpeed);

    //���񏈗�
    Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
    if (moveVec.x != 0 /*|| moveVec.y != 0 */||moveVec.z != 0)return true;
    return false;
}
void Player::TransitionMoveState()
{
    state = State::Move;
    //����A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Running, true);
}
void Player::UpdateMoveState(float elapsedTime)
{
    //�ړ����͏���
    if (!InputMove(elapsedTime))
    {
        TransitionIdleState();
    }

    //�W�����v����
    if (InputJump())
    {
        TransitionJumpState();
    }

    //�U������
    if (InputAttack())
    {
        TransitionAttackState();
    }

    //�e�ۓ��͏���
    InputProjectile();
}


void Player::OnLanding()
{
    jumpCount = 0;
    if (state != State::Damage && state != State::Death && velocity.y > 0.1f)
    {
        TransitionLandState();
    }
}
void Player::TransitionLandState()
{
    state = State::Land;
    //���n�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Landing, false);
}
void Player::UpdateLandState(float elapsedTime)
{
    ////�ړ����͏���
    //InputMove(elapsedTime);
    ////�e�ۓ��͏���
    //InputProjectile();

    //���n���[�V�������I�������ҋ@���[�V�����Ɉړ�
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}


bool Player::InputAttack()
{
    bool result = false;
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        result = true;
    }
    return result;
}
void Player::TransitionAttackState()
{
    state = State::Attack;
    //����A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Attack, false);
}
void Player::UpdateAttackState(float elapsedTime)
{
    //�C�ӂ̃A�j���[�V������Ԃł̂ݏՓˏ���
    float animationTime = 0.138;
    attackCollisionFlag = animationTime ? true : false;
    if(attackCollisionFlag)    CollisionNodeVsEnemies("mixamorig:LeftHand", leftHandRadius);
    //�U�����[�V�������I�������ҋ@���[�V�����Ɉړ�
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}


void Player::OnDamaged()
{
    TransitionDamageState();
}
void Player::TransitionDamageState()
{
    state = State::Damage;
    model->PlayAnimation(Anim_GetHit1, false);
}
void Player::UpdateDamageState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}


void Player::OnDead()
{
    if (health <= 0)
    {
        TransitionDeathState();
    }
}
void Player::TransitionDeathState()
{
    state = State::Death;
    model->PlayAnimation(Anim_Death, false);
}
void Player::UpdateDeathState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        GamePad& gamePad = Input::Instance().GetGamePad();
        if (gamePad.GetButtonDown() & GamePad::BTN_A)
        {
            TransitionReviveState();
        }
    }
}


void Player::TransitionReviveState()
{
    state = State::Revive;

    health = maxHealth;

    model->PlayAnimation(Anim_Revive, false);
}
void Player::UpdateReviveState(float elapsedTime)
{
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
    }
}


bool Player::InputJump()
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        //Jump�񐔐���
        if (jumpCount == jumpLimit)
        {
            return false;
        }
        jumpCount++;
        //�W�����v
        Jump(jumpSpeed);
        return true;
    }
    return false;
}
void Player::TransitionJumpState()
{
    state = State::Jump;
    //�W�����v�A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Jump, false);

}
void Player::UpdateJumpState(float elapsedTime)
{
    InputMove(elapsedTime);
    //�W�����v����
    if (InputJump())
    {
        TransitionJumpState();
    }

    //�e�ۓ��͏���
    InputProjectile();

    //�n�ʂɕt�����璅�n���[�V�����Ɉڍs
    if (isGround)
    {
        TransitionLandState();
    }
}


void Player::InputProjectile()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //���i�e�۔���
    if (gamePad.GetButtonDown() & GamePad::BTN_X)
    {
        //�O����
        DirectX::XMFLOAT3 dir;
        dir.x = transform._31 * 100.0f;
        dir.y = 0.0f;
        dir.z = transform._33 * 100.0f;
        //���ˈʒu�i�v���C���[�̍�������j
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y + height * 0.5f;
        pos.z = position.z;
        //����
        ProjectileStraight* projectile = new ProjectileStraight(&projectileManager);
        projectile->Launch(dir, pos);
        //projectileManager.Register(projectile);
    }
    //�ǔ��e�۔���
    if (gamePad.GetButtonDown() & GamePad::BTN_Y)
    {
        //�O����
        DirectX::XMFLOAT3 dir;
        dir.x = transform._31 * 100.0f;
        dir.y = 0.0f;
        dir.z = transform._33 * 100.0f;
        //���ˈʒu�i�v���C���[�̍�������j
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y + height * 0.5f;
        pos.z = position.z;

        //�^�[�Q�b�g�i�f�t�H���g�ł̓v���C���[�̑O��
        DirectX::XMFLOAT3 target;
        target.x = pos.x + dir.x * 1000.0f;
        target.y = pos.y + dir.y * 1000.0f;
        target.z = pos.z + dir.z * 1000.0f;

        //��ԋ߂��̓G���^�[�Q�b�g�ɂ���
        float dist = FLT_MAX;
        EnemyManager& enemyManager = EnemyManager::Instance();
        int enemyCount = enemyManager.GetEnemyCount();
        for (int i = 0; i < enemyCount; i++)
        {
            //�G�Ƃ̋�������
            Enemy* enemy = EnemyManager::Instance().GetEnemy(i);
            DirectX::XMVECTOR P = DirectX::XMLoadFloat3(&position);
            DirectX::XMVECTOR E = DirectX::XMLoadFloat3(&enemy->GetPosition());
            DirectX::XMVECTOR V = DirectX::XMVectorSubtract(E, P);
            DirectX::XMVECTOR D = DirectX::XMVector3LengthSq(V);
            float d;
            DirectX::XMStoreFloat(&d, D);
            if (d < dist)
            {
                dist = d;
                target = enemy->GetPosition();
                target.y += enemy->GetHeight() * 0.5f;

            }
        }

        //����
        ProjectileHoming* projectile = new ProjectileHoming(&projectileManager);
        projectile->Launch(dir, pos, target);
    }
}
