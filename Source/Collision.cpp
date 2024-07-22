#include "Collision.h"
#include "Mathf.h"

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
    if (sphere.position.y - sphere.radius > cylinder.sphere.position.y + cylinder.sphere.radius)
        return false;

    return IntersectSphereVsSphere(sphere, cylinder.sphere);
    //{
    //// XZ 平面での範囲チェック
    //// positionB - positionA の距離が
    //DirectX::XMFLOAT2 posA(spherePosition.x, spherePosition.z);
    //DirectX::XMFLOAT2 posB(cylinderPosition.x, cylinderPosition.z);
    //
    //// posA を XMVECTOR に変換
    //DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat2(&posA);
    //// posB を XMVECTOR に変換
    //DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat2(&posB);
    //// posA から posB へのベクトルを計算(posB - posA)
    //DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
    //// Vec の長さを計算(XMVector2LengthSq を利用しても良い)
    //DirectX::XMVECTOR LengthSq = DirectX::XMVector2LengthSq(Vec);
    //float lengthSq;
    //DirectX::XMStoreFloat(&lengthSq, LengthSq);
    //
    //// radiusA と radiusB の長さ
    //float range = sphereRadius + cylinderRadius;
    //
    //// radisuA + radisuB より大きかったら
    //if (lengthSq > range)
    //{
    //    // 当たってない
    //    return false;
    //}
    //
    ////正規化
    //Vec = DirectX::XMVector3Normalize(Vec);
    //// めり込み量を求める
    //float diff = range - lengthSq;
    //Vec = DirectX::XMVectorScale(Vec, diff);
    //
    //// ２つの球の重さから押し出し比率を求める
    //float rateA = sphereWeight / (sphereWeight + cylinderWeight);
    //float rateB = 1.0f - rateA;
    //
    //// 球Bの補正後の座標
    //DirectX::XMVECTOR VelocityB = DirectX::XMVectorScale(Vec, rateA);
    //PositionB = DirectX::XMVectorAdd(PositionB, VelocityB);
    //
    //// 球Aの補正後の座標
    //DirectX::XMVECTOR VelocityA = DirectX::XMVectorScale(Vec, rateB);
    //PositionA = DirectX::XMVectorSubtract(PositionA, VelocityA);
    //
    //DirectX::XMFLOAT2 position;
    //DirectX::XMStoreFloat2(&position, PositionA);
    //cylinder.sphere.position.x = cylinder.sphere.position.x + position.x;
    //cylinder.sphere.position.z = cylinder.sphere.position.z + position.y;
    //DirectX::XMStoreFloat2(&position, PositionB);
    //sphere.position.x = position.x;
    //sphere.position.z = position.y;
    //
    //return true;
    //}
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

