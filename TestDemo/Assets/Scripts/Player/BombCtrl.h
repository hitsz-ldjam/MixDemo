#pragma once
#include "../Utils/DmPool.h"
#include "../../../../Mx/Component/Script/MxScript.h"

using namespace Mix;

class BombCtrl final : public Script {
public:
    BombCtrl() = default;
    ~BombCtrl() = default;

    BombCtrl(HDmPool _pool);

private:
    void update() override;

    HDmPool pool;

    constexpr static float bombTime = 5;
    float bombTimeCnt = bombTime;

    constexpr static float maxRadius = 3,
                           expandTime = 0.5,
                           forwardSpeed = 30,
                           waitTime = 0,
                           waitTimeStep = 0.2;
};

using HBombCtrl = SceneObjectHandle<BombCtrl>;
