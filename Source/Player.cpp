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

    //ヒットエフェクト読み込み
    //hitEffect = new Effect("Data/Effect/GP3_sample.efk"); 
    hitEffect = new Effect("Data/Effect/testEFK.efkefc");
    //auraEffect= new Effect("Data/Effect/aura.efkefc");
    //待機ステートへの遷移
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

    //速力処理更新
    UpdateVelocity(elapsedTime);

    UpdateInvincibleTime(elapsedTime);

    //弾丸更新処理
    projectileManager.Update(elapsedTime);

    //プレイヤーと敵との衝突処理
    CollisionPlayerVsEnemies();

    //弾丸と敵の衝突処理
    CollisionProjectilesVsEnemies();

    //オブジェクト行列を更新
    UpdateTransform();

    //auraEffect->Play(position);

    //モデルアニメーション更新処理
#ifdef Player_Animation
    model->UpdateAnimation(elapsedTime);
#endif // Player_Animation

    //モデル行列更新
    model->UpdateTransform(transform);
}

void Player::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    shader->Draw(dc, model);

    //弾丸描画処理
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
//デバッグプリミティブ描画
void Player::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

    ////衝突判定用のデバッグ球を描画
    //debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

    //弾丸デバッグプリミティブ描画
    projectileManager.DrawDebugPrimitive();

    //攻撃衝突用の左手ノードのデバッグ球を描画
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

    //すべての敵と総当たりで衝突判定
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < enemyCount; i++)
    {
        Enemy* enemy = enemyManager.GetEnemy(i);

        //衝突処理
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

    //すべての弾丸とすべての敵をそう当たりで衝突処理
    int projectileCount = projectileManager.GetProjectileCount();
    int enemyCount = enemyManager.GetEnemyCount();
    for (int i = 0; i < projectileCount; ++i)
    {
        Projectile* projectile = projectileManager.GetProjectile(i);

        for (int j = 0; j < enemyCount; ++j)
        {
            Enemy* enemy = enemyManager.GetEnemy(j);

            //衝突処理
            DirectX::XMFLOAT3 outPosition;
            if (Collision::IntersectSphereVsCylinder(
                projectile->GetPosition(),
                projectile->GetRadius(),
                enemy->GetPosition(),
                enemy->GetRadius(),
                enemy->GetHeight(),
                outPosition))
            {
                //ダメージを与える
                if (enemy->ApplyDamage(1, 0.5f))
                {
                    //吹き飛ばす
                    {
                        DirectX::XMFLOAT3 impulse;
                        //吹き飛ばす力
                        const float power = 10.0f;

                        //敵の位置
                        DirectX::XMVECTOR eVec = DirectX::XMLoadFloat3(&enemy->GetPosition());
                        //弾の位置
                        DirectX::XMVECTOR pVec = DirectX::XMLoadFloat3(&projectile->GetPosition());
                        //弾から敵への方向ベクトルを計算（敵 - 弾）
                        auto v = DirectX::XMVectorSubtract(eVec, pVec);
                        //方向ベクトルを正規化
                        v = DirectX::XMVector3Normalize(v);

                        DirectX::XMFLOAT3 vec;
                        DirectX::XMStoreFloat3(&vec, v);

                        impulse.x = power * vec.x;
                        impulse.y = power * 0.5f;
                        impulse.z = power * vec.z;

                        enemy->AddImpulse(impulse);
                    }

                    //ヒットエフェクト再生
                    {
                        DirectX::XMFLOAT3 e = enemy->GetPosition();
                        e.y += enemy->GetHeight() * 0.5f;
                        hitEffect->Play(e);
                    }
                    //弾丸破棄
                    projectile->Destroy();
                }
            }
        }
    }
}
void Player::CollisionNodeVsEnemies(const char* nodeName, float nodeRadius)
{
    //ノード取得
    Model::Node* node = model->FindNode(nodeName);

    //ノードの位置取得
    DirectX::XMFLOAT3 nodePosition;
    nodePosition.x = node->worldTransform._41;
    nodePosition.y = node->worldTransform._42;
    nodePosition.z = node->worldTransform._43;

    //指定ノードと全ての敵を総当たりで衝突処理
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
            //ダメージを与える
            enemy->ApplyDamage(1, 0.5f);
            //ヒットエフェクト再生
            DirectX::XMFLOAT3 e = enemy->GetPosition();
            e.y += enemy->GetHeight() * 0.5f;
            hitEffect->Play(e);
        }
    }
}

DirectX::XMFLOAT3 Player::GetMoveVec() const
{
    //入力情報の取得
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    float ay = gamePad.GetAxisLY();

    //カメラ方向とスティックの入力によって進行方向を計算する
    Camera& camera = Camera::Instance();
    const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
    const DirectX::XMFLOAT3& cameraFront = camera.GetFront();

    //移動ベクトルはXY平面に水平なベクトルになるようにする

    //カメラ右方向ベクトルをXZ単位ベクトルに変換
    float cameraRightX = cameraRight.x;
    float cameraRightZ = cameraRight.z;
    float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
    if (cameraRightLength > 0.0f)
    {
        //単位ベクトル化
        cameraRightX /=  cameraRightLength;
        cameraRightZ /=  cameraRightLength;
    }

    //カメラ前方向ベクトルをXZ単位ベクトルに変換
    float cameraFrontX = cameraFront.x;
    float cameraFrontZ = cameraFront.z;
    float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
    if (cameraFrontLength > 0.0f)
    {
        cameraFrontX /= cameraFrontLength;
        cameraFrontZ /= cameraFrontLength;
    }

    //スティックの水平入力値をカメラの右方向に反映し、
    //スティックの垂直入力値をカメラの前方向に反映し、
    //進行ベクトルを計算する
    DirectX::XMFLOAT3 vec;
    vec.x = (cameraRightX*ax) + (cameraFrontX*ay);
    vec.z = (cameraRightZ*ax) + (cameraFrontZ*ay);
    //Y軸方向には移動しない
    vec.y = 0.0f;

    return vec;
}


