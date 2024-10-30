#include "Collision.h"
#include "Mathf.h"
#include <DirectXCollision.h>

//�~���Ɖ~���̌�������
bool Collision::IntersectCylinderVsCylinder(
    Cylinder& A,
    Cylinder& B)
{
    //A�̑�����B�̓�����Ȃ瓖�����ĂȂ�
    if (A.sphere.position.y > B.sphere.position.y + B.height)
    {
        return false;
    }
    //A�̓���B�̑�����艺�Ȃ瓖�����ĂȂ�
    if (A.sphere.position.y + A.height < B.sphere.position.y)
    {
        return false;
    }

    return IntersectSphereVsSphere(A.sphere, B.sphere);
    //{
    //DirectX::XMFLOAT2 posA(positionA.x, positionA.z);
    //DirectX::XMFLOAT2 posB(positionB.x, positionB.z);
    //DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat2(&posA);
    //DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat2(&posB);
    //
    //DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
    //// Vec �̒������v�Z(XMVector2LengthSq �𗘗p���Ă��ǂ�)
    //DirectX::XMVECTOR LengthSq = DirectX::XMVector2LengthSq(Vec);
    //float lengthSq;
    //DirectX::XMStoreFloat(&lengthSq, LengthSq);
    //
    //// radiusA �� radiusB �̒���
    //float range = radiusA + radiusB;
    //
    //// radisuA + radisuB ���傫��������
    //if (lengthSq > range)
    //{
    //    // �������ĂȂ�
    //    return false;
    //}
    ////���K��
    //Vec = DirectX::XMVector3Normalize(Vec);
    //// �߂荞�ݗʂ����߂�
    //float diff = range - lengthSq;
    //Vec = DirectX::XMVectorScale(Vec, diff);
    //
    //// �Q�̋��̏d�����牟���o���䗦�����߂�
    //float rateA = weightA / (weightA + weightB);
    //rateA = 1;
    //
    //// ��B�̕␳��̍��W
    //DirectX::XMVECTOR VelocityB = DirectX::XMVectorScale(Vec, rateA);
    //PositionB = DirectX::XMVectorAdd(PositionB, VelocityB);
    //
    //// ��A�̕␳��̍��W
    //DirectX::XMVECTOR VelocityA = DirectX::XMVectorScale(Vec, 1.0f - rateA);
    //PositionA = DirectX::XMVectorSubtract(PositionA, VelocityA);
    //
    //DirectX::XMFLOAT2 position;
    //DirectX::XMStoreFloat2(&position, PositionA);
    //A.sphere.position.x = position.x;
    //A.sphere.position.z = position.y;
    //DirectX::XMStoreFloat2(&position, PositionB);
    //B.sphere.position.x = position.x;
    //B.sphere.position.z = position.y;
    //
    //return true;
    //}
}



bool Collision::IntersectSphereVsCylinder(
    Sphere& sphere,
    Cylinder& cylinder
)
{
    // ���̓�(.y + radius )���~���̑���(.y)��艺�Ȃ� false
    if (sphere.position.y + sphere.radius < cylinder.sphere.position.y)
        return false;

    // ���̑���( .y - radius)���~���̓�(.y + Height)����Ȃ� false
    if (sphere.position.y - sphere.radius > cylinder.sphere.position.y + cylinder.height)
        return false;

    //return IntersectSphereVsSphere(sphere, cylinder.sphere);

    {
        // XZ ���ʂł͈̔̓`�F�b�N
        DirectX::XMFLOAT2 pos(sphere.position.x, sphere.position.z);
        DirectX::XMFLOAT2 pos2(cylinder.sphere.position.x, cylinder.sphere.position.z);
        if (CircleVsCircle(pos, sphere.radius, pos2, cylinder.sphere.radius))
        {
            IntersectSphereVsSphere(sphere, cylinder.sphere);
            return true;
        }
        return false;
    }
}

bool Collision::IntersectSphereVsSphere(Sphere& A, Sphere& B)
{
    DirectX::XMFLOAT3 positionA(A.position.x, A.position.y, A.position.z);
    DirectX::XMFLOAT3 positionB(B.position.x, B.position.y, B.position.z);
    float radiusA = A.radius;
    float radiusB = B.radius;
    float weightA = A.weight;
    float weightB = B.weight;

    float length = 0;
    length =Mathf::Distance(positionA, positionB);

    DirectX::XMFLOAT2 posA(positionA.x, positionA.z);
    DirectX::XMFLOAT2 posB(positionB.x, positionB.z);
    
    DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat2(&posA);
    DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat2(&posB);


    DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
    // Vec �̒������v�Z(XMVector2LengthSq �𗘗p���Ă��ǂ�)
    DirectX::XMVECTOR Length = DirectX::XMVector2LengthSq(Vec);

    // radiusA �� radiusB �̒���
    float range = radiusA + radiusB;

    // radisuA + radisuB ���傫��������
    if (length > range)
    {
        // �������ĂȂ�
        return false;
    }

    // �P�ʃx�N�g����
    Vec = DirectX::XMVector3Normalize(Vec);
    // �߂荞�ݗʂ����߂�
    float diff = (radiusA + radiusB) - length;
    Vec = DirectX::XMVectorScale(Vec, diff);
    // �Q�̋��̏d�����牟���o���䗦�����߂�
    float rateA = weightA / (weightA + weightB);
    float rateB = 1.0f - rateA;
    // ��B�̕␳��̍��W
    DirectX::XMVECTOR VelocityB = DirectX::XMVectorScale(Vec, rateA);
    PositionB = DirectX::XMVectorAdd(PositionB, VelocityB);
    // ��A�̕␳��̍��W
    DirectX::XMVECTOR VelocityA = DirectX::XMVectorScale(Vec, rateB);
    PositionA = DirectX::XMVectorSubtract(PositionA, VelocityA);

    DirectX::XMFLOAT2 position;
    DirectX::XMStoreFloat2(&position, PositionA);
    A.position.x = position.x;
    A.position.z = position.y;
    DirectX::XMStoreFloat2(&position, PositionB);
    B.position.x = position.x;
    B.position.z = position.y;
    return true;
}