bool Collision::IntersectRayVsModel(
    const DirectX::XMFLOAT3& start,
    const DirectX::XMFLOAT3& end,
    const Model* model,
    HitResult& result)
{
    ////以前の処理が正しく動くように仮の実装
    //if (end.y < 0.0f)
    //{
    //    result.position.x = end.x;
    //    result.position.y = 0.0f;
    //    result.position.z = end.z;
    //    result.normal.x = 0.0f;
    //    result.normal.y = 1.0f;
    //    result.normal.z = 0.0f;
    //    return true;
    //}
    //return false;


    DirectX::XMVECTOR WorldStart = DirectX::XMLoadFloat3(&start);
    DirectX::XMVECTOR WorldEnd = DirectX::XMLoadFloat3(&end);
    DirectX::XMVECTOR WorldRayVec = DirectX::XMVectorSubtract(WorldEnd, WorldStart);
    DirectX::XMVECTOR WorldRayLength = DirectX::XMVector3Length(WorldRayVec);

    //ワールド空間のレイの長さ
    DirectX::XMStoreFloat(&result.distance, WorldRayLength);

    bool hit = false;
    const ModelResource* resource = model->GetResource();
    for (const ModelResource::Mesh& mesh : resource->GetMeshes())
    {
        //メッシュノード取得
        const Model::Node& node = model->GetNodes().at(mesh.nodeIndex);

        //レイをワールド空間からローカル空間へ変換
        DirectX::XMMATRIX WorldTransform = DirectX::XMLoadFloat4x4(&node.worldTransform);
        DirectX::XMMATRIX InverseWorldTransform = DirectX::XMMatrixInverse(nullptr, WorldTransform);

        DirectX::XMVECTOR S = DirectX::XMVector3TransformCoord(WorldStart, InverseWorldTransform);
        DirectX::XMVECTOR E = DirectX::XMVector3TransformCoord(WorldEnd, InverseWorldTransform);
        DirectX::XMVECTOR SE = DirectX::XMVectorSubtract(E, S);
        DirectX::XMVECTOR V = DirectX::XMVector3Normalize(SE);
        DirectX::XMVECTOR Length = DirectX::XMVector3Length(SE);

        //レイの長さ
        float neart;
        DirectX::XMStoreFloat(&neart, Length);

        //三角形（面）との交差判定
        const std::vector<ModelResource::Vertex>& vertices = mesh.vertices;
        const std::vector<UINT> indices = mesh.indices;

        int materialIndex = -1;
        DirectX::XMVECTOR HitPosition;
        DirectX::XMVECTOR HitNormal;
        for (const ModelResource::Subset& subset : mesh.subsets)
        {
            for (UINT i = 0; i < subset.indexCount; i += 3)
            {
                UINT index = subset.startIndex + i;

                //三角形の頂点を抽出
                const ModelResource::Vertex& a = vertices.at(indices.at(index));
                const ModelResource::Vertex& b = vertices.at(indices.at(index + 1));
                const ModelResource::Vertex& c = vertices.at(indices.at(index + 2));

                DirectX::XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
                DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
                DirectX::XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

                //三角形の三辺ベクトルを算出
                DirectX::XMVECTOR AB = DirectX::XMVectorSubtract(B, A);
                DirectX::XMVECTOR BC = DirectX::XMVectorSubtract(C, B);
                DirectX::XMVECTOR CA = DirectX::XMVectorSubtract(A, C);

                //三角形の法線ベクトルを算出
                DirectX::XMVECTOR N = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(AB, BC));

                //内積の結果がプラスならば裏向き
                DirectX::XMVECTOR Dot = DirectX::XMVector3Dot(V, N);
                float fDot;
                fDot = DirectX::XMVectorGetX(Dot);
                if (fDot >= 0.0f) continue;

                //レイと平面の交点を算出
                DirectX::XMVECTOR SA = DirectX::XMVectorSubtract(A, S);
                DirectX::XMVECTOR X = DirectX::XMVectorDivide(DirectX::XMVector3Dot(SA, N), Dot);
                float x;
                DirectX::XMStoreFloat(&x, X);
                if (x < .0f || x > neart) continue;     //交点までの距離が今までに計算した最近距離より
                                                        //大きい時はスキップ
                DirectX::XMVECTOR P = DirectX::XMVectorAdd(S, DirectX::XMVectorScale(V, x));

                //交点が三角形の内側にあるか判定
                //１つめ
                DirectX::XMVECTOR PA = DirectX::XMVectorSubtract(A, P);
                DirectX::XMVECTOR Cross1 = DirectX::XMVector3Cross(PA, DirectX::XMVectorSubtract(B, P));
                DirectX::XMVECTOR Dot1 = DirectX::XMVector3Dot(Cross1, N);
                float fDot1;
                fDot1 = DirectX::XMVectorGetX(Dot1);
                if (fDot1 < 0.0f) continue;
                //２つめ
                DirectX::XMVECTOR PB = DirectX::XMVectorSubtract(B, P);
                DirectX::XMVECTOR Cross2 = DirectX::XMVector3Cross(PB, DirectX::XMVectorSubtract(C, P));
                DirectX::XMVECTOR Dot2 = DirectX::XMVector3Dot(Cross2, N);
                float fDot2;
                fDot2 = DirectX::XMVectorGetX(Dot2);
                if (fDot2 < 0.0f) continue;
                //３つめ
                DirectX::XMVECTOR PC = DirectX::XMVectorSubtract(C, P);
                DirectX::XMVECTOR Cross3 = DirectX::XMVector3Cross(PC, DirectX::XMVectorSubtract(A, P));
                DirectX::XMVECTOR Dot3 = DirectX::XMVector3Dot(Cross3, N);
                float fDot3;
                fDot3 = DirectX::XMVectorGetX(Dot3);
                if (fDot3 < 0.0f) continue;

                //最近距離を更新
                neart = x;

                //交点と法線を更新
                HitPosition = P;
                HitNormal = N;
                materialIndex = subset.materialIndex;
            }
        }
        if (materialIndex >= 0)
        {
            //ローカル空間からワールド空間へ変換
            DirectX::XMVECTOR WorldPosition = DirectX::XMVector3TransformCoord(HitPosition,
                                                                                WorldTransform);
            DirectX::XMVECTOR WorldCrossVec = DirectX::XMVectorSubtract(WorldPosition, WorldStart);
            DirectX::XMVECTOR WorldCrossLength = DirectX::XMVector3Length(WorldCrossVec);
            float distance;
            DirectX::XMStoreFloat(&distance, WorldCrossLength);

            //ヒット情報保存
            if (result.distance > distance)
            {
                DirectX::XMVECTOR WorldNormal = DirectX::XMVector3TransformNormal(HitNormal,
                    WorldTransform);
                result.distance = distance;
                result.materialIndex = materialIndex;
                DirectX::XMStoreFloat3(&result.position, WorldPosition);
                DirectX::XMStoreFloat3(&result.normal, DirectX::XMVector3Normalize(WorldNormal));
                hit = true;
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

bool Collision::InPoint(DirectX::XMFLOAT3 bottom_left_front, DirectX::XMFLOAT3 top_right_back, DirectX::XMFLOAT3 move_pos)
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

bool Collision::InPoint2D(DirectX::XMFLOAT3 bottom_left_front, DirectX::XMFLOAT3 top_right_back, DirectX::XMFLOAT3 move_pos, Axis2D axis)
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
