#pragma once
#include "Component.h"

class AnimationState :public Component
{
public:
    AnimationState();
    virtual ~AnimationState();

    //���O�擾
    const char* GetName()const override { return "AnimationState"; }

    //ImGui�`��
    void DrawImGui()override;

    // �X�V����
    virtual void Update(float elapsedTime);

public:
    //�Z�b�^�[�E�Q�b�^�[
private:

};