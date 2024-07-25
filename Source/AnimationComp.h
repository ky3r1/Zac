#pragma once
#include "Component.h"
#include "Model.h"

class AnimationComp :public Component
{
public:
    AnimationComp();
    virtual ~AnimationComp();

    //���O�擾
    const char* GetName()const override { return "AnimationState"; }

    //ImGui�`��
    void DrawImGui()override;

    // �X�V����
    virtual void Update(float elapsedTime);

    // �A�j���[�V��������~���Ă����A�j���[�V����������
    bool IsAnimationStopFlg();

public:
    //�Z�b�^�[�E�Q�b�^�[
private:
    //std::vector<AnimUnity> Storage;
    Animation old_animation;
};