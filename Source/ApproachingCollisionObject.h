#include "Object.h"

class ApproachingCollisionObject : public Object
{
public:
    //名前取得
    const char* GetName()const override { return "ApproachingCollisionObject"; }

    // コンストラクタ
    ApproachingCollisionObject();
    // デストラクタ
    ~ApproachingCollisionObject();
    // 初期化
    void Start() override;
    // 更新
    void Update(float elapsedTime) override;
    // GUI描画
    void DrawImGui() override;
    //デバッグプリミティブ描画
    void DrawDebug() override;
public:
    void SetSphereRadius(float r) { this->c_sphere.radius = r; }
private:
    Sphere c_sphere = { {0,0,0},10.0f };
    bool test_flg = false;
    bool run_obj = false;
    DirectX::XMFLOAT3 default_position = {};
};