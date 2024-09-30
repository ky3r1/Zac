#pragma once
#include "Component.h"

class TimeTrackingObject : public Component
{
public:
    TimeTrackingObject() {}
    ~TimeTrackingObject() {}

    //���O�擾
    const char* GetName() const { return "TimeTrackingObject"; }

    // ������
    void Start() override;
    // �X�V
    void Update(float elapsedTime) override;
    // GUI�`��
    void DrawImGui() override;
    //�f�o�b�O�v���~�e�B�u�`��
    void DrawDebug() override;
public:
    void SetRunTimer(float time) { run_timer = time; }
private:
    int timer = 0;
    float run_timer = FLT_MAX;
};