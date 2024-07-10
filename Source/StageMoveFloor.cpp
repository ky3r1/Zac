#include "StageMoveFloor.h"

//�R���X�g���N�^
StageMoveFloor::StageMoveFloor()
{
    scale.x = scale.z = 3.0f;
    scale.y = 0.5f;

    //�X�e�[�W���f����ǂݍ���
    model = new Model("Data/Model/Cube/Cube.mdl");
}

//�f�X�g���N�^
StageMoveFloor::~StageMoveFloor()
{
    //�X�e�[�W���f����ǂݍ���
    delete model;
}

//�X�V����
void StageMoveFloor::Update(float elapsedTime)
{
    //�O��̏���ۑ�
    oldTransform = transform;
    oldAngle = angle;

    //�X�^�[�g����S�[���܂ł̋������Z�o
    DirectX::XMVECTOR Start = DirectX::XMLoadFloat3(&start);
    DirectX::XMVECTOR Goal = DirectX::XMLoadFloat3(&goal);
    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Goal, Start);
    DirectX::XMVECTOR Length = DirectX::XMVector3Length(Vec);
    float length;
    DirectX::XMStoreFloat(&length, Length);

    //�X�^�[�g����S�[���܂ł̊Ԃ���b�ԂŐi�ފ���(0.0�`1.0)���Z�o����
    float speed = moveSpeed * elapsedTime;
    float speedRate = speed / length;
    moveRate += speedRate;

    //�S�[���ɓ��B�A�܂��̓X�^�[�g�ɖ߂����ꍇ�A�ړ������𔽓]������
    if (moveRate <= 0.0f || moveRate >= 1.0f)
    {
        moveSpeed = -moveSpeed;
    }

    //���`�⊮�ňʒu���Z�o����
    DirectX::XMVECTOR Position = DirectX::XMVectorLerp(Start, Goal, moveRate);
    DirectX::XMStoreFloat3(&position, Position);

    //��]
    angle.x += torque.x * elapsedTime;
    angle.y += torque.y * elapsedTime;
    angle.z += torque.z * elapsedTime;

    //�s��X�V
    UpdateTransform();
#ifdef Unit16_OnCharacter
    //���C�L���X�g�p�Ƀ��f����ԍs��ɂ��邽�߂̒P�ʍs���n��
    const DirectX::XMFLOAT4X4 transformIdentity =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    model->UpdateTransform(transformIdentity);
#else
    //���f���s��X�V
    model->UpdateTransform(transform);
#endif
}

//�`�揈��
void StageMoveFloor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
    //�\���p�̂��߃��[���h�s��ɍX�V����
    model->UpdateTransform(transform);
    shader->Draw(dc, model);
}

//���C�L���X�g
bool StageMoveFloor::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, HitResult& hit)
{
#ifdef Unit16_OnCharacter
    //�O��̃��[���h�s��̋t�s������߂�
    DirectX::XMMATRIX OldTransform;
    OldTransform = DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&oldTransform));

    //�O��̃��[�J����Ԃł̃��C�ɕϊ�
    
    //���[���h���
    DirectX::XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);//�n�_
    DirectX::XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);//�I�_

    //���C�̎n�_
    DirectX::XMVECTOR LocalStart = DirectX::XMVector3TransformCoord(WorldStart, OldTransform);
    //���C�̏I�_
    DirectX::XMVECTOR LocalEnd = DirectX::XMVector3TransformCoord(WorldEnd, OldTransform);

    //���[�J����Ԃł̃��C�Ƃ̌�_�����߂�
    DirectX::XMFLOAT3 localStart, localEnd;
    DirectX::XMStoreFloat3(&localStart, LocalStart);
    DirectX::XMStoreFloat3(&localEnd, LocalEnd);

    HitResult localHit;
    if (Collision::IntersectRayVsModel(localStart, localEnd, model, localHit))
    {
        //�O��̃��[�J����Ԃ��獡��̃��[���h��Ԃւ̕ϊ�
        //�O�񂩂獡��ɂ����ĕύX���ꂽ���e������Ă���I�u�W�F�N�g�ɔ��f�����B
        DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);

        DirectX::XMVECTOR LocalCharacterPosition = DirectX::XMLoadFloat3(&localHit.position);

        DirectX::XMVECTOR WorldCharacterPosition = DirectX::XMVector3TransformCoord(LocalCharacterPosition, Transform);

        DirectX::XMStoreFloat3(&hit.position, WorldCharacterPosition);

        //��]�������Z�o
        hit.rotation.x = angle.x-oldAngle.x;
        hit.rotation.y = angle.y-oldAngle.y;
        hit.rotation.z = angle.z-oldAngle.z;

        DirectX::XMVECTOR V = DirectX::XMVectorSubtract(WorldCharacterPosition, WorldStart);
        DirectX::XMVECTOR WorldLength = DirectX::XMVector3Length(V);
        DirectX::XMStoreFloat(&hit.distance, WorldLength);

        return true;
    }
    return false;
#else
    return Collision::IntersectRayVsModel(start, end, model, hit);
#endif
}

//�s��X�V����
void StageMoveFloor::UpdateTransform()
{
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    DirectX::XMMATRIX W = S * R * T;
    DirectX::XMStoreFloat4x4(&transform, W);
}
