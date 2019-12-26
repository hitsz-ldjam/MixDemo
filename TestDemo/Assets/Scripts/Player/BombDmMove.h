#pragma once
#include "../../../../Mx/Component/Script/MxScript.h"
#include "../../../../Mx/Math/MxVector3.h"
#include "../Utils/DmPool.h"

using namespace Mix;

// add this directly to dm
class BombDmMove final : public Script {
MX_DECLARE_RTTI

public:
    BombDmMove() = default;
    ~BombDmMove() = default;

    BombDmMove(HDmPool _pool,
               const float _maxRadius,
               const float _expandTime,
               const float _forwardSpeed,
               const float _waitTime);

private:
    void start() override;
    void update() override;

    HDmPool pool;

    float maxRadius;
    float expandTime;
    float forwardSpeed;
    float waitTime;

    enum class State {
        Dead,
        Expand,
        Wait,
        Forward,
        Die,
    } state;

    float vel, acc;
    Vector3f center;
};

using HBombDmMove = SceneObjectHandle<BombDmMove>;
