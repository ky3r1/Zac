#include "Collision.h"
#include "Mathf.h"
#include <DirectXCollision.h>

//円柱と円柱の交差判定
bool Collision::IntersectCylinderVsCylinder(
    Cylinder& A,
    Cylinder& B)
{
    //Aの足元がBの頭より上なら当たってない
    if (A.sphere.position.y > B.sphere.position.y + B.height)
    {
        return false;
    }
    //Aの頭がBの足元より下なら当たってない
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
    //// Vec の長さを計算(XMVector2LengthSq を利用しても良い)
    //DirectX::XMVECTOR LengthSq = DirectX::XMVector2LengthSq(Vec);
    //float lengthSq;
    //DirectX::XMStoreFloat(&lengthSq, LengthSq);
    //
    //// radiusA と radiusB の長さ
    //float range = radiusA + radiusB;
    //
    //// radisuA + radisuB より大きかったら
    //if (lengthSq > range)
    //{
    //    // 当たってない
    //    return false;
    //}
    ////正規化
    //Vec = DirectX::XMVector3Normalize(Vec);
    //// めり込み量を求める
    //float diff = range - lengthSq;
    //Vec = DirectX::XMVectorScale(Vec, diff);
    //
    //// ２つの球の重さから押し出し比率を求める
    //float rateA = weightA / (weightA + weightB);
    //rateA = 1;
    //
    //// 球Bの補正後の座標
    //DirectX::XMVECTOR VelocityB = DirectX::XMVectorScale(Vec, rateA);
    //PositionB = DirectX::XMVectorAdd(PositionB, VelocityB);
    //
    //// 球Aの補正後の座標
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
    // 球の頭(.y + radius )が円柱の足元(.y)より下なら false
    if (sphere.position.y + sphere.radius < cylinder.sphere.position.y)
        return false;

    // 球の足元( .y - radius)が円柱の頭(.y + Height)より上なら false
    if (sphere.position.y - sphere.radius > cylinder.sphere.position.y + cylinder.height)
        return false;

    //return IntersectSphereVsSphere(sphere, cylinder.sphere);

    {
        // XZ 平面での範囲チェック
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
    // Vec の長さを計算(XMVector2LengthSq を利用しても良い)
    DirectX::XMVECTOR Length = DirectX::XMVector2LengthSq(Vec);

    // radiusA と radiusB の長さ
    float range = radiusA + radiusB;

    // radisuA + radisuB より大きかったら
    if (length > range)
    {
        // 当たってない
        return false;
    }

    // 単位ベクトル化
    Vec = DirectX::XMVector3Normalize(Vec);
    // めり込み量を求める
    float diff = (radiusA + radiusB) - length;
    Vec = DirectX::XMVectorScale(Vec, diff);
    // ２つの球の重さから押し出し比率を求める
    float rateA = weightA / (weightA + weightB);
    float rateB = 1.0f - rateA;
    // 球Bの補正後の座標
    DirectX::XMVECTOR VelocityB = DirectX::XMVectorScale(Vec, rateA);
    PositionB = DirectX::XMVectorAdd(PositionB, VelocityB);
    // 球Aの補正後の座標
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

    // 始点と終点からレイのベクトルと長さを求める
    DirectX::XMVECTOR WorldRayStart = DirectX::XMLoadFloat3(&start);
    DirectX::XMVECTOR WorldRayEnd = DirectX::XMLoadFloat3(&end);
    DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldRayEnd, WorldRayStart);
    DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);

    float nearestDist = DirectX::XMVectorGetX(WorldRayLength);
    if (nearestDist <= 0.0f) return false;

    DirectX::XMMATRIX ParentWorldTransform = DirectX::XMLoadFloat4x4(&worldTransform);

    // モデル内の全てのメッシュと交差判定を行う
    const ModelResource* resource = model->GetResource();
    for (const ModelResource::Mesh& mesh : resource->GetMeshes())
    {
        // メッシュのワールド行列を求める
        const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);
        DirectX::XMMATRIX GlobalTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
        DirectX::XMMATRIX WorldTransform = DirectX::XMMatrixMultiply(GlobalTransform, ParentWorldTransform);

        // レイをメッシュのローカル空間に変換する
        DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);
        DirectX::XMVECTOR LocalRayStart = DirectX::XMVector3Transform(WorldRayStart, InverseWorldTransform);
        DirectX::XMVECTOR LocalRayEnd = DirectX::XMVector3Transform(WorldRayEnd, InverseWorldTransform);
        DirectX::XMVECTOR LocalRayVec = DirectX::XMVectorSubtract(LocalRayEnd, LocalRayStart);
        DirectX::XMVECTOR LocalRayDirection = DirectX::XMVector3Normalize(LocalRayVec);
        float distance = DirectX::XMVectorGetX(DirectX::XMVector3Length(LocalRayVec));

        // メッシュ内の全ての三角形と交差判定を行う
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            // 三角形の頂点座標を取得
            const ModelResource::Vertex& a = mesh.vertices.at(mesh.indices.at(i + 0));
            const ModelResource::Vertex& b = mesh.vertices.at(mesh.indices.at(i + 1));
            const ModelResource::Vertex& c = mesh.vertices.at(mesh.indices.at(i + 2));

            DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
            DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
            DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

            // 三角形の交差判定
            if (DirectX::TriangleTests::Intersects(LocalRayStart, LocalRayDirection, A, B, C, distance))
            {
                // メッシュのローカル空間での交点を求める
                DirectX::XMVECTOR LocalHitVec = DirectX::XMVectorScale(LocalRayDirection, distance);
                DirectX::XMVECTOR LocalHitPosition = DirectX::XMVectorAdd(LocalRayStart, LocalHitVec);

                // メッシュのローカル空間での交点をワールド空間に変換する
                DirectX::XMVECTOR WorldHitPosition = DirectX::XMVector3Transform(LocalHitPosition, WorldTransform);

                // ワールド空間でのレイの始点から交点までの距離を求める
                DirectX::XMVECTOR WorldHitVec = DirectX::XMVectorSubtract(WorldHitPosition, WorldRayStart);
                DirectX::XMVECTOR WorldHitDist = DirectX::XMVector3Length(WorldHitVec);
                float worldHitDist = DirectX::XMVectorGetX(WorldHitDist);

                // 交点までの距離が今までに計算した交点より近い場合は交差したと判定する
                if (worldHitDist <= nearestDist)
                {
                    // メッシュのローカル空間での三角形の法線ベクトルを算出
                    DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
                    DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
                    DirectX::XMVECTOR LocalHitNormal = DirectX::XMVector3Cross(AB, BC);

                    // メッシュのローカル空間での法線ベクトルをワールド空間に変換する
                    DirectX::XMVECTOR WorldHitNormal = DirectX::XMVector3TransformNormal(LocalHitNormal, WorldTransform);

                    // 三角形の裏表判定（内積の結果がマイナスならば表向き）
                    DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(LocalRayDirection, LocalHitNormal);
                    float dot = DirectX::XMVectorGetX(Dot);
                    if (dot < 0)
                    {
                        // 交差したのでヒット情報を格納
                        DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldHitNormal));
                        DirectX::XMStoreFloat3(&result.position, WorldHitPosition);
                        result.distance = worldHitDist;

                        // 交点までの距離を更新する
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
    if (player_position.x > enemy_position.x - 10.0f || player_position.x < enemy_position.x + 10.0f)//X軸
    {
        if (player_position.y > enemy_position.y - 10.0f || player_position.y < enemy_position.y + 10.0f)//Y軸
        {
            if (player_position.z > enemy_position.z - 10.0f || player_position.z < enemy_position.z + 10.0f)//Z軸
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
    //X軸、Y軸、Z軸それぞれの範囲内に入っているかの判定
    //bottom_left_front < top_right_backじゃないと通らない
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
    //2軸それぞれの範囲内に入っているかの判定
    //bottom_left_front < top_right_backじゃないと通らない
    if (bottom_left_front.x < top_right_back.x)
    {
        if (bottom_left_front.y < top_right_back.y)
        {
            if (bottom_left_front.z < top_right_back.z)
            {
                _ASSERT_EXPR(true, "2軸それぞれの範囲内に入っているかの判定に失敗しました");
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