bool Collision::RayCast(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, const DirectX::XMFLOAT4X4& worldTransform, const Model* model, HitResult& result)
{
    bool hit = false;

    // �n�_�ƏI�_���烌�C�̃x�N�g���ƒ��������߂�
    DirectX::XMVECTOR WorldRayStart = DirectX::XMLoadFloat3(&start);
    DirectX::XMVECTOR WorldRayEnd = DirectX::XMLoadFloat3(&end);
    DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldRayEnd, WorldRayStart);
    DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);

    float nearestDist = DirectX::XMVectorGetX(WorldRayLength);
    if (nearestDist <= 0.0f) return false;

    DirectX::XMMATRIX ParentWorldTransform = DirectX::XMLoadFloat4x4(&worldTransform);

    // ���f�����̑S�Ẵ��b�V���ƌ���������s��
    const ModelResource* resource = model->GetResource();
    for (const ModelResource::Mesh& mesh : resource->GetMeshes())
    {
        // ���b�V���̃��[���h�s������߂�
        const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);
        DirectX::XMMATRIX GlobalTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
        DirectX::XMMATRIX WorldTransform = DirectX::XMMatrixMultiply(GlobalTransform, ParentWorldTransform);

        // ���C�����b�V���̃��[�J����Ԃɕϊ�����
        DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);
        DirectX::XMVECTOR LocalRayStart = DirectX::XMVector3Transform(WorldRayStart, InverseWorldTransform);
        DirectX::XMVECTOR LocalRayEnd = DirectX::XMVector3Transform(WorldRayEnd, InverseWorldTransform);
        DirectX::XMVECTOR LocalRayVec = DirectX::XMVectorSubtract(LocalRayEnd, LocalRayStart);
        DirectX::XMVECTOR LocalRayDirection = DirectX::XMVector3Normalize(LocalRayVec);
        float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(LocalRayVec));

        // ���b�V�����̑S�Ă̎O�p�`�ƌ���������s��
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            // �O�p�`�̒��_���W���擾
            const ModelResource::Vertex& a = mesh.vertices.at(mesh.indices.at(i + 0));
            const ModelResource::Vertex& b = mesh.vertices.at(mesh.indices.at(i + 1));
            const ModelResource::Vertex& c = mesh.vertices.at(mesh.indices.at(i + 2));

            DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
            DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
            DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

            // �O�p�`�̌�������
            if (DirectX::TriangleTests::Intersects(LocalRayStart, LocalRayDirection, A, B, C, distance))
            {
                // ���b�V���̃��[�J����Ԃł̌�_�����߂�
                DirectX::XMVECTOR LocalHitVec = DirectX::XMVectorScale(LocalRayDirection, distance);
                DirectX::XMVECTOR LocalHitPosition = DirectX::XMVectorAdd(LocalRayStart, LocalHitVec);

                // ���b�V���̃��[�J����Ԃł̌�_�����[���h��Ԃɕϊ�����
                DirectX::XMVECTOR WorldHitPosition = DirectX::XMVector3Transform(LocalHitPosition, WorldTransform);

                // ���[���h��Ԃł̃��C�̎n�_�����_�܂ł̋��������߂�
                DirectX::XMVECTOR WorldHitVec = DirectX::XMVectorSubtract(WorldHitPosition, WorldRayStart);
                DirectX::XMVECTOR WorldHitDist = DirectX::XMVector3Length(WorldHitVec);
                float worldHitDist = DirectX::XMVectorGetX(WorldHitDist);

                // ��_�܂ł̋��������܂łɌv�Z������_���߂��ꍇ�͌��������Ɣ��肷��
                if (worldHitDist <= nearestDist)
                {
                    // ���b�V���̃��[�J����Ԃł̎O�p�`�̖@���x�N�g�����Z�o
                    DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
                    DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
                    DirectX::XMVECTOR LocalHitNormal = DirectX::XMVector3Cross(AB, BC);

                    // ���b�V���̃��[�J����Ԃł̖@���x�N�g�������[���h��Ԃɕϊ�����
                    DirectX::XMVECTOR WorldHitNormal = DirectX::XMVector3TransformNormal(LocalHitNormal, WorldTransform);

                    // �O�p�`�̗��\����i���ς̌��ʂ��}�C�i�X�Ȃ�Ε\�����j
                    DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(LocalRayDirection, LocalHitNormal);
                    float dot = DirectX::XMVectorGetX(Dot);
                    if (dot < 0)
                    {
                        // ���������̂Ńq�b�g�����i�[
                        DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldHitNormal));
                        DirectX::XMStoreFloat3(&result.position, WorldHitPosition);
                        result.distance = worldHitDist;

                        // ��_�܂ł̋������X�V����
                        nearestDist = worldHitDist;
                        hit = true;
                    }
                }
            }
        }
    }
    return hit;
}