void Player::TransitionIdleState()
{
#ifdef Player_Animation
    state = State::Idle;
    //待機アニメーション再生
    model->PlayAnimation(Anim_Idle, true);
#endif // Player_Animation
}
void Player::UpdateIdleState(float elapsedTime)
{
    //移動入力処理
    if (InputMove(elapsedTime))
    {
        TransitionMoveState();
    }

    //ジャンプ処理
    if(InputJump())
    {
        TransitionJumpState();
    }

    //攻撃処理
    if (InputAttack())
    {
        TransitionAttackState();
    }

    //弾丸入力処理
    InputProjectile();
}


bool Player::InputMove(float elapsedTime)
{
    //進行ベクトル取得
    DirectX::XMFLOAT3 moveVec = GetMoveVec();

    //移動処理
    Move(moveVec.x, moveVec.z, moveSpeed);

    //旋回処理
    Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed);
    if (moveVec.x != 0 /*|| moveVec.y != 0 */||moveVec.z != 0)return true;
    return false;
}
void Player::TransitionMoveState()
{
    state = State::Move;
    //走りアニメーション再生
    model->PlayAnimation(Anim_Running, true);
}
void Player::UpdateMoveState(float elapsedTime)
{
    //移動入力処理
    if (!InputMove(elapsedTime))
    {
        TransitionIdleState();
    }

    //ジャンプ処理
    if (InputJump())
    {
        TransitionJumpState();
    }

    //攻撃処理
    if (InputAttack())
    {
        TransitionAttackState();
    }

    //弾丸入力処理
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
    //着地アニメーション再生
    model->PlayAnimation(Anim_Landing, false);
}
void Player::UpdateLandState(float elapsedTime)
{
    ////移動入力処理
    //InputMove(elapsedTime);
    ////弾丸入力処理
    //InputProjectile();

    //着地モーションが終わったら待機モーションに移動
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
    //走りアニメーション再生
    model->PlayAnimation(Anim_Attack, false);
}
void Player::UpdateAttackState(float elapsedTime)
{
    //任意のアニメーション区間でのみ衝突処理
    float animationTime = 0.138;
    attackCollisionFlag = animationTime ? true : false;
    if(attackCollisionFlag)    CollisionNodeVsEnemies("mixamorig:LeftHand", leftHandRadius);
    //攻撃モーションが終わったら待機モーションに移動
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
        //Jump回数制限
        if (jumpCount == jumpLimit)
        {
            return false;
        }
        jumpCount++;
        //ジャンプ
        Jump(jumpSpeed);
        return true;
    }
    return false;
}
void Player::TransitionJumpState()
{
    state = State::Jump;
    //ジャンプアニメーション再生
    model->PlayAnimation(Anim_Jump, false);

}
void Player::UpdateJumpState(float elapsedTime)
{
    InputMove(elapsedTime);
    //ジャンプ処理
    if (InputJump())
    {
        TransitionJumpState();
    }

    //弾丸入力処理
    InputProjectile();

    //地面に付いたら着地モーションに移行
    if (isGround)
    {
        TransitionLandState();
    }
}


void Player::InputProjectile()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    //直進弾丸発射
    if (gamePad.GetButtonDown() & GamePad::BTN_X)
    {
        //前方向
        DirectX::XMFLOAT3 dir;
        dir.x = transform._31 * 100.0f;
        dir.y = 0.0f;
        dir.z = transform._33 * 100.0f;
        //発射位置（プレイヤーの腰当たり）
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y + height * 0.5f;
        pos.z = position.z;
        //発射
        ProjectileStraight* projectile = new ProjectileStraight(&projectileManager);
        projectile->Launch(dir, pos);
        //projectileManager.Register(projectile);
    }
    //追尾弾丸発射
    if (gamePad.GetButtonDown() & GamePad::BTN_Y)
    {
        //前方向
        DirectX::XMFLOAT3 dir;
        dir.x = transform._31 * 100.0f;
        dir.y = 0.0f;
        dir.z = transform._33 * 100.0f;
        //発射位置（プレイヤーの腰当たり）
        DirectX::XMFLOAT3 pos;
        pos.x = position.x;
        pos.y = position.y + height * 0.5f;
        pos.z = position.z;

        //ターゲット（デフォルトではプレイヤーの前方
        DirectX::XMFLOAT3 target;
        target.x = pos.x + dir.x * 1000.0f;
        target.y = pos.y + dir.y * 1000.0f;
        target.z = pos.z + dir.z * 1000.0f;

        //一番近くの敵をターゲットにする
        float dist = FLT_MAX;
        EnemyManager& enemyManager = EnemyManager::Instance();
        int enemyCount = enemyManager.GetEnemyCount();
        for (int i = 0; i < enemyCount; i++)
        {
            //敵との距離判定
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

        //発射
        ProjectileHoming* projectile = new ProjectileHoming(&projectileManager);
        projectile->Launch(dir, pos, target);
    }
}
