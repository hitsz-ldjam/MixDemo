#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../../../../Mx/Math/MxVector3.h"


using namespace Mix;

class PlayerAdapter final : public Script {
MX_DECLARE_RTTI;
public:
    PlayerAdapter() = default;
    ~PlayerAdapter() = default;

    void move(const Vector3f& _dir);

    void attack();

    void setHMoveSpeed(float _Hspeed);

    void setLMoveSpeed(float _Lspeed);

private:
    void awake() override;

    void start() override;

    void update() override;

    void fixedUpdate() override;

    float mHMoveSpeed = 1.5f;
    float mLMoveSpeed = 1.0f;
    float mAccelerate = 0.5f;
    float mDecelerate = 0.5f;
    Vector3f mSmoothMove;

};

using HPlayerAdapter = SceneObjectHandle<PlayerAdapter>;