bool Collision::HPbarPoint(DirectX::XMFLOAT3 player_position, DirectX::XMFLOAT3 enemy_position)
{
    bool HPpoint;
    if (player_position.x > enemy_position.x - 10.0f || player_position.x < enemy_position.x + 10.0f)//X��
    {
        if (player_position.y > enemy_position.y - 10.0f || player_position.y < enemy_position.y + 10.0f)//Y��
        {
            if (player_position.z > enemy_position.z - 10.0f || player_position.z < enemy_position.z + 10.0f)//Z��
            {
                HPpoint = true;
            }
        }
    }
    HPpoint = false;
    return HPpoint;
}

bool Collision::RectInPoint(DirectX::XMFLOAT3 bottom_left_front, DirectX::XMFLOAT3 top_right_back, DirectX::XMFLOAT3 move_pos)
{
    //X���AY���AZ�����ꂼ��͈͓̔��ɓ����Ă��邩�̔���
    //bottom_left_front < top_right_back����Ȃ��ƒʂ�Ȃ�
    if (bottom_left_front.x<move_pos.x && top_right_back.x>move_pos.x)
    {
        if (bottom_left_front.y<move_pos.y && top_right_back.y>move_pos.y)
        {
            if (bottom_left_front.z<move_pos.z && top_right_back.z>move_pos.z)
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision::RectInPoint2D(DirectX::XMFLOAT3 bottom_left_front, DirectX::XMFLOAT3 top_right_back, DirectX::XMFLOAT3 move_pos, Axis2D axis)
{
    //2�����ꂼ��͈͓̔��ɓ����Ă��邩�̔���
    //bottom_left_front < top_right_back����Ȃ��ƒʂ�Ȃ�
    if (bottom_left_front.x < top_right_back.x)
    {
        if (bottom_left_front.y < top_right_back.y)
        {
            if (bottom_left_front.z < top_right_back.z)
            {
                _ASSERT_EXPR(true, "2�����ꂼ��͈͓̔��ɓ����Ă��邩�̔���Ɏ��s���܂���");
            }
        }
    }
    DirectX::XMFLOAT2 bp = {};
    DirectX::XMFLOAT2 tp = {};
    DirectX::XMFLOAT2 mp = {};
    switch (axis)
    {
    case Axis2D::X_Y:
        bp = { bottom_left_front.x,bottom_left_front.y };
        tp = { top_right_back.x,top_right_back.y };
        mp = { move_pos.x,move_pos.y };
        break;
    case Axis2D::Y_Z:
        bp = { bottom_left_front.y,bottom_left_front.z };
        tp = { top_right_back.y,top_right_back.z };
        mp = { move_pos.y,move_pos.z };
        break;
    case Axis2D::Z_X:
        bp = { bottom_left_front.z,bottom_left_front.x };
        tp = { top_right_back.z,top_right_back.x };
        mp = { move_pos.z,move_pos.x };
        break;
    default:
        bp = {};
        tp = {};
        mp = {};
        break;
    }
    if (bp.x<mp.x && tp.x>mp.x)
    {
        if (bp.y<mp.y && tp.y>mp.y)
        {
            return true;
        }
    }
    return false;
}

bool Collision::SphereInPoint(DirectX::XMFLOAT3 center, float radius, DirectX::XMFLOAT3 move_pos)
{
    if (Mathf::Distance(center, move_pos) < radius)return true;
    return false;
}

bool Collision::PointInsideCircle(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 center, float radius)
{
    float distance = sqrt(pow(point.x - center.x, 2) + pow(point.z - center.z, 2));

    return distance <= radius;
}

void Collision::UpdateCylinder(DirectX::XMFLOAT3 p, float r, float w, float h, Cylinder& c)
{
    c.sphere.position = p;
    c.sphere.radius = r;
    c.sphere.weight = w;
    c.height = h;
}

void Collision::UpdateSphere(DirectX::XMFLOAT3 p, float r, float w, Sphere& s)
{
    s.position = p;
    s.radius = r;
    s.weight = w;
}

bool Collision::CircleVsCircle(DirectX::XMFLOAT2 Apos, float Ar, DirectX::XMFLOAT2 Bpos, float Br)
{
    float distance = pow(Bpos.x - Apos.x, 2) + pow(Bpos.y - Apos.y, 2);
    float radius = pow(Ar + Br, 2);
    return distance <= radius;
}
